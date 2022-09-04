#include "Navigation.h"
#include "Course.h"
#include "Engine/Math.h"

XMFLOAT3 Navigation::XMFLOAT3PRUSXMFLOAT3(XMFLOAT3 fl3a, XMFLOAT3 fl3b)
{
	XMFLOAT3 result;

	result = XMFLOAT3(fl3a.x + fl3b.x, fl3a.y + fl3b.y, fl3a.z + fl3b.z);

	return result;
}

XMFLOAT3 Navigation::XMFLOAT3AVERAGE(XMFLOAT3 fl3a, XMFLOAT3 fl3b)
{
	XMFLOAT3 result;

	result = XMFLOAT3PRUSXMFLOAT3(fl3a, fl3b);

	result = XMFLOAT3(result.x / 2, result.y / 2, result.z / 2);

	return result;
}

int Navigation::ReturnShortest(float Left, float Right, float Upper, float Lower)
{
	if (Left < Right && Left <= Upper && Left <= Lower)
	{
		return left;
	}
	if (Right < Left && Right <= Upper && Right <= Lower)
	{
		return right;
	}
	if (Upper <= Left && Upper <= Right && Upper < Lower)
	{
		return upper;
	}
	return lower;
}

int Navigation::ReturnLongest(float Left, float Right, float Upper, float Lower)
{
	if (Left > Right && Left >= Upper && Left >= Lower)
	{
		return left;
	}
	if (Right > Left && Right >= Upper && Right >= Lower)
	{
		return right;
	}
	if (Upper >= Left && Upper >= Right && Upper > Lower)
	{
		return upper;
	}
	return lower;
}

Navigation::Navigation(GameObject* parent)
	: GameObject(parent, "Navigation"), pCourse_(nullptr), Upper_(), Lower_(), Left_(), Right_(),
	L_side_(), R_side_(), A_side_(), U_side_(), Left_Goal(), Right_Goal(), Upper_Goal()
{
	Checkpoint_.clear();
}

Navigation::~Navigation()
{
}

void Navigation::Initialize()
{
	transform_.scale_.x = 0.25f;
	transform_.scale_.y = 0.25f;
	transform_.scale_.z = 0.25f;

	pCourse_ = (Course*)FindObject("Course");
	int hCourseModel = pCourse_->GetModelHandle();

	L_side_.start = transform_.position_;
	L_side_.dir = matL;
	Model::RayCast(hCourseModel, &L_side_);

	Left_ = XMFLOAT3(transform_.position_.x - L_side_.dist + Adjuster_, transform_.position_.y, transform_.position_.z);

	R_side_.start = transform_.position_;
	R_side_.dir = matR;
	Model::RayCast(hCourseModel, &R_side_);

	Right_ = XMFLOAT3(transform_.position_.x + R_side_.dist - Adjuster_, transform_.position_.y, transform_.position_.z);

	A_side_.start = transform_.position_;
	A_side_.dir = matA;
	Model::RayCast(hCourseModel, &A_side_);

	Upper_ = XMFLOAT3(transform_.position_.x, transform_.position_.y + A_side_.dist - Adjuster_, transform_.position_.z);

	U_side_.start = transform_.position_;
	U_side_.dir = matU;
	Model::RayCast(hCourseModel, &U_side_);

	Lower_ = XMFLOAT3(transform_.position_.x, transform_.position_.y - U_side_.dist + Adjuster_, transform_.position_.z);

	Checkpoint_.push_back(transform_.position_);

	Left_Goal = Left_;
	Right_Goal = Right_;
	Upper_Goal = XMFLOAT3(Upper_.x, Upper_.y + Adjuster_, Upper_.z);

	transform_.position_ = XMFLOAT3AVERAGE(XMFLOAT3AVERAGE(Left_, Right_), XMFLOAT3AVERAGE(Upper_, Lower_));

	Scan();
}

