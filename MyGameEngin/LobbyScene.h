#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

enum LOBBY
{
	LOBBY_COURSE = 0,
	LOBBY_PLAY,
	LOBBY_CUSTOM,
	MAX_LOBBY,
};

//�����V�[�����Ǘ�����N���X
class LobbyScene : public GameObject
{
	short lobby_;
	bool mouseMoob_;
	XMFLOAT3 mousePos_;
	XMFLOAT3 mouseNext_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	LobbyScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};