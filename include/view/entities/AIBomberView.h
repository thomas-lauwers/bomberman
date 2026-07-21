/**
 * @file AIBomberView.h
 * @brief Defines the AIBomberView class for rendering AI bomber entities.
 */

#ifndef BOMBERMAN_AIBOMBERVIEW_H
#define BOMBERMAN_AIBOMBERVIEW_H
#include "../../logic/factory/AIBomber.h"
#include "BomberView.h"

/**
 * @class AIBomberView
 * @brief View component for AI-controlled bomber entities.
 */
class AIBomberView : public BomberView {
public:
    /**
     * @brief Constructs an AIBomberView instance.
     * @param t_manager Reference to the texture manager.
     * @param type The type of the AI bomber.
     */
    AIBomberView(const TextureManager& t_manager, BomberType type);

protected:
    BomberType type;            ///< The type of AI bomber
    
    /**
     * @brief Configures animations for the AI bomber.
     */
    void configureAnimations();
};

#endif // BOMBERMAN_AIBOMBERVIEW_H
