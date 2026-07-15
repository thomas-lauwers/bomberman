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
        for (auto it = observers.begin(); it != observers.end();) {
            if (const auto observer = it->lock()) {
                observer->onNotify(entity, event);
                ++it;
            } else {
                it = observers.erase(it);
            }
        }
    }

private:
    std::vector<std::weak_ptr<Observer>> observers;
};

#endif
