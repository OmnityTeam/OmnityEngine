#pragma once
#include <memory>
#include <vector>
#include <base/type.h>
#include <fmt/format.h>

namespace omnity {
    class log_sink {
    public:
        log_sink() = default;
        virtual void log(std::u16string_view category, std::u16string_view message) = 0;
        virtual ~log_sink() = default;
    };
    class logger final {
        std::vector<std::unique_ptr<log_sink>> log_sinks_;
        logger();
        ~logger();
        static logger& get_instance();
    public:
        logger(logger&) = delete;
        logger(logger&&) = delete;
        logger& operator =(logger& str) = delete;
        logger& operator =(logger&& str) = delete;
        static void log(std::u16string_view category, std::u16string_view message);
        template <class T, typename... Args>
        static void add_log_sink(Args... args) {
            get_instance().log_sinks_.emplace_back(std::unique_ptr<log_sink>(static_cast<log_sink*>(new T(args...))));
        }
        static void log_info(const std::u16string_view message) {
            log(u"Info", message);
        }
    };
}