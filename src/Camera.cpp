#include "Camera.h"
#include "Ray.h"
#include <iostream>

Camera::Camera()
{
    this->FOV = 0;
    this->lookAt = Vector3D<float> (0.f, 0.f, 0.f);
    //this->ray = nullptr;
}

auto Camera::init(Vector2D<int> screen_res, RenderBuffer* rend_buffer) -> void
{
    this->render_buffer = rend_buffer;
    std::cout<<"LookAt = "<<this->lookAt<<std::endl;

	this->position = Vector3D<float>(0.f, 0.f, 1.0f);
    this->viewDirection = this->lookAt - this->position;
    this->up = Vector3D<float> (0.f, 1.f, 0.f);
    this->screen_size.x = float (screen_res.x);
    this->screen_size.y = float (screen_res.y);
    this->u = viewDirection * up;
    this->v = u * viewDirection;
}

auto Camera::render() -> void
{
    /*if (this->ray == nullptr)
    {
        this->ray = new Ray(this->position, this->screen_size, 1.f , 1.f , this->render_buffer);
    }*/
}

auto Camera::shot() -> void
{

}
