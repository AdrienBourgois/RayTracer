#include <iostream>

#include "Raytracer.h"
#include "Log.h"
#include "RenderBuffer.h"

Raytracer::Raytracer()
{
	Log* log = Log::getInstance();
	log->info("Raytracer creation...");

	this->render_buffer.reset(new RenderBuffer);
	this->camera.reset(new Camera());
	
	log->info("Raytracer created.");
}

Raytracer::~Raytracer()
{
	this->render_buffer = nullptr;
}

auto Raytracer::init(Vector2D<float> screen_res) -> void
{
	Log* log = Log::getInstance();
	log->info("Raytracer initialization...");

	this->screen_size = screen_res;

	log->info("Raytracer initialized.");
}

auto Raytracer::render() -> void
{

}

auto Raytracer::close() -> void
{

}

