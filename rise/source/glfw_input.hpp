#ifndef RISE__GLFW_INPUT_HPP
#define RISE__GLFW_INPUT_HPP

#include "input.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace rise {

class Glfw_Input final : public Input {	
	friend class Glfw_Window;

public:
	Glfw_Input(GLFWwindow *window);
	virtual ~Glfw_Input(void) override = default;
	
protected:
	virtual bool is_key_pressed_(Key key_code) const override;
	virtual bool is_mouse_pressed_(Key key_code) const override;
	virtual std::pair<float, float> get_cursor_(void) const override;

private:
	GLFWwindow *window = nullptr;
};

} // rise

#endif // RISE__GLFW_INPUT_HPP
