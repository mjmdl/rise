#include "game.hpp"

#include <rise/imgui_layer.hpp>

namespace testbed {

Game::Game(const Config &config) : Engine(config) {
	push_layer(new Example_Layer("First_Layer"));
	push_layer(new Example_Layer("Second_Layer"));
	push_layer(new Example_Layer("Third_Layer"));

	if (window->has_succeeded()) {
		push_overlay(new rise::Imgui_Layer(window->get_handle()));
	}
}

Game::~Game(void) {
}

} // testbed
