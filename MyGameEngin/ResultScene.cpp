#include "ResultScene.h"

//�R���X�g���N�^
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene")
{
}

//������
void ResultScene::Initialize()
{
	SetScreen(0, 0, 0);
}

//�X�V
void ResultScene::Update()
{
	SCENE_CHANGE(SCENE_ID_LOBBY);
}

//�`��
void ResultScene::Draw()
{
}

//�J��
void ResultScene::Release()
{
}