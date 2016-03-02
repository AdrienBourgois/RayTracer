#include "ReflexionCalc.h"
#include "MaterialBuffer.h"

auto calculateReflexion(GeometryBuffer* node, std::vector<GeometryBuffer*> node_list, Vector3D<float> coll_point) -> Vector3D<float>
{
	if (node_list.size() == 1)
		return Vector3D<float>(0.f, 0.f, 0.f);

(void)node;
	Vector3D<float> final_reflected_color;
	for (unsigned int i = 0; i < node_list.size(); ++i)
	{
		if (!node_list[i]->material_buffer->is_light)
		{
			if (!isNodeBeforeSource(node_list[i], node_list, coll_point))
			{
//				std::cout << "ref color : " << node_list[i]->material_buffer->color << std::endl;	
				final_reflected_color += node_list[i]->material_buffer->color;
			}
			else
				final_reflected_color += Vector3D<float>(0.f, 0.f, 0.f);
		}
	}
	return final_reflected_color;
}
