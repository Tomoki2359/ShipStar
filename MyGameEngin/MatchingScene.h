#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
//#include "Image/BackButton.h"
//#include "Image/MatchingStart.h"
//
//enum MATCHING
//{
//	MATCHING_BACK = 0,
//	MATCHING_STRAT,
//	MAX_MATCHING,
//};

//�����V�[�����Ǘ�����N���X
class MatchingScene : public GameObject
{
	//short matching_;
	//bool mouseMoob_;	//�}�E�X�������Ă��邩�ǂ���
	//bool first_;		//�摜�̃|�C���^���w�肵�����ǂ���

	////�}�E�X����
	//XMFLOAT3 mousePos_;		//�O�̃}�E�X�̈ʒu
	//XMFLOAT3 mouseNext_;	//���̃}�E�X�̈ʒu

	////�摜�̃|�C���^
	//BackButton* pBack_;
	//MatchingStart* pStart_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	MatchingScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};