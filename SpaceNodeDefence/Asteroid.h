#pragma once
#include "IGameObject.h"
#include <string>
#include <memory>

class Asteroid : public IGameObject {
private:
	float x, y;
	float dx, dy; //скорости
	bool is_dead = false;
	int screen_height_;
	int screen_width_;
public:
	Asteroid(float x, float y, float dx, float dy, int height, int width) : x(x), y(y), dx(dx), dy(dy), screen_height_(height), screen_width_(width) {}
	 bool isDead() const override;
	 void onCollision() override;
	 void update() override;
	 std::string getSymbol() const override;
	 int getX() const override;
	 int getY() const override;
};

class AsteroidFactory
{
public:
	std::unique_ptr<IGameObject> createRandom(int screen_width, int screen_height);
};