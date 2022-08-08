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
	Instantiate<Player>(this);
	Instantiate<Computer>(this);
	Instantiate<Course>(this);
}

//�X�V
void PlayScene::Update()
{
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}