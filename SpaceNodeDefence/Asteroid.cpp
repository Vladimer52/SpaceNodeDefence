#include "Asteroid.h"
#include <Windows.h>
#include <random>
int Asteroid::getX() const
{
    return static_cast<int>(x);
}

int Asteroid::getY() const
{
    return static_cast<int>(y);
}

bool Asteroid::isDead() const
{
    if (is_dead == true  || y >= screen_height_)
        return true;
    return false;
}

void Asteroid::onCollision()
{
    is_dead = true;
}

void Asteroid::update()
{
    x += dx;
    y += dy;
}

std::string Asteroid::getSymbol() const
{
    return "*";
}

std::unique_ptr<IGameObject> AsteroidFactory::createRandom(int screen_width, int screen_height)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> random_x(1, screen_width);
    std::uniform_real_distribution<float> random_speed(0.005f, 0.015f);
    return std::make_unique<Asteroid>(random_x(gen), 0.0f, random_speed(gen), random_speed(gen), screen_height, screen_width);
}
