#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"

#include "Engine/Particle.h"

//■■シーンを管理するクラス
class PlayScene : public GameObject
{
	bool Initcomprete_ = false;
	int CallNav_;
	int UdCobj_;
	bool Start_ = false;
	int hPict_1;    //画像番号
	int hPict_2;    //画像番号
	int hPict_3;    //画像番号
	int timer;

	Particle* pParticle_;
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

	//セッター
	void SetStart(bool start);

	//ゲッター
	bool GetStart();

	std::list<GameObject*> PlayerList_;
};