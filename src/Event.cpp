#include <SDL2/SDL.h>

#include "Event.h"

auto Event::eventListener(Device* device) -> void
{
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
				//case SDL_SCANCODE_RIGHT:
					//device->getNodeTest2();
					

				default : break;
			}
		}
	}
}
