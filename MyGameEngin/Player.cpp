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

//コンストラクタ
Player::Player(GameObject* parent)
	: Airframe(parent, "Player"), PrevPos_(), CountInside_(), CountOutside_()
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