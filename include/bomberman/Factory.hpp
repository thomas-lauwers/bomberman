#pragma once

#include "bomberman/Observer.hpp"

#include <memory>

namespace bomberman {

class AbstractFactory {
  public:
    virtual ~AbstractFactory() = default;
    virtual std::shared_ptr<IObserver> createWorldView() = 0;
};

} // namespace bomberman
