#pragma once
#include "../Engine/GameObject.h"
#include "BodyParts.h"
#include "CookpitParts.h"
#include "EnginParts.h"
#include "WingParts.h"

//�X�^�[�g�E�S�[�����C���ɒu���I�u�W�F�N�g
class PartsUnion : public GameObject
{
	int hModel_;    //���f���ԍ�
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PartsUnion(GameObject* parent);

	//�f�X�g���N�^
	~PartsUnion();

	//������
	void Initialize() override;

	//�`��
	void Draw() override;

	//�@�̂���
	void RotationParts();

	void TransPos();
};