#pragma once
#include "Airframe.h"

class Ghost : public Airframe
{
	std::list<char> GhostData_Command_;	//ゴーストとして格納されるデータ
	std::list<int> GhostData_Frame_;
	short ProgFrame_;							//経過フレーム

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Ghost(GameObject* parent);

	//デストラクタ
	~Ghost();

	void UpdateState() override;

	void StayInside() override;
};

