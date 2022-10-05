#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

//■■シーンを管理するクラス
class PlayScene : public GameObject
{
	bool Initcomprete_ = false;
	int CallNav_;
	int UdCobj_;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayScene(GameObject* parent);

	~PlayScene();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	std::list<GameObject*> PlayerList_;
};