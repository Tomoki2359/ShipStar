#pragma once
#include "Airframe.h"

//�����V�[�����Ǘ�����N���X
class Player : public Airframe
{
	void StayInside() override;

	const char Initial_ = 0;
	std::vector<char> GhostData_Command_;	//�S�[�X�g�Ƃ��Ċi�[�����f�[�^
	std::vector<int> GhostData_Frame_;
	short ProgFrame_;							//�o�߃t���[��
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Player(GameObject* parent);

	//�f�X�g���N�^
	~Player();

	void UpdateState() override;

	//�S�[��������Storage�Ƀf�[�^��n��
	void ThrowData();
};