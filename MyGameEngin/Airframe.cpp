#include "Airframe.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
Airframe::Airframe(GameObject* parent)
	: GameObject(parent, "Airframe"), hModel_(-1), cAscent_(false), speed_(0.0f),
	cDescent_(false), lCurve_(false), rCurve_(false), cTurbo_(false), tTurbo_(0),
	cCamera_(false), status_(), PartsSet()
{
}

Airframe::Airframe(GameObject* parent, std::string name)
	: GameObject(parent, name), hModel_(-1), cAscent_(false), speed_(0.0f),
	cDescent_(false), lCurve_(false), rCurve_(false), cTurbo_(false), tTurbo_(0),
	cCamera_(false), status_(), PartsSet()
{
}

Airframe::~Airframe()
{
}

//������
void Airframe::Initialize()
{
	csv.Load("Assets/PartsStatus.csv");

	//�S�ăf�t�H���g�l�ŏ�����
	PartsSet = { NULL, NULL, NULL, NULL, NULL, NULL };

	//�X�e�[�^�X�̎擾
	SetStatus();

	//���f���f�[�^�̃��[�h
	//�p�[�c���Ăяo����悤�ɂȂ��������
	hModel_ = Model::Load(fileName_);
	assert(hModel_ >= 0);

	status_[MAX_SPEED] = (float)((int)status_[MAX_SPEED] * 10000000 / 216000) / 10000;	//�ō����x
	status_[ACCELE] = (float)((int)status_[ACCELE] * 10000000 / 216000 / 60 / 7) / 10000;	//�����x
	status_[TURBO] = status_[TURBO] / 100 * 60;	//�^�[�{�l
	speed_ = 0;	//���݂̑��x
}

//�X�V
void Airframe::Update()
{
	//�p����ŌĂяo��
	UpdateState();

	//���ɌX���Ă����Ԃ̂Ƃ�
	if (lCurve_ == true)
	{
		//�p�x��߂�����
		transform_.rotate_.z -= 1;
		if (transform_.rotate_.z <= 0)
		{
			lCurve_ = false;
			transform_.rotate_.z = 0;
		}
	}

	//�E�ɌX���Ă����Ԃ̂Ƃ�
	if (rCurve_ == true)
	{
		//�p�x��߂�����
		transform_.rotate_.z += 1;
		if (transform_.rotate_.z >= 0)
		{
			rCurve_ = false;
			transform_.rotate_.z = 0;
		}
	}

	//�㏸��ԂȂ�
	if (cAscent_ == true)
	{
		if (transform_.position_.y >= 15)
		{
			transform_.rotate_.x += 0.4f;
		}
		transform_.rotate_.x += 0.2f;
		if (transform_.rotate_.x >= 0)
		{
			cAscent_ = false;
			transform_.rotate_.x = 0;
		}
	}

	//���~��ԂȂ�
	if (cDescent_ == true)
	{
		if (transform_.position_.y <= -5)
		{
			transform_.rotate_.x -= 0.4f;
		}
		transform_.rotate_.x -= 0.2f;
		if (transform_.rotate_.x <= 0)
		{
			cDescent_ = false;
			transform_.rotate_.x = 0;
		}
	}

	//������ʒu�����ɂ���
	Limit();

	//�^�[�{���̏���
	if (cTurbo_ == true)
	{
		//�X�s�[�h���グ��
		speed_ = status_[MAX_SPEED] * 2.0f;
		//���Ԃ��o������I���
		if (tTurbo_ >= status_[TURBO])
		{
			cTurbo_ = false;
			tTurbo_ = 0;
		}
	}

	//�ړ�����
	//���x���x�N�^�[�ɕϊ�
	XMFLOAT3 Move_ = { 0,0,speed_ };
	XMVECTOR vMove_ = XMLoadFloat3(&Move_);

	//�@�̂�X��,Y���̊p�x�̎擾
	XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
	mRotate = mRotate * XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

	//���ݒn����@�̂̌����ɂ���Đi��
	vMove_ = XMVector3TransformCoord(vMove_, mRotate);
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	vPos += vMove_;
	XMStoreFloat3(&transform_.position_, vPos);

	//�J�������g�p���邩�ǂ���
	if (cCamera_ == true)
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

	//�^�[�{�l�𒙂߂�
	tTurbo_++;
}

//�`��
void Airframe::Draw()
{
	//�p�[�c���Ăяo����悤�ɂȂ��������
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
	if (speed_ >= status_[MAX_SPEED])
	{
		speed_ = status_[MAX_SPEED];
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

void Airframe::SetPartsNum(char engine, char body, char wing, char cockpit, char pattern)
{
	PartsSet.ENGINE = engine;
	PartsSet.BODY = body;
	PartsSet.WING = wing;
	PartsSet.COCKPIT = cockpit;
	PartsSet.PATTERN = pattern;

	SetStatus();
}

//�X�e�[�^�X�̎擾
void Airframe::SetStatus()
{
	//���Ƃ�for����CSV��������
	status_[MAX_SPEED] = (float)csv.GetValue(PARTS_WING ,PartsSet.WING);
	status_[ACCELE] = (float)csv.GetValue(PARTS_COCKPIT, PartsSet.COCKPIT);	//�l250�ŋt�i���m�F
	status_[TURBO] = (float)csv.GetValue(PARTS_ENGINE, PartsSet.ENGINE);
	status_[ENDURANCE] = (float)csv.GetValue(PARTS_BODY, PartsSet.BODY);

	//�p�[�c���Ăяo����悤�ɂȂ�����C��
	//fileName_ = "";
	//cCamera_ = false;

	fileName_ = "Assets\\Airframe.fbx";	//�t�@�C���̖��O
	if (this->objectName_ == "Player")
	{
		cCamera_ = true;	//�J����ON
	}
	else
	{
		cCamera_ = false;	//�J����OFF
	}
	transform_.scale_.x = 0.25;
	transform_.scale_.y = 0.25;
	transform_.scale_.z = 0.25;
}

void Airframe::Accelerate()
{
	//�������̑��x�𑝂₷
	speed_ = speed_ + status_[ACCELE];
}

void Airframe::Decelerate()
{
	//�������̑��x�����炷
	speed_ = speed_ - (status_[ACCELE] * 2);
	//���x���ő呬�x�𒴂����Ƃ��ő呬�x�ɂ���
	if (speed_ <= 0)
	{
		speed_ = 0;
	}
}

void Airframe::TurnRight()
{
	if (speed_ > 0)
	{
		transform_.rotate_.y += 1.5f;
	}
	if (lCurve_ != true)
	{
		//�E�ɋȂ���Ƃ��̌X��
		transform_.rotate_.z -= 2;
		rCurve_ = true;
		if (transform_.rotate_.z <= -40)
		{
			transform_.rotate_.z = -40;
		}
	}
}

void Airframe::TurnLeft()
{
	if (speed_ > 0)
	{
		transform_.rotate_.y -= 1.5f;
	}
	if (rCurve_ != true)
	{
		//���ɋȂ���Ƃ��̌X��
		transform_.rotate_.z += 2;
		lCurve_ = true;
		if (transform_.rotate_.z >= 40)
		{
			transform_.rotate_.z = 40;
		}
	}
}

void Airframe::Rise()
{
	//���~��Ԃł͂Ȃ��Ƃ�
	if (cDescent_ != true)
	{
		//�㏸��Ԃɂ���
		transform_.rotate_.x -= 0.4f;
		cAscent_ = true;
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
	if (cAscent_ != true)
	{
		//���~��Ԃɂ���
		transform_.rotate_.x += 0.4f;
		cDescent_ = true;
		//�p�x���|15�𒴂�����-15�ɂ���
		if (transform_.rotate_.x >= 25)
		{
			transform_.rotate_.x = 25;
		}
	}
}

void Airframe::Turbo()
{
	cTurbo_ = true;
	tTurbo_ = 0;
}

XMFLOAT3 Airframe::GetDistance(GameObject* pTarget)
{
	float DisX = this->GetPosition().x - pTarget->GetPosition().x;
	float DisY = this->GetPosition().y - pTarget->GetPosition().y;
	float DisZ = this->GetPosition().z - pTarget->GetPosition().z;
	return XMFLOAT3(DisX, DisY, DisZ);
}