#include "Camera.h"
#include "Log.h"

Camera::Camera()
{
	Log* log = Log::getInstance();
	log->info("Camera creation...");

	log->info("Camera created.");
}
