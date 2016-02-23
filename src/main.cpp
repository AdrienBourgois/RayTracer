#include <iostream>
#include <string>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl.h>
#include "gui.h"
//#include "Raytracer.h"

auto main() -> int
{
    Gui_class gui;
    gui.open();

    SDL_Renderer* renderer = SDL_CreateSoftwareRenderer(gui.getSurface());
    SDL_Texture* SDLtexture = SDL_CreateTextureFromSurface(renderer, gui.getSurface());
    (void)SDLtexture;
    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 30, 30, 0, GL_RGB, GL_UNSIGNED_BYTE, gui.getSurface()->pixels);

    bool show_another_window = true;

    while(gui.updateEvent())
    {
        gui.newFrame();
        gui.configWindow();
        {
            ImGui::SetNextWindowPos(ImVec2(650, 500), ImGuiSetCond_FirstUseEver);
            ImGui::Begin("Image", &show_another_window);
            ImGui::Text("Test");
            ImGui::Image(reinterpret_cast<void*>(texture), ImVec2(30, 30));
            ImGui::End();
        }
        gui.render();

    }

    gui.close();


    return EXIT_SUCCESS;
}
