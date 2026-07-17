#ifndef BOMBERMAN_AIBOMBERVIEW_H
#define BOMBERMAN_AIBOMBERVIEW_H
#include "BomberView.h"
#include "../../logic/factory/AIBomber.h"

class AIBomberView : public BomberView {
public:
    AIBomberView(const TextureManager& t_manager, AIBomberType type);

protected:
    AIBomberType type;
    void setupAnimations() override;
};

#endif // BOMBERMAN_AIBOMBERVIEW_H
