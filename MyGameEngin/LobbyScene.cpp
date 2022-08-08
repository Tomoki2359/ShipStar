#include "LobbyScene.h"

//�R���X�g���N�^
LobbyScene::LobbyScene(GameObject* parent)
	: GameObject(parent, "LobbyScene")
{
}

//������
void LobbyScene::Initialize()
{
	SetScreen(0, 0, 0);
}

//�X�V
void LobbyScene::Update()
{
	SCENE_CHANGE(SCENE_ID_MATCHING);
	SCENE_CHANGE(SCENE_ID_CUSTOM);
}

//�`��
void LobbyScene::Draw()
{
}

//�J��
void LobbyScene::Release()
{
}