#pragma once
#ifndef __LANDFISH_H__
#define __LANDFISH_H__
#include "Enemy.h"
#include "Obstacle.h"

class LandFish final: public Obstacle, public Enemy
{
public:
    LandFish();
    void Draw() override;
    void Update() override;
    void Clean() override;
private:
    void BuildAnimations();

    float animVelo;
};
#endif //!__LANDFISH_H__