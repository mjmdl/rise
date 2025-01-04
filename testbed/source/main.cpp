#include "game.hpp"

#include <rise/event.hpp>
#include <rise/logger.hpp>

int main(int argc, char *argv[]) {	
	testbed::Game game({argc, argv, "Testbed"});
	return game.run();
}
