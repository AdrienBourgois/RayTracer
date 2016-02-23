#include <iostream>
#include <string>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl.h>
#include "gui.h"

auto main() -> int
{
    Gui_class gui;
    gui.open();

    SDL_Surface* image = IMG_Load("assets/rin.png");

    bool show_another_window = true;

    while(gui.updateEvent())
    {
        gui.newFrame();
        {
            ImGui::SetNextWindowPos(ImVec2(650, 500), ImGuiSetCond_FirstUseEver);
            ImGui::Begin("Image", &show_another_window);
            ImGui::Text("Test");
            gui.displayImage(image);
            ImGui::End();
        }
        gui.render();

    }

    gui.close();


    return EXIT_SUCCESS;
}
