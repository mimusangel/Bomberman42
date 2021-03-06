#include <Core/Graphics/Lights/AmbiantLight.hpp>
#include <Core/Graphics/Lights/DirectionalLight.hpp>
#include "Game/SceneRandom.hpp"
#include "Game/Components/Settings.hpp"
#include "Core/IO/FileUtils.hpp"
#include "Core/Component/BoxCollider2D.hpp"
#include "Core/Component/CircleCollider.hpp"
#include "Core/Component/RigidBody2D.hpp"
#include "Core/Component/RaysRenderer.hpp"
#include "Core/Component/ParticleBase.hpp"
#include "Core/Component/ParticleExplode.hpp"
#include "Core/Component/ModelRenderer.hpp"
#include "Core/Graphics/Lights/ALight.hpp"
#include "Core/Audio/AudioSource.hpp"
#include "Game/Components/Player.hpp"
#include "Game/Components/IA.hpp"
#include "Game/Components/Character.hpp"
#include "Game/Components/Item.hpp"
#include "Game/Components/Map.hpp"
#include "Game/Components/Bomb.hpp"
#include "Game/Components/GameManager.hpp"
#include "Game/Components/UIThemeManager.hpp"
#include "Game/Components/InGameMenu.hpp"
#include "Game/Components/GameOverMenu.hpp"
#include "Game/Components/VictoryMenu.hpp"
#include "Game/Components/TimeUI.hpp"
#include "Game/Components/StartTimerUI.hpp"
#include "Game/Components/ItemsUI.hpp"
#include "Game/Components/AudioManager.hpp"

#include "Game/Components/CameraController.hpp"
#include "Game/Components/MouseRayTest.hpp"
#include "Game/Components/BeerRoutineTester.hpp"
#include "Core/Graphics/AMaterial.hpp"
#include "Core/Json/Json.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/Graphics/ShaderProgram.hpp"
#include "Game/Assets.hpp"
#include "Core/Graphics/Cubemap.hpp"
#include "Game/SceneBasics.hpp"

