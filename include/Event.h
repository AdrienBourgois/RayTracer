#ifndef __EVENT_DECLARATION__
#define __EVENT_DECLARATION__

#include "Device.h"

class Event
{
public:
	~Event() = default;
	static auto eventListener(Device* device) -> void;

private:
	Event() = default;
};

#endif
