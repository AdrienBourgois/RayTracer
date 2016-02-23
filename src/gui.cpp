#include "gui.h"

auto Gui_class::open() -> void
{
    SDL_Init(SDL_INIT_VIDEO);

    this->window = SDL_CreateWindow("Chat", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 800, SDL_WINDOW_OPENGL);
    this->context = SDL_GL_CreateContext(window);
    SDL_assert(context);

    this renderer = SDL_CreateSoftwareRenderer(this->surface);

    glewExperimental = GL_TRUE;
    auto status = glewInit();
    SDL_assert(status == GLEW_OK);

    Gui::Init(window);

    this->imageSurface = IMG_Load("assets/rin.png");
    if(IMG_GetError())
        std::cout << "Error :" << IMG_GetError() << std::endl;
}

auto Gui_class::close() -> void
{
    Gui::Shutdown();
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

auto Gui_class::updateEvent() -> bool
{
    while (SDL_PollEvent(&event))
    {
        Gui::ProcessEvent(&event);
        if (event.type == SDL_QUIT)
        run = false;
    }

    return run;
}

auto Gui_class::render() -> void
{
    glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui::Render();
    SDL_GL_SwapWindow(window);
}

auto Gui_class::configWindow() -> void
{
    if(show_test_window)
    {
        ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
        ImGui::ShowTestWindow(&show_test_window);
    }
}

auto Gui_class::displayImage() -> void
{
    SDL_Texture* SDLtexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
    (void)SDLtexture;
    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 30, 30, 0, GL_RGB, GL_UNSIGNED_BYTE, gui.getSurface()->pixels);
    ImGui::Image(reinterpret_cast<void*>(texture), ImVec2(30, 30));
}
