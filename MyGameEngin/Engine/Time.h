#pragma once

class Transform;

namespace Time
{
	//������(Main�ŏ�����)
	void Initialize();

	//�X�V(Main�ōX�V)
	void Update(short FPS);

	void Reset();

	void Lock();

	void UnLock();

	//�b�̂ݕ\���ɂ��邩�ǂ���
	//true = �b�̂�
	//false = �l�ɉ����Ď�/���̕\��
	void SetDisplayMode(bool Mode);

	//������ : �\������Transform ������ : �����_�ȉ�������\�����邩
	void Draw(Transform tr, int digit);

	//�Ăяo�����_�̎��Ԃ��擾
	float GetTime();
};

