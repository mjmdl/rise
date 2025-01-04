#ifndef RISE__LAYER_HPP
#define RISE__LAYER_HPP

#include "event.hpp"

namespace rise {

class Layer {
public:
	Layer(const std::string &name = "Layer") : name(name) {
	}

	virtual ~Layer(void) {
	}
	
	virtual void attach(void) {
	}
	
	virtual void detach(void) {
	}
	
	virtual void update(void) {
	}
	
	virtual void handle_event(Event &event) {
	}

	inline const std::string &get_name(void) const {
		return name;
	}
	
protected:
	std::string name;	
};

class Layer_Stack {
public:
	Layer_Stack(void) = default;
	~Layer_Stack(void);

	void push(Layer *layer);
	void pop(Layer *layer);
	void push_overlay(Layer *layer);
	void pop_overlay(Layer *layer);

	inline std::vector<Layer *>::iterator begin(void) {
		return layers.begin();
	}

	inline std::vector<Layer *>::iterator end(void) {
		return layers.end();
	}

	inline std::vector<Layer *>::const_iterator begin(void) const {
		return layers.begin();
	}
	
	inline std::vector<Layer *>::const_iterator end(void) const {
		return layers.end();
	}

	inline std::vector<Layer *>::reverse_iterator rbegin(void) {
		return layers.rbegin();
	}

	inline std::vector<Layer *>::reverse_iterator rend(void) {
		return layers.rend();
	}

	inline std::vector<Layer *>::const_reverse_iterator rbegin(void) const {
		return layers.rbegin();
	}

	inline std::vector<Layer *>::const_reverse_iterator rend(void) const {
		return layers.rend();
	}
	
private:
	std::vector<Layer *> layers;
	uint32_t insert_index = 0;
};

} // rise

#endif // RISE__LAYER_HPP
