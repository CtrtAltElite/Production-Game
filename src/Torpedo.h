#pragma once
#include "Projectile.h"

class Torpedo final : public Projectile
{
public:
    Torpedo(Player* player);
    void Draw() override;
    void Update() override;
    void Clean() override;
    void Start() override;
private:
    glm::vec2 m_mousePos;
};
