#include "Airframe.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Player.h"
//�R���X�g���N�^
Airframe::Airframe(GameObject* parent, std::string name)
	: GameObject(parent, name), hModel_(-1), aRotate_(false), dRotate_(false), lRotate_(false), rRotate_(false), cTurbo_(false), tTurbo_(0)
{
}

Airframe::~Airframe()
{
}

//������
void Airframe::Initialize()
{
	//�X�e�[�^�X�̎擾
	SetStatus();

	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load(failName_);
	assert(hModel_ >= 0);

	status_[MAX_SPEAD] = (float)((int)status_[MAX_SPEAD] * 10000000 / 216000) / 10000;	//�ō����x
	status_[ACCELE] = (float)((int)status_[ACCELE] * 10000000 / 216000 / 60 / 7) / 10000;	//�����x
	status_[TURBO] = status_[TURBO] / 100 * 60;	//�^�[�{�l
	Spead_ = 0;	//���݂̑��x
}

//�X�V
void Airframe::Update()
{
	//�O�i����
	if (Input::IsKey(DIK_W))
	{
		//�������̑��x�𑝂₷
		Spead_ = Spead_ + status_[ACCELE];
	}

	//�u���[�L����
	if (Input::IsKey(DIK_S))
	{
		//�������̑��x�����炷
		Spead_ = Spead_ - (status_[ACCELE] * 2);
		//���x���ő呬�x�𒴂����Ƃ��ő呬�x�ɂ���
		if (Spead_ <= 0)
		{
			Spead_ = 0;
		}
	}

	//���ɃJ�[�u����
	if (Input::IsKey(DIK_A))
	{
		transform_.rotate_.y -= 1.5;
		if (rRotate_ != true)
		{
			//���ɋȂ���Ƃ��̌X��
			transform_.rotate_.z += 2;
			lRotate_ = true;
			if (transform_.rotate_.z >= 40)
			{
				transform_.rotate_.z = 40;
			}
		}
	}

	//�E�ɃJ�[�u����
	if (Input::IsKey(DIK_D))
	{
		transform_.rotate_.y += 1.5;
		if (lRotate_ != true)
		{
			//�E�ɋȂ���Ƃ��̌X��
			transform_.rotate_.z -= 2;
			rRotate_ = true;
			if (transform_.rotate_.z <= -40)
			{
				transform_.rotate_.z = -40;
			}
		}
	}

	//���ɌX���Ă����Ԃ̂Ƃ�
	if (lRotate_ == true)
	{
		//�p�x��߂�����
		transform_.rotate_.z -= 1;
		if (transform_.rotate_.z <= 0)
		{
			lRotate_ = false;
			transform_.rotate_.z = 0;
		}
	}

	//�E�ɌX���Ă����Ԃ̂Ƃ�
	if (rRotate_ == true)
	{
		//�p�x��߂�����
		transform_.rotate_.z += 1;
		if (transform_.rotate_.z >= 0)
		{
			rRotate_ = false;
			transform_.rotate_.z = 0;
		}
	}

	//�㏸����
	if (Input::IsKey(DIK_E))
	{
		//���~��Ԃł͂Ȃ��Ƃ�
		if (dRotate_ != true)
		{
			//�㏸��Ԃɂ���
			transform_.rotate_.x -= 0.4;
			aRotate_ = true;
			//�p�x��15�𒴂�����15�ɂ���
			if (transform_.rotate_.x <= -25)
			{
				transform_.rotate_.x = -25;
			}
		}
	}

	//���~����
	if (Input::IsKey(DIK_Q))
	{
		//�㏸��Ԃł͂Ȃ��Ƃ�
		if (aRotate_ != true)
		{
			//���~��Ԃɂ���
			transform_.rotate_.x += 0.4;
			dRotate_ = true;
			//�p�x���|15�𒴂�����-15�ɂ���
			if (transform_.rotate_.x >= 25)
			{
				transform_.rotate_.x = 25;
			}
		}
	}

	//�㏸��ԂȂ�
	if (aRotate_ == true)
	{
		if (transform_.position_.y >= 15)
		{
			transform_.rotate_.x += 0.4;
		}
		transform_.rotate_.x += 0.2;
		if (transform_.rotate_.x >= 0)
		{
			aRotate_ = false;
			transform_.rotate_.x = 0;
		}
	}

	//���~��ԂȂ�
	if (dRotate_ == true)
	{
		if (transform_.position_.y <= -5)
		{
			transform_.rotate_.x -= 0.4;
		}
		transform_.rotate_.x -= 0.2;
		if (transform_.rotate_.x <= 0)
		{
			dRotate_ = false;
			transform_.rotate_.x = 0;
		}
	}

	//5�b��������^�[�{���g����悤�ɂ���
	if (tTurbo_ >= 300)
	{
		if (Input::IsKeyDown(DIK_C))
		{
			cTurbo_ = true;
			tTurbo_ = 0;
		}
	}

	//�^�[�{���̏���
	if (cTurbo_ == true)
	{
		//�X�s�[�h���グ��
		Spead_ = status_[MAX_SPEAD] * 2.0;
		//���Ԃ��o������I���
		if (tTurbo_ >= status_[TURBO])
		{
			cTurbo_ = false;
			tTurbo_ = 0;
		}
	}

	//������ʒu�����ɂ���
	Limit();

	//�ړ�����
	//���x���x�N�^�[�ɕϊ�
	XMFLOAT3 Moob_ = { 0,0,Spead_ };
	XMVECTOR vMoob_ = XMLoadFloat3(&Moob_);

	//�@�̂�X��,Y���̊p�x�̎擾
	XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
	mRotate = mRotate * XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

	//���ݒn����@�̂̌����ɂ���Đi��
	vMoob_ = XMVector3TransformCoord(vMoob_, mRotate);
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	vPos += vMoob_;
	XMStoreFloat3(&transform_.position_, vPos);

	//�J�������������ǂ���
	if (sCamera_ == true)
	{
		//�J�����̐ݒu
		XMFLOAT3 camPos;
		XMVECTOR vCam = XMVectorSet(0.0f, 5.0f, -10.0f, 0.0f);	//�J�����̈ʒu
		XMMATRIX mRotate_ = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));	//Y����]
		vCam = XMVector3TransformCoord(vCam, mRotate_);	//�p�x�ŃJ�����̈ʒu��ύX
		XMStoreFloat3(&camPos, vPos + vCam);	//�J�����̈ʒu�Ǝ����̈ʒu�����킹��
		Camera::SetPosition(XMVectorSet(camPos.x, camPos.y, camPos.z, 1.0));

		//�J�����͎����̈ʒu�����Ă�
		XMVECTOR Pos_ = XMLoadFloat3(&transform_.position_);
		Camera::SetTarget(Pos_);
	}

	//�^�[�{�𒙂߂�
	tTurbo_++;
}

//�`��
void Airframe::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Airframe::Release()
{
}

//������ʒu�Ȃǂ̌��E
void Airframe::Limit()
{
	//���x���ő呬�x�𒴂����Ƃ��ő呬�x�ɂ���
	if (Spead_ >= status_[MAX_SPEAD])
	{
		Spead_ = status_[MAX_SPEAD];
	}

	//���ȏ�㏸���Ȃ�
	if (transform_.position_.y >= 15)
	{
		transform_.position_.y = 15;
	}

	//���ȉ����~���Ȃ�
	if (transform_.position_.y <= -5)
	{
		transform_.position_.y = -5;
	}
}

//�X�e�[�^�X�̎擾
void Airframe::SetStatus()
{
	//���Ƃ�for����CSV��������
	status_[MAX_SPEAD] = 150;
	status_[ACCELE] = 200;
	status_[TURBO] = 150;
	status_[ENDURANCE] = 100;

	failName_ = "";
	sCamera_ = false;
}