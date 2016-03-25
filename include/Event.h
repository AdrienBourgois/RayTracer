#ifndef __EVENT_DECLARATION__
#define __EVENT_DECLARATION__

#include <vector>

#include "Device.h"
#include "SceneNode.h"

class Event
{
public:
	~Event() = default;
	Event(Event const&) = delete;
	Event(Event&&) = delete;

	auto operator =(Event const&) -> Event& = delete;
	auto operator =(Event&&) -> Event& = delete;

	static auto eventListener(Device* device) -> void;
	static unsigned int idx;
	static bool node_mode;
private:
    Event() = default;
};

#endif

