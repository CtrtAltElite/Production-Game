#pragma once
#include "Agent.h"
#include "Enemy.h"

class Pufferfish final: public Enemy, public Agent
{
public:
    Pufferfish();
    void Draw() override;
    void Update() override;
    void Clean() override;
};
