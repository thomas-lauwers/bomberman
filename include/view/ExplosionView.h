#ifndef BOMBERMAN_EXPLOSIONVIEW_H
#define BOMBERMAN_EXPLOSIONVIEW_H
#include "IEntityView.h"

class TextureManager;

class ExplosionView : public IEntityView {
public:
    explicit ExplosionView(const TextureManager& t_manager);
    void draw(sf::RenderWindow& window, const Entity& entity) override;
    void onNotify(const Entity& entity, Event event) override;
private:
    sf::Sprite sprite;
};

#endif //BOMBERMAN_EXPLOSIONVIEW_H
