#pragma once

class Transform;

namespace Time
{
	//������
	void Initialize();

	//�b�̂ݕ\���ɂ��邩�ǂ���
	//true = �b�̂�
	//false = �l�ɉ����Ď�/���̕\��
	void SetDisplayMode(bool Mode);

	void Draw(int value, Transform tr);
	void Draw(float value, Transform tr);
};

