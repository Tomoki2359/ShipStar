#include "Player.h"
#include "Engine/Input.h"
#include "Course.h"
#include "CourseOutObject.h"
#include "Engine/Model.h"

void Player::StayInside()
{
}

void Player::StayOutside()
{
	XMMATRIX mRotate = XMMatrixIdentity();// = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
	mRotate *= XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	//mRotate *= XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));

	XMVECTOR Left = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR Right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	Left = XMVector3TransformCoord(Left, mRotate);
	Right = XMVector3TransformCoord(Right, mRotate);

	Left = XMVector3Normalize(Left);
	Right = XMVector3Normalize(Right);

	XMFLOAT3 matL, matR;
	XMStoreFloat3(&matL, Left);
	XMStoreFloat3(&matR, Right);

	Course* pCourse = (Course*)FindObject("Course");
	int hCourseModel = pCourse->GetModelHandle();

	RayCastData Ray_Right;		//�E�Ƀ��C���΂�
	Ray_Right.start = transform_.position_;   //���C�̔��ˈʒu
	Ray_Right.dir = matR;				      //���C�̕���
	Model::RayCast(hCourseModel, &Ray_Right); //���C�𔭎�

	RayCastData Ray_Left;		//���Ƀ��C���΂�
	Ray_Left.start = transform_.position_;   //���C�̔��ˈʒu
	Ray_Left.dir = matL;				     //���C�̕���
	Model::RayCast(hCourseModel, &Ray_Left); //���C�𔭎�

	XMFLOAT3 pos = transform_.position_;
	XMVECTOR vPos = XMLoadFloat3(&pos);

	if (Ray_Left.dist > Ray_Right.dist)
	{
		vPos = vPos * Right;
		XMStoreFloat3(&pos, vPos);
		UpdateCObject(pos, Ray_Right.dir);
	}
	else
	{
		vPos = vPos * Left;
		XMStoreFloat3(&pos, vPos);
		UpdateCObject(pos, Ray_Left.dir);
	}
}

void Player::UpdateCObject(XMFLOAT3 pos, XMFLOAT3 dir)
{
	Course* pCourse = (Course*)FindObject("Course");
	int hCourseModel = pCourse->GetModelHandle();

	CourseOutObject* pCO = (CourseOutObject*)FindObject("CourseOutObject");
	int hCO = pCO->GetModelHandle();

	XMFLOAT3 COpos = transform_.position_;

	XMFLOAT3 direction = XMFLOAT3(COpos.x - pos.x, COpos.y - pos.y, COpos.z - pos.z);

	XMVECTOR vDir = XMLoadFloat3(&dir);
	vDir = XMVector3Normalize(vDir);
	vDir = -vDir;
	XMStoreFloat3(&dir, vDir);

	Model::PushOut(hCourseModel, &COpos, 5, dir);

	pCO->SetPosition(COpos);
}

//�R���X�g���N�^
Player::Player(GameObject* parent)
	: Airframe(parent, "Player")
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