#ifndef BOMBERMAN_LOGIC_OBSERVER_H
#define BOMBERMAN_LOGIC_OBSERVER_H

namespace logic {

/**
 * @brief Base class for observers in the Observer pattern.
 */
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
};

/**
 * @brief Base class for subjects in the Observer pattern.
 */
class Subject {
public:
    virtual ~Subject() = default;
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify() = 0;
};

} // namespace logic

#endif // BOMBERMAN_LOGIC_OBSERVER_H
