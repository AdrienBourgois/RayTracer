#ifndef __EVENT_DECLARATION__
#define __EVENT_DECLARATION__

#include <vector>

#include "Device.h"
#include "GeometryBuffer.h"

class Event
{
public:
    ~Event() = default;
    static auto eventListener(Device* device, std::vector<GeometryBuffer*> geometry_list) -> void;

private:
    Event() = default;
	static unsigned int num;
};

#endif

