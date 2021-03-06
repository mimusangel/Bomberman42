#include "Game/SceneLoader.hpp"
#include "Core/SceneManager.hpp"
#include "Game/SceneRandom.hpp"
#include "Game/SceneMain.hpp"
#include "Core/SceneManager.hpp"
#include "Game/Level1.hpp"
#include "Game/Level2.hpp"
#include "Game/Level3.hpp"
#include "Game/Level4.hpp"
#include "Game/Level5.hpp"
#include "Game/Level6.hpp"
#include "Game/LevelEnd.hpp"
#include "Game/Versus1.hpp"
#include "Game/Versus2.hpp"
#include "Game/Versus3.hpp"

namespace Game
{
	std::map<std::string, LoadScene> SceneLoader::nameToLoad = {
		{"SceneMain", BeerEngine::SceneManager::LoadScene<SceneMain>},
		{"Level1", BeerEngine::SceneManager::LoadScene<Level1>},
		{"Level2", BeerEngine::SceneManager::LoadScene<Level2>},
		{"Level3", BeerEngine::SceneManager::LoadScene<Level3>},
		{"Level4", BeerEngine::SceneManager::LoadScene<Level4>},
		{"Level5", BeerEngine::SceneManager::LoadScene<Level5>},
		{"Level6", BeerEngine::SceneManager::LoadScene<Level6>},
		{"LevelEnd", BeerEngine::SceneManager::LoadScene<LevelEnd>},
		{"Versus1", BeerEngine::SceneManager::LoadScene<Versus1>},
		{"Versus2", BeerEngine::SceneManager::LoadScene<Versus2>},
		{"Versus3", BeerEngine::SceneManager::LoadScene<Versus3>},
		{"Random", BeerEngine::SceneManager::LoadScene<SceneRandom>},
	};

	void SceneLoader::loadByName(std::string name)
	{
		auto load = nameToLoad.find(name);
		if (load != nameToLoad.end())
			nameToLoad[name]();
		else
			std::cout << "no matching scene!" << std::endl;
	}

	void SceneLoader::load()
	{
		loadByName(name);
	}
}
