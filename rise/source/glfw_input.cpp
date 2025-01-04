#include "glfw_input.hpp"

namespace rise {

Input *Input::instance = nullptr;

Glfw_Input::Glfw_Input(GLFWwindow *window) : window(window) {
}

bool Glfw_Input::is_key_pressed_(Key key_code) const {
	int state = glfwGetKey(window, static_cast<int>(key_code));
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Glfw_Input::is_mouse_pressed_(Key key_code) const {
	int state = glfwGetMouseButton(window, static_cast<int>(key_code));
	return state == GLFW_PRESS;
}

std::pair<float, float> Glfw_Input::get_cursor_(void) const {
	double x;
	double y;
	glfwGetCursorPos(window, &x, &y);
	return {static_cast<float>(x), static_cast<float>(y)};
}

} // rise
