#pragma once

#include "bomberman/Types.hpp"

#include <algorithm>
#include <memory>
#include <vector>

namespace bomberman {

class IObserver {
  public:
    virtual ~IObserver() = default;
    virtual void onEvent(const GameEvent& event) = 0;
};

class Subject {
  public:
    virtual ~Subject() = default;

    void attach(const std::shared_ptr<IObserver>& observer) { observers_.push_back(observer); }

    void detach(const std::shared_ptr<IObserver>& observer) {
        observers_.erase(std::remove_if(observers_.begin(),
                                        observers_.end(),
                                        [&observer](const std::weak_ptr<IObserver>& candidate) {
                                            const auto locked = candidate.lock();
                                            return !locked || locked == observer;
                                        }),
                         observers_.end());
    }

  protected:
    void notify(const GameEvent& event) {
        observers_.erase(std::remove_if(observers_.begin(),
                                        observers_.end(),
                                        [](const std::weak_ptr<IObserver>& observer) {
                                            return observer.expired();
                                        }),
                         observers_.end());
        for (const auto& observer : observers_) {
            if (const auto locked = observer.lock()) {
                locked->onEvent(event);
            }
        }
    }

  private:
    std::vector<std::weak_ptr<IObserver>> observers_{};
};

} // namespace bomberman
