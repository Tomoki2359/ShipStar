#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

enum RESULT
{
	RESULT_BACK = 0,
	RESULT_OK,
	MAX_RESULT,
};

//�����V�[�����Ǘ�����N���X
class ResultScene : public GameObject
{
	short result_;
	bool mouseMoob_;
	XMFLOAT3 mousePos_;
	XMFLOAT3 mouseNext_;
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