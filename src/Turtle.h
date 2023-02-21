#pragma once
#include "Agent.h"
#include "Obstacle.h"

class Turtle final : public Agent, public Obstacle
{
public:
    Turtle();
    void Draw() override;
    void Update() override;
    void Clean() override;
};
