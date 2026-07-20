#include "../../../include/logic/state/TitleState.h"
#include <SFML/Graphics.hpp>

TitleState::TitleState(std::function<void()> onSelect)
    : onSelect(std::move(onSelect)) {}

TitleState::~TitleState() = default;

void TitleState::handleInput(const Input input) {
    if (input == Input::Select) {
        onSelect();
    }
}

void TitleState::update(const float deltaTime, IWorldView& renderer) {
    blinkTimer += deltaTime;
    if (blinkTimer >= 0.5f) {
        blinkTimer = 0.0f;
        showText = !showText;
    }
}

void TitleState::render(IWorldView& renderer) {
    renderer.renderTitle(showText);
}
