#pragma once
#include "Agent.h"
#include "Enemy.h"


class Shark final : public Enemy, public Agent
{
public:
    Shark();
    void Draw() override;
    void Update() override;
    void Clean() override;

    void LookForPlayer();
    void LookTowardsPlayer();
    void TakeDamage(float damage) override;

private:
    float animVelo;
};
