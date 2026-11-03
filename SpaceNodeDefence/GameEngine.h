#pragma once
#include <vector>
#include <memory>
#include <mutex>
#include "Logger.h"

struct RenderData {
	int x;
	int y;
	std::string symbol; // для цвета
};

class IGameObject {
public:
	virtual ~IGameObject() = default;
	virtual int getX() const = 0;
	virtual int getY() const = 0;
	virtual bool isDead() const = 0;
	virtual void onCollision() = 0;
	virtual void update() = 0;
	virtual std::string getSymbol() const = 0;
};

class GameEngine {
private:
	std::vector<std::unique_ptr<IGameObject>> storage_;
	std::mutex mtx_;
	Logger& logger_;
public:
	explicit GameEngine(Logger& logger) : logger_(logger) {}
	void spawn(std::unique_ptr<IGameObject> object);
	void tick();
	std::vector<RenderData> getSnapshot();
};