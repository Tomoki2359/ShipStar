#pragma once
#include "Engine/GameObject.h"

//�X�^�[�g�E�S�[�����C���ɒu���I�u�W�F�N�g
class CourseOutObject : public GameObject
{
	int hModel_;    //���f���ԍ�
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	CourseOutObject(GameObject* parent);

	//�f�X�g���N�^
	~CourseOutObject();

	//������
	void Initialize() override;

	//�`��
	void Draw() override;
};