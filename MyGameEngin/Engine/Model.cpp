#include "Model.h"
#include "Define.h"

namespace Model
{
	struct MODEL
	{
		Fbx* pFbx = nullptr;
		Transform TransformModel;
		std::string FileModel;
		float alpha_ = 1.0f;
		XMFLOAT3 color_ = XMFLOAT3(1.0f, 1.0f, 1.0f);
		bool zBuffer_ = true;
	};
	std::vector<MODEL*> modelList_;
}

int Model::Load(std::string fileName)
{
	MODEL* pLoadModel;
	pLoadModel = new MODEL;
	pLoadModel->FileModel = fileName;

	for (auto itr = modelList_.begin(); itr < modelList_.end(); itr++)
	{
		if (fileName == (*itr)->FileModel)
		{
			pLoadModel->pFbx = (*itr)->pFbx;
			return (int)modelList_.size() - 1;
		}
	}
	pLoadModel->pFbx = new Fbx;
	pLoadModel->pFbx->Load(pLoadModel->FileModel);
	modelList_.push_back(pLoadModel);
	return (int)modelList_.size() - 1;
}


void Model::Draw(int hModel_)
{
	modelList_[hModel_]->pFbx->Draw(modelList_[hModel_]->TransformModel, modelList_[hModel_]->alpha_, modelList_[hModel_]->color_,modelList_[hModel_]->zBuffer_);
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
