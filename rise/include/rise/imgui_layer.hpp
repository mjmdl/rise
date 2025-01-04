#ifndef RISE__IMGUI_LAYER_HPP
#define RISE__IMGUI_LAYER_HPP

#include "layer.hpp"

#include <imgui.h>

namespace rise {

class Imgui_Layer final : public Layer {
public:
	Imgui_Layer(void *window_handle);
	virtual ~Imgui_Layer(void) override;

	virtual void attach(void) override;
	virtual void detach(void) override;
	virtual void update(void) override;
	virtual void handle_event(Event &event) override;

private:	
	bool show_demo_window = true;
	float last_time = 0.0f;
	uint32_t width = 0;
	uint32_t height = 0;
	void *window_handle = nullptr;
};

} // rise

#endif // RISE__IMGUI_LAYER_HPP
