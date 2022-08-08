#include "TitleScene.h"

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene")
{
}

//������
void TitleScene::Initialize()
{
	SetScreen(0, 0, 0);
}

//�X�V
void TitleScene::Update()
{
	//SCENE_CHANGE(SCENE_ID_LOBBY);
	SCENE_CHANGE(SCENE_ID_PLAY);
}

//�`��
void TitleScene::Draw()
{
}

//�J��
void TitleScene::Release()
{
}