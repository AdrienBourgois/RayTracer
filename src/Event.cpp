#include <SDL2/SDL.h>

#include "Event.h"
#include "SceneNode.h"

auto Event::eventListener(Device* device) -> void
{
	SceneNode* node;
	node = device->getNodeTest2();
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
					move = node->getPosition().x;
					node->setPosition(++move, node->getPosition().y, node->getPosition().z); 
					break;

				case SDL_SCANCODE_LEFT:
                    move = node->getPosition().x;
                    node->setPosition(--move, node->getPosition().y, node    ->getPosition().z);
                    break;

				case SDL_SCANCODE_UP:
                    move = node->getPosition().y;
                    node->setPosition(node->getPosition().x, ++move, node    ->getPosition().z);
                    break;

				case SDL_SCANCODE_DOWN:
                    move = node->getPosition().y;
                    node->setPosition(node->getPosition().x, --move, node    ->getPosition().z);
                    break;
					
				case SDL_SCANCODE_Q:
                     move = node->getPosition().z;
                     node->setPosition(node->getPosition().x, node->getPosition().y, --move);
                     break;

				case SDL_SCANCODE_E:
                     move = node->getPosition().z;
                     node->setPosition(node->getPosition().x, node->getPosition().y, ++move);
                     break;
					

				default:
					 break;
			}
		}
	}
}
