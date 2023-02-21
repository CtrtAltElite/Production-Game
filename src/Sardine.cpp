#include "Sardine.h"

Sardine::Sardine()
{
    SetType(GameObjectType::SARDINE);
}

void Sardine::Draw()
{
    Obstacle::Draw();
}

void Sardine::Update()
{
    Obstacle::Update();
}

void Sardine::Clean()
{
    Obstacle::Clean();
}
