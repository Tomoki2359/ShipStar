#include "Navigation.h"
#include "Course.h"
#include "Engine/Math.h"
#include "Player.h"
#include "Option.h"

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

	const float error = 0.001f;	//誤差修正のための定数
	if (result.x < error)
	{
		result.x = NULL;
	}
	if (result.y < error)
	{
		result.y = NULL;
	}
	if (result.z < error)
	{
		result.z = NULL;
	}

	return result;
}

float Navigation::Getdistance(XMFLOAT3 a, XMFLOAT3 b)
{
	float answer;
	XMFLOAT3 c = XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z);
	answer = (float)sqrt(pow(c.x, 2.0) + pow(c.y, 2.0) + pow(c.z, 2.0));
	return answer;
}

Navigation::Navigation(GameObject* parent)
	: GameObject(parent, "Navigation"), pCourse_(nullptr),pPlayer_(nullptr), Left_(), Right_(),
	Upper_Goal(), Left_Goal(), Right_Goal(), Limit_(NULL)
{
	Checkpoint_.clear();
}

Navigation::~Navigation()
{
	Checkpoint_.clear();
}

void Navigation::Initialize()
{
	pCourse_ = (Course*)FindObject("Course");
	int hCourseModel = pCourse_->GetModelHandle();

	RayCastData ray;
	ray.start = transform_.position_;
	ray.dir = matR;
	Model::RayCast(hCourseModel, &ray);

	Right_ = XMFLOAT3(transform_.position_.x + ray.dist, transform_.position_.y, transform_.position_.z);

	ray.dir = matL;
	Model::RayCast(hCourseModel, &ray);

	Left_ = XMFLOAT3(transform_.position_.x - ray.dist, transform_.position_.y, transform_.position_.z);

	ray.dir = Shot_;
	Model::RayCast(hCourseModel, &ray);

	/*Right_ = XMFLOAT3(Right_.x, Right_.y - ray.dist, Right_.z);
	Left_ = XMFLOAT3(Left_.x, Left_.y - ray.dist, Left_.z);*/

	ray.dir = matU;
	Model::RayCast(hCourseModel, &ray);

	Upper_Goal = XMFLOAT3(transform_.position_.x, transform_.position_.y + ray.dist, transform_.position_.z);

	Left_Goal = Left_;
	Right_Goal = Right_;

	//Scan();
}

void Navigation::Update()
{
	if (Option::GetMode() != MODE_REPLAY &&
		Option::GetMode() != MODE_ONLYGHOST)
	{
		if (Limit_ > UpdateLimit)
		{
			UpdateCourseout();
			Limit_ = NULL;
		}
		else
		{
			Limit_++;
		}

	}
}

void Navigation::Scan()
{
	/*pCourse_ = (Course*)FindObject("Course");
	int hCourseModel = pCourse_->GetModelHandle();*/



	//for (int i = NULL; i < DIVISION_MAX; i++)
	//{
	//	//走査する区域に移動する
	//	switch (i)
	//	{
	//	case UPPER_LEFT:transform_.position_ = XMFLOAT3((float)-Range_, NULL, Range_); break;
	//	case UPPER_RIGHT:transform_.position_ = XMFLOAT3(NULL, NULL, Range_); break;
	//	case LOWER_LEFT:transform_.position_ = XMFLOAT3((float)-Range_, NULL, NULL); break;
	//	case LOWER_RIGHT:transform_.position_ = Initial; break;
	//	}

	//	//走査区域内で最も離れた場所を格納しておくもの
	//	XMFLOAT3 Storage = transform_.position_;


	//	//範囲内の走査回数
	//	for (int x = NULL; x < Range_; x += Move_)
	//	{
	//		for (int z = NULL; z < Range_; z += Move_)
	//		{
	//			RayCastData data;
	//			data.start = XMFLOAT3PRUSXMFLOAT3(transform_.position_, XMFLOAT3((float)x, NULL, (float)-z));
	//			data.dir = Shot_;
	//			Model::RayCast(hCourseModel, &data);

	//			if (!data.hit)
	//			{
	//				XMFLOAT3 prevSto = data.start;

	//				RayCastData L_data;
	//				L_data.start = prevSto;
	//				L_data.dir = matL;
	//				Model::RayCast(hCourseModel, &L_data);

	//				RayCastData R_data;
	//				R_data.start = prevSto;
	//				R_data.dir = matR;
	//				Model::RayCast(hCourseModel, &R_data);

	//				RayCastData B_data;
	//				B_data.start = prevSto;
	//				B_data.dir = matB;
	//				Model::RayCast(hCourseModel, &B_data);

	//				RayCastData F_data;
	//				F_data.start = prevSto;
	//				F_data.dir = matF;
	//				Model::RayCast(hCourseModel, &F_data);

	//				int dir = GetShortest(L_data, R_data, F_data, B_data);

	//				switch (dir)
	//				{
	//				case left: Storage.x = transform_.position_.x - L_data.dist + out; break;
	//				case right: Storage.x = transform_.position_.x + R_data.dist - out; break;
	//				case front: Storage.z = transform_.position_.z - F_data.dist + out; break;
	//				case back: Storage.z = transform_.position_.z + B_data.dist - out; break;
	//				}

	//				bool Near = false;

	//				for (auto it = Checkpoint_.begin(); it != Checkpoint_.end(); it++)
	//				{
	//					float dist = Getdistance(*it, Storage);
	//					if (dist < 5)
	//					{
	//						Near = true;
	//					}
	//					else
	//					{
	//						Near = false;
	//					}
	//				}

	//				if (!Near)
	//				{
	//					Checkpoint_.push_back(Storage);
	//				}
	//				
	//			}
	//		}
	//	}
	//}
}

