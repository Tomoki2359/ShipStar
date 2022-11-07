#include "Airframe.h"
#include "Course.h"
#include "Engine/Math.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include <algorithm>
#include <math.h>

//�R���X�g���N�^
Airframe::Airframe(GameObject* parent, std::string name)
	: GameObject(parent, name), hModel_(-1), cAscent_(false), speed_(NULL), RespawnPos_(), RespawnRot_(), RespawnUpdate_(NULL),
	cDescent_(false), lCurve_(false), rCurve_(false), cTurbo_(false), tTurbo_(NULL), Lap_(NULL), Side_(true),
	cCamera_(false), status_(), PartsSet(), start_(false), timeCount_(180), PrevPosition_(), pNav_(nullptr), IsGoal_(false)
{
}

Airframe::Airframe(GameObject* parent)
	: Airframe(parent, "Airframe")
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
	ZeroMemory(&PartsSet, sizeof(PartsSet));
	//�X�e�[�^�X�̎擾
	SetStatus();

	//���f���f�[�^�̃��[�h
	//�p�[�c���Ăяo����悤�ɂȂ��������
	hModel_ = Model::Load(fileName_);
	assert(hModel_ >= 0);

	status_[MAX_SPEED] = (float)((int)status_[MAX_SPEED] * 10000000 / 216000) / 10000;	//�ō����x
	status_[ACCELE] = (float)((int)status_[ACCELE] * 10000000 / 216000 / 60 / 7) / 10000;	//�����x
	status_[TURBO] = status_[TURBO] / 100 * 60;	//�^�[�{�l

	transform_.position_.z = 0.1f;
	PrevPosition_ = transform_.position_;
}

//�X�V
void Airframe::Update()
{
	//3�b��ɃX�^�[�g����
	if (start_)
	{
		pNav_ = (Navigation*)FindObject("Navigation");
		LapMeasure();
		JudgeGoal();
		PrevPosition_ = transform_.position_;

		//�p����ŌĂяo��
		UpdateState();

		FixInclination();

		//������ʒu�����ɂ���
		Limit();

		TurboProcess();
	}

	//�J�E���g�_�E��
	else
	{
		//timeCount_��0�ȉ��ɂȂ����瑀��\�ɂ���
		timeCount_--;	
		if (timeCount_ <= 0)
		{
			start_ = true;
		}
	}

	MoveProcess();
	JudgeSide();

	if (Side_)	//�R�[�X���ɂ���ꍇ
	{
		StayInside();
		RespawnPos_[RespawnUpdate_] = PrevPosition_;
		RespawnRot_[RespawnUpdate_] = transform_.rotate_;
		RespawnUpdate_++;
		if (RespawnUpdate_ >= Past)	//�z��̍ő吔�͒����Ȃ��悤�ɂ���
		{
			cTurbo_ = false;
			tTurbo_ = NULL;
			RespawnUpdate_ = NULL;
		}
	}
	else		//�R�[�X�O�ɂ���ꍇ
	{

		Respawn();
	}

	ChaseCamera();
}


void Airframe::JudgeSide()
{
	Course* pCourse = (Course*)FindObject("Course");
	int hCourseModel = pCourse->GetModelHandle();

	RayCastData data;
	data.start = transform_.position_;
	data.dir = XMFLOAT3(NULL, -1.0, NULL);
	Model::RayCast(hCourseModel, &data);
	Side_ = data.hit;
}

void Airframe::JudgeSide(RayCastData& data)
{
	Course* pCourse = (Course*)FindObject("Course");
	int hCourseModel = pCourse->GetModelHandle();
	data.dir = XMFLOAT3(NULL, -1.0, NULL);
	Model::RayCast(hCourseModel, &data);
}

bool Airframe::JudgeSide(XMFLOAT3 pos)
{
	Course* pCourse = (Course*)FindObject("Course");
	int hCourseModel = pCourse->GetModelHandle();

	RayCastData data;
	data.start = pos;
	data.dir = XMFLOAT3(NULL, -1.0, NULL);
	Model::RayCast(hCourseModel, &data);
	return data.hit;
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
	SAFE_RELEASE(pNav_);
}