void    SceneRandom::init(void)
{
	// this->load("test2.scene");
	// this->save("destest.scene");


	// return;

	// std::cout << "init test scene" << "\n";

	BeerEngine::Graphics::Cubemap *skyboxCubemap = new BeerEngine::Graphics::Cubemap("assets/skyboxes/pano_1.jpg", 512);
	setSkybox(skyboxCubemap);

	// Shader
	auto shader = Assets::GetShaderProgram("shaders/basic_v.glsl", "shaders/basic_f.glsl");


	// // cube 1
	// // Texture
	// BeerEngine::Graphics::Texture *crate = Assets::GetTexture("assets/textures/crate1_diffuse.png");
	// BeerEngine::Graphics::Texture *crate_normal = BeerEngine::Graphics::Texture::LoadPNG("assets/textures/crate1_normal.png");
	// BeerEngine::Graphics::Texture *crate_bump = BeerEngine::Graphics::Texture::LoadPNG("assets/textures/crate1_bump.png");

	// // Material
	// auto materialA = new BeerEngine::Graphics::AMaterial(shader);
	// materialA->setAlbedo(crate);
	// materialA->setNormal(crate_normal);
	// materialA->setBump(crate_bump);

	// auto linesGO = instantiate<BeerEngine::GameObject>();
	// auto linesRenderer = linesGO->AddComponent<BeerEngine::Component::RaysRenderer>();
	// linesGO->name = "lines Holder";

	// Camera
	auto cameraGO = instantiate<BeerEngine::GameObject>();

	auto soundManager = cameraGO->AddComponent<Game::Component::AudioManager>();
	soundManager->setClip("assets/sounds/ride.ogg");
	soundManager->setLooping(true);
	soundManager->audioType = Game::Component::Music;

	Game::SceneBasics::CreateCameraBasics(cameraGO);

	auto gameManager = cameraGO->GetComponent<Game::Component::GameManager>();
	cameraGO->GetComponent<Game::Component::Settings>()->audioManager = soundManager;
	gameManager->audioManager = soundManager;

	gameManager->storyMode = false;

	cameraGO->GetComponent<Game::Component::VictoryMenu>()->sceneLoader.name = "Random";
	cameraGO->GetComponent<Game::Component::GameOverMenu>()->sceneLoader.name = "Random";
	cameraGO->GetComponent<Game::Component::InGameMenu>()->sceneLoader.name = "Random";

	// cameraGO->GetComponent<Game::Component::LevelInstructions>()->setInstructions({
	// 	{"test instr 1", 2.0}
	// });

	// Player
	auto playerGO = instantiate<BeerEngine::GameObject>();
	Game::SceneBasics::CreatePlayerBasics(playerGO, gameManager, 1);
	auto player = playerGO->GetComponent<Game::Component::Player>();
	auto character = playerGO->GetComponent<Game::Component::Character>();

	//instantiate map
	auto MapGO = instantiate<BeerEngine::GameObject>();
	MapGO->name = "map";
	auto map = MapGO->AddComponent<Game::Component::Map>();
	map->_player = player;
	map->_shader = shader;
	std::vector<int>  line0{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	std::vector<int>  line1{1,S,8,0,0,0,0,0,0,0,0,0,0,0,8,S,1};
	std::vector<int>  line2{1,8,1,0,1,0,1,0,1,0,1,0,1,0,1,8,1};
	std::vector<int>  line3{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
	std::vector<int>  line4{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
	std::vector<int>  line5{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
	std::vector<int>  line6{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
	std::vector<int>  line7{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
	std::vector<int>  line8{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
	std::vector<int>  line9{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
	std::vector<int> line10{1,8,1,0,1,0,1,0,1,0,1,0,1,0,1,8,1};
	std::vector<int> line11{1,S,8,0,0,0,0,0,0,0,0,0,0,0,8,S,1};
	std::vector<int> line12{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	std::vector<std::vector<int>> tab{line0,line1,line2,line3,line4,line5,line6,line7,line8,line9,line10,line11,line12};
	map->setRandomMap(tab, line0.size(), tab.size());
	character->map = map;

	//test obj house
	Game::SceneBasics::GenerateModel(this,
		"house",
		"assets/models/HouseOBJ/house_01.obj",
		"assets/models/HouseOBJ/DSC_5871_.jpg",
		glm::vec3(-5.5, 0, 16.5),
		glm::vec3(0, 0, 0),
		glm::vec3(0.05, 0.05, 0.05)
	);

	// auto objet = instantiate<BeerEngine::GameObject>();
	// objet->name = "house";
	// auto meshRenderer = objet->AddComponent<BeerEngine::Component::MeshRenderer>();
	// meshRenderer->setMesh("assets/models/HouseOBJ/house_01.obj");
	// auto objetTex = Assets::GetTexture("assets/models/HouseOBJ/DSC_5871_.jpg");
	// auto objetMat = new BeerEngine::Graphics::AMaterial(shader);
	// objetMat->setAlbedo(objetTex);
	// meshRenderer->setMaterial(objetMat);
	// objet->transform.position = glm::vec3(-5.5, 0, 16.5);
	// objet->transform.scale = glm::vec3(0.05, 0.05, 0.05);
	// objet->transform.rotation = glm::vec3(0, 0, 0);


	Game::SceneBasics::GenerateModel(this,
		"house2",
		"assets/models/HouseOBJ/house_01.obj",
		"assets/models/HouseOBJ/DSC_5871_.jpg",
		glm::vec3(4.5, 0, 14.4),
		glm::vec3(0, 3.14, 0),
		glm::vec3(0.05, 0.05, 0.05)
	);

	// auto house2 = instantiate<BeerEngine::GameObject>();
	// house2->name = "house2";
	// auto meshRenderer = house2->AddComponent<BeerEngine::Component::MeshRenderer>();
	// meshRenderer->setMesh("assets/models/HouseOBJ/house_01.obj");
	// auto house2Tex = Assets::GetTexture("assets/models/HouseOBJ/DSC_5871_.jpg");
	// auto house2Mat = new BeerEngine::Graphics::AMaterial(shader);
	// house2Mat->setAlbedo(house2Tex);
	// meshRenderer->setMaterial(house2Mat);
	// house2->transform.position = glm::vec3(4.5, 0, 14.4);
	// house2->transform.scale = glm::vec3(0.05, 0.05, 0.05);
	// house2->transform.rotation = glm::vec3(0, 3.14, 0);

	BeerEngine::Graphics::DirectionalLight *light = instantiateLight<BeerEngine::Graphics::DirectionalLight>();
	light->setDirection(glm::normalize(glm::vec3(1, 2, -1)));
	light->setColor(glm::vec4(1, 0.9, 0.8, 1));
	light->setIntensity(1.5f);

	// Plane
	Game::SceneBasics::GeneratePlane(
		this,
		"assets/textures/grass.png",
		glm::vec2(80, 80),
		glm::vec2(0.5, 0.5),
		glm::vec3(-3, 0, 6),
		glm::vec3(40, 1, 40)
	);

	Game::SceneBasics::GenerateDecorations(this, glm::vec2(20, 15), glm::vec2(-20, 0), glm::vec2(10, 20), glm::vec2(-10, 0));

	// std::cout << "saving scene.." << "\n";
	this->save("assets/scenes/random.scene");
}