int Navigation::GetShortest(RayCastData L, RayCastData R, RayCastData F, RayCastData B)
{
	if (L.dist > R.dist && L.dist > F.dist && L.dist > B.dist)
	{
		return left;
	}
	else if (R.dist > F.dist && R.dist > B.dist)
	{
		return right;
	}
	else if (F.dist > B.dist)
	{
		return front;
	}
	else
	{
		return back;
	}
}

int Navigation::Correcter(float Target)
{
	Target = Target / 15;
	Target = (float)(int)(Target + 0.8f);
	Target = Target * 15;
	return (int)Target;
}

void Navigation::UpdateCourseout()
{
	pPlayer_ = (Player*)FindObject("Player");

	transform_.position_ = pPlayer_->GetPosition();
	transform_.rotate_ = pPlayer_->GetRotate();

	transform_.rotate_.y = (float)Correcter(transform_.rotate_.y);

	//機体のX軸,Y軸の角度の取得
	XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
	mRotate = mRotate * XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

	XMVECTOR vLeft = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
	vLeft = XMVector3TransformCoord(vLeft, mRotate);
	vLeft = XMVector3Normalize(vLeft);
	XMFLOAT3 matLeft;
	XMStoreFloat3(&matLeft, vLeft);

	XMVECTOR vRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	vRight = XMVector3TransformCoord(vRight, mRotate);
	vRight = XMVector3Normalize(vRight);
	XMFLOAT3 matRight;
	XMStoreFloat3(&matRight, vRight);

	pCourse_ = (Course*)FindObject("Course");
	short hCourseModel = (short)pCourse_->GetModelHandle();

	RayCastData LeftData;
	LeftData.start = transform_.position_;
	LeftData.dir = matLeft;
	Model::RayCast(hCourseModel, &LeftData);

	RayCastData RightData;
	RightData.start = transform_.position_;
	RightData.dir = matRight;
	Model::RayCast(hCourseModel, &RightData);

	const float adj = 5.0f;

	

	if (LeftData.hit)
	{
		XMVECTOR vPos = XMVectorSet(-LeftData.dist - adj, NULL, NULL, NULL);
		vPos = XMVector3TransformCoord(vPos, mRotate);
		XMVECTOR pos = XMLoadFloat3(&transform_.position_);
		pos += vPos;
		XMStoreFloat3(&ObjLeft, pos);
	}
	if (RightData.hit)
	{
		XMVECTOR vPos = XMVectorSet(RightData.dist + adj, NULL, NULL, NULL);
		vPos = XMVector3TransformCoord(vPos, mRotate);
		XMVECTOR pos = XMLoadFloat3(&transform_.position_);
		pos += vPos;
		XMStoreFloat3(&ObjRight, pos);
	}

}

void Navigation::Release()
{
	SAFE_RELEASE(pCourse_);
}
