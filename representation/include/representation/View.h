#ifndef BOMBERMAN_REP_VIEW_H
#define BOMBERMAN_REP_VIEW_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "logic/Observer.h"
#include "logic/Entity.h"

namespace rep {

/**
 * @brief Base class for SFML graphical representations of logic entities.
 */
class View : public logic::Observer, public sf::Drawable {
public:
    View(std::shared_ptr<logic::Entity> model);
    virtual ~View() = default;

    // Observer interface
    void update() override;

    bool isAlive() const;

    // sf::Drawable interface
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

protected:
    std::weak_ptr<logic::Entity> model;
};

/**
 * @brief View for the Player entity.
 */
class PlayerView : public View {
public:
    using View::View;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

class EnemyView : public View {
public:
    using View::View;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

class BombView : public View {
public:
    using View::View;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

class WallView : public View {
public:
    using View::View;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

class PowerUpView : public View {
public:
    using View::View;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

class ExplosionView : public View {
public:
    using View::View;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

} // namespace rep

#endif // BOMBERMAN_REP_VIEW_H
