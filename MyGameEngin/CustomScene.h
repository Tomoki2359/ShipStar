#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Image/OKButton.h"
#include "Image/BackButton.h"
#include "Image/FixeButton.h"
#include "Image/CurrentStatus.h"
#include "Image/PartsList.h"
#include "Image/OriginalStatus.h"
#include "Image/ChangeStatus.h"

enum CUSTOM
{
	CUSTOM_BACK = 0,
	CUSTOM_OK,
	MAX_CUSTOM,
};

//�����V�[�����Ǘ�����N���X
class CustomScene : public GameObject
{
	short custom_;
	bool change_;	//�{���ɕύX���邩�ǂ���
	bool mouseMoob_;	//�}�E�X�������Ă��邩�ǂ���
	bool first_;		//�摜�̃|�C���^���w�肵�����ǂ���

	//�}�E�X����
	XMFLOAT3 mousePos_;		//�O�̃}�E�X�̈ʒu
	XMFLOAT3 mouseNext_;	//���̃}�E�X�̈ʒu

	//�摜�̃|�C���^
	BackButton* pBack_;
	OKButton* pOK_;
	CurrentStatus* pCurrent_;
	PartsList* pParts_;
	FixeButton* pFixe_;
	OriginalStatus* pOriginal_;
	ChangeStatus* pChange_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	CustomScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void BeforeChange();

	void AfterChange();
};