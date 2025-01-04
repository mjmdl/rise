#include "glfw_input.hpp"
#include "glfw_window.hpp"
#include "logger.hpp"

namespace rise {

bool Glfw_Window::glfw_is_initialized = false;
bool Glfw_Window::glad_is_loaded = false;
int Glfw_Window::glfw_window_count = 0;

std::unique_ptr<Window> Window::create(const Config &config) {
	return std::make_unique<Glfw_Window>(config);
}

Glfw_Window::Glfw_Window(const Config &config) : Window(config) {
	if (!glfw_is_initialized) {
		glfwSetErrorCallback(glfw_error_callback);
		
		if (!glfwInit()) {
			fatal("Could not initialize GLFW!");
			return;
		}
		glfw_is_initialized = true;
	}

	GLFWmonitor *primary_monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode *video_mode = glfwGetVideoMode(primary_monitor);
	width = video_mode->width * 0.75;
	height = width / 16 * 9;
	
	glfwGetMonitorPos(primary_monitor, reinterpret_cast<int *>(&x), reinterpret_cast<int *>(&y));
	x += (video_mode->width - width) / 2;
	y += (video_mode->height - height) / 2;

	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, height, config.title.c_str(), nullptr, nullptr);
	glfwDefaultWindowHints();
	
	if (!window) {
		fatal("Could not create the GLFW window!");
		return;
	}
	
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glfwSetWindowUserPointer(window, this);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetWindowCloseCallback(window, close_callback);
	glfwSetWindowFocusCallback(window, focus_callback);
	glfwSetWindowPosCallback(window, pos_callback);
	glfwSetWindowSizeCallback(window, size_callback);
	
	if (!glad_is_loaded) {
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			fatal("Could not load GLAD!");
			return;
		}
		glad_is_loaded = true;
	}

	Input::instance = new Glfw_Input(window);

	glfwSetWindowPos(window, x, y);
	glfwShowWindow(window);

	glfw_window_count++;
	is_success = true;
}

Glfw_Window::~Glfw_Window(void) {
	glfwDestroyWindow(window);
	
	glfw_window_count--;
	if (glfw_is_initialized && glfw_window_count == 0) {
		glfwTerminate();
	}
}

bool Glfw_Window::has_succeeded(void) const {
	return is_success;
}

bool Glfw_Window::should_close(void) const {
	return is_requested_to_close;
}

void Glfw_Window::poll_events(void) {
	glfwPollEvents();
}

void Glfw_Window::swap_buffers(void) {
	glfwSwapBuffers(window);
}

std::string Glfw_Window::to_string(void) const {
	std::stringstream stream;
	stream << "Glfw_Window{ title = " << config.title << ", x = " << x << ", y = " << y << ", width = " << width << ", height = " << height << ", is_requested_to_close = " << (is_requested_to_close ? "true" : "false") << " }";
	return stream.str();
}

uint32_t Glfw_Window::get_width(void) const {
	return width;
}

uint32_t Glfw_Window::get_height(void) const {
	return height;
}

void *Glfw_Window::get_handle(void) const {
	return window;
}

void Glfw_Window::glfw_error_callback(int error_code, const char *description) {
	rise::error("GLFW error #{0}: {1}", error_code, description);
}

void Glfw_Window::close_callback(GLFWwindow *window) {
	auto wrapper = reinterpret_cast<Glfw_Window *>(glfwGetWindowUserPointer(window));
	wrapper->is_requested_to_close = true;

	Window_Close_Event close_event;
	wrapper->event_callback(close_event);
}

void Glfw_Window::size_callback(GLFWwindow *window, int width, int height) {
	auto wrapper = reinterpret_cast<Glfw_Window *>(glfwGetWindowUserPointer(window));
	wrapper->width = static_cast<uint32_t>(width);
	wrapper->height = static_cast<uint32_t>(height);
	glViewport(0, 0, width, height);

	Window_Resize_Event resize_event(width, height);
	wrapper->event_callback(resize_event);
}

void Glfw_Window::pos_callback(GLFWwindow *window, int x, int y) {
	auto wrapper = reinterpret_cast<Glfw_Window *>(glfwGetWindowUserPointer(window));
	wrapper->x = static_cast<uint32_t>(x);
	wrapper->y = static_cast<uint32_t>(y);

	Window_Move_Event move_event(x, y);
	wrapper->event_callback(move_event);
}

void Glfw_Window::key_callback(GLFWwindow *window, int key_code, int scan_code, int action, int mods) {
	auto wrapper = reinterpret_cast<Glfw_Window *>(glfwGetWindowUserPointer(window));

	switch (action) {
	case GLFW_PRESS: {
		Keyboard_Press_Event press_event(key_code, 0);
		wrapper->event_callback(press_event);
	} break;

	case GLFW_RELEASE: {
		Keyboard_Release_Event release_event(key_code);
		wrapper->event_callback(release_event);
	} break;

	case GLFW_REPEAT: {
		Keyboard_Press_Event press_event(key_code, 1);
		wrapper->event_callback(press_event);
	} break;
	}
}

void Glfw_Window::mouse_button_callback(GLFWwindow *window, int key_code, int action, int mods) {
	auto wrapper = reinterpret_cast<Glfw_Window *>(glfwGetWindowUserPointer(window));

	switch (action) {
	case GLFW_PRESS: {
		Mouse_Press_Event press_event(key_code, 0);
		wrapper->event_callback(press_event);
	} break;

	case GLFW_RELEASE: {
		Mouse_Release_Event release_event(key_code);
		wrapper->event_callback(release_event);
	} break;

	case GLFW_REPEAT: {
		Mouse_Press_Event press_event(key_code, 1);
		wrapper->event_callback(press_event);
	} break;
	}	
}

void Glfw_Window::cursor_pos_callback(GLFWwindow *window, double x, double y) {
	auto wrapper = reinterpret_cast<Glfw_Window *>(glfwGetWindowUserPointer(window));

	Cursor_Move_Event move_event(x, y);
	wrapper->event_callback(move_event);
}

void Glfw_Window::focus_callback(GLFWwindow *window, int is_focus) {
	auto wrapper = reinterpret_cast<Glfw_Window *>(glfwGetWindowUserPointer(window));

	if (is_focus) {
		Window_Focus_Event focus_event;
		wrapper->event_callback(focus_event);
	} else {
		Window_Blur_Event blur_event;
		wrapper->event_callback(blur_event);
	}
}

void Glfw_Window::scroll_callback(GLFWwindow* window, double delta_x, double delta_y) {
	auto wrapper = reinterpret_cast<Glfw_Window *>(glfwGetWindowUserPointer(window));

	Scroll_Event scroll_event(delta_x, delta_y);
	wrapper->event_callback(scroll_event);
}

} // rise
