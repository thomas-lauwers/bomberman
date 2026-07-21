#ifndef BOMBERMAN_IWORLDVIEW_H
#define BOMBERMAN_IWORLDVIEW_H
#include <string>

class World;

class IWorldView {
public:
    virtual ~IWorldView() = default;
    virtual void render(const World& world) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void renderCenteredText(const std::string& text, float y) = 0;
    virtual void renderText(const std::string& text, float x, float y) = 0;
    virtual void renderPortrait(float x, float y) = 0;
    virtual void renderTitle(bool showEnter) = 0;
};

#endif // BOMBERMAN_IWORLDVIEW_H
