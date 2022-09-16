#include "PlayScene.h"
#include "Computer.h"
#include "Course.h"
#include "GoalObject.h"
#include "Navigation.h"
#include "Player.h"
#include "Image/PlayBackground.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"), PlayerList_()
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
	static int j = 0;
	j++;
	if (j == 2 && !Initcomprete_)	//�J�n�t���[���͌�قǒ���
	{
		Instantiate<Navigation>(this);
		Initcomprete_ = true;
	}

	Player* pPlayer = (Player*)FindObject("Player");
	if (pPlayer->GetisGoal())
	{
		SCENE_CHANGE(SCENE_ID_RESULT);
	}
	
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}