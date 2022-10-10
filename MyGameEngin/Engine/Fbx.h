#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include "Texture.h"

#pragma comment(lib, "LibFbxSDK-MT.lib")
#pragma comment(lib, "LibXml2-MT.lib")
#pragma comment(lib, "zlib-MT.lib")

class Texture;

class Fbx
{
	//マテリアル
	struct MATERIAL
	{
		Texture*	pTexture;
		XMFLOAT4	diffuse;
		DWORD		polygonCount;//マテリアルのポリゴン数
	};
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
		XMFLOAT4	diffuseColor;
		int			isTexture;
		float		red_;
		float		green_;
		float		blue_;
		float		alpha_;
	};

	struct VERTEX
	{
		XMFLOAT3 position;
		XMVECTOR uv;
		XMVECTOR normal;
		XMVECTOR color_;
	};

	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
	int materialCount_;	//マテリアルの個数

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer** pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	MATERIAL* pMaterialList_;

	int* indexCount_;
	DWORD** ppIndexData_;

	VERTEX* vertices;

public:
	Fbx();
	~Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform, float alpha, XMFLOAT3 color,bool zBuffer);
	void    Release();

	void RayCast(RayCastData* data);

	void PushOut(XMFLOAT3* position, float size, XMFLOAT3 dir);

private:
	void InitVertex(fbxsdk::FbxMesh* pMesh);
	void InitIndex(fbxsdk::FbxMesh* pMesh);
	void IntConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);
};