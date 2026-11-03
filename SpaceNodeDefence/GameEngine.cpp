#include "GameEngine.h"
#include <algorithm>
void GameEngine::spawn(std::unique_ptr<IGameObject> object)
{
	std::lock_guard<std::mutex> lock(mtx_);
	storage_.push_back(std::move(object));
}

void GameEngine::tick()
{
	std::lock_guard<std::mutex> lock(mtx_);
	for (const auto& object : storage_)
	{
		object->update();

	}
	for (size_t i = 0; i < storage_.size(); i++)
	{
		for (size_t j = i+1; j < storage_.size(); j++)
		{
			if((storage_[i]->getX() == storage_[j]->getX()) 
				&& (storage_[i]->getY() == storage_[j]->getY()))
			{
				storage_[i]->onCollision();
				storage_[j]->onCollision();
			}
		}
	}
	std::erase_if(storage_, [this](const std::unique_ptr<IGameObject>& obj) {
		if (obj->isDead()) {
			if (obj->isPlayer())
			{
				is_running_ = false;
			}
			return true;
		}
		return false;
		});

}

std::vector<RenderData> GameEngine::getSnapshot()
{
	std::vector<RenderData> snapshot;
	snapshot.reserve(storage_.size());

	for (const auto& obj : storage_)
	{
		RenderData data
		{
			.x = obj->getX(),
			.y = obj->getY(),
			.symbol = obj->getSymbol()
		};
		snapshot.push_back(data);
	}
	return snapshot;
}
