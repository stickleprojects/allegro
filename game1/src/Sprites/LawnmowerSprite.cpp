/**
 * Copyright 2019 Kieron Wray
 * 
 **/


#include "LawnmowerSprite.h"

/**
 * @brief LawnmowerSprite is a composite of 2 sprites, one for tthe mower and one for the driver
 * color is fwd'd to the driver
 * draw is overridden to draw both sprites
 * x,y as fwd'd and offset as appropriate
 * hit boundary is both sprites
 */
class LawnmowerSprite: Sprite {

    public:
        LawnmowerSprite();
    
        void Update() override;
        bool Draw() override;


}
