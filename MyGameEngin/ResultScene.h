#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

//�����V�[�����Ǘ�����N���X
class ResultScene : public GameObject
{
	int hPict_[10];

	enum
	{
		Pict_Lately,
		Pict_Recbreak
	};
	int hPictRecord_[2];
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