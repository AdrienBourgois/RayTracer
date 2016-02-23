#include "ImGui/imgui_impl.h"

GLuint ImGuiImpl::prg = 0;
GLuint ImGuiImpl::vao = 0;
GLuint ImGuiImpl::vbo = 0;
GLuint ImGuiImpl::ebo = 0;
GLuint ImGuiImpl::font_tex = 0;
GLuint ImGuiImpl::sampler_loc = 0;
GLuint ImGuiImpl::proj_loc = 0;

auto	ImGuiImpl::init() -> void
{
	GLchar const* vertex_shader =
	R"--(#version 420

uniform mat4 proj;

in vec2 vertex_pos;
in vec2 vertex_uv;
in vec4 vertex_color;

out vec2 fragment_uv;
out vec4 fragment_color;

void main(void)
{
	fragment_uv = vertex_uv;
	fragment_color = vertex_color;
	gl_Position = proj * vec4(vertex_pos, 0.0, 1.0);
}
)--";

	GLchar const* fragment_shader =
	R"--(#version 420

uniform sampler2D sampler;

in vec2 fragment_uv;
in vec4 fragment_color;

out vec4 out_color;

void main(void)
{
	out_color = fragment_color * texture(sampler, fragment_uv);
}
)--";

	prg = glCreateProgram();
	auto vs_id = glCreateShader(GL_VERTEX_SHADER);
	auto fs_id = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vs_id, 1, &vertex_shader, 0);
	glShaderSource(fs_id, 1, &fragment_shader, 0);

	glCompileShader(vs_id);
	glCompileShader(fs_id);

	glAttachShader(prg, vs_id);
	glAttachShader(prg, fs_id);
	glLinkProgram(prg);

	glDetachShader(prg, vs_id);
	glDeleteShader(vs_id);
	glDetachShader(prg, fs_id);
	glDeleteShader(fs_id);

	sampler_loc = glGetUniformLocation(prg, "sampler");
	proj_loc = glGetUniformLocation(prg, "proj");
	auto pos_loc = glGetAttribLocation(prg, "vertex_pos");
	auto uv_loc = glGetAttribLocation(prg, "vertex_uv");
	auto color_loc = glGetAttribLocation(prg, "vertex_color");

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glEnableVertexAttribArray(pos_loc);
	glEnableVertexAttribArray(uv_loc);
	glEnableVertexAttribArray(color_loc);

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE*)0)->ELEMENT))
	glVertexAttribPointer(pos_loc, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, pos));
	glVertexAttribPointer(uv_loc, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, uv));
	glVertexAttribPointer(color_loc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, col));
#undef OFFSETOF

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	ImGui::GetIO().RenderDrawListsFn = &ImGuiImpl::draw;

	createFontsTexture();
}

auto	ImGuiImpl::createFontsTexture() -> void
{
	ImGuiIO& io = ImGui::GetIO();

	unsigned char* pixels;
	int width, height;

	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

	glGenTextures(1, &font_tex);
	glBindTexture(GL_TEXTURE_2D, font_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	io.Fonts->TexID = (void*)(intptr_t)font_tex;

	io.Fonts->ClearInputData();
	io.Fonts->ClearTexData();
}

auto	ImGuiImpl::draw(ImDrawData* draw_data) -> void
{
	GLint last_program, last_texture;

	glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);

	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	glActiveTexture(GL_TEXTURE0);

	float const width = ImGui::GetIO().DisplaySize.x;
	float const height = ImGui::GetIO().DisplaySize.y;
	float const ortho_proj[4][4] =
	{
		{ 2.f/width,	0.f,			0.f,		0.f },
		{ 0.f,			2.f/-height,	0.f,		0.f },
		{ 0.f,			0.f,			-1.f,		0.f },
		{ -1.f,			1.f,			0.f,		1.f },
	};

	glUseProgram(prg);
	glUniform1i(sampler_loc, 0);
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, &ortho_proj[0][0]);
	glBindVertexArray(vao);

	for (int n = 0; n < draw_data->CmdListsCount; ++n)
	{
		ImDrawList const* cmd_list = draw_data->CmdLists[n];
		ImDrawIdx const* idx_buffer_offset = nullptr;

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)cmd_list->VtxBuffer.size() * sizeof(ImDrawVert), (GLvoid*)&cmd_list->VtxBuffer.front(), GL_STREAM_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)cmd_list->IdxBuffer.size() * sizeof(ImDrawIdx), (GLvoid*)&cmd_list->IdxBuffer.front(), GL_STREAM_DRAW);

		for (ImDrawCmd const* pcmd = cmd_list->CmdBuffer.begin(); pcmd != cmd_list->CmdBuffer.end(); ++pcmd)
		{
			if (pcmd->UserCallback)
				pcmd->UserCallback(cmd_list, pcmd);
			else
			{
				glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
				glScissor((int)pcmd->ClipRect.x, (int)(height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));

				glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, GL_UNSIGNED_SHORT, idx_buffer_offset);
			}

			idx_buffer_offset += pcmd->ElemCount;
		}
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(last_program);
	glDisable(GL_SCISSOR_TEST);
	glBindTexture(GL_TEXTURE_2D, last_texture);
}

auto	ImGuiImpl::shutdown() -> void
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	glDeleteProgram(prg);

	glDeleteTextures(1, &font_tex);
	ImGui::GetIO().Fonts->TexID = 0;

}
