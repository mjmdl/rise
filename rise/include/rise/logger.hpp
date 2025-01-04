#ifndef RISE__LOGGER_HPP
#define RISE__LOGGER_HPP

#include <spdlog/spdlog.h>

#ifdef RISE__INTERNAL_COMPILATION
#   define SELECTED_LOGGER internal_logger
#else
#   define SELECTED_LOGGER external_logger
#endif

#define LOGGER_FUNCTION(NAME, METHOD) \
	template<typename ...Args> \
	void NAME(Args ...args) { \
		SELECTED_LOGGER->METHOD(args...); \
	}

namespace rise {

using Logger = std::shared_ptr<spdlog::logger>;

extern Logger SELECTED_LOGGER;

LOGGER_FUNCTION(trace, trace)
LOGGER_FUNCTION(debug, debug)
LOGGER_FUNCTION(info, info)
LOGGER_FUNCTION(warn, warn)
LOGGER_FUNCTION(error, error)
LOGGER_FUNCTION(fatal, critical)

} // rise

#undef LOGGER_FUNCTION
#undef SELECTED_LOGGER

#endif // RISE__LOGGER_HPP
