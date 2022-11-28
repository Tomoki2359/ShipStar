#pragma once
#include "Airframe.h"

class Ghost : public Airframe
{
	std::list<char> GhostData_Command_;	//�S�[�X�g�Ƃ��Ċi�[�����f�[�^
	std::list<int> GhostData_Frame_;
	short ProgFrame_;							//�o�߃t���[��

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Ghost(GameObject* parent);

	//�f�X�g���N�^
	~Ghost();

	void UpdateState() override;

	void StayInside() override;
};
