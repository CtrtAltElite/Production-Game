#include "Turtle.h"

Turtle::Turtle()
{
    SetType(GameObjectType::TURTLE);
}

void Turtle::Draw()
{
    Obstacle::Draw();
}

void Turtle::Update()
{
    Obstacle::Update();
}

void Turtle::Clean()
{
    Obstacle::Clean();
}
