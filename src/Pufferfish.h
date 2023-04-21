#pragma once
#ifndef __PUFFERFISH_H__
#define __PUFFERFISH_H__
#include "Enemy.h"
#include "Obstacle.h"

class Pufferfish final: public Obstacle, public Enemy
{
public:
    Pufferfish();
    void Draw() override;
    void Update() override;
    void Clean() override;
private:
    void BuildAnimations();

    float animVelo;
};
#endif //!__PUFFERFISH_H__