#ifndef RISE__GLFW_WINDOW_HPP
#define RISE__GLFW_WINDOW_HPP

#include "window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace rise {

class Glfw_Window final : public Window {
public:
	Glfw_Window(const Config &config);
	virtual ~Glfw_Window(void) override;

	virtual bool has_succeeded(void) const override;
	virtual bool should_close(void) const override;
	virtual void poll_events(void) override;
	virtual void swap_buffers(void) override;
	virtual std::string to_string(void) const override;
	virtual uint32_t get_width(void) const override;
	virtual uint32_t get_height(void) const override;
	virtual void *get_handle(void) const override;

private:
	static bool glfw_is_initialized;
	static bool glad_is_loaded;
	static int glfw_window_count;

	static void glfw_error_callback(int error_code, const char *description);
	static void close_callback(GLFWwindow *window);
	static void size_callback(GLFWwindow *window, int width, int height);
	static void pos_callback(GLFWwindow *window, int x, int y);
	static void key_callback(GLFWwindow *window, int key_code, int scan_code, int action, int mods);
	static void mouse_button_callback(GLFWwindow *window, int key_code, int action, int mods);
	static void cursor_pos_callback(GLFWwindow *window, double x, double y);
	static void focus_callback(GLFWwindow *window, int is_focus);
	static void scroll_callback(GLFWwindow* window, double delta_x, double delta_y);
	
	bool is_success = false;
	bool is_requested_to_close = false;
	GLFWwindow *window = nullptr;
	uint32_t x;
	uint32_t y;
	uint32_t width;
	uint32_t height;
};

} // rise

#endif // RISE__GLFW_WINDOW_HPP
