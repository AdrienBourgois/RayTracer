#include "gui.h"

auto Gui_class::open() -> void
{
    SDL_Init(SDL_INIT_VIDEO);

    this->window = SDL_CreateWindow("Chat", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 800, SDL_WINDOW_OPENGL);
    this->context = SDL_GL_CreateContext(window);
    SDL_assert(context);

    glewExperimental = GL_TRUE;
    auto status = glewInit();
    SDL_assert(status == GLEW_OK);

    Gui::Init(window);

    this->texture = 0;
    glGenTextures(1, &this->texture);
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

auto Gui_class::displayImage(SDL_Surface* image) -> void
{
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    ImGui::Image(reinterpret_cast<void*>(this->texture), ImVec2(image->w, image->h));
}
