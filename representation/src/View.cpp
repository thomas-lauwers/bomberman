#include "representation/View.h"
#include "logic/Wall.h"

namespace rep {

View::View(std::shared_ptr<logic::Entity> model) : model(model) {}

void View::update() {
    // Sync graphical state if needed
}

bool View::isAlive() const {
    return !model.expired();
}

void PlayerView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (auto m = model.lock()) {
        sf::CircleShape shape(15.0f);
        shape.setOrigin({15.0f, 15.0f});
        shape.setFillColor(sf::Color::Blue);
        float px = (m->getX() + 1.0f) * 400.0f;
        float py = (1.0f - m->getY()) * 300.0f;
        shape.setPosition({px, py});
        target.draw(shape, states);
    }
}

void EnemyView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (auto m = model.lock()) {
        sf::CircleShape shape(15.0f);
        shape.setOrigin({15.0f, 15.0f});
        shape.setFillColor(sf::Color::Red);
        float px = (m->getX() + 1.0f) * 400.0f;
        float py = (1.0f - m->getY()) * 300.0f;
        shape.setPosition({px, py});
        target.draw(shape, states);
    }
}

void BombView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (auto m = model.lock()) {
        sf::CircleShape shape(12.0f);
        shape.setOrigin({12.0f, 12.0f});
        shape.setFillColor(sf::Color::Black);
        shape.setOutlineThickness(2);
        shape.setOutlineColor(sf::Color::White);
        float px = (m->getX() + 1.0f) * 400.0f;
        float py = (1.0f - m->getY()) * 300.0f;
        shape.setPosition({px, py});
        target.draw(shape, states);
    }
}

void WallView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (auto m = model.lock()) {
        sf::RectangleShape shape({50.0f, 40.0f});
        shape.setOrigin({25.0f, 20.0f});
        
        if (m->getType() == logic::EntityType::Wall) {
            auto& wall = static_cast<const logic::Wall&>(*m);
            if (wall.isDestructible()) {
                shape.setFillColor(sf::Color(139, 69, 19)); // Brown
            } else {
                shape.setFillColor(sf::Color(105, 105, 105)); // Dim Gray
            }
        }
        
        float px = (m->getX() + 1.0f) * 400.0f;
        float py = (1.0f - m->getY()) * 300.0f;
        shape.setPosition({px, py});
        target.draw(shape, states);
    }
}

void PowerUpView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (auto m = model.lock()) {
        sf::CircleShape shape(10.0f, 5);
        shape.setOrigin({10.0f, 10.0f});
        shape.setFillColor(sf::Color::Yellow);
        float px = (m->getX() + 1.0f) * 400.0f;
        float py = (1.0f - m->getY()) * 300.0f;
        shape.setPosition({px, py});
        target.draw(shape, states);
    }
}

void ExplosionView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (auto m = model.lock()) {
        sf::RectangleShape shape({50.0f, 40.0f});
        shape.setOrigin({25.0f, 20.0f});
        shape.setFillColor(sf::Color(255, 140, 0, 180));
        float px = (m->getX() + 1.0f) * 400.0f;
        float py = (1.0f - m->getY()) * 300.0f;
        shape.setPosition({px, py});
        target.draw(shape, states);
    }
}

} // namespace rep
