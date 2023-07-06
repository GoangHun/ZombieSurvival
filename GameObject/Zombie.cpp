#include "stdafx.h"
#include "Zombie.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "SceneDev1.h"
#include "Player.h"
#include "VertexArrayGo.h"


const std::string Zombie::textureIds[3] =
{
        "graphics/bloater.png",
        "graphics/chaser.png",
        "graphics/crawler.png",
};

const float Zombie::speedStats[3] = { 40.f, 70.f, 20.f };
const int Zombie::hpStats[3] = { 100, 75, 50 };
const int Zombie::damageStats[3] = { 10, 5, 7 };
const float Zombie::attackRateStats[3] = { 2.f, 0.5f, 1.5f };


Zombie::Zombie(const std::string& n)
    : SpriteGo("", n)
{
}

Zombie::~Zombie()
{
}

void Zombie::Init()
{
    SpriteGo::Init();
    SetOrigin(Origins::MC);
}

void Zombie::Release()
{
    SpriteGo::Release();
}

void Zombie::Reset()
{
    SpriteGo::Reset();

    hp = maxHp;
    attackTimer = attackRate;
}

void Zombie::Update(float dt)
{
    SpriteGo::Update(dt);

    if (player == nullptr)
        return;

    float distance = Utils::Distance(player->GetPosition(), position);

    //회전
    direction = look = Utils::Normalize(player->GetPosition() - position);
    sprite.setRotation(Utils::Angle(look));

    if (distance > 5.f)
    {
        //이동
        SetPosition(position + direction * speed * dt);
        //OnCollisionWall();
    }

    /*if (sprite.getGlobalBounds().intersects(player->sprite.getGlobalBounds()))
    {
        Scene* scene = SCENE_MGR.GetCurrScene();
        SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);
        if (sceneDev1 != nullptr)
        {
            sceneDev1->OnDieZombie(this);
        }
    }*/
    
    //공격 딜레이
    attackTimer += dt;
    if (attackTimer > attackRate)
    {
        if (player->isAlive && sprite.getGlobalBounds().intersects(player->sprite.getGlobalBounds()))
        {
            attackTimer = 0.f;
            player->OnHitted(damage);
        }
    }

    
}

void Zombie::Draw(sf::RenderWindow& window)
{
    SpriteGo::Draw(window);
}

void Zombie::SetType(Types t)
{
    zombieType = t;
    int index = (int)zombieType;

    textureId = textureIds[index];
    speed = speedStats[index];
    maxHp = hpStats[index];
    damage = damageStats[index];
    attackRate = attackRateStats[index];
}

Zombie::Types Zombie::GetType() const
{
    return zombieType;
}

void Zombie::SetPlayer(Player* player)
{
    this->player = player;
}

void Zombie::OnHitBullet(int damage)
{
    hp -= damage;
    if (hp <= 0)
    {
        Scene* scene = SCENE_MGR.GetCurrScene();
        SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);
        if (sceneDev1 != nullptr)
        {
            sceneDev1->OnDieZombie(this);
        }
    }
}

void Zombie::SetBackground(VertexArrayGo* background)
{
    this->background = background;
}

//bool Zombie::OnCollisionWall()
//{
//    sf::FloatRect wall = background->vertexArray.getBounds();
//
//    if (wall.top > position.y)
//    {
//        SetPosition(position.x, wall.top);
//        return true;
//    }
//    else if (wall.top + wall.height < position.y)
//    {
//        SetPosition(position.x, wall.top + wall.height);
//        return true;
//    }
//    else if (wall.left > position.x)
//    {
//        SetPosition(wall.left, position.y);
//        return true;
//    }
//    else if (wall.left + wall.width < position.x)
//    {
//        SetPosition(wall.left + wall.width, position.y);
//        return true;
//    }
//    return false;
//}
