#include <iostream>
#include <string>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl.h>
#include "gui.h"
#include "PNGExport.h"

auto main() -> int
{
    BIT8 pixels[] = {255, 255, 255, 1, 1, 1, 2, 2, 2};
    
    PNGExport png(pixels, 3, 1, "assets/test.png");

    png.write();

    return EXIT_SUCCESS;
}
