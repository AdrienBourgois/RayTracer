#ifndef __EVENT_DECLARATION__
#define __EVENT_DECLARATION__

#include <vector>

#include "Device.h"
#include "SceneNode.h"

class Event
{
public:
    ~Event() = default;
     static auto eventListener(Device* device) -> void;

private:
    Event() = default;

	unsigned int light_idx = 0;
};

#endif

