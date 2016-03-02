#include <SDL2/SDL.h>
#include <iostream>

#include "Event.h"
#include "MaterialBuffer.h"

auto Event::eventListener(Device* device, std::vector<GeometryBuffer*> geometry_list) -> void
{
 
	std::vector<GeometryBuffer*> light_list;
	for (unsigned int i = 0; i < geometry_list.size(); ++i)
	{
		if (geometry_list[i]->material_buffer->is_light)
			light_list.push_back(geometry_list[i]);
	} 
    
	unsigned int num = 0;
 
    SDL_Event evt;
    while (SDL_PollEvent(&evt))
    {   
	GeometryBuffer* node = light_list[num];	 

        if (evt.type == SDL_KEYDOWN)
        {
            switch (evt.key.keysym.scancode)
            {
                case SDL_SCANCODE_ESCAPE:
                    device->quit();
                    break;

                case SDL_SCANCODE_RIGHT:
                    ++node->position.x;
                    std::cout<<"Light pos = "<<node->position<<std::endl;
                    break;

                case SDL_SCANCODE_LEFT:
                    --node->position.x;
                    std::cout<<"Light pos = "<<node->position<<std::endl;
                    break;

                case SDL_SCANCODE_UP:
                    ++node->position.y;
                    std::cout<<"Light pos = "<<node->position<<std::endl;
                    break;

                case SDL_SCANCODE_DOWN:
                    --node->position.y;
                    std::cout<<"Light pos = "<<node->position<<std::endl;
                    break;
                    
                case SDL_SCANCODE_Q:
                    ++node->position.z;
                    std::cout<<"Light pos = "<<node->position<<std::endl;
                     break;

                case SDL_SCANCODE_E:
                     --node->position.z;
                    std::cout<<"Light pos = "<<node->position<<std::endl;
                     break;
                
                case SDL_SCANCODE_L:

                    if (num == light_list.size() - 1)
                    {
			num = 0;
                    }

                    else
                    {
			++num;
                    }
                    break;

                default:
                     break;
                                                 
           }
        }
    }
}

