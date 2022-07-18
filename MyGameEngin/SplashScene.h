#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

//�����V�[�����Ǘ�����N���X
class SplashScene : public GameObject
{
	const int change_;		//���S�̕ύX
	const int startTime_;	//�]��
	int hPict_[2];
	int alpha_;				//�����x�̒���
	int time_;				//�\������^�C�~���O
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	SplashScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};