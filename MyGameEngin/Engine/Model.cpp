#include "Model.h"
#include "Define.h"

namespace Model
{
	struct MODEL
	{
		Fbx* pFbx = nullptr;
		Transform TransformModel;
		XMFLOAT3 color_ = XMFLOAT3(1.0f, 1.0f, 1.0f);
		std::string FileModel;
		float alpha_ = 1.0f;
		float brightness_ = 0.5f;
		bool zBuffer_ = true;
	};
	std::vector<MODEL*> modelList_;
}

int Model::Load(std::string fileName)
{
	MODEL* pLoadModel;
	pLoadModel = new MODEL;
	pLoadModel->FileModel = fileName;
	pLoadModel->pFbx = nullptr;
	for (int i = 0; i < modelList_.size(); i++)
	{
		if (modelList_[i]->FileModel == fileName)
		{
			pLoadModel->pFbx = modelList_[i]->pFbx;
			break;
		}
	}

	if (pLoadModel->pFbx == nullptr)
	{
		pLoadModel->pFbx = new Fbx;
		pLoadModel->pFbx->Load(fileName);
	}


	modelList_.push_back(pLoadModel);
	return modelList_.size() - 1;
}


void Model::Draw(int hModel_)
{
	modelList_[hModel_]->pFbx->Draw(modelList_[hModel_]->TransformModel, modelList_[hModel_]->alpha_, modelList_[hModel_]->color_,modelList_[hModel_]->zBuffer_, modelList_[hModel_]->brightness_);
}

void Model::Release()
{
	for (int i = 0; i < modelList_.size(); i++)
	{
		bool isExist = false;	//今消そうとしているFbxデータを参照してるやつがいるかどうか
		for (int j = i + 1; j < modelList_.size(); j++)
		{
			if (modelList_[i]->pFbx == modelList_[j]->pFbx)
			{
				isExist = true;
				break;
			}
		}
		//もうそのデータを誰も参照してなければ
		if (!isExist)
		{
			SAFE_DELETE(modelList_[i]->pFbx);
		}
		SAFE_DELETE(modelList_[i]);
	}
	modelList_.clear();
}

void Model::SetAlpha(int hModel_, int alpha)
{
	modelList_[hModel_]->alpha_ = (float)alpha / 255;
}

void Model::SetColor(int hModel_, int red, int green, int blue)
{
	modelList_[hModel_]->color_ = XMFLOAT3((float)red / 255, (float)green / 255, (float)blue / 255);
}

void Model::SetBrightness(int hModel_, float brightness)
{
	modelList_[hModel_]->brightness_ = brightness;
}

void Model::AllRelease()
{
	for (int i = 0; i < modelList_.size(); i++)
	{
		if (modelList_[i] != nullptr)
		{
			Release();
		}
	}
	modelList_.clear();
}

//ZバッファのON/OFF
void Model::IsZBuffer(int hModel_, bool zBuffer)
{
	modelList_[hModel_]->zBuffer_ = zBuffer;
}

void Model::AllSetAlpha(int alpha)
{
	for (int i = 0; i < modelList_.size(); i++)
	{
		modelList_[i]->alpha_ = (float)alpha / UINT8_MAX;
	}
}

void Model::SetTransform(int hModel_, Transform transform_)
{
	modelList_[hModel_]->TransformModel = transform_;
}

//レイキャスト（レイを飛ばして当たり判定）
void Model::RayCast(int handle, RayCastData* data)
{
	XMFLOAT3 target;
	target.x = data->start.x + data->dir.x;
	target.y = data->start.y + data->dir.y;
	target.z = data->start.z + data->dir.z;
	XMMATRIX matInv = XMMatrixInverse(nullptr, modelList_[handle]->TransformModel.GetWorldMatrix());
	XMVECTOR vecStart = XMVector3TransformCoord(XMLoadFloat3(&data->start), matInv);
	XMVECTOR vecTarget = XMVector3TransformCoord(XMLoadFloat3(&target), matInv);
	XMVECTOR vecDir = vecTarget - vecStart;

	XMStoreFloat3(&data->start, vecStart);
	XMStoreFloat3(&data->dir, vecDir);

	modelList_[handle]->pFbx->RayCast(data);
}

void Model::PushOut(int handle, XMFLOAT3* position, float size, XMFLOAT3 dir)
{
	XMFLOAT3 target = XMFLOAT3(position->x + dir.x, position->y + dir.y, position->z + dir.z);
	/*XMMATRIX matInv = XMMatrixInverse(nullptr, modelList_[handle]->TransformModel.GetWorldMatrix());
	XMVECTOR vecStart = XMVector3TransformCoord(XMLoadFloat3(position), matInv);
	XMVECTOR vecTarget = XMVector3TransformCoord(XMLoadFloat3(&target), matInv);
	XMVECTOR vecDir = vecTarget - vecStart;*/

	XMVECTOR vecStart = XMLoadFloat3(position);
	XMVECTOR vecTarget = XMLoadFloat3(&target);
	XMVECTOR vecDir = vecTarget - vecStart;

	XMStoreFloat3(position, vecStart);
	XMStoreFloat3(&dir, vecDir);

	modelList_[handle]->pFbx->PushOut(position, size, dir);
}
