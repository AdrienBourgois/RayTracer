#include <iostream>
#include <string>

#include <GL/glew.h>
//#include <SDL2/SDL.h>
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl.h>
#include "gui.h"
#include "Raytracer.h"
#include "SceneNode.h"

//#include "Raytracer.h"

auto main() -> int
{
	Vector2D<float> screen_res = Vector2D<float>(640.f, 480.f);
	
    Gui_class gui;
    gui.open();
	
	Raytracer* raytracer = new Raytracer();
	raytracer->init(screen_res);

	SceneNode* scene_node = new SceneNode();
	scene_node->init(Vector3D<float> (0.f, 0.f, -2.f), Vector3D<float> (255.f, 255.f, 0.f), false, 1.f);

	SceneNode* sun_node = new SceneNode();
	sun_node->init(Vector3D<float> (0.f, 2.f, -2.f), Vector3D<float> (255.f, 255.f, 255.f), true, 1.f);

	raytracer->genGeometryBuffer(scene_node->getPosition(), scene_node->getRadius(), scene_node->getVerticeList(), EGeometry_type::SPHERE);
	raytracer->genMaterialBuffer(scene_node->getColor(), 100.f, 0.f, false);

	raytracer->genGeometryBuffer(sun_node->getPosition(), sun_node->getRadius(), sun_node->getVerticeList(), EGeometry_type::SPHERE);
	raytracer->genMaterialBuffer(sun_node->getColor(), 100.f, 0.f, true);

    //SDL_Surface* image = IMG_Load("assets/RinL.jpg");
    //unsigned char pixels[] = {255, 255, 255, 255, 0, 0};

	

    bool show_another_window = true;

    while(gui.updateEvent())
    {
		raytracer->render();

        gui.newFrame();
        {
            ImGui::SetNextWindowPos(ImVec2(30, 30), ImGuiSetCond_FirstUseEver);
            ImGui::Begin("Image", &show_another_window, ImGuiWindowFlags_NoSavedSettings);
            ImGui::Text("Test");
            gui.displayImage(raytracer->getRenderBuffer()->getFormattedData<Uint8>(true), screen_res.x, screen_res.y);
            ImGui::End();
        }
        gui.render();
		raytracer->getRenderBuffer()->clearBuffer();

    }

    gui.close();


    return EXIT_SUCCESS;
}
