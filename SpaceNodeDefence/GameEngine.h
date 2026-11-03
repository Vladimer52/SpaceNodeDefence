#pragma once
#include <vector>
#include <memory>
#include <mutex>
#include "Logger.h"
#include "IGameObject.h"

struct RenderData {
	int x;
	int y;
	std::string symbol; // для цвета
};



class GameEngine {
private:
	std::vector<std::unique_ptr<IGameObject>> storage_;
	std::mutex mtx_;
	Logger& logger_;
	std::atomic<bool> is_running_{ true };
public:
	bool isRunning() const { return is_running_; }
	explicit GameEngine(Logger& logger) : logger_(logger) {}
	void spawn(std::unique_ptr<IGameObject> object);
	void tick();
	std::vector<RenderData> getSnapshot();
};