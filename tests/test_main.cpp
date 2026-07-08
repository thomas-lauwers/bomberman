#include "TestFramework.hpp"

#include <exception>
#include <iostream>

int main() {
    int failures = 0;
    for (const auto& [name, test] : testfw::registry()) {
        try {
            test();
            std::cout << "[PASS] " << name << '\n';
        } catch (const std::exception& exception) {
            ++failures;
            std::cerr << "[FAIL] " << name << ": " << exception.what() << '\n';
        }
    }

    return failures == 0 ? 0 : 1;
}
