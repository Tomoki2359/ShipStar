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

	RayCastData Ray_Right;		//右にレイを飛ばす
	Ray_Right.start = transform_.position_;   //レイの発射位置
	Ray_Right.dir = matR;				      //レイの方向
	Model::RayCast(hCourseModel, &Ray_Right); //レイを発射

	RayCastData Ray_Left;		//左にレイを飛ばす
	Ray_Left.start = transform_.position_;   //レイの発射位置
	Ray_Left.dir = matL;				     //レイの方向
	Model::RayCast(hCourseModel, &Ray_Left); //レイを発射

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

//コンストラクタ
Player::Player(GameObject* parent)
	: Airframe(parent, "Player")
{
}

Player::~Player()
{
}

void Player::UpdateState()
{
	//前進する
	if (Input::IsKey(DIK_W) && !Input::IsKey(DIK_S))
	{
		Accelerate();
	}
	//ブレーキする
	if (Input::IsKey(DIK_S) && !Input::IsKey(DIK_W))
	{
		Decelerate();
	}
	//左にカーブする
	if (Input::IsKey(DIK_A) && !Input::IsKey(DIK_D))
	{
		TurnLeft();
	}
	//右にカーブする
	if (Input::IsKey(DIK_D) && !Input::IsKey(DIK_A))
	{
		TurnRight();
	}
	//上昇する
	if (Input::IsKey(DIK_E) && !Input::IsKey(DIK_Q))
	{
		Rise();
	}
	//下降する
	if (Input::IsKey(DIK_Q) && !Input::IsKey(DIK_E))
	{
		Descent();
	}
	//ターボ
	//300は順位によって発動する時間が変動する(最下位から5秒,10秒,15秒,20秒)
	if (tTurbo_ >= 300 && Input::IsKeyDown(DIK_C))
	{
		tTurbo_ = 0;
		Turbo();
	}
	Course* pCourse = (Course*)FindObject("Course");    //ステージオブジェクトを探す
	int hGroundModel = pCourse->GetModelHandle();    //モデル番号を取得
}

//void Player::SetStatus()
//{
//	//あとでfor分でCSVから入れる
//	status_[MAX_SPEED] = 150;
//	status_[ACCELE] = 200;
//	status_[TURBO] = 150;
//	status_[ENDURANCE] = 100;
//
//	//パーツを呼び出せるようになったら修正
//	fileName_ = "Assets\\oden.fbx.";	//ファイルの名前
//	cCamera_ = true;	//カメラON
//	transform_.scale_.x = 0.25;
//	transform_.scale_.y = 0.25;
//	transform_.scale_.z = 0.25;
//}