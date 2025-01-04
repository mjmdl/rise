#ifndef RISE__WINDOW_HPP
#define RISE__WINDOW_HPP

#include "event.hpp"

namespace rise {

class Window {
public:
	using Event_Callback = std::function<void(Event &)>;
	
	struct Config {
		std::string title = "Rise Engine";
	};

	static std::unique_ptr<Window> create(const Config &config);

	virtual ~Window(void) = default;

	virtual bool has_succeeded(void) const = 0;
	virtual bool should_close(void) const = 0;
	virtual void poll_events(void) = 0;
	virtual void swap_buffers(void) = 0;
	virtual std::string to_string(void) const = 0;
	virtual uint32_t get_width(void) const = 0;
	virtual uint32_t get_height(void) const = 0;
	virtual void *get_handle(void) const = 0;

	inline void set_event_callback(const Event_Callback &callback) {
		event_callback = callback;
	}

	operator bool(void) const {
		return has_succeeded();
	}
	
protected:
	Config config;
	Event_Callback event_callback;
	
	inline Window(const Config &config) : config(config) {
	}
};

} // rise

#endif // RISE__WINDOW_HPP
