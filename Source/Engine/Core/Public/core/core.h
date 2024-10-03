#pragma once

namespace omnity::core {
    class application {
    public:
        application() = delete;
        application(application&) = delete;
        application(application&&) = delete;
        application& operator=(application&) = delete;
        application& operator=(application&&) = delete;
        static void run(int argc, const char* argv[]);
        static void run(int argc, const char16_t* argv[]);
        ~application();
    };
}