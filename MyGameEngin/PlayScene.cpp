#include "PlayScene.h"
#include "Building.h"
#include "Computer.h"
#include "Course.h"
#include "Image/CouseMap.h"
#include "Icon/PlayerIcon.h"
#include "Icon/ComputerIcon.h"
#include "GoalObject.h"
#include "Navigation.h"
#include "Player.h"
#include "Image/PlayBackground.h"
#include "Observer.h"
#include "Option.h"
#include "Engine/Time.h"
#include "Ghost.h"


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
	SetScreen(255, 255, 255);
	Instantiate<PlayBackground>(this);
	Instantiate<Course>(this);
	Instantiate<GoalObject>(this);
	Instantiate<Building>(this);
	Instantiate<Observer>(this);
	Instantiate<CouseMap>(this);
	switch (Option::GetMode())				//モードによって呼び出すものを変更
	{
	case MODE_VSCOM:						//Computerと戦うモード
		Instantiate<Player>(this);
		Instantiate<Computer>(this);
		Instantiate<PlayerIcon>(this);
		Instantiate<ComputerIcon>(this);
		break;
	case MODE_SOLO:							//一人プレイ
		Instantiate<Player>(this);
		Instantiate<PlayerIcon>(this);
		break;
	case MODE_REPLAY:						//リプレイ
		Instantiate<Ghost>(this);
		break;
	default:
		break;
	}
	Time::Reset();
}

//更新
void PlayScene::Update()
{

	if (CallNav_ == 2 && !Initcomprete_)	//開始フレームは後ほど調整
	{
		Instantiate<Navigation>(this);
		Initcomprete_ = true;
	}
	else if (!Initcomprete_ && CallNav_ < 5)
	{
		CallNav_++;
	}

	if (Option::GetMode() != MODE_REPLAY)
	{
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
			Time::Lock();
			if (pPlayer != nullptr)
			{
				pPlayer->ThrowData();
			}
			SCENE_CHANGE(SCENE_ID_RESULT);
		}
		SAFE_RELEASE(pPlayer);
		//UdCobj_++;

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

void PlayScene::SetStart(bool start)
{
	Start_ = start;
}

bool PlayScene::GetStart()
{
	return Start_;
}
