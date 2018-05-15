#include <Core/Graphics/Lights/AmbiantLight.hpp>
#include <Core/Graphics/Lights/DirectionalLight.hpp>
#include "Game/SceneTest.hpp"
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
#include "Game/Components/ItemsUI.hpp"

#include "Game/Components/CameraController.hpp"
#include "Game/Components/MouseRayTest.hpp"
#include "Game/Components/BeerRoutineTester.hpp"
#include "Game/CameraTest.hpp"
#include "Core/Graphics/AMaterial.hpp"
#include "Core/Json/Json.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/Graphics/ShaderProgram.hpp"
#include "Game/Assets.hpp"
#include "Core/Graphics/Cubemap.hpp"

void    SceneTest::init(void)
{
	// this->load("test2.scene");
	// this->save("destest.scene");


	// return;

	std::cout << "init test scene" << "\n";

	BeerEngine::Graphics::Cubemap *skyboxCubemap = new BeerEngine::Graphics::Cubemap("assets/skyboxes/pano_1.jpg", 512);
	setSkybox(skyboxCubemap);

	// Shader
	auto shader = Assets::GetShaderProgram("shaders/basic_v.glsl", "shaders/basic_f.glsl");
	BeerEngine::Graphics::AMaterial *material = new BeerEngine::Graphics::AMaterial(shader);
	material->setColor(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));

	// prefab test
	// auto crateGO = addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(10, 0, 5), true);
	// crateGO->save("assets/Prefabs/crate.prefab");

	// auto crate2 = instantiate<BeerEngine::GameObject>("assets/Prefabs/crate.prefab");
	// crate2->transform.position.x += 2;
	// crate2->save("assets/Prefabs/reserializedCrate.prefab");

	// return;
	// cube 1
	// Texture
	BeerEngine::Graphics::Texture *crate = Assets::GetTexture("assets/textures/crate1_diffuse.png");
	BeerEngine::Graphics::Texture *crate_normal = BeerEngine::Graphics::Texture::LoadPNG("assets/textures/crate1_normal.png");
	BeerEngine::Graphics::Texture *crate_bump = BeerEngine::Graphics::Texture::LoadPNG("assets/textures/crate1_bump.png");

	// Material
	auto materialA = new BeerEngine::Graphics::AMaterial(shader);
	materialA->setAlbedo(crate);
	materialA->setNormal(crate_normal);
	materialA->setBump(crate_bump);
	// BeerEngine::Graphics::AMaterial *materialB = new BeerEngine::Graphics::AMaterial(shader);
	// materialB->setAlbedo(crate);
	// materialB->setNormal(crate_normal);
	// BeerEngine::Graphics::AMaterial *materialC = new BeerEngine::Graphics::AMaterial(shader);
	// materialC->setAlbedo(crate);
	// BeerEngine::Graphics::AMaterial *material2 = new BeerEngine::Graphics::AMaterial(shader);
	// material2->setColor(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));
	// material2->setAlbedo(crate);

	// GameObject
	//
	BeerEngine::GameObject *gameObject;
	BeerEngine::Component::MeshRenderer *meshRenderer;
	BeerEngine::Component::ModelRenderer *modelRenderer;

	auto linesGO = instantiate<BeerEngine::GameObject>();
	auto linesRenderer = linesGO->AddComponent<BeerEngine::Component::RaysRenderer>();
	linesGO->name = "lines Holder";

	// Camera
	auto cameraGO = instantiate<BeerEngine::GameObject>();
	cameraGO->name = "Camera";

	auto gameManager = cameraGO->AddComponent<Game::Component::GameManager>();
	auto soundManager = cameraGO->AddComponent<BeerEngine::Audio::AudioSource>();
	gameManager->srcAudio = soundManager;
	
	auto cameraController = cameraGO->AddComponent<Game::Component::CameraController>();
	auto mouseRay = cameraGO->AddComponent<Game::Component::MouseRayTest>();
	mouseRay->linesRenderer = linesRenderer;
	auto uiManager = cameraGO->AddComponent<Game::Component::UIThemeManager>();
	auto inGameMenu = cameraGO->AddComponent<Game::Component::InGameMenu>();
	auto gameOverMenu = cameraGO->AddComponent<Game::Component::GameOverMenu>();
	auto victoryMenu = cameraGO->AddComponent<Game::Component::VictoryMenu>();
	auto timeUI = cameraGO->AddComponent<Game::Component::TimeUI>();
	auto itemsUI = cameraGO->AddComponent<Game::Component::ItemsUI>();

	gameManager->inGameMenu = inGameMenu;
	gameManager->gameOverMenu = gameOverMenu;
	gameManager->victoryMenu = victoryMenu;

	inGameMenu->uiManager = uiManager;
	gameOverMenu->uiManager = uiManager;
	victoryMenu->uiManager = uiManager;

	inGameMenu->setActive(false);
	gameOverMenu->setActive(false);
	victoryMenu->setActive(false);

	timeUI->uiManager = uiManager;
	itemsUI->uiManager = uiManager;

	// Player
	auto playerGO = instantiate<BeerEngine::GameObject>();
	playerGO->name = "player";
	// auto meshRenderer = playerGO->AddComponent<BeerEngine::Component::MeshRenderer>();
	// meshRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);
	// auto playerTex = BeerEngine::Graphics::Texture::LoadPNG("assets/textures/player2.png");
	// auto playerMat = new BeerEngine::Graphics::AMaterial(shader);
	// playerMat->setAlbedo(playerTex);
	// meshRenderer->setMaterial(playerMat);
	// playerGO->transform.scale = glm::vec3(1, 1, 1);
	// auto character = playerGO->AddComponent<Game::Component::Character>();
	// auto playerBreakable = playerGO->AddComponent<Game::Component::Breakable>();
	// auto player = playerGO->AddComponent<Game::Component::Player>();
	// auto routineTester = playerGO->AddComponent<Game::Component::BeerRoutineTester>();
	// auto settings = playerGO->AddComponent<Game::Component::Settings>();
