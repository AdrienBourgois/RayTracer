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

    SDL_Surface* image = IMG_Load("assets/RinL.jpg");
    //unsigned char pixels[] = {255, 255, 255, 255, 0, 0};

    bool show_another_window = true;

    while(gui.updateEvent())
    {
        gui.newFrame();
        {
            ImGui::SetNextWindowPos(ImVec2(30, 30), ImGuiSetCond_FirstUseEver);
            ImGui::Begin("Image", &show_another_window, ImGuiWindowFlags_NoSavedSettings);
            ImGui::Text("Test");
            gui.displayImage(image->pixels, image->w, image->h);
            ImGui::End();
        }
        gui.render();

    }

    gui.close();


    return EXIT_SUCCESS;
}
