#include "Camera.h"
#include <iostream>

Camera::Camera()
{
    this->FOV = 0;
    this->lookAt = Vector3D<float> (0.f, 0.f, 0.f);
}

auto Camera::init(Vector2D<int> screen_res) -> void
{
    std::cout<<"LookAt = "<<this->lookAt<<std::endl;

	this->position = Vector3D<float>(0.f, 0.f, -1.0f);
    
    this->viewDirection = this->lookAt - this->position;

    this->up = Vector3D<float> (0.f, 1.f, 0.f);
    this->screen_size = screen_res;
    this->u = viewDirection * up;
    this->v = u * viewDirection;
    std::cout<<"Pos = "<< this->position<<std::endl;
    std::cout<<"ViewDirection = "<< this->viewDirection<<std::endl;
    std::cout<<"LookAt after - = "<< this->lookAt<<std::endl;
    std::cout<<"Up = "<< this->up<<std::endl;
    std::cout<<"U = "<< this->u<<std::endl;
    std::cout<<"V = "<< this->v<<std::endl;
}
