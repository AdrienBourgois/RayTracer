#include <SDL2/SDL.h>
#include <iostream>

#include "Event.h"
#include "MaterialBuffer.h"

unsigned int Event::num = 0;

auto Event::eventListener(Device* device, std::vector<GeometryBuffer*> geometry_list) -> void
{
 
	std::vector<GeometryBuffer*> light_list;
	for (unsigned int i = 0; i < geometry_list.size(); ++i)
	{
		if (geometry_list[i]->material_buffer->is_light)
			light_list.push_back(geometry_list[i]);
	} 
    
	GeometryBuffer* node;	 

    SDL_Event evt;
    while (SDL_PollEvent(&evt))
    {   
        if (evt.type == SDL_KEYDOWN)
        {
            switch (evt.key.keysym.scancode)
            {
                case SDL_SCANCODE_ESCAPE:
                    device->quit();
                    break;

                case SDL_SCANCODE_RIGHT:
		{
			node = light_list[num];
                    node->position.x += 0.5f;
                    std::cout<<"Light pos = "<<node->position<<std::endl;
                 }   break;

                case SDL_SCANCODE_LEFT:
		{
			node = light_list[num];
                    node->position.x -= 0.5f;
                    std::cout<<"Light pos = "<<node->position<<std::endl;
                 }   break;

                case SDL_SCANCODE_UP:
		{
			node = light_list[num];
                    node->position.y += 0.5f;
                    std::cout<<"Light pos = "<<node->position<<std::endl;
                 }   break;

                case SDL_SCANCODE_DOWN:
		{
			node = light_list[num];
                    node->position.y -= 0.5f;
                    std::cout<<"Light pos = "<<node->position<<std::endl;
                 }   break;
                    
                case SDL_SCANCODE_Q:
		{
			node = light_list[num];
                    node->position.z += 0.5f;
                    std::cout<<"Light pos = "<<node->position<<std::endl;
	         }  break;

                case SDL_SCANCODE_E:
		{
			node = light_list[num];
                     node->position.z -= 0.5f;
                    std::cout<<"Light pos = "<<node->position<<std::endl;
                 }    break;
                
                case SDL_SCANCODE_L:
		{
                    if (num == light_list.size() - 1u)
			num = 0;
                    else
			++num;
                 }break;

                default:
                     break;
                                                 
           }
        }
    }
}