void Navigation::Scan()
{
	//この4つをゴール判定として使用する
	/*XMFLOAT3 Left_Goal = Left_;
	XMFLOAT3 Right_Goal = Right_;
	XMFLOAT3 Upper_Goal = XMFLOAT3(Upper_.x, Upper_.y + Adjuster_, Upper_.z);*/
	//XMFLOAT3 Lower_Goal = Lower_;

	while (!Math::Intersect(A_side_.start, A_side_.dir, Left_Goal, Right_Goal, Upper_Goal))
	{
		pCourse_ = (Course*)FindObject("Course");
		int hCourseModel = pCourse_->GetModelHandle();

		XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
		mRotate *= XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
		mRotate *= XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));

		XMVECTOR Ray = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		Ray = XMVector3TransformCoord(Ray, mRotate);
		Ray = XMVector3Normalize(Ray);
		XMFLOAT3 matS;
		XMStoreFloat3(&matS, Ray);

		RayCastData R;
		R.start = transform_.position_;
		R.dir = matS;
		Model::RayCast(hCourseModel, &R);

		if (R.hit)
		{
			XMFLOAT3 Move_ = { 0, 0, R.dist - Adjuster_ };
			XMVECTOR vMove_ = XMLoadFloat3(&Move_);

			//現在地から機体の向きによって進む
			vMove_ = XMVector3TransformCoord(vMove_, mRotate);
			XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
			vPos += vMove_;
			XMStoreFloat3(&transform_.position_, vPos);
			//transform_.position_ = XMFLOAT3(transform_.position_.x, transform_.position_.y, transform_.position_.z + R.dist - Adjuster_);

			L_side_.start = transform_.position_;
			L_side_.dir = matS;
			Model::RayCast(hCourseModel, &L_side_);

			R_side_.start = transform_.position_;
			R_side_.dir = matS;
			Model::RayCast(hCourseModel, &R_side_);

			A_side_.start = transform_.position_;
			A_side_.dir = matS;
			Model::RayCast(hCourseModel, &A_side_);

			U_side_.start = transform_.position_;
			U_side_.dir = matS;
			Model::RayCast(hCourseModel, &U_side_);

			/*int longest = ReturnLongest(L_side_.dist, R_side_.dist, A_side_.dist, U_side_.dist);
			switch (longest)
			{
			case left:
				transform_.rotate_.y -= Turn_;
				break;
			case right:
				transform_.rotate_.y += Turn_;
				break;
			case upper:
				transform_.rotate_.x += Turn_;
				break;
			case lower:
				transform_.rotate_.x -= Turn_;
				break;
			}*/

			if (R.dist > 10)
			{
				if (L_side_.dist > R_side_.dist)
				{
					transform_.rotate_.y -= Turn_;
				}
				else
				{
					transform_.rotate_.y += Turn_;
				}
			}
			else
			{
				if (L_side_.dist > R_side_.dist)
				{
					transform_.rotate_.y -= 5;
				}
				else
				{
					transform_.rotate_.y += 5;
				}
			}
			

			/*if (A_side_.dist > U_side_.dist)
			{
				transform_.rotate_.x += 5;
			}
			else
			{
				transform_.rotate_.x -= 5;
			}*/

			/*L_side_.start = Left_;
			L_side_.dir = matS;
			Model::RayCast(hCourseModel, &L_side_);

			R_side_.start = Right_;
			R_side_.dir = matS;
			Model::RayCast(hCourseModel, &R_side_);

			A_side_.start = Upper_;
			A_side_.dir = matS;
			Model::RayCast(hCourseModel, &A_side_);

			U_side_.start = Lower_;
			U_side_.dir = matS;
			Model::RayCast(hCourseModel, &U_side_);

			XMVECTOR Landing = XMVectorSet(0.0f, 0.0f, L_side_.dist, 0.0f);
			Landing = XMVector3TransformCoord(Landing, mRotate);
			XMFLOAT3 mat;
			XMStoreFloat3(&mat, Landing);
			XMFLOAT3PRUSXMFLOAT3(Left_, mat);

			Landing = XMVectorSet(0.0f, 0.0f, R_side_.dist, 0.0f);
			Landing = XMVector3TransformCoord(Landing, mRotate);
			XMStoreFloat3(&mat, Landing);
			XMFLOAT3PRUSXMFLOAT3(Right_, mat);

			Landing = XMVectorSet(0.0f, 0.0f, A_side_.dist, 0.0f);
			Landing = XMVector3TransformCoord(Landing, mRotate);
			XMStoreFloat3(&mat, Landing);
			XMFLOAT3PRUSXMFLOAT3(Upper_, mat);

			Landing = XMVectorSet(0.0f, 0.0f, U_side_.dist, 0.0f);
			Landing = XMVector3TransformCoord(Landing, mRotate);
			XMStoreFloat3(&mat, Landing);
			XMFLOAT3PRUSXMFLOAT3(Lower_, mat);*/

			//一番短いレイを検索
			/*int shortest = ReturnShortest(L_side_.dist, R_side_.dist, A_side_.dist, U_side_.dist);
			switch (shortest)
			{
			case left:
				transform_.position_ = XMFLOAT3AVERAGE(Left_, Right_);
				transform_.rotate_.y += Turn_;
				break;
			case right:
				transform_.position_ = XMFLOAT3AVERAGE(Left_, Right_);
				transform_.rotate_.y -= Turn_;
				break;
			case upper:
				transform_.position_ = XMFLOAT3AVERAGE(Lower_, Upper_);
				transform_.rotate_.x -= Turn_;
				break;
			case lower:
				transform_.position_ = XMFLOAT3AVERAGE(Lower_, Upper_);
				transform_.rotate_.x += Turn_;
				break;
			}*/

			//向いている方向を取得
			mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
			mRotate *= XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
			//mRotate *= XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));

			Ray = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
			Ray = XMVector3TransformCoord(Ray, mRotate);
			Ray = XMVector3Normalize(Ray);
			XMStoreFloat3(&matS, Ray);

			/*R.start = transform_.position_;
			R.dir = matS;
			Model::RayCast(hCourseModel, &R);
			XMFLOAT3PRUSXMFLOAT3(matS, transform_.position_);*/

			L_side_.start = transform_.position_;
			L_side_.dir = matL;
			Model::RayCast(hCourseModel, &L_side_);

			Left_ = XMFLOAT3(transform_.position_.x - L_side_.dist + Adjuster_, transform_.position_.y, transform_.position_.z);

			R_side_.start = transform_.position_;
			R_side_.dir = matR;
			Model::RayCast(hCourseModel, &R_side_);

			Right_ = XMFLOAT3(transform_.position_.x + R_side_.dist - Adjuster_, transform_.position_.y, transform_.position_.z);

			A_side_.start = transform_.position_;
			A_side_.dir = matA;
			Model::RayCast(hCourseModel, &A_side_);

			Upper_ = XMFLOAT3(transform_.position_.x, transform_.position_.y + A_side_.dist, transform_.position_.z);

			U_side_.start = transform_.position_;
			U_side_.dir = matU;
			Model::RayCast(hCourseModel, &U_side_);

			Lower_ = XMFLOAT3(transform_.position_.x, transform_.position_.y - U_side_.dist, transform_.position_.z);

			//transform_.position_ = XMFLOAT3AVERAGE(XMFLOAT3AVERAGE(Left_, Right_), XMFLOAT3AVERAGE(Upper_, Lower_));

			transform_.position_ = XMFLOAT3AVERAGE(Upper_, Lower_);

			if (R.dist > 10.0f)
			{
				Checkpoint_.push_back(transform_.position_);
			}
			

			int s = (int)Checkpoint_.size();
		}
		else
		{
		transform_.rotate_.y += Turn_;
		}
		
	}
}

void Navigation::Release()
{
	SAFE_RELEASE(pCourse_);
}
