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

	const float error = 0.001f;	//åÎç∑èCê≥ÇÃÇΩÇﬂÇÃíËêî
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
	: GameObject(parent, "Navigation"), pCourse_(nullptr), Left_(), Right_(),
	Upper_Goal(), Left_Goal(), Right_Goal()
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

	Right_ = XMFLOAT3(Right_.x, Right_.y - ray.dist, Right_.z);
	Left_ = XMFLOAT3(Left_.x, Left_.y - ray.dist, Left_.z);

	ray.dir = matU;
	Model::RayCast(hCourseModel, &ray);

	Upper_Goal = XMFLOAT3(transform_.position_.x, transform_.position_.y + ray.dist, transform_.position_.z);

	Left_Goal = Left_;
	Right_Goal = Right_;

	Scan();
}

void Navigation::Scan()
{
	pCourse_ = (Course*)FindObject("Course");
	int hCourseModel = pCourse_->GetModelHandle();

	for (int i = NULL; i < DIVISION_MAX; i++)
	{
		//ëñç∏Ç∑ÇÈãÊàÊÇ…à⁄ìÆÇ∑ÇÈ
		switch (i)
		{
		case UPPER_LEFT:transform_.position_ = XMFLOAT3((float)-Range_, Sky_, Range_); break;
		case UPPER_RIGHT:transform_.position_ = XMFLOAT3(NULL, Sky_, Range_); break;
		case LOWER_LEFT:transform_.position_ = XMFLOAT3((float)-Range_, Sky_, NULL); break;
		case LOWER_RIGHT:transform_.position_ = XMFLOAT3(NULL, Sky_, NULL); break;
		}

		//ëñç∏ãÊàÊì‡Ç≈ç≈Ç‡ó£ÇÍÇΩèÍèäÇäiî[ÇµÇƒÇ®Ç≠Ç‡ÇÃ
		XMFLOAT3 Storage = XMFLOAT3(NULL, NULL, NULL);

		const XMFLOAT3 Initial = XMFLOAT3(NULL, NULL, NULL);

		//îÕàÕì‡ÇÃëñç∏âÒêî
		//char Density = Range_ / Move_;
		for (int x = NULL; x < Range_; x += Move_)
		{
			for (int z = NULL; z < Range_; z += Move_)
			{
				RayCastData data;
				data.start = XMFLOAT3PRUSXMFLOAT3(transform_.position_, XMFLOAT3((float)x, NULL, (float)-z));
				data.dir = Shot_;
				Model::RayCast(hCourseModel, &data);

				if (data.hit && Getdistance(XMFLOAT3(data.start.x, NULL, data.start.z), Initial) > Getdistance(Storage, Initial))
				{
					//Storage = XMFLOAT3((float)-x, NULL, (float)z);
					XMFLOAT3 prevSto = XMFLOAT3((float)-x, NULL, (float)z);

					RayCastData L_data;
					L_data.start = prevSto;
					L_data.dir = matL;
					Model::RayCast(hCourseModel, &L_data);

					RayCastData R_data;
					R_data.start = prevSto;
					R_data.dir = matR;
					Model::RayCast(hCourseModel, &R_data);

					if (L_data.hit && R_data.hit)
					{
						Left_ = XMFLOAT3(prevSto.x - L_data.dist, prevSto.y, prevSto.z);
						Right_ = XMFLOAT3(prevSto.x + R_data.dist, prevSto.y, prevSto.z);
						Storage = XMFLOAT3AVERAGE(Left_, Right_);
					}
				}
			}
		}
		
		//StorageÇ™0Ç≈Ç»ÇØÇÍÇŒCheckpoint_Ç…äiî[Ç∑ÇÈ
		if (Getdistance(Storage, Initial) != NULL)
		{
			Checkpoint_.push_back(Storage);
		}

	}
}

void Navigation::Release()
{
	SAFE_RELEASE(pCourse_);
}
