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
    void SetExplodeAfter(float explodeAfter);
    [[nodiscard]] float GetExplodeAfter() const;

private:
    glm::vec2 m_mousePos;
    float m_explodeAfter;
    Uint32 m_explodeTime;
    float m_deleteAfter;
    bool m_isExploded;
};

class TorpedoPool final : public DisplayObject
{
public:
    TorpedoPool();
    std::vector<Torpedo*> GetPool();

    void Fire();

private:
    // Just overrides of the basic functions 
    void Update() override;
    void Clean() override;
    void Draw();

    std::vector<Torpedo*> m_torpedoes;
};


