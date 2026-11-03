#include "Logger.h"
#include <thread>
#include <functional>
#include "GameEngine.h"
#include <iostream>
#include "Asteroid.h"
#include "Player.h"
#include <conio.h>
#include <Windows.h>

#define ASTEROID_COUNT (5U)

void renderLoop(GameEngine& engine, Player* hero)
{
	std::vector<RenderData> prev_snapshot;
	while (engine.isRunning()) {
		if (_kbhit())
		{
			char ch = _getch();
			if (ch == 'a') hero->moveLeft();
			if (ch == 'd') hero->moveRight();
		}
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

void physicsLoop(GameEngine& engine, int screen_width, int screen_height)
{
	int spawn_counter = 0;
	while (engine.isRunning())
	{
		AsteroidFactory factory;

		if (spawn_counter++ == 200) {
			spawn_counter = 0;
			engine.spawn(factory.createRandom(screen_width, screen_height));
		}
		engine.tick();
		std::this_thread::sleep_for(std::chrono::microseconds(100));
	}
}
int main(void)
{
	Logger logger;
	GameEngine engine(logger);

	//получаем ширину и высоту консоли
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int screen_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int screen_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	auto player = std::make_unique<Player>(10, 20, screen_width);
	Player* hero = player.get(); //слабый указатель для управления
	engine.spawn(std::move(player));
	std::cout << "\033[2J\033[H"; //очищаем экран на старте
	AsteroidFactory factory;
	for (size_t i = 0; i < ASTEROID_COUNT; i++)
	{
		engine.spawn(factory.createRandom(screen_width, screen_height));
	}

	std::thread physics_thread(physicsLoop, std::ref(engine), screen_width, screen_height);
	logger.log_i("Starting main thread..");
	renderLoop(engine, hero);
	physics_thread.join();

	logger.flush("game_debug.log");
	std::cout << "\033[? 25h";
	std::cout << "\033[2J\033[H";
	std::cout << "GAME OVER!!!\n";
	
}