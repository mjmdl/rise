#include "logger.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace rise {

Logger internal_logger;
Logger external_logger;

void initialize_loggers(const std::string &external_name) {
	spdlog::set_pattern("%T %^[%n] %v%$");
	
	internal_logger = spdlog::stdout_color_mt("Rise");
	internal_logger->set_level(spdlog::level::trace);
	
	external_logger = spdlog::stdout_color_mt(external_name);
	external_logger->set_level(spdlog::level::trace);
}

} // rise
