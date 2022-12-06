#pragma once
#include "Airframe.h"

class Ghost : public Airframe
{
	std::list<char> GhostData_Command_;	//�S�[�X�g�Ƃ��Ċi�[�����f�[�^
	std::list<int> GhostData_Frame_;
	short ProgFrame_;							//�o�߃t���[��
	const char ReplayEnd_ = 2;		//���v���C���I��������
	char Endcount_;					//ReplayEnd�ȏ�ɂȂ����烊�v���C�������I��������

	void CallOnly();				//���݂̃��[�h�����v���C�܂��̓S�[�X�g�݂̂Ȃ�ΌĂяo�����
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Ghost(GameObject* parent);

	//�f�X�g���N�^
	~Ghost();

	void UpdateState() override;

	void StayInside() override;
};

