#include "PlayScene.h"
#include "Course.h"
#include "Player.h"
#include "Computer.h"
#include "Navigation.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"), PlayerList_()
{
}

//������
void PlayScene::Initialize()
{
	char PlayerNum = NULL;
	PlayerList_.clear();
	SetScreen(0, 0, 0);
	Instantiate<Course>(this);
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
	/*static int j = 0;
	j++;
	if (j == 2 && !Initcomprete_)
	{
		Instantiate<Navigation>(this);
		Initcomprete_ = true;
	}*/

	//SCENE_CHANGE(SCENE_ID_RESULT);
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}