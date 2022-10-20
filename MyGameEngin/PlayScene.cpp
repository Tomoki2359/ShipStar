#include "PlayScene.h"
#include "Building.h"
#include "Computer.h"
#include "Course.h"
#include "CourseOutObject.h"
#include "GoalObject.h"
#include "Navigation.h"
#include "Player.h"
#include "Image/PlayBackground.h"
#include "Observer.h"


//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"), PlayerList_(), CallNav_(NULL), UdCobj_(NULL),hPict_1(-1), hPict_2(-1), hPict_3(-1), timer(0),Start_(false)
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
	Instantiate<CourseOutObject>(this);
	Instantiate<Observer>(this);
	Instantiate<Building>(this);
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
		Initcomprete_ = true;
	}
	else if(!Initcomprete_ && CallNav_ < 5)
	{
		CallNav_++;
	}

	Player* pPlayer = (Player*)FindObject("Player");

	/*if (pPlayer->GetStart() && UdCobj_ > 300)
	{
		Navigation* pNav = (Navigation*)FindObject("Navigation");
		CourseOutObject* pCobj = (CourseOutObject*)FindObject("CourseOutObject");
		pCobj->SetPosition(pNav->GetLeft());
		UdCobj_ = NULL;
	}*/
	if (pPlayer->GetisGoal())
	{
		SCENE_CHANGE(SCENE_ID_RESULT);
	}
	//UdCobj_++;

}

//描画
void PlayScene::Draw()
{
	
}

//開放
void PlayScene::Release()
{
}

void PlayScene::SetStart(bool start)
{
	Start_ = start;
}

bool PlayScene::GetStart()
{
	return Start_;
}
