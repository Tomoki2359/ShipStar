#include "MatchingScene.h"

//�R���X�g���N�^
MatchingScene::MatchingScene(GameObject* parent)
	: GameObject(parent, "MatchingScene")
{
}

//������
void MatchingScene::Initialize()
{
	SetScreen(0, 0, 0);
}

//�X�V
void MatchingScene::Update()
{
	//SCENE_CHANGE(SCENE_ID_LOBBY);
	//SCENE_CHANGE(SCENE_ID_PLAY);
}

//�`��
void MatchingScene::Draw()
{
}

//�J��
void MatchingScene::Release()
{
}