#include <SDL2/SDL.h>
#include <iostream>

#include "Event.h"
#include "MaterialBuffer.h"


auto Event::eventListener(Device* device) -> void
{
  SceneNode* node;
    node = device->getLightList()[0];
    
    float move = 0.f;
  
 
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
                    move = node->getPosition().x + 0.5f;
                    node->setPosition(Vector3D<float>(move, node->getPosition().y, node->getPosition().z)); 
                    std::cout<<"Light pos = "<<node->getPosition()<<std::endl;
                    break;

                case SDL_SCANCODE_LEFT:
                    move = node->getPosition().x - 0.5f;
                    node->setPosition(Vector3D<float>(move, node->getPosition().y, node->getPosition().z));
                    std::cout<<"Light pos = "<<node->getPosition()<<std::endl;
                    break;

                case SDL_SCANCODE_UP:
                    move = node->getPosition().y + 0.5f;
                    node->setPosition(Vector3D<float>(node->getPosition().x, move, node->getPosition().z));
                    std::cout<<"Light pos = "<<node->getPosition()<<std::endl;
                    break;

                case SDL_SCANCODE_DOWN:
                    move = node->getPosition().y - 0.5f;
                    node->setPosition(Vector3D<float>(node->getPosition().x, move, node->getPosition().z));
                    std::cout<<"Light pos = "<<node->getPosition()<<std::endl;
                    break;
                    
                case SDL_SCANCODE_Q:
                     move = node->getPosition().z - 0.5f;
                     node->setPosition(Vector3D<float>(node->getPosition().x, node->getPosition().y, move));
                    std::cout<<"Light pos = "<<node->getPosition()<<std::endl;
                     break;

                case SDL_SCANCODE_E:
                     move = node->getPosition().z + 0.5f;
                     node->setPosition(Vector3D<float>(node->getPosition().x, node->getPosition().y, move));
                    std::cout<<"Light pos = "<<node->getPosition()<<std::endl;
                     break;
                
/*                case SDL_SCANCODE_L:

                    if (node == device->getNodeTest2())
                    {
                        std::cout<<"SCANCODE L"<<std::endl;
                        node = device->getNodeTest3();
                    }

                	break;
*/
                	default:
                     break;
                                                 
           }
        }
    }
}

