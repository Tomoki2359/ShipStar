#include "CustomScene.h"

//�R���X�g���N�^
CustomScene::CustomScene(GameObject* parent)
	: GameObject(parent, "CustomScene")
{
}

//������
void CustomScene::Initialize()
{
	SetScreen(0, 0, 0);
}

//�X�V
void CustomScene::Update()
{
	//SCENE_CHANGE(SCENE_ID_LOBBY);
}

//�`��
void CustomScene::Draw()
{
}

//�J��
void CustomScene::Release()
{
}