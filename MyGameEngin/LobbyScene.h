#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Image/LobbyCourse.h"
#include "Image/LobbyCustom.h"
#include "Image/LobbyPlay.h"

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
	bool mouseMoob_;	//�}�E�X�������Ă��邩�ǂ���
	bool first_;		//�摜�̃|�C���^���w�肵�����ǂ���

	//�}�E�X����
	XMFLOAT3 mousePos_;		//�O�̃}�E�X�̈ʒu
	XMFLOAT3 mouseNext_;	//���̃}�E�X�̈ʒu

	//�摜�̃|�C���^
	LobbyCourse* pCourse_;
	LobbyPlay* pPlay_;
	LobbyCustom* pCustom_;
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