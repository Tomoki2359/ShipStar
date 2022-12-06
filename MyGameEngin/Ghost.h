#pragma once
#include "Airframe.h"

class Ghost : public Airframe
{
	std::list<char> GhostData_Command_;	//ゴーストとして格納されるデータ
	std::list<int> GhostData_Frame_;
	short ProgFrame_;							//経過フレーム
	const char ReplayEnd_ = 2;		//リプレイを終了させる
	char Endcount_;					//ReplayEnd以上になったらリプレイを強制終了させる

	void CallOnly();				//現在のモードがリプレイまたはゴーストのみならば呼び出される
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Ghost(GameObject* parent);

	//デストラクタ
	~Ghost();

	void UpdateState() override;

	void StayInside() override;
};

