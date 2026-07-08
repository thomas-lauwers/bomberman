#pragma once

#include <functional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace testfw {

using Test = std::function<void()>;

inline std::vector<std::pair<std::string, Test>>& registry() {
    static std::vector<std::pair<std::string, Test>> tests;
    return tests;
}

struct Registration {
    Registration(std::string name, Test test) { registry().emplace_back(std::move(name), std::move(test)); }
};

} // namespace testfw

#define TEST(name)                                                                                                     \
    void name();                                                                                                       \
    namespace {                                                                                                        \
    testfw::Registration name##Registration(#name, name);                                                             \
    }                                                                                                                  \
    void name()

#define CHECK(condition)                                                                                               \
    do {                                                                                                               \
        if (!(condition)) {                                                                                            \
            throw std::runtime_error(std::string("Check failed: ") + #condition);                                    \
        }                                                                                                              \
    } while (false)
