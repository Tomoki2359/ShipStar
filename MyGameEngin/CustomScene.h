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
#include "Parts/PartsUnion.h"

enum BEFORE_CUSTOM
{
	BEFORE_BACK = 0,
	BEFORE_OK,
	BEFORE_ENGIN,
	BEFORE_BODY,
	BEFORE_WING,
	BEFORE_COOKPIT,
	BEFORE_MAX,
};

enum AFTER_CUSTOM
{
	AFTER_BACK = 0,
	AFTER_OK,
	AFTER_MAX,
};

//�����V�[�����Ǘ�����N���X
class CustomScene : public GameObject
{
	short custom_;
	bool change_;	//�{���ɕύX���邩�ǂ���
	bool mouseMoob_;	//�}�E�X�������Ă��邩�ǂ���
	bool first_;		//�摜�̃|�C���^���w�肵�����ǂ���

	//�@�̂̃p�[�c�ԍ�
	int engineNum_;
	int bodyNum_;
	int wingNum_;
	int cookpitNum_;

	//�@�̂̐F�ԍ�
	int engineColor_;
	int bodyColor_;
	int wingColor_;
	int cookpitColor_;

	//���x�֘A
	float partsBrightness_;
	bool isBrightness_;

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

	//�@�̂̃p�[�c�̃|�C���^
	EnginParts* pEngin_;
	BodyParts* pBody_;
	WingParts* pWing_;
	CookpitParts* pCookpit_;
	PartsUnion* pUnion_;
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

	//�ύX�O
	void BeforeChange();

	//�ύX��
	void AfterChange();

	//�p�[�c�̕ύX
	//����:������ �@�̂̃p�[�c:������ �p�[�c�ԍ�:��O���� �p�[�c�̐F�ԍ�
	void PartsChange(Parts* parts, int& partsNum, int& partsColor);
};