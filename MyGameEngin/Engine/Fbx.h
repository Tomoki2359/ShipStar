#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"

#pragma comment(lib, "LibFbxSDK-MT.lib")
#pragma comment(lib, "LibXml2-MT.lib")
#pragma comment(lib, "zlib-MT.lib")

class Texture;

//���C�L���X�g�p�\����
struct RayCastData
{
	XMFLOAT3	start;	//���C���ˈʒu
	XMFLOAT3	dir;	//���C�̌����x�N�g��
	float       dist;	//�Փ˓_�܂ł̋���
	BOOL        hit;	//���C������������
	XMFLOAT3 normal;	//�@��

	RayCastData() : start(), dir(), dist(), hit(), normal() { dist = 99999.0f; }
};

class Fbx
{
	//�}�e���A��
	struct MATERIAL
	{
		Texture*	pTexture;
		XMFLOAT4	diffuse;
		DWORD		polygonCount;//�}�e���A���̃|���S����
	};
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
		XMFLOAT4	diffuseColor;
		int			isTexture;
	};

	struct VERTEX
	{
		XMFLOAT3 position;
		XMVECTOR uv;
		XMVECTOR normal;
		XMVECTOR color_;
	};

	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	int materialCount_;	//�}�e���A���̌�

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
	void    Draw(Transform& transform);
	void    Release();

	void RayCast(RayCastData* data);

private:
	void InitVertex(fbxsdk::FbxMesh* pMesh);
	void InitIndex(fbxsdk::FbxMesh* pMesh);
	void IntConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);
};