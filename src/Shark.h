#pragma once
#include "Agent.h"
#include "Enemy.h"


class Shark final : public Enemy, public Agent
{
    friend Agent;
public:
    Shark();
    void Draw() override;
    void Update() override;
    void Clean() override;
    void Move() override;

    void LookTowardsPlayer();
    
private:
    
};
