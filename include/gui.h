#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl.h>

class Gui_class
{
    public:
        Gui_class() = default;
        ~Gui_class() = default;

        Gui_class(Gui_class const&) = delete;
        Gui_class(Gui_class &&) = delete;
        auto operator=(Gui_class const&) -> Gui_class = delete;
        auto operator=(Gui_class &&) -> Gui_class = delete;

        auto open() -> void;
        auto close() -> void;
        auto updateEvent() -> bool;
        auto newFrame() -> void { Gui::NewFrame(window); }
        auto render() -> void;
        auto configWindow() -> void;
        auto getSurface() -> SDL_Surface* {return this->surface;}
        auto getWindow() -> SDL_Window* {return this->window;}

    private:
        SDL_Window* window;
        SDL_GLContext context;
        SDL_Event event;
        SDL_Surface* surface;

        bool run = true;
        bool show_test_window = true;
        bool show_another_window = true;
        ImVec4 clear_color = ImColor(114, 144, 154);
};
