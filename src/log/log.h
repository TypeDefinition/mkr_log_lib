#pragma once

#include <utility>
#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace mkr {
    enum class log_level {
        trace = spdlog::level::level_enum::trace,
        debug = spdlog::level::level_enum::debug,
        info = spdlog::level::level_enum::info,
        warn = spdlog::level::level_enum::warn,
        error = spdlog::level::level_enum::err,
        critical = spdlog::level::level_enum::critical,
        off = spdlog::level::level_enum::off,
    };

    class log {
    private:
        static std::shared_ptr<spdlog::async_logger> logger_;

    public:
        log() = delete;

        static void init(log_level _console_level = log_level::trace, log_level _file_level = log_level::trace, const std::string& _filename = "./log/log.txt");

        static void exit();

        template<typename... Args>
        static void trace(std::string _fmt, Args&& ... _args) {
            logger_->trace(fmt::runtime(_fmt), std::forward<Args>(_args)...);
        }

        template<typename... Args>
        static void debug(std::string _fmt, Args&& ... _args) {
            logger_->debug(fmt::runtime(_fmt), std::forward<Args>(_args)...);
        }

        template<typename... Args>
        static void info(std::string _fmt, Args&& ... _args) {
            logger_->info(fmt::runtime(_fmt), std::forward<Args>(_args)...);
        }

        template<typename... Args>
        static void warn(std::string _fmt, Args&& ... _args) {
            logger_->warn(fmt::runtime(_fmt), std::forward<Args>(_args)...);
        }

        template<typename... Args>
        static void error(std::string _fmt, Args&& ... _args) {
            logger_->error(fmt::runtime(_fmt), std::forward<Args>(_args)...);
        }

        template<typename... Args>
        static void critical(std::string _fmt, Args&& ... _args) {
            logger_->critical(fmt::runtime(_fmt), std::forward<Args>(_args)...);
        }
    };
}
