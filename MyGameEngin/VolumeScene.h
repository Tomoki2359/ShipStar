#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

enum VOLUME
{
	VOLUME_BACK = 0,
	VOLUME_OK,
	MAX_VOLUME,
};

//�����V�[�����Ǘ�����N���X
class VolumeScene : public GameObject
{
	short volume_;
	bool mouseMoob_;
	XMFLOAT3 mousePos_;
	XMFLOAT3 mouseNext_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	VolumeScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};