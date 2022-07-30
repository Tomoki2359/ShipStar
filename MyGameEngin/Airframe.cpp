#include "Airframe.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
Airframe::Airframe(GameObject* parent)
	: GameObject(parent, "Airframe"), hModel_(-1), aRotate_(false), Speed_(0.0f),
	dRotate_(false), lRotate_(false), rRotate_(false), cTurbo_(false), tTurbo_(0),
	sCamera_(false), status_()
{
}

Airframe::Airframe(GameObject* parent, std::string name)
	: GameObject(parent, name), hModel_(-1), aRotate_(false), Speed_(0.0f),
	dRotate_(false), lRotate_(false), rRotate_(false), cTurbo_(false), tTurbo_(0),
	sCamera_(false), status_()
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

	status_[MAX_SPEED] = (float)((int)status_[MAX_SPEED] * 10000000 / 216000) / 10000;	//�ō����x
	status_[ACCELE] = (float)((int)status_[ACCELE] * 10000000 / 216000 / 60 / 7) / 10000;	//�����x
	status_[TURBO] = status_[TURBO] / 100 * 60;	//�^�[�{�l
	Speed_ = 0;	//���݂̑��x
}

//�X�V
void Airframe::Update()
{
	//�p����ŌĂяo��
	UpdateState();

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

	//�㏸��ԂȂ�
	if (aRotate_ == true)
	{
		if (transform_.position_.y >= 15)
		{
			transform_.rotate_.x += 0.4f;
		}
		transform_.rotate_.x += 0.2f;
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
			transform_.rotate_.x -= 0.4f;
		}
		transform_.rotate_.x -= 0.2f;
		if (transform_.rotate_.x <= 0)
		{
			dRotate_ = false;
			transform_.rotate_.x = 0;
		}
	}

	//������ʒu�����ɂ���
	Limit();

	//�ړ�����
	//���x���x�N�^�[�ɕϊ�
	XMFLOAT3 Move_ = { 0,0,Speed_ };
	XMVECTOR vMove_ = XMLoadFloat3(&Move_);

	//�@�̂�X��,Y���̊p�x�̎擾
	XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
	mRotate = mRotate * XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

	//���ݒn����@�̂̌����ɂ���Đi��
	vMove_ = XMVector3TransformCoord(vMove_, mRotate);
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	vPos += vMove_;
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
	if (Speed_ >= status_[MAX_SPEED])
	{
		Speed_ = status_[MAX_SPEED];
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
	status_[MAX_SPEED] = 150;
	status_[ACCELE] = 200;
	status_[TURBO] = 150;
	status_[ENDURANCE] = 100;

	failName_ = "";
	sCamera_ = false;
}

void Airframe::Accelerate()
{
	//�������̑��x�𑝂₷
	Speed_ = Speed_ + status_[ACCELE];
}

void Airframe::Decelerate()
{
	//�������̑��x�����炷
	Speed_ = Speed_ - (status_[ACCELE] * 2);
	//���x���ő呬�x�𒴂����Ƃ��ő呬�x�ɂ���
	if (Speed_ <= 0)
	{
		Speed_ = 0;
	}
}

void Airframe::TurnRight()
{
	transform_.rotate_.y += 1.5f;
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

void Airframe::TurnLeft()
{
	transform_.rotate_.y -= 1.5f;
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

void Airframe::Rise()
{
	//���~��Ԃł͂Ȃ��Ƃ�
	if (dRotate_ != true)
	{
		//�㏸��Ԃɂ���
		transform_.rotate_.x -= 0.4f;
		aRotate_ = true;
		//�p�x��15�𒴂�����15�ɂ���
		if (transform_.rotate_.x <= -25)
		{
			transform_.rotate_.x = -25;
		}
	}
}

void Airframe::Descent()
{
	//�㏸��Ԃł͂Ȃ��Ƃ�
	if (aRotate_ != true)
	{
		//���~��Ԃɂ���
		transform_.rotate_.x += 0.4f;
		dRotate_ = true;
		//�p�x���|15�𒴂�����-15�ɂ���
		if (transform_.rotate_.x >= 25)
		{
			transform_.rotate_.x = 25;
		}
	}
}

void Airframe::Turbo()
{
	//�X�s�[�h���グ��
	Speed_ = status_[MAX_SPEED] * 2.0f;
	//���Ԃ��o������I���
	if (tTurbo_ >= status_[TURBO])
	{
		cTurbo_ = false;
		tTurbo_ = 0;
	}
}
