#include <math.h>
#include <SDL2/SDL.h>

#include "Ray.h"
#include "RenderBuffer.h"
#include "SceneNode.h"
#include "Log.h"
#include "Collision.h"


Ray::Ray(Vector3D<float> position, Vector2D<float> screen_res, RenderBuffer* rend_buff, std::vector<SceneNode*> node, bool child)
{
 //   Log* log = Log::getInstance();
   // log->info("Ray creation...");

    this->screen_size = screen_res;
    this->node_list = node;
    this->lenght_max = 1000.f;
    this->render_buffer = rend_buff;
    this->start_point = position;
    this->collision_result = false;
    this->power = 100.f;
    this->is_child = child;

    //log->info("Ray created.");
}

Ray::Ray(Vector3D<float> position, /*Vector2D<float> screen_res, RenderBuffer* rend_buff,*/ std::vector<SceneNode*> node, bool child)
{
	this->node_list = node;
	this->lenght_max = 1000.f;
	this->start_point = position;
	this->is_child = child;
	
}

auto Ray::findDestPoint(float idx_x, float idx_y) -> void
{
    float NDC_x = (idx_x + 0.5f) / this->screen_size.x;
    float NDC_y = (idx_y + 0.5f) / this->screen_size.y;

    this->dest_point.x = ((2.f * NDC_x) - 1.f); // (this->screen_size.x / this->screen_size.y);
    this->dest_point.y = (1.f - (2.f * NDC_y)) * (this->screen_size.y/this->screen_size.x);

    this->findDirection();
}

auto Ray::findDirection() -> void
{
    this->direction = this->dest_point - this->start_point;
}

auto Ray::run() -> void
{
    if(this->is_child == true)
        this->runChild();
    else
    {
	    SceneNode* node = nullptr;

	    for (float idx_y = 0.f; idx_y < this->screen_size.y; ++idx_y)
	    {
		for (float idx_x = 0.f; idx_x < this->screen_size.x; ++idx_x)
		{
		    this->findDestPoint(idx_x, idx_y);
	/*            Collision collision = Collision(); 
		   if(collision.detectCollision(this, this->scene_node))
	*/
		    for(unsigned int idx = 0; idx < this->node_list.size(); ++idx)
		    {
			node = this->node_list[idx];

			if(this->collision(node))// && !node->getIsLight())
			{
			    this->render_buffer->setColorList(Vector3D<Uint8> (255.f, 0.f, 0.f));
			    this->render_buffer->setScreenCoordList(Vector2D<float>(idx_x, idx_y));
//			    if(node->getReflectionIdx() > 0)
//			    {
				Ray* ray = new Ray(this->collision_point, this->screen_size, this->render_buffer, this->node_list, true);
				ray->setDirection(this->calculateReflexion(node));
				ray->run();

				if (ray->getCollisionRes())
				{
//					std::cout << "ChangeColor" << std::endl;
					this->render_buffer->setColorList(Vector3D<Uint8> (250.f, 250.f, 250.f));
					this->render_buffer->setScreenCoordList(Vector2D<float>(idx_x, idx_y));
				}

				ray->close();
				delete ray;
				ray = nullptr;
//			    }

			}
		    }
		}
	    }
    }
}

auto Ray::runChild() -> void
{
    SceneNode* node = nullptr;
    for(unsigned int idx = 0; idx < this->node_list.size(); ++idx)
    {
        node = this->node_list[idx];
        
        if(this->collision(node) && node->getIsLight())
        {
		//std::cout<<"collision with light"<<std::endl;
//		this->render_buffer->setColorList(Vector3D<Uint8>(250.f, 0.f, 0.f));
		this->collision_result = true;
        }
	else
		this->collision_result = false;
    }
}

auto Ray::collision(SceneNode* scene_node) -> bool
{
    SDL_assert(scene_node);

    Vector3D<float> circle_posi = scene_node->getPosition();

    float circle_radius = scene_node->getRadius(); // get rad

    float A = this->DOT(this->direction, this->direction);
    Vector3D<float> dist = this->start_point - circle_posi;

    float B = 2 * DOT(this->direction, dist);

    float C = DOT(dist, dist) - (circle_radius * circle_radius);

    float discri = B * B - 4 * A * C;
    if (discri < 0)
        return false; // no colision
    else
    {   
        float sqrt_discri = (float)(sqrt(discri));
        float t0 = (-B + sqrt_discri)/(2);
        float t1 = (-B - sqrt_discri)/(2);
                                                            
        // We want the closest one 
        if (t0 > t1) 
            t0 = t1;


       // Verify t0 larger than 0 and less than the original t 
        if ((t0 > 0.001f) && (t0 < this->lenght_max))
        {
            this->calculateCollisionPoint(t0);
            return true;
        }
    }
    return false;
}

auto Ray::calculateReflexion(SceneNode* node) -> Vector3D<float>
{
    Vector3D<float> normal = this->calculateNormal(node);

    float reflexionCalc = -DOT(normal, this->direction);
        
    //std::cout << "ReflexionCalc = " << reflexionCalc << std::endl;

    Vector3D<float> reflexionRay = this->direction + (normal * reflexionCalc * 2.f);
 
    //std::cout << "ReflexionRay = " << reflexionRay << std::endl;

    return reflexionRay;
}

auto Ray::calculateNormal(SceneNode* node) -> Vector3D<float>
{
    return (this->collision_point - node->getPosition());// + this->collision_point; 
}

auto Ray::calculateCollisionPoint(float distance) -> void
{
    this->collision_point = (this->direction * distance) + this->start_point;
}

auto Ray::close() -> void
{
    this->render_buffer = nullptr;
    //this->scene_node = nullptr;
    this->collision_result = false;
}

auto Ray::DOT(Vector3D<float> vector_1, Vector3D<float> vector_2) -> float
{
    float result = vector_1.x * vector_2.x + vector_1.y * vector_2.y + vector_1.z * vector_2.z;
    return result;
}
