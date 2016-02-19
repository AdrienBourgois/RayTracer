#include <cmath>
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

Ray::Ray(Vector3D<float> position, RenderBuffer* rend_buff, std::vector<SceneNode*> node, bool child, Vector3D<Uint8> color_val)
{
	this->node_list = node;
	this->lenght_max = 1000.f;
	this->start_point = position;
    this->render_buffer = rend_buff;
	this->is_child = child;
    this->color_value = color_val;
	
}

auto Ray::findDestPoint(float idx_x, float idx_y) -> void
{
    float NDC_x = (idx_x + 0.5f) / this->screen_size.x;
    float NDC_y = (idx_y + 0.5f) / this->screen_size.y;

    this->dest_point.x = ((2.f * NDC_x) - 1.f) *  (this->screen_size.x / this->screen_size.y);
    this->dest_point.y = (1.f - (2.f * NDC_y)); // * (this->screen_size.y/this->screen_size.x);

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

		    for(unsigned int idx = 0; idx < this->node_list.size(); ++idx)
		    {
			node = this->node_list[idx];

              if(this->collision(node)/* && !node->getIsLight()*/)
                {
	                this->color_value = node->getColor();
                    //this->render_buffer->setColorList(this->color_value);
					//this->render_buffer->setScreenCoordList(Vector2D<float>(idx_x, idx_y));
                    if(!node->getIsLight())
                    {
                        Ray* ray = new Ray(this->collision_point, this->render_buffer, this->node_list, true, this->color_value);
                        ray->setDirection(this->calculateReflexion(node));
                        this->child_list.push_back(ray);
                        ray->run();
 Vector3D<float> _light_ ;

//						if (ray->getCollisionRes())
//						{
							//this->final_color = this->calculateAmbiantLight(node) + this->calculateSpecularLight(node, this->getLightList());
							this->final_color = this->calculateAmbiantLight(node) + this->calculateDiffuseLight(node, this->getLightList());
							this->color_value.x = Uint8 (this->final_color.x);
							this->color_value.y = Uint8 (this->final_color.y);
							this->color_value.z = Uint8 (this->final_color.z);

							this->render_buffer->setColorList(this->color_value);
//						}
/*						else
						{
							this->final_color = this->calculateAmbiantLight(node) + this->calculateDiffuseLight(node, this->getLightList());

							this->color_value.x = Uint8 (this->final_color.x);
							this->color_value.y = Uint8 (this->final_color.y);
							this->color_value.z = Uint8 (this->final_color.z);
							this->render_buffer->setColorList(this->color_value);
						}*/
						ray->close();
						delete ray;
						ray = nullptr;
						this->child_list.clear();
				
						this->render_buffer->setScreenCoordList(Vector2D<float>(idx_x, idx_y));
                    }
					else
					{
						this->render_buffer->setColorList(this->color_value);
						this->render_buffer->setScreenCoordList(Vector2D<float>(idx_x, idx_y));
					}

                }
            }
        }
    }
    }
}

auto Ray::runChild() -> void
{
    SceneNode* node = nullptr;
	(void) node;
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
	//this->render_buffer->setColorList(Vector3D<Uint8> (0, 255, 0));
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

      Vector3D<float> reflexionRay = (normal * reflexionCalc * 2.f) + direction;
 
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

auto Ray::getLightList() -> std::vector<SceneNode*>
{
	std::vector<SceneNode*> light_list;
	for (unsigned int i = 0; i < this->node_list.size(); ++i)
	{
		if (this->node_list[i]->getIsLight())
			light_list.push_back(this->node_list[i]);
	}

	return light_list;
}

auto Ray::calculateAmbiantLight(SceneNode* node) -> Vector3D<float>
{
	Vector3D<float> node_color;
	node_color.x = float (node->getColor().x);
	node_color.y = float (node->getColor().y);
	node_color.z = float (node->getColor().z);

	float coef = 0.30f; // a remplacer [ar la valeur de la node
	Vector3D<float> color = node_color * coef;

	Vector3D<Uint8> color_shade;
	color_shade.x = Uint8 (color.x);
	color_shade.y = Uint8 (color.y);
	color_shade.z = Uint8 (color.z);
	
	return color;
}

auto Ray::calculateDiffuseLight(SceneNode* node, std::vector<SceneNode*> light_list) -> Vector3D<float>
{
		SceneNode* light = nullptr;
		light = light_list[0];
		Vector3D<float> def_color;
	
		//for(unsigned int idx = 0; idx < light_list.size(); ++idx)
		//{

		Vector3D<float> node_color;
		node_color.x = float (node->getColor().x);
		node_color.y = float (node->getColor().y);
		node_color.z = float (node->getColor().z);

//		light = light_list[idx];

		Vector3D<float> l =  (this->collision_point - light->getPosition()).normalize();
		float shade = DOT(this->calculateNormal(light), l.normalize()) * 0.2f;

		if (shade < 0.f)
			shade = 0.f;
		
		Vector3D<float> color;
		if ((node_color.x - node_color.x * shade) < 0.f)
			color.x = 0.f;
		else
			color.x = node_color.x - node_color.x * shade;
			
		def_color += color;
		//}

	return def_color;
}

auto Ray::calculateSpecularLight(SceneNode* node, std::vector<SceneNode*>light_list) -> Vector3D<float>
{
	Vector3D<float> specular_light;
	SceneNode* light = nullptr;
	for(unsigned int idx = 0; idx < light_list.size(); ++idx)
	{	
	light = light_list[idx];

	Vector3D<float> n = (this->calculateNormal(node)).normalize();
	//Vector3D<float> l = (this->collision_point - light->getPosition()).normalize();
	Vector3D<float> l = (light->getPosition() - this->collision_point).normalize();
	Vector3D<float> v = this->start_point - this->collision_point;
	v = v.normalize();

	//Vector3D<float> r = (n - l);// * (2 * DOT(n, l));

	//r = r * (2 * DOT(n, l));
	float nl = DOT(n, l);
	Vector3D<float> r = (n * (nl * 2.f)) - l;
	r = r.normalize();
 
	//Vector3D<float> specular_light = /*konstant_light(from 0 to 1)*/ (Vector3D<float> (255.f, 255.f, 255.f) * 0.30f) * float(DOT(r, v.pow(0.1f)));
	specular_light = /*konstant_light(from 0 to 1)*/ (Vector3D<float> (255.f, 255.f, 255.f) * 0.70f) * float (pow(DOT(r, v) ,0.01f));
	
	//std::cout<<"specular_light = "<<specular_light<<std::endl;	

	if(specular_light.x < 0.f)
		specular_light.x = std::fabs(specular_light.x);
	if(specular_light.y < 0.f)
		specular_light.y = std::fabs(specular_light.y);
	if(specular_light.z < 0.f)
		specular_light.z = std::fabs(specular_light.z);
	}
	
	Vector3D<Uint8> specular_color;
	specular_color.x = Uint8 (specular_light.x);
	specular_color.y = Uint8 (specular_light.y);
	specular_color.z = Uint8 (specular_light.z);

	return specular_light;
}

auto Ray::close() -> void
{
    this->render_buffer = nullptr;
    this->collision_result = false;
}

auto Ray::DOT(Vector3D<float> vector_1, Vector3D<float> vector_2) -> float
{
    float result = vector_1.x * vector_2.x + vector_1.y * vector_2.y + vector_1.z * vector_2.z;
    return result;
}
