#include "gui.h"
#include "ImGui/imgui_demo.cpp"

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

auto Gui_class::configWindow(Driver* driver) -> void
{
    if(show_test_window)
    {
        ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
        ImGui::ShowTestWindow(&show_test_window);
    }
    {
        ImGui::SetNextWindowSize(ImVec2(700,500), ImGuiSetCond_FirstUseEver);
        ImGui::Begin("Image", &show_another_window);
        //SDL_Renderer* renderer = SDL_CreateSoftwareRenderer(driver->getSurface());
        //SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, driver->getSurface());
        ImGui::Image(driver->getSurface()->userdata, ImVec2(640, 480), ImVec2(0,0), ImVec2(1,1), ImColor(255,255,255,255), ImColor(255,255,255,128));
        ImGui::Text("Hello");
        ImGui::End();
    }
    (void)driver;
}
