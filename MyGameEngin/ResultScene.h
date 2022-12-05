#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Image/BackButton.h"
#include "Image/RetryButton.h"

enum RESULT
{
	RESULT_BACK = 0,
	RESULT_OK,
	MAX_RESULT,
};

//�����V�[�����Ǘ�����N���X
class ResultScene : public GameObject
{
	int hPict_[10];
	short result_;
	bool mouseMoob_;	//�}�E�X�������Ă��邩�ǂ���
	bool first_;		//�摜�̃|�C���^���w�肵�����ǂ���

	//�}�E�X����
	XMFLOAT3 mousePos_;		//�O�̃}�E�X�̈ʒu
	XMFLOAT3 mouseNext_;	//���̃}�E�X�̈ʒu

	//�摜�̃|�C���^
	BackButton* pBack_;
	RetryButton* pOK_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ResultScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};