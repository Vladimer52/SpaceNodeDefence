#pragma once
#include <string>

class IGameObject {
public:
	virtual ~IGameObject() = default;
	virtual int getX() const = 0;
	virtual int getY() const = 0;
	virtual bool isDead() const = 0;
	virtual void onCollision() = 0;
	virtual void update() = 0;
	virtual std::string getSymbol() const = 0;
	virtual bool isPlayer() const { return false; }
};