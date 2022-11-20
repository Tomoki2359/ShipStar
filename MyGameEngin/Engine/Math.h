#pragma once
#include <DirectXMath.h>

using namespace DirectX;

namespace Math
{
	float Det(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c);

	//�O�p�`�̓����蔻��
	bool Intersect(XMFLOAT3 start, XMFLOAT3 dir, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2);

	//�����ƕ��ʂ̓����蔻��
	//������ : �����̎n�_ ������ : �����̏I�_ ��O�`��܈��� : �|���S���̊e���_
	bool SegmentToPlane(XMFLOAT3 segstart, XMFLOAT3 segend, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2);
	bool SegmentToPlane(XMFLOAT3 segstart, XMFLOAT3 segend, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, float *dist);

	//���ƕ��ʂ̓����蔻��
	//������ : ���̒��S�ʒu ������ : ���̔��a ��O�`��܈��� : �|���S���̊e���_
	bool CircleToPlane(XMFLOAT3 center, float size, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2);
	bool CircleToPlane(XMFLOAT3 center, float size, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, float *dist);
	void ElasticCollision(XMFLOAT3 pos1, XMVECTOR* vMove1, XMFLOAT3 pos2, XMVECTOR* vMove2);

	bool InsidePlane(XMFLOAT3 pos, XMFLOAT3 HLt, XMFLOAT3 LwR);

	//�������擾����֐�
	//������ : �Ώۂ̒l ������ : ���߂�ŏ��̌� ��O���� : ���߂�ő�̌�
	int GetDigits(int value, int m, int n);

	//�����_�ȉ��̒l���擾����֐�
	//������ : �Ώۂ̒l ���/�O���� ������m�`n��
	float GetFraction(float value, int m, int n);	//��񗎂����Ĉꕔ�̒l���擾�ł��Ȃ�
	//�����_�ȉ��̎w�肵�����𐮐��l�Ŏ擾����֐�
	int GetFraction(float value, int m);

	//����̌��̐��l��؂蔲���֐�
	//������ : �Ώۂ̒l ������ : ������m�� ��O���� : ���������̍ő�̌�
	float GetNum(float value, int m, int n);
};
