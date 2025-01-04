#include "engine.hpp"
#include "logger.hpp"

#include <stdlib.h>

#include <glad/glad.h>

namespace rise {

extern void initialize_loggers(const std::string &external_name);

Engine::Engine(const Config &config) : config(config) {
	initialize_loggers(config.name);

	window = Window::create({config.name});
	if (!window->has_succeeded()) {
		return;
	}
	window->set_event_callback(std::bind(&Engine::on_event, this, std::placeholders::_1));
	
	is_success = true;
}

Engine::~Engine(void) {
}

void Engine::on_event(Event &event) {
	Event_Dispatcher event_dispatcher(event);
	event_dispatcher.handle<Window_Close_Event>([this](auto &) -> bool {
		is_running = false;
		return false;
	});
	
	for (auto it = layer_stack.rbegin(); it != layer_stack.rend(); it++) {
		if (event.is_handled) {
			break;
		}
		Layer *layer = *it;
		layer->handle_event(event);
	}
}
	
int Engine::run(void) {
	if (!is_success) {
		return EXIT_FAILURE;
	}
	
	is_running = true;

	while (is_running) {
		window->poll_events();

		glClearColor(0.17f, 0.17f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		for (Layer *layer : layer_stack) {
			layer->update();
		}
		
		window->swap_buffers();
	}

	is_running = false;
	return EXIT_SUCCESS;
}

void Engine::push_layer(Layer *layer) {
	layer_stack.push(layer);
	layer->attach();
}

void Engine::push_overlay(Layer *layer) {
	layer_stack.push_overlay(layer);
	layer->attach();
}

} // rise
