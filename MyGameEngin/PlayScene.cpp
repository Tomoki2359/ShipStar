#include "PlayScene.h"
#include "Computer.h"
#include "Course.h"
#include "CourseOutObject.h"
#include "GoalObject.h"
#include "Navigation.h"
#include "Player.h"
#include "Image/PlayBackground.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"), PlayerList_(), CallNav_(NULL), UdCobj_(NULL)
{
}

PlayScene::~PlayScene()
{
	PlayerList_.clear();
}

//������
void PlayScene::Initialize()
{
	char PlayerNum = NULL;
	PlayerList_.clear();
	SetScreen(255, 255, 255);
	Instantiate<PlayBackground>(this);
	Instantiate<Course>(this);
	Instantiate<GoalObject>(this);
	Instantiate<CourseOutObject>(this);
	PlayerList_.push_back(Instantiate<Player>(this));
	PlayerNum += (char)PlayerList_.size();
	while (PlayerNum < 2)
	{
		PlayerList_.push_back(Instantiate<Computer>(this));
		PlayerNum++;
	}


}

//�X�V
void PlayScene::Update()
{
	if (CallNav_ == 2 && !Initcomprete_)	//�J�n�t���[���͌�قǒ���
	{
		Instantiate<Navigation>(this);
		Initcomprete_ = true;
	}
	else if(!Initcomprete_ && CallNav_ < 5)
	{
		CallNav_++;
	}

	Player* pPlayer = (Player*)FindObject("Player");

	if (pPlayer->GetStart() && UdCobj_ > 300)
	{
		Navigation* pNav = (Navigation*)FindObject("Navigation");
		CourseOutObject* pCobj = (CourseOutObject*)FindObject("CourseOutObject");
		pCobj->SetPosition(pNav->GetLeft());
		UdCobj_ = NULL;
	}
	if (pPlayer->GetisGoal())
	{
		SCENE_CHANGE(SCENE_ID_RESULT);
	}
	
	UdCobj_++;
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}