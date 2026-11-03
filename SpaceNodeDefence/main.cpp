#include "Logger.h"
#include <thread>
#include <functional>
#include "GameEngine.h"
#include <iostream>
void renderLoop(GameEngine& engine)
{
	std::vector<RenderData> prev_snapshot;
	while (true) {
		auto current_snapshot = engine.getSnapshot();
		for (auto& symbol : prev_snapshot)
		{
			std::cout << "\033[" << symbol.y+1 << ';' << symbol.x+1 << "H" << ' ';
		}
		for (auto& symbol : current_snapshot)
		{
			std::cout << "\033[" << symbol.y+1 << ';' << symbol.x+1 << "H" << symbol.symbol;
		}
		prev_snapshot = std::move(current_snapshot);
		std::cout.flush();
		
		//ограничение 30 fps
		std::this_thread::sleep_for(std::chrono::microseconds(33));
	}
}

void physicsLoop(GameEngine& engine)
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(100));
	}
}
int main(void)
{
	Logger logger;
	GameEngine engine(logger);
	std::cout << "\033[2J\033[H"; //очищаем экран на старте

	std::thread physics_thread(physicsLoop, std::ref(engine));
	logger.log_i("Starting main thread..");
	renderLoop(engine);
	physics_thread.join();

	logger.flush("game_debug.log");
}