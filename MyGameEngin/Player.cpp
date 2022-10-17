#include "Player.h"
#include "Engine/Input.h"
#include "Course.h"
#include "CourseOutObject.h"
#include "Engine/Model.h"

void Player::StayInside()
{
	if (CountInside_ == 60)
	{
		PrevPos_ = transform_.position_;
		CountInside_ = NULL;
	}
	CountInside_++;
}

void Player::StayOutside()
{
	XMMATRIX mRotate = XMMatrixIdentity();// = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
	mRotate *= XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	//mRotate *= XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));

	XMFLOAT3 dir = XMFLOAT3(transform_.position_.x - PrevPos_.x, transform_.position_.y - PrevPos_.y, transform_.position_.z - PrevPos_.z);

	if (CountOutside_ == 60)
	{
		UpdateCObject(dir);
		CountOutside_ = NULL;
	}
	
	CountOutside_++;
}

void Player::UpdateCObject(XMFLOAT3 dir)
{
	Course* pCourse = (Course*)FindObject("Course");
	int hCourseModel = pCourse->GetModelHandle();

	CourseOutObject* pCO = (CourseOutObject*)FindObject("CourseOutObject");
	int hCO = pCO->GetModelHandle();

	XMFLOAT3 COpos = transform_.position_;

	XMVECTOR vDir = XMLoadFloat3(&dir);
	vDir = XMVector3Normalize(vDir);
	vDir = -vDir;
	XMStoreFloat3(&dir, vDir);

	Model::PushOut(hCourseModel, &COpos, 5, dir);

	pCO->SetPosition(COpos);
}

//�R���X�g���N�^
Player::Player(GameObject* parent)
	: Airframe(parent, "Player"), PrevPos_(), CountInside_(), CountOutside_()
{
}

Player::~Player()
{
}

void Player::UpdateState()
{
	//�O�i����
	if (Input::IsKey(DIK_W) && !Input::IsKey(DIK_S))
	{
		Accelerate();
	}
	//�u���[�L����
	if (Input::IsKey(DIK_S) && !Input::IsKey(DIK_W))
	{
		Decelerate();
	}
	//���ɃJ�[�u����
	if (Input::IsKey(DIK_A) && !Input::IsKey(DIK_D))
	{
		TurnLeft();
	}
	//�E�ɃJ�[�u����
	if (Input::IsKey(DIK_D) && !Input::IsKey(DIK_A))
	{
		TurnRight();
	}
	//�㏸����
	if (Input::IsKey(DIK_E) && !Input::IsKey(DIK_Q))
	{
		Rise();
	}
	//���~����
	if (Input::IsKey(DIK_Q) && !Input::IsKey(DIK_E))
	{
		Descent();
	}
	//�^�[�{
	//300�͏��ʂɂ���Ĕ������鎞�Ԃ��ϓ�����(�ŉ��ʂ���5�b,10�b,15�b,20�b)
	if (tTurbo_ >= 300 && Input::IsKeyDown(DIK_C))
	{
		tTurbo_ = 0;
		Turbo();
	}
	Course* pCourse = (Course*)FindObject("Course");    //�X�e�[�W�I�u�W�F�N�g��T��
	int hGroundModel = pCourse->GetModelHandle();    //���f���ԍ����擾
}

//void Player::SetStatus()
//{
//	//���Ƃ�for����CSV��������
//	status_[MAX_SPEED] = 150;
//	status_[ACCELE] = 200;
//	status_[TURBO] = 150;
//	status_[ENDURANCE] = 100;
//
//	//�p�[�c���Ăяo����悤�ɂȂ�����C��
//	fileName_ = "Assets\\oden.fbx.";	//�t�@�C���̖��O
//	cCamera_ = true;	//�J����ON
//	transform_.scale_.x = 0.25;
//	transform_.scale_.y = 0.25;
//	transform_.scale_.z = 0.25;
//}