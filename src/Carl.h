#pragma once
#include "Agent.h"
#include "Enemy.h"

class Carl final : public Enemy, public Agent
{
public:
    Carl();
    void Draw() override;
    void Update() override;
    void Clean() override;
private:
    
    
};
