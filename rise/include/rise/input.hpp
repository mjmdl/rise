#ifndef RISE__INPUT_HPP
#define RISE__INPUT_HPP

namespace rise {

#define X(STRING, NAME, GLFW) \
	NAME = GLFW,

enum class Key {
#include "key_codes.def"
};

#undef X

class Input {
public:
	virtual ~Input(void) = default;
	
	static inline bool is_key_pressed(Key key_code) {
		return instance->is_key_pressed_(key_code);
	}

	static inline bool is_mouse_pressed(Key key_code) {
		return instance->is_mouse_pressed_(key_code);
	}

	static inline std::pair<float, float> get_cursor(void) {
		return instance->get_cursor_();
	}

protected:
	static Input *instance;

	virtual bool is_key_pressed_(Key key_code) const = 0;
	virtual bool is_mouse_pressed_(Key key_code) const = 0;
	virtual std::pair<float, float> get_cursor_(void) const = 0;
};

} // rise

#endif // RISE__INPUT_HPP
