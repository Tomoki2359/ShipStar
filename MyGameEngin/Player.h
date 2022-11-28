#pragma once
#include "Airframe.h"

//■■シーンを管理するクラス
class Player : public Airframe
{
	void StayInside() override;

	const char Initial_ = 0;
	std::vector<char> GhostData_Command_;	//ゴーストとして格納されるデータ
	std::vector<int> GhostData_Frame_;
	short ProgFrame_;							//経過フレーム
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Player(GameObject* parent);

	//デストラクタ
	~Player();

	void UpdateState() override;

	//ゴールしたらStorageにデータを渡す
	void ThrowData();
};