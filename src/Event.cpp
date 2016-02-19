#include <SDL2/SDL.h>
#include <iostream>

#include "Event.h"
#include "SceneNode.h"

auto Event::eventListener(Device* device) -> void
{
	SceneNode* node;
	if (device->getLight().size() < 1)
		node = nullptr;
	else
		node = device->getLight()[0];
	float move = 0;
	
	
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
					if (node == nullptr)
						return;
					move = node->getPosition().x;
					node->setPosition(++move, node->getPosition().y, node->getPosition().z); 
					std::cout<<"Light pos = "<<node->getPosition()<<std::endl;
					break;

				case SDL_SCANCODE_LEFT:
					if (node == nullptr)
						return;
                    move = node->getPosition().x;
                    node->setPosition(--move, node->getPosition().y, node->getPosition().z);
					std::cout<<"Light pos = "<<node->getPosition()<<std::endl;
                    break;

				case SDL_SCANCODE_UP:
					if (node == nullptr)
						return;
                    move = node->getPosition().y;
                    node->setPosition(node->getPosition().x, ++move, node->getPosition().z);
					std::cout<<"Light pos = "<<node->getPosition()<<std::endl;
                    break;

				case SDL_SCANCODE_DOWN:
					if (node == nullptr)
						return;
                    move = node->getPosition().y;
                    node->setPosition(node->getPosition().x, --move, node->getPosition().z);
					std::cout<<"Light pos = "<<node->getPosition()<<std::endl;
                    break;
					
				case SDL_SCANCODE_Q:
					if (node == nullptr)
						return;
                     move = node->getPosition().z;
                     node->setPosition(node->getPosition().x, node->getPosition().y, --move);
					std::cout<<"Light pos = "<<node->getPosition()<<std::endl;
                     break;

				case SDL_SCANCODE_E:
					if (node == nullptr)
						return;
                     move = node->getPosition().z;
                     node->setPosition(node->getPosition().x, node->getPosition().y, ++move);
					std::cout<<"Light pos = "<<node->getPosition()<<std::endl;
                     break;
				
				case SDL_SCANCODE_L:

					/*if (node == device->getNodeTest2())
					{
						std::cout<<"SCANCODE L"<<std::endl;
						node = device->getNodeTest3();
					}

					else
					{
						node = device->getNodeTest2();
					}*/
					break;

				default:
					 break;
			}
		}
	}
}
