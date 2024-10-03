#include <base/types.h>
#include <vector>
#include <core/core.h>
#include <graphic/graphic.h>
#include <base/logger.h>
#include <base/string_utils.h>

#include <chrono>
#include <iostream>

namespace omnity::core {
    void setup(const std::vector<std::u16string>& args) {
        auto str = std::u16string(u"12🌹34");
        const auto str2 = std::move(str);
        const auto str3 = str2;
        logger::log_info(str2);
        logger::log_info(str3.substr(1, 3));
        logger::log_info(u"🌹Started!");
        logger::log_info(u"Started!2");
        for (const auto& arg : args)
            logger::log_info(arg);
        omnity::graphic::init_graphic();
        omnity::graphic::setup_graphic_backend();
    }
    void application::run(const int argc, const char* argv[]) {
        std::vector<std::u16string> args;
        args.reserve(argc);
        for (int i = 0; i < argc; ++i)
            args.push_back(std::u16string(string_utils::from_utf8_ptr(argv[i])));
        setup(args);
    }
    void application::run(const int argc, const char16_t* argv[]) {
        std::vector<std::u16string> args;
        args.reserve(argc);
        for (int i = 0; i < argc; ++i)
            args.emplace_back(argv[i]);
        setup(args);
    }

    application::~application() = default;
}
