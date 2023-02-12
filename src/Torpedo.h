#pragma once
#include "Projectile.h"

class Torpedo final : public Projectile
{
public:
    Torpedo();
    void Draw() override;
    void Update() override;
    void Clean() override;
    void Start() override;
    void Explode();
    void SetExplodeAfter(float explodeAfter);
    float GetExplodeAfter() const;
    
private:
    glm::vec2 m_mousePos;
    float m_explodeAfter;
};
