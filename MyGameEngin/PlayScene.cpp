#include "PlayScene.h"
#include "Computer.h"
#include "Course.h"
#include "CourseOutObject.h"
#include "GoalObject.h"
#include "Navigation.h"
#include "Player.h"
#include "Image/PlayBackground.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"), PlayerList_(), CallNav_(NULL)
{
}

PlayScene::~PlayScene()
{
	PlayerList_.clear();
}

//初期化
void PlayScene::Initialize()
{
	char PlayerNum = NULL;
	PlayerList_.clear();
	SetScreen(255, 255, 255);
	Instantiate<PlayBackground>(this);
	Instantiate<Course>(this);
	Instantiate<GoalObject>(this);
	PlayerList_.push_back(Instantiate<Player>(this));
	PlayerNum += (char)PlayerList_.size();
	while (PlayerNum < 2)
	{
		PlayerList_.push_back(Instantiate<Computer>(this));
		PlayerNum++;
	}
	

}

//更新
void PlayScene::Update()
{
	
	
	if (CallNav_ == 2 && !Initcomprete_)	//開始フレームは後ほど調整
	{
		Instantiate<Navigation>(this);
		Navigation* pNav = (Navigation*)FindObject("Navigation");
		for (auto it = pNav->Checkpoint_.begin(); it != pNav->Checkpoint_.end(); it++)
		{
			GameObject* pObj = Instantiate<CourseOutObject>(this);
			pObj->SetPosition(*it);
		}
		Initcomprete_ = true;
	}
	else if(!Initcomprete_ && CallNav_ < 5)
	{
		CallNav_++;
	}

	Player* pPlayer = (Player*)FindObject("Player");
	if (pPlayer->GetisGoal())
	{
		SCENE_CHANGE(SCENE_ID_RESULT);
	}
	
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}