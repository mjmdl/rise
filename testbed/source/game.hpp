#ifndef TESTBED__GAME_HPP
#define TESTBED__GAME_HPP

#include <rise/engine.hpp>
#include <rise/input.hpp>
#include <rise/layer.hpp>
#include <rise/logger.hpp>

namespace testbed {

class Game final : public rise::Engine {
public:
	Game(const Config &config);
	virtual ~Game(void) override;
};

class Example_Layer final : public rise::Layer {
public:
	Example_Layer(const std::string &name) : Layer(name) {
	}

	virtual void handle_event(rise::Event &event) override {
		rise::Event_Dispatcher event_dispatcher(event);
		event_dispatcher.handle<rise::Keyboard_Press_Event>([](auto &press_event) -> bool {
			if (rise::Input::is_key_pressed(rise::Key::SPACE)) {
				auto [x, y] = rise::Input::get_cursor();
				rise::debug("Mouse position: {0}, {1}", x, y);
				
				return true;
			}
			return false;
		});
	}
};

} // testbed

#endif // TESTBED__GAME_HPP