//������ʒu�Ȃǂ̌��E
void Airframe::Limit()
{
	//���x���ő呬�x�𒴂����Ƃ��ő呬�x�ɂ���
	if (speed_ >= status_[MAX_SPEED])
	{
		speed_ = status_[MAX_SPEED];
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

	const float Scale = 0.25f;
	transform_.scale_ = XMFLOAT3(Scale, Scale, Scale);
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
	if (speed_ > NULL)
	{
		transform_.rotate_.y += RotationRate_Y;
	}
	if (lCurve_ != true)
	{
		//�E�ɋȂ���Ƃ��̌X��
		transform_.rotate_.z -= RotationRate_Z;
		rCurve_ = true;
		if (transform_.rotate_.z <= -RotationMax_Z)
		{
			transform_.rotate_.z = -RotationMax_Z;
		}
	}
}

void Airframe::TurnLeft()
{
	if (speed_ > NULL)
	{
		transform_.rotate_.y -= RotationRate_Y;
	}
	if (rCurve_ != true)
	{
		//���ɋȂ���Ƃ��̌X��
		transform_.rotate_.z += RotationRate_Z;
		lCurve_ = true;
		if (transform_.rotate_.z >= RotationMax_Z)
		{
			transform_.rotate_.z = RotationMax_Z;
		}
	}
}

void Airframe::Turbo()
{
	cTurbo_ = true;
	tTurbo_ = NULL;
}

XMFLOAT3 Airframe::GetDistance(GameObject* pTarget)
{
	float DisX = this->GetPosition().x - pTarget->GetPosition().x;
	float DisY = this->GetPosition().y - pTarget->GetPosition().y;
	float DisZ = this->GetPosition().z - pTarget->GetPosition().z;
	return XMFLOAT3(DisX, DisY, DisZ);
}

float Airframe::Getdistance(XMFLOAT3 a, XMFLOAT3 b)
{
	float answer;
	XMFLOAT3 c = XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z);
	answer = (float)sqrt(pow(c.x, 2.0) + pow(c.y, 2.0) + pow(c.z, 2.0));
	return answer;
}

void Airframe::JudgeGoal()
{
	if (Math::SegmentToPlane(PrevPosition_, transform_.position_, pNav_->Upper_Goal, pNav_->Left_Goal, pNav_->Right_Goal) && Lap_ > NULL)
	{
		IsGoal_ = true;
	}
}

void Airframe::ResetOverRotate(float* rotate)
{
	const int of = 360;
	const int uf = 0;

	if (*rotate > of)
	{
		*rotate -= of;
	}
	if (*rotate < uf)
	{
		*rotate += of;
	}
}

void Airframe::LapMeasure()
{
	//�t���ŃS�[�����C����ʉ߂����ꍇ
	if (Math::SegmentToPlane(PrevPosition_, transform_.position_, pNav_->Upper_Goal, pNav_->Left_Goal, pNav_->Right_Goal) &&
		PrevPosition_.z > transform_.position_.z)
	{
		Lap_--;
	}
	else if (Math::SegmentToPlane(PrevPosition_, transform_.position_, pNav_->Upper_Goal, pNav_->Left_Goal, pNav_->Right_Goal))
	{
		Lap_++;
	}
}

void Airframe::Respawn()
{
	transform_.position_ = RespawnPos_[RespawnUpdate_];			//����̈ʒu�ɖ߂�
	transform_.rotate_.x = RespawnRot_[RespawnUpdate_].x;		//��]���߂�
	transform_.rotate_.y = RespawnRot_[RespawnUpdate_].y;
	transform_.rotate_.z = NULL;
	speed_ = NULL;						//�X�s�[�h��0�ɂ���
}

void Airframe::FixInclination()
{
	//���ɌX���Ă����Ԃ̂Ƃ�
	if (lCurve_)
	{
		//�p�x��߂�����
		transform_.rotate_.z--;
		if (transform_.rotate_.z <= NULL)
		{
			lCurve_ = false;
			transform_.rotate_.z = NULL;
		}
	}

	//�E�ɌX���Ă����Ԃ̂Ƃ�
	if (rCurve_)
	{
		//�p�x��߂�����
		transform_.rotate_.z++;
		if (transform_.rotate_.z >= NULL)
		{
			rCurve_ = false;
			transform_.rotate_.z = NULL;
		}
	}
}

void Airframe::TurboProcess()
{
	//�^�[�{���̏���
	if (cTurbo_)
	{
		//�X�s�[�h���グ��
		speed_ = status_[MAX_SPEED] * 2.0f;
		//���Ԃ��o������I���
		if (tTurbo_ >= status_[TURBO])
		{
			cTurbo_ = false;
			tTurbo_ = NULL;
		}
	}

	//�^�[�{�l�𒙂߂�
	tTurbo_++;
}

void Airframe::MoveProcess()
{
	//�ړ�����
	XMVECTOR vMove_ = XMVectorSet(NULL, NULL, speed_, NULL);

	//�@�̂�X��,Y���̊p�x�̎擾
	XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
	mRotate = mRotate * XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

	//���ݒn����@�̂̌����ɂ���Đi��
	vMove_ = XMVector3TransformCoord(vMove_, mRotate);
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	vPos += vMove_;
	XMStoreFloat3(&transform_.position_, vPos);
}

void Airframe::ChaseCamera()
{
	//�J�������g�p���邩�ǂ���
	if (cCamera_)
	{
		XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

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
}
