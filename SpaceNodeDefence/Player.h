#pragma once
#include "IGameObject.h"
#include <string>
class Player : public IGameObject {
private:
	int x, y;
	bool is_dead = false;
	int screen_width_;
public:
	Player(int x, int y, int screen_width) : x(x), y(y), screen_width_(screen_width) {}
	void moveLeft();
	void moveRight();
	void update() override;
	 int getX() const override;
	 int getY() const override;
	 bool isDead() const override;
	 void onCollision() override;
	 std::string getSymbol() const override;
	 bool isPlayer() const override { return true; }
};