#include "PlayScene.h"
#include "Course.h"
#include "Player.h"
#include "Computer.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//������
void PlayScene::Initialize()
{
	SetScreen(0, 0, 0);
	Instantiate<Course>(this);
	Instantiate<Player>(this);
	Instantiate<Computer>(this);
	
}

//�X�V
void PlayScene::Update()
{
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