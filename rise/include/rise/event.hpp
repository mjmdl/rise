#ifndef RISE__EVENT_HPP
#define RISE__EVENT_HPP

namespace rise {

enum class Event_Type {
	NONE = 0,
	ENGINE_TICK,
	ENGINE_RENDER,
	ENGINE_SIMULATE,
	WINDOW_OPEN,
	WINDOW_CLOSE,
	WINDOW_RESIZE,
	WINDOW_MOVE,
	WINDOW_FOCUS,
	WINDOW_BLUR,
	KEYBOARD_PRESS,
	KEYBOARD_RELEASE,
	MOUSE_PRESS,
	MOUSE_RELEASE,
	SCROLL,
	CURSOR_MOVE,
};

using Event_Flags_Mask = uint32_t;

enum Event_Flag {
	NONE = 0,
	EVENT_FLAG_ENGINE = 1 << 0,
	EVENT_FLAG_WINDOW = 1 << 1,
	EVENT_FLAG_INPUT = 1 << 2,
	EVENT_FLAG_KEYBOARD = 1 << 3,
	EVENT_FLAG_CURSOR_MOVE = 1 << 4,
	EVENT_FLAG_MOUSE = 1 << 5,
};

struct Event {
	bool is_handled = false;

	virtual Event_Type get_type(void) const = 0;
	virtual const char *get_name(void) const = 0;
	virtual Event_Flags_Mask get_flags(void) const = 0;
	
	virtual std::string to_string(void) const {
		return get_name();
	}
};

struct Event_Dispatcher {
	template<typename Type>
	using Callback = std::function<bool(Type &)>;

	Event &event;
	
	Event_Dispatcher(Event &event) : event(event) {
	}

	template<typename Type>
	bool handle(Callback<Type> callback) {
		if (event.get_type() == Type::get_static_type()) {
			event.is_handled = callback(*static_cast<Type *>(&event));
			return true;
		}
		return false;
	}
};

#define EVENT_CLASS_TYPE(TYPE) \
	static Event_Type get_static_type(void) { \
		return Event_Type::TYPE; \
	} \
	virtual Event_Type get_type(void) const override { \
		return get_static_type(); \
	} \
	virtual const char *get_name(void) const override { \
		return #TYPE; \
	}
#define EVENT_CLASS_FLAGS(FLAGS) \
	virtual Event_Flags_Mask get_flags(void) const override { \
		return FLAGS; \
	}

struct Engine_Tick_Event final : public Event {
	std::string to_string(void) const override {
		return "Engine_Tick_Event";
	}
	
	EVENT_CLASS_TYPE(ENGINE_TICK);
	EVENT_CLASS_FLAGS(EVENT_FLAG_ENGINE);
};

struct Engine_Render_Event final : public Event {
	double time_step;

	Engine_Render_Event(double time_step) : time_step(time_step) {
	}
	
	std::string to_string(void) const override {
		std::stringstream stream;
		stream << "Engine_Render_Event{ time_step = " << time_step << " }";
		return stream.str();
	}
	
	EVENT_CLASS_TYPE(ENGINE_RENDER);
	EVENT_CLASS_FLAGS(EVENT_FLAG_ENGINE);
};

struct Engine_Simulate_Event final : public Event {
	double time_step;

	Engine_Simulate_Event(double time_step) : time_step(time_step) {
	}
	
	std::string to_string(void) const override {
		std::stringstream stream;
		stream << "Engine_Simulate_Event{ time_step = " << time_step << " }";
		return stream.str();
	}
	
	EVENT_CLASS_TYPE(ENGINE_SIMULATE);
	EVENT_CLASS_FLAGS(EVENT_FLAG_ENGINE);
};

struct Window_Open_Event final : public Event {
	std::string to_string(void) const override {
		return "Window_Open_Event";
	}

	EVENT_CLASS_TYPE(WINDOW_OPEN);
	EVENT_CLASS_FLAGS(EVENT_FLAG_WINDOW);
};

struct Window_Close_Event final : public Event {
	std::string to_string(void) const override {
		return "Window_Close_Event";
	}

	EVENT_CLASS_TYPE(WINDOW_CLOSE);
	EVENT_CLASS_FLAGS(EVENT_FLAG_WINDOW);
};

struct Window_Resize_Event final : public Event {
	uint32_t width;
	uint32_t height;

	Window_Resize_Event(uint32_t width, uint32_t height) : width(width), height(height)	{
	}

	std::string to_string(void) const override {
		std::stringstream stream;
		stream << "Window_Resize_Event{ width = " << width << ", height = " << height << " }";
		return stream.str();
	}

	EVENT_CLASS_TYPE(WINDOW_RESIZE);
	EVENT_CLASS_FLAGS(EVENT_FLAG_WINDOW);
};

struct Window_Move_Event final : public Event {
	uint32_t x;
	uint32_t y;

