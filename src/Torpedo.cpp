﻿#include "Torpedo.h"
#include "Projectile.h"
#include "Camera.h"
#include "Game.h"
#include "TextureManager.h"
#include "Util.h"

TorpedoPool::TorpedoPool()
{ }

std::vector<Torpedo*> TorpedoPool::GetPool()
{
    return m_torpedoes;
}

void TorpedoPool::Fire()
{
    m_torpedoes.push_back(new Torpedo());
}

void TorpedoPool::Update()
{
    for(unsigned i = 0; i < m_torpedoes.size(); i++)
    {
        if (m_torpedoes[i]->GetDeleteMe() == true) // If we need to delete the torpedoes
        {
            delete m_torpedoes[i];
            m_torpedoes[i] = nullptr;
            m_torpedoes.erase(i + m_torpedoes.begin());
            m_torpedoes.shrink_to_fit();
        } else
        {
            m_torpedoes[i]->Update();
        }
    }
}

void TorpedoPool::Clean()
{}

void TorpedoPool::Draw()
{
    for (Torpedo* torpedo : m_torpedoes)
    {
        torpedo->Draw();
    }
}

Torpedo::Torpedo()
{
    SetPlayer(Game::Instance().GetPlayer());
    Start();
}
void Torpedo::Draw()
{
    // If we are in debug mode, draw the collider rect.
    if(Game::Instance().GetDebugMode())
    {
        Util::DrawRect(Camera::Instance().CameraDisplace(this) -
                glm::vec2(this->GetWidth() * 0.5f, this->GetHeight() * 0.5f),
                this->GetWidth(), this->GetHeight());
    }
    // draw the target
    if(m_isExploded)
    {
        TextureManager::Instance().Draw("explosion", Camera::Instance().CameraDisplace(this), GetTransform()->rotation.r*Util::Rad2Deg, 255, true);
    }
    else
    {
        TextureManager::Instance().Draw("torpedo", Camera::Instance().CameraDisplace(this), GetTransform()->rotation.r*Util::Rad2Deg, 255, true);
    }
    
}
void Torpedo::Start()
{
    // Getting sprite + setting transform.
    TextureManager::Instance().Load("../Assets/textures/Small_Torpedo.png", "torpedo");
    TextureManager::Instance().Load("../Assets/textures/Explosion.png", "explosion");
    SoundManager::Instance().Load("../Assets/audio/hitHurt.wav", "hitHurt", SoundType::SOUND_SFX);
    SoundManager::Instance().Load("../Assets/audio/submarineShoot.wav", "subShoot", SoundType::SOUND_SFX);
    SoundManager::Instance().PlaySound("subShoot");
    SetWidth(20);
    SetHeight(20);
    // Setting velocity and speed
    SetVeloDamp({0.9975,0.9975});
    SetSpeed(400.0f);
    SetMaxSpeed(500.0f);
    // Setting specific stats (dmg, delete buffer, etc.) as well as getting mouse position
    m_mousePos = Util::GetMousePos();
    SetDeleteBuffer(100.0f);
    SetDamage(50.0f);
    SetExplodeAfter(1.35f);
    m_deleteAfter = 0.1f;
    // Setting source of projectile and the type, as well as setting the rotation, position, and velocity.
    SetProjectileSource(GetPlayer());
    SetType(GameObjectType::TORPEDO);
    GetTransform()->rotation.r= GetPlayer()->GetTransform()->rotation.r;
    GetRigidBody()->velocity+= glm::vec2{cos(GetPlayer()->GetTransform()->rotation.r)*GetSpeed(),sin(GetPlayer()->GetTransform()->rotation.r)*GetSpeed()};
    GetTransform()->position = GetPlayer()->GetTransform()->position;
    

    //debug
    //std::cout << "Spawned projectile at:" << GetTransform()->position.x << " , " << GetTransform()->position.y<<std::endl;
    //std::cout << GetRigidBody()->velocity.x << " , " << GetRigidBody()->velocity.y<<std::endl;
}

void Torpedo::SetExplodeAfter(float explodeAfter)
{
    m_explodeAfter = explodeAfter;
}


float Torpedo::GetExplodeAfter() const
{
    return m_explodeAfter;
}


void Torpedo::Update()
{
    Move();
    if(GetRigidBody()->isColliding||(SDL_GetTicks()-GetStartTime())/1000.0f > GetExplodeAfter())
    {
        if(!m_isExploded)
        {
            SoundManager::Instance().PlaySound("hitHurt");
            m_isExploded = true;
            SetWidth(GetWidth()*2);
            SetHeight(GetHeight()*2);
            m_explodeTime = SDL_GetTicks();
            GetRigidBody()->velocity={0.0f,0.0f};
        }
    }
    if(m_isExploded&&(SDL_GetTicks()-m_explodeTime)/1000.0f > m_deleteAfter)
    {
        SetDeleteMe(true);
    }
}
void Torpedo::Clean()
{ }


