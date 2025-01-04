#ifndef RISE__ENGINE_HPP
#define RISE__ENGINE_HPP

#include "event.hpp"
#include "layer.hpp"
#include "window.hpp"

namespace rise {

class Engine {
public:
	struct Config {
		int argc = 0;
		char **argv = nullptr;
		std::string name = "Game";
	};

	int run(void);
	void on_event(Event &event);

	void push_layer(Layer *layer);
	void push_overlay(Layer *layer);
	
protected:
	std::unique_ptr<Window> window;
	Config config;
	bool is_success = false;
	bool is_running = false;
	
	Engine(const Config &config);
	virtual ~Engine(void);

private:
	Layer_Stack layer_stack;
};

} // rise

#endif // RISE__ENGINE_HPP
