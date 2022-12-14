#pragma once
#include <list>
#include <vector>

namespace Storage
{
	//�f�[�^���X�g���[�W�ɑ���֐�
	void ThrowData(std::vector<char> command, std::vector<int> frame);

	//���v���C�p�̃f�[�^���擾����֐�
	void CopyData(std::list<char> &command, std::list<int> &frame);

	//�ۑ����ꂽ�S�[�X�g�f�[�^���擾����֐�
	void LoadData(std::list<char>& command, std::list<int>& frame);

	//�I������Ă���R�[�X�̃f�[�^�����݂��邩
	///�߂�l : true = ����  false = �Ȃ�
	bool ExistData();

	//�L�^���X�V���ꂽ����Ԃ�
	bool IsBreaked();
};