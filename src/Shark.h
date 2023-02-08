#pragma once
#include "Enemy.h"


class Shark final : public Enemy
{
public:
    Shark();
    void Draw() override;
    void Update() override;
    void Clean() override;
    void Move() override;

    void LookTowardsPlayer();
private:
    
};
