#include <iostream>

#include "Driver.h"
#include "Window.h"
#include "Log.h"
#include "RenderBuffer.h"
#include "Camera.h"

#include "SceneNode.h"
#include "Ray.h"

Driver::Driver()
{
    Log* log = Log::getInstance();
    log->info("Driver creation...");
    this->screenSurface = nullptr;
    this->format = nullptr;

    this->collision_result = false;
    this->render_buffer.reset(new RenderBuffer);
    this->camera.reset(new Camera);
    this->screen_size = Vector2D<int>(640.f, 480.f);
    this->f_screen_size = this->convert(this->screen_size);
    this->ray = nullptr;

    log->info("Driver created.");
}

Driver::~Driver()
{
    Log* log = Log::getInstance();
    log->info("Driver destroying...");
    this->screenSurface = nullptr;
    this->format = nullptr;
    SDL_Quit();
    log->info("Driver destroyed.");
}

auto Driver::init(/* Vector2D<int> screen_res */) -> void
{
    Log* log = Log::getInstance();
    log->info("Driver initialization...");

    this->screenSurface = new(SDL_Surface);
    this->format = this->screenSurface->format;
    this->mapRGB = SDL_MapRGB(this->screenSurface->format, 255, 255, 255);

    this->camera->init(this->screen_size, this->render_buffer.get());

    this->node_test = new SceneNode(ModelType::SPHERE);
    node_test->setPosition(Vector3D<float>(1.f, 1.f, -5.f)); 

    this->ray = new Ray(this->camera->getPosition(), this->convert(this->screen_size), this->render_buffer.get(), node_test, this);
    log->info("Driver initialized.");
}

auto Driver::render() -> void
{
    this->ray->run();
   //for (float idx_y = 0.f; idx_y < this->f_screen_size.y; ++idx_y)
   //{
       //for (float idx_x = 0.f; idx_x < this->f_screen_size.x; ++idx_x)
        //{
            //this->ray->findDestPoint(idx_x, idx_y);
            //this->collision_result = this->ray->collision();
            //std::cout<<"idx_x = "<<idx_x<<"   "<<" idx_y = "<<idx_y<<std::endl;
            //if(this->ray->getCollisionRes() == true)
            //{
                //std::cout<<"collision"<<std::endl;
                this->changePixelColor(255, 0, 0, (this->render_buffer->getScreenCoordList()));
            //}
        //}
   //}
}

auto Driver::close() -> void
{
}

auto Driver::changePixelColor(Uint8 r, Uint8 g, Uint8 b, std::vector<Vector2D<float>> screen_coord_list) -> void
{
    unsigned int idx = 0;
    while(idx<screen_coord_list.size())
    {
        Vector2D<float> actual_screen_coord = screen_coord_list[idx];

	    Uint32 *_pixels = (Uint32 *)this->screenSurface->pixels;
	
	    Uint32 pixel = _pixels[(0 * this->screenSurface->w) + 0];// copy of a screen pixel
	    pixel = SDL_MapRGB(this->format, r, g, b);// new pixel color : RGB format

	    _pixels[(int (actual_screen_coord.y) * this->screenSurface->w) + int (actual_screen_coord.x)] = pixel;//x = screen length, y = screen width
								   
        ++idx;
    }   
}

auto Driver::getPixelColor(int pos_x, int pos_y, Uint8* r, Uint8* g, Uint8* b) -> void
{
	Uint32 *pixels_list = (Uint32 *)this->screenSurface->pixels;
	
	Uint32 pixel = pixels_list[(pos_y * this->screenSurface->w) + pos_x];
	SDL_GetRGB(pixel, this->format, r, g, b);
}

auto Driver::convert(Vector2D<int> vec) -> Vector2D<float>
{
    Vector2D<float> res;

    res.x = float(vec.x);
    res.y = float(vec.y);

    return res;
}
