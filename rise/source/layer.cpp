#include "layer.hpp"

namespace rise {

Layer_Stack::~Layer_Stack(void) {
	for (Layer *layer : layers) {
		layer->detach();
		delete layer;
	}
}

void Layer_Stack::push(Layer *layer) {
	layers.emplace(layers.begin() + insert_index, layer);
	insert_index++;
}

void Layer_Stack::pop(Layer *layer) {
	auto it = std::find(layers.begin(), layers.begin() + insert_index, layer);
	if (it != layers.begin() + insert_index) {
		layer->detach();
		layers.erase(it);
		insert_index--;
	}
}

void Layer_Stack::push_overlay(Layer *layer) {
	layers.emplace_back(layer);
}

void Layer_Stack::pop_overlay(Layer *layer) {
	auto it = std::find(layers.begin() + insert_index, layers.end(), layer);
	if (it != layers.end()) {
		layer->detach();
		layers.erase(it);
	}
}

} // rise
