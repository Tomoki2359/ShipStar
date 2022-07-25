#include "Model.h"
#include "Define.h"

namespace Model
{
	struct MODEL
	{
		Fbx* pFbx = nullptr;
		Transform TransformModel;
		std::string FileModel;
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
	modelList_[hModel_]->pFbx->Draw(modelList_[hModel_]->TransformModel);
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

void Model::SetTransform(int hModel_, Transform transform_)
{
	modelList_[hModel_]->TransformModel = transform_;
}