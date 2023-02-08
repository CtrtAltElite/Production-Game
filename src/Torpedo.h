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
    void Move() override;
private:
    glm::ivec2 m_mousePos;
};
