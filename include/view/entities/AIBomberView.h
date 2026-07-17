#ifndef BOMBERMAN_AIBOMBERVIEW_H
#define BOMBERMAN_AIBOMBERVIEW_H
#include "BomberView.h"
#include "../../logic/factory/AIBomber.h"

class AIBomberView : public BomberView {
public:
    AIBomberView(const TextureManager& t_manager, BomberType type);

protected:
    BomberType type;
    void configureAnimations();
};

#endif // BOMBERMAN_AIBOMBERVIEW_H
