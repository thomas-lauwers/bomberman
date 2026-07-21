/**
 * @file Subject.h
 * @brief Defines the Subject class for the Observer pattern.
 */

#ifndef BOMBERMAN_SUBJECT_H
#define BOMBERMAN_SUBJECT_H

#include "Observer.h"
#include <algorithm>
#include <memory>
#include <vector>

class Entity;

/**
 * @class Subject
 * @brief Implements the Subject side of the Observer pattern.
 *
 * This class maintains a list of observers and notifies them of events triggered
 * by entities.
 */
class Subject {
public:
    virtual ~Subject() = default;

    /**
     * @brief Adds an observer to the subject.
     * @param observer Weak pointer to the observer.
     */
    void addObserver(const std::weak_ptr<Observer>& observer) { observers.push_back(observer); }

protected:
    /**
     * @brief Notifies all registered observers of an event.
     * @param entity The entity triggering the event.
     * @param event The event type.
     */
    void notify(const Entity& entity, const Event event) {
        std::vector<std::weak_ptr<Observer>> observers_copy = observers;
        for (auto& weak_observer : observers_copy) {
            if (const auto observer = weak_observer.lock()) {
                observer->onNotify(entity, event);
            }
        }
        observers.erase(
            std::remove_if(observers.begin(), observers.end(),
                           [](const std::weak_ptr<Observer>& weak_observer) { return weak_observer.expired(); }),
            observers.end());
    }

private:
    std::vector<std::weak_ptr<Observer>> observers;
};

#endif
