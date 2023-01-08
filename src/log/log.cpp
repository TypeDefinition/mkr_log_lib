#include "log/log.h"

namespace mkr {
    std::shared_ptr<spdlog::async_logger> log::logger_ = nullptr;

    void log::init(log_level _console_level, log_level _file_level, const std::string& _filename) {
        spdlog::init_thread_pool(8192, 1);

        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level((spdlog::level::level_enum) _console_level);
        // console_sink->set_color(spdlog::level::level_enum::trace, console_sink->white);
        // console_sink->set_color(spdlog::level::level_enum::debug, console_sink->cyan);
        // console_sink->set_color(spdlog::level::level_enum::info, console_sink->green);
        // console_sink->set_color(spdlog::level::level_enum::warn, console_sink->yellow_bold);
        // console_sink->set_color(spdlog::level::level_enum::err, console_sink->red_bold);
        // console_sink->set_color(spdlog::level::level_enum::critical, console_sink->bold_on_red);

        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(_filename, 5242880, 3, true);
        file_sink->set_level((spdlog::level::level_enum) _file_level);

        spdlog::sinks_init_list sink_list = {console_sink, file_sink};
        logger_ = std::make_shared<spdlog::async_logger>("mkr_logger", sink_list.begin(), sink_list.end(), spdlog::thread_pool());
        logger_->set_level(spdlog::level::level_enum::trace); // Set the logger's log level to the lowest so that it does not override the sinks.
        logger_->flush_on(spdlog::level::level_enum::trace); // Set the logger's flush level to the lowest so that everything gets written to the file.
    }

    void log::exit() {
        logger_ = nullptr;
        spdlog::drop_all(); // Under VisualStudio, this must be called before main finishes to work around a known VS issue.
    }
}