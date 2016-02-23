#ifndef __IMGUIIMPL_H_INCLUDED__
#define __IMGUIIMPL_H_INCLUDED__

#include <GL/glew.h>

#include "imgui.h"

class ImGuiImpl
{
public:
	static auto	init() -> void;
	static auto shutdown() -> void;

private:
	static auto createFontsTexture() -> void;
	static auto	draw(ImDrawData* draw_data) -> void;

	static GLuint vao;
	static GLuint vbo;
	static GLuint ebo;
	static GLuint prg;
	static GLuint font_tex;
	static GLuint proj_loc;
	static GLuint sampler_loc;
};

#endif // __IMGUIIMPL_H_INCLUDED__
