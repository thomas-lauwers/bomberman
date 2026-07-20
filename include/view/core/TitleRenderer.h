#ifndef BOMBERMAN_TITLERENDERER_H
#define BOMBERMAN_TITLERENDERER_H

#include "../../logic/IWorldView.h"

class TitleRenderer {
public:
    static void render(IWorldView& renderer, bool showEnter);
};

#endif // BOMBERMAN_TITLERENDERER_H