//	meshRenderer = playerGO->AddComponent<BeerEngine::Component::MeshRenderer>();
	modelRenderer = playerGO->AddComponent<BeerEngine::Component::ModelRenderer>();
	modelRenderer->load("assets/models/Run Forward.fbx");
//	modelRenderer->load("assets/models/test.fbx");
//	meshRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);
	auto *playerTex = BeerEngine::Graphics::Texture::LoadPNG("assets/textures/player2.png");
	auto *playerMat = new BeerEngine::Graphics::AMaterial(shader);
	playerMat->setAlbedo(playerTex);
	modelRenderer->addMaterial(0, playerMat);
//	meshRenderer->setMaterial(playerMat);
//	playerGO->transform.position = glm::vec3(0, 0, 0);
	playerGO->transform.scale = glm::vec3(0.03, 0.03, 0.03);
//	playerGO->transform.scale = glm::vec3(0.5, 0.5, 0.5);
	auto *character = playerGO->AddComponent<Game::Component::Character>();
	auto *breakable = playerGO->AddComponent<Game::Component::Breakable>();
	auto *player = playerGO->AddComponent<Game::Component::Player>();
	auto *routineTester = playerGO->AddComponent<Game::Component::BeerRoutineTester>();
	auto *settings = playerGO->AddComponent<Game::Component::Settings>();
	auto playerColl = playerGO->AddComponent<BeerEngine::Component::CircleCollider>();
	auto playerRB2D = playerGO->AddComponent<BeerEngine::Component::RigidBody2D>();
	playerColl->_radius = 0.3;
	auto listener = playerGO->AddComponent<BeerEngine::Audio::AudioListener>();
	playerRB2D->kinematic = BeerEngine::Component::RBType::Static;
	auto as2 = playerGO->AddComponent<BeerEngine::Audio::AudioSource>();
	auto itemAs = playerGO->AddComponent<BeerEngine::Audio::AudioSource>();
	player->srcAudio = as2;
	player->itemSrcAudio = itemAs;
	// itemsUI->player = player;
	gameManager->playerBreakable = breakable;
	modelRenderer->setAnimation(1);
	modelRenderer->setLoopAnimation(true);
	modelRenderer->playAnimation();

	//instantiate map
	auto MapGO = instantiate<BeerEngine::GameObject>();
	MapGO->name = "map";
	auto map = MapGO->AddComponent<Game::Component::Map>();
	map->_player = player;
	map->_shader = shader;
	std::vector<int>  line0{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	std::vector<int>  line1{1,S,8,0,0,0,0,I,0,0,0,0,0,0,8,S,1};
	std::vector<int>  line2{1,8,1,0,1,0,1,0,1,0,1,0,1,0,1,8,1};
	std::vector<int>  line3{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
	std::vector<int>  line4{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
	std::vector<int>  line5{1,0,0,0,0,0,0,I,0,0,0,0,0,0,0,0,1};
	std::vector<int>  line6{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
	std::vector<int>  line7{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
	std::vector<int>  line8{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
	std::vector<int>  line9{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
	std::vector<int> line10{1,8,1,0,1,0,1,0,1,0,1,0,1,0,1,8,1};
	std::vector<int> line11{1,S,8,0,0,0,0,0,0,0,0,0,0,0,8,S,1};
	std::vector<int> line12{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	std::vector<std::vector<int>> tab{line0,line1,line2,line3,line4,line5,line6,line7,line8,line9,line10,line11,line12};
	map->setRandomMap(tab, line0.size(), tab.size());
	// map->drawMap(shader);
	character->map = map;

	// map->addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), BeerEngine::Component::RBType::Kinematic);
	// auto mapCrateGO2 = instantiate<BeerEngine::GameObject>("assets/Prefabs/mapCrate.prefab");
	// std::cout << "mapCrateGO2 name : " << mapCrateGO2->name << "\n";
	// mapCrateGO2->save("assets/Prefabs/reMapCrate.prefab");

	//test obj house
	auto objet = instantiate<BeerEngine::GameObject>();
	objet->name = "house";
	meshRenderer = objet->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh("assets/models/HouseOBJ/house_01.obj");
	auto objetTex = BeerEngine::Graphics::Texture::LoadJPG("assets/models/HouseOBJ/DSC_5871_.jpg");
	auto objetMat = new BeerEngine::Graphics::AMaterial(shader);
	objetMat->setAlbedo(objetTex);
	meshRenderer->setMaterial(objetMat);
	objet->transform.position = glm::vec3(-5.5, 0, 16.5);
	objet->transform.scale = glm::vec3(0.05, 0.05, 0.05);
	objet->transform.rotation = glm::vec3(0, 0, 0);

	auto house2 = instantiate<BeerEngine::GameObject>();
	house2->name = "house2";
	meshRenderer = house2->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh("assets/models/HouseOBJ/house_01.obj");
	auto house2Tex = BeerEngine::Graphics::Texture::LoadJPG("assets/models/HouseOBJ/DSC_5871_.jpg");
	auto house2Mat = new BeerEngine::Graphics::AMaterial(shader);
	house2Mat->setAlbedo(house2Tex);
	meshRenderer->setMaterial(house2Mat);
	house2->transform.position = glm::vec3(4.5, 0, 14.4);
	house2->transform.scale = glm::vec3(0.05, 0.05, 0.05);
	house2->transform.rotation = glm::vec3(0, 3.14, 0);

	// Audio test
	// auto al = cameraGO->AddComponent<BeerEngine::Audio::AudioListener>();

	// auto Old = instantiate<BeerEngine::GameObject>();
	// Old->name = "old";
	// modelRenderer = Old->AddComponent<BeerEngine::Component::ModelRenderer>();
	// modelRenderer->load("assets/models/Old_man/muro.obj");
	// // modelRenderer->loadMaterials(shader);
	// auto *OldTex = BeerEngine::Graphics::Texture::LoadTGA("assets/models/Old_man/Muro_head_dm.tga");
	// auto *OldMat = new BeerEngine::Graphics::AMaterial(shader);
	// OldMat->setAlbedo(OldTex);
	// modelRenderer->addMaterial(0, OldMat);
	// Old->transform.position = glm::vec3(1, 0.5, 10);
	// Old->transform.scale = glm::vec3(0.012, 0.012, 0.012);
	// Old->transform.rotation = glm::vec3(0, -3.14, 0);
	// BeerEngine::Audio::AudioClip   clip("assets/sounds/castle_wav.wav");
	// as->setBuffer(clip.getBuffer());
	// as->setVolume(1);
	// as->setPitch(1);
	// as->setLooping(true);
	// as->play();

	BeerEngine::Graphics::DirectionalLight *light = instantiateLight<BeerEngine::Graphics::DirectionalLight>();
	light->setDirection(glm::normalize(glm::vec3(1, 1, -1)));
	light->setColor(glm::vec4(1, 0.9, 0.8, 1));
	light->setIntensity(1.0f);

	// plane
	BeerEngine::GameObject *mapGO;
	mapGO = instantiate<BeerEngine::GameObject>();
	BeerEngine::Component::MeshRenderer *mapMeshRenderer = mapGO->AddComponent<BeerEngine::Component::MeshRenderer>();
	mapMeshRenderer->setMesh(BeerEngine::Graphics::Graphics::plane);
	mapMeshRenderer->setMaterial(material);
	auto planeTex = BeerEngine::Graphics::Texture::LoadJPG("assets/textures/ground_color.png");
	auto planeMat = new BeerEngine::Graphics::AMaterial(shader);
	planeMat->setAlbedo(planeTex);
	mapMeshRenderer->setMaterial(planeMat);
	mapGO->transform.position = glm::vec3(-3, 0, 6);
	mapGO->transform.scale = glm::vec3(40, 1, 40);

	// loaded here because it cannot be loaded in the start of a later instantiated object
	// Game::Component::Bomb::explosionTexture = Assets::GetTexture("assets/textures/ParticleAtlas.png");

	// // ==================
	// // === ANIMATIONS ===
	// // ==================

	// auto dragon = instantiate<BeerEngine::GameObject>();
	// dragon->name = "dragon";
	// modelRenderer = dragon->AddComponent<BeerEngine::Component::ModelRenderer>();
	// modelRenderer->load("assets/models/BlackDragon/Dragon_Baked_Actions.fbx");
	// auto *dragonTex = BeerEngine::Graphics::Texture::LoadJPG("assets/models/BlackDragon/textures/Dragon_Bump_Col2.jpg");
	// auto *dragonMat = new BeerEngine::Graphics::AMaterial(animShader);
	// dragonMat->setAlbedo(dragonTex);
	// modelRenderer->addMaterial(0, dragonMat);
	// dragon->transform.position = glm::vec3(0, 8, 5);
	// dragon->transform.scale = glm::vec3(0.0005, 0.0005, 0.0005);
	// dragon->transform.rotation = glm::vec3(0, 0, 0);
	// modelRenderer->setAnimation(1);
	// modelRenderer->playAnimation();
	// modelRenderer->setLoopAnimation(true);

	// // auto Old = instantiate<BeerEngine::GameObject>();
	// // Old->name = "old";
	// // modelRenderer = Old->AddComponent<BeerEngine::Component::ModelRenderer>();
	// // modelRenderer->load("assets/models/Old_man/muro.obj");
	// // auto *OldTex = BeerEngine::Graphics::Texture::LoadTGA("assets/models/Old_man/Muro_head_dm.tga");
	// // auto *OldMat = new BeerEngine::Graphics::AMaterial(animShader);
	// // OldMat->setAlbedo(OldTex);
	// // modelRenderer->addMaterial(0, OldMat);
	// // Old->transform.position = glm::vec3(1, 0.5, 10);
	// // Old->transform.scale = glm::vec3(0.012, 0.012, 0.012);
	// // Old->transform.rotation = glm::vec3(0, -3.14, 0);

	// // ==================
	// // =/= ANIMATIONS =\=
	// // ==================

	std::cout << "saving scene.." << "\n";
	this->save("assets/scenes/level1.scene");

	// this->save("test2.scene");
	// std::cout << "init end" << "\n";
	// std::cout << "GameObject List Size : " << getGameObjects().size() << std::endl;
}
