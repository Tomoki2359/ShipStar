#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

enum Logo_ID
{
	LOGO_TEAM,
	LOGO_SCHOOL,
	LOGO_MAX
};

class SplashScene : public GameObject
{
	const short change_;		//���S�̕ύX
	const short startTime_;		//�]��
	short hPict_[LOGO_MAX];
	short alpha_;				//�����x�̒���
	short time_;				//�\������^�C�~���O
	const short MoveAlpha_;		//�����x�̕ω����x
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