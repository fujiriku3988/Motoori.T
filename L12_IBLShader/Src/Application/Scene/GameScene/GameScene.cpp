#include "GameScene.h"
#include"../SceneManager.h"

#include "../../GameObject/Terrain/Terrain.h"
#include"../../GameObject/Water/Water.h"
#include "../../GameObject/Character/Character.h"

#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"

// 少数第n位で四捨五入する
void round_n(float& number, int n)
{
	number = number * static_cast<float>(pow(10, n - 1));
	number = round(number);
	number /= static_cast<float>(pow(10, n - 1));
}

void GameScene::Init()
{
	KdShaderManager::Instance().WorkAmbientController().SetAmbientLight({ 0.6f,0.6f,0.6f,1.0f });
	//===================================================================
	// ステージ初期化
	//===================================================================
	std::shared_ptr<Terrain> _terrain = std::make_shared<Terrain>();
	_terrain->Init();
	AddObject(_terrain);

	std::shared_ptr<Water> water = std::make_shared<Water>();
	water->Init();
	AddObject(water);

	//===================================================================
	// キャラクター初期化
	//===================================================================
	std::shared_ptr<Character> _character = std::make_shared<Character>();
	_character->Init();
	_character->RegistHitObject(_terrain);
	AddObject(_character);

	//===================================================================
	// カメラ初期化
	//===================================================================
//	std::shared_ptr<FPSCamera>		_camera = std::make_shared<FPSCamera>();
	std::shared_ptr<TPSCamera>		_camera = std::make_shared<TPSCamera>();
	_camera->Init();
	_camera->SetTarget(_character);
	_camera->RegistHitObject(_terrain);
	_character->SetCamera(_camera);
	AddObject(_camera);
}

void GameScene::Event()
{
}