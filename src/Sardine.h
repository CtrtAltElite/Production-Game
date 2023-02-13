#pragma once
#include "Agent.h"
#include "Obstacle.h"

class Sardine final : public Agent, public Obstacle
{
public:
    Sardine();
    void Draw() override;
    void Update() override;
    void Clean() override;
};