	Window_Move_Event(uint32_t x, uint32_t y) : x(x), y(y) {
	}

	std::string to_string(void) const override {
		std::stringstream stream;
		stream << "Window_Move_Event{ x = " << x << ", y = " << y << " }";
		return stream.str();
	}

	EVENT_CLASS_TYPE(WINDOW_MOVE);
	EVENT_CLASS_FLAGS(EVENT_FLAG_WINDOW);
};

struct Window_Focus_Event final : public Event {
	std::string to_string(void) const override {
		return "Window_Focus_Event";
	}

	EVENT_CLASS_TYPE(WINDOW_FOCUS);
	EVENT_CLASS_FLAGS(EVENT_FLAG_WINDOW | EVENT_FLAG_INPUT);
};

struct Window_Blur_Event final : public Event {
	std::string to_string(void) const override {
		return "Window_Blur_Event";
	}

	EVENT_CLASS_TYPE(WINDOW_BLUR);
	EVENT_CLASS_FLAGS(EVENT_FLAG_WINDOW | EVENT_FLAG_INPUT);
};

struct Keyboard_Press_Event final : public Event {
	uint32_t key_code;
	uint32_t repeat_count;

	Keyboard_Press_Event(uint32_t key_code, uint32_t repeat_count) : key_code(key_code), repeat_count(repeat_count) {
	}	
	
	std::string to_string(void) const override {
		std::stringstream stream;
		stream << "Keyboard_Press_Event{ key_code = " << key_code << ", repeat_count = " << repeat_count << " }";
		return stream.str();
	}

	EVENT_CLASS_TYPE(KEYBOARD_PRESS);
	EVENT_CLASS_FLAGS(EVENT_FLAG_INPUT | EVENT_FLAG_KEYBOARD);
};

struct Keyboard_Release_Event final : public Event {
	uint32_t key_code;

	Keyboard_Release_Event(uint32_t key_code) : key_code(key_code) {
	}	
	
	std::string to_string(void) const override {
		std::stringstream stream;
		stream << "Keyboard_Release_Event{ key_code = " << key_code << " }";
		return stream.str();
	}

	EVENT_CLASS_TYPE(KEYBOARD_RELEASE);
	EVENT_CLASS_FLAGS(EVENT_FLAG_INPUT | EVENT_FLAG_KEYBOARD);
};

struct Mouse_Press_Event final : public Event {
	uint32_t key_code;
	uint32_t repeat_count;

	Mouse_Press_Event(uint32_t key_code, uint32_t repeat_count) : key_code(key_code), repeat_count(repeat_count) {
	}	
	
	std::string to_string(void) const override {
		std::stringstream stream;
		stream << "Mouse_Press_Event{ key_code = " << key_code << ", repeat_count = " << repeat_count << " }";
		return stream.str();
	}

	EVENT_CLASS_TYPE(MOUSE_PRESS);
	EVENT_CLASS_FLAGS(EVENT_FLAG_INPUT | EVENT_FLAG_MOUSE);
};

struct Mouse_Release_Event final : public Event {
	uint32_t key_code;
	
	Mouse_Release_Event(uint32_t key_code) : key_code(key_code) {
	}	

	std::string to_string(void) const override {
		std::stringstream stream;
		stream << "Mouse_Release_Event{ key_code = " << key_code << " }";
		return stream.str();
	}

	EVENT_CLASS_TYPE(MOUSE_RELEASE);
	EVENT_CLASS_FLAGS(EVENT_FLAG_INPUT | EVENT_FLAG_MOUSE);
};

struct Scroll_Event final : public Event {
	double delta_x;
	double delta_y;

	Scroll_Event(double delta_x, double delta_y) : delta_x(delta_x), delta_y(delta_y) {
	}	
	
	std::string to_string(void) const override {
		std::stringstream stream;
		stream << "Scroll_Event{ delta_x = " << delta_x << ", delta_y = " << delta_y << " }";
		return stream.str();
	}

	EVENT_CLASS_TYPE(SCROLL);
	EVENT_CLASS_FLAGS(EVENT_FLAG_INPUT | EVENT_FLAG_MOUSE);
};

struct Cursor_Move_Event final : public Event {
	double x;
	double y;

	Cursor_Move_Event(double x, double y) : x(x), y(y) {
	}
	
	std::string to_string(void) const override {
		std::stringstream stream;
		stream << "Cursor_Move_Event{ x = " << x << ", y = " << y << " }";
		return stream.str();
	}

	EVENT_CLASS_TYPE(CURSOR_MOVE);
	EVENT_CLASS_FLAGS(EVENT_FLAG_INPUT | EVENT_FLAG_MOUSE);
};

#undef EVENT_CLASS_TYPE
#undef EVENT_CLASS_FLAGS

inline std::ostream &operator<<(std::ostream &stream, const Event &event) {
	return stream << event.to_string();
}

} // rise

#endif // RISE__EVENT_HPP
