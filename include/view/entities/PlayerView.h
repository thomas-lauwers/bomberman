#ifndef BOMBERMAN_PLAYERVIEW_H
#define BOMBERMAN_PLAYERVIEW_H
#include "BomberView.h"

class PlayerView : public BomberView {
public:
    explicit PlayerView(const TextureManager& t_manager);
    void draw(sf::RenderWindow& window, const Entity& entity) override;

private:
};

#endif // BOMBERMAN_PLAYERVIEW_H
