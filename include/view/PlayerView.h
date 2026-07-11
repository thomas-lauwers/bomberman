#ifndef BOMBERMAN_PLAYERVIEW_H
#define BOMBERMAN_PLAYERVIEW_H
#include "IEntityView.h"


class TextureManager;

class PlayerView : public IEntityView {
public:
    explicit PlayerView(const TextureManager& t_manager);

    void draw(sf::RenderWindow& window, const Entity& entity) override;

private:
    sf::Sprite sprite;

};


#endif //BOMBERMAN_PLAYERVIEW_H
