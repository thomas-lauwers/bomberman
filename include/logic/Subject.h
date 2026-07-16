#ifndef BOMBERMAN_SUBJECT_H
#define BOMBERMAN_SUBJECT_H

#include "Observer.h"
#include <algorithm>
#include <memory>
#include <vector>

class Entity;

class Subject {
public:
    virtual ~Subject() = default;

    void addObserver(const std::weak_ptr<Observer>& observer) { observers.push_back(observer); }

protected:
    void notify(const Entity& entity, const Event event) {
        std::vector<std::weak_ptr<Observer>> observers_copy = observers;
        for (auto& weak_observer : observers_copy) {
            if (const auto observer = weak_observer.lock()) {
                observer->onNotify(entity, event);
            }
        }
        observers.erase(std::remove_if(observers.begin(), observers.end(), [](const std::weak_ptr<Observer>& weak_observer) {
            return weak_observer.expired();
        }), observers.end());
    }

private:
    std::vector<std::weak_ptr<Observer>> observers;
};

#endif
