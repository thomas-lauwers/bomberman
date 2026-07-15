#ifndef BOMBERMAN_DESTRUCTIBLEWALLVIEW_H
#define BOMBERMAN_DESTRUCTIBLEWALLVIEW_H
#include "IEntityView.h"
#include "Animation.h"

class TextureManager;

class DestructibleWallView : public IEntityView {
public:
    explicit DestructibleWallView(const TextureManager& t_manager);

    void draw(sf::RenderWindow& window, const Entity& entity) override;
    void update(float deltaTime) override;
    void onNotify(const Entity& entity, Event event) override;

private:
    sf::Sprite sprite;
};


#endif //BOMBERMAN_DESTRUCTIBLEWALLVIEW_H
