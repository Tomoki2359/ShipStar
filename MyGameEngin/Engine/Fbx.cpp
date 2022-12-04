#include "Fbx.h"
#include "Direct3D.h"
#include "Camera.h"
#include "Math.h"

Fbx::Fbx() :
	vertexCount_(0), polygonCount_(0), materialCount_(0),
	pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr),
	indexCount_(nullptr), pMaterialList_(nullptr), ppIndexData_(), vertices()
{
}

Fbx::~Fbx()
{
	Release();
}

HRESULT Fbx::Load(std::string fileName)
{
	//マネージャを生成
	FbxManager* pFbxManager = FbxManager::Create();

	//インポーターを生成
	FbxImporter* fbxImporter = FbxImporter::Create(pFbxManager, "imp");
	fbxImporter->Initialize(fileName.c_str(), -1, pFbxManager->GetIOSettings());

	//シーンオブジェクトにFBXファイルの情報を流し込む
	FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "fbxscene");
	fbxImporter->Import(pFbxScene);
	fbxImporter->Destroy();


	//メッシュ情報を取得
	FbxNode* pRootNode = pFbxScene->GetRootNode();
	FbxNode* pNode = pRootNode->GetChild(0);
	FbxMesh* pMesh = pNode->GetMesh();

	//現在のカレントディレクトリを覚えておく
	WCHAR defaultCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

	//引数のfileNameからディレクトリ部分を取得
	wchar_t wtext[FILENAME_MAX];
	size_t ret;
	mbstowcs_s(&ret, wtext, fileName.c_str(), fileName.length());
	WCHAR dir[MAX_PATH];
	_wsplitpath_s(wtext, nullptr, 0, dir, MAX_PATH, nullptr, 0, nullptr, 0);

	//カレントディレクトリ変更
	SetCurrentDirectory(dir);


	//各情報の個数を取得
	vertexCount_ = pMesh->GetControlPointsCount();	//頂点の数
	polygonCount_ = pMesh->GetPolygonCount();		//ポリゴンの数
	materialCount_ = pNode->GetMaterialCount();		//マテリアルの数
	pMaterialList_ = new MATERIAL[materialCount_];
	

	InitVertex(pMesh);		//頂点バッファ準備
	InitIndex(pMesh);		//インデックスバッファ準備
	IntConstantBuffer();	//コンスタントバッファ準備
	InitMaterial(pNode);


	//終わったら戻す
	SetCurrentDirectory(defaultCurrentDir);

	//マネージャ解放
	pFbxManager->Destroy();
	return S_OK;
}

//頂点バッファ準備
void Fbx::InitVertex(fbxsdk::FbxMesh* pMesh)
{
	//頂点情報を入れる配列
	vertices = new VERTEX[vertexCount_];

	//全ポリゴン
	for (DWORD poly = 0; poly < (unsigned)polygonCount_; poly++)
	{
		//3頂点分
		for (int vertex = 0; vertex < 3; vertex++)
		{
			//調べる頂点の番号
			int index = pMesh->GetPolygonVertex(poly, vertex);

			//頂点の位置
			FbxVector4 pos = pMesh->GetControlPointAt(index);
			vertices[index].position = XMFLOAT3((float)pos[0], (float)pos[1], (float)pos[2]);

			//頂点のUV
			FbxLayerElementUV* pUV = pMesh->GetLayer(0)->GetUVs();
			int uvIndex = pMesh->GetTextureUVIndex(poly, vertex, FbxLayerElement::eTextureDiffuse);
			FbxVector2  uv = pUV->GetDirectArray().GetAt(uvIndex);
			vertices[index].uv = XMVectorSet((float)uv.mData[0], (float)(1.0f - uv.mData[1]), 0.0f, 0.0f);

			//頂点の法線
			FbxVector4 Normal;
			pMesh->GetPolygonVertexNormal(poly, vertex, Normal);	//ｉ番目のポリゴンの、ｊ番目の頂点の法線をゲット
			vertices[index].normal = XMVectorSet((float)Normal[0], (float)Normal[1], (float)Normal[2], 0.0f);
			vertices[index].color_ = { 0.5f, 0.0f, 1.0f, 0.3f };

		}
	}


	HRESULT hr;
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * vertexCount_;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"頂点バッファの作成に失敗しました", L"エラー", MB_OK);
		//return hr;
	}
}

//インデックスバッファ準備
void Fbx::InitIndex(fbxsdk::FbxMesh* pMesh)
{
	pIndexBuffer_ = new ID3D11Buffer * [materialCount_];
	indexCount_ = new int[materialCount_];
	ppIndexData_ = new DWORD * [materialCount_];

	int* index = new int[(long long)polygonCount_ * 3];

	int count = 0;
	for (int i = 0; i < materialCount_; i++)
	{

		//全ポリゴン
		for (DWORD poly = 0; poly < (unsigned)polygonCount_; poly++)
		{
			FbxLayerElementMaterial* mtl = pMesh->GetLayer(0)->GetMaterials();
			int mtlId = mtl->GetIndexArray().GetAt(poly);

			if (mtlId == i)
			{

				//3頂点分
				for (DWORD vertex = 0; vertex < 3; vertex++)
				{
					index[count] = pMesh->GetPolygonVertex(poly, vertex);
					count++;
				}
			}
		}
		indexCount_[i] = count;

		D3D11_BUFFER_DESC   bd;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(int) * polygonCount_ * 3;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = index;
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;

		HRESULT hr;
		hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_[i]);
		if (FAILED(hr))
		{
			MessageBox(NULL, L"インデックスバッファの作成に失敗しました", L"エラー", MB_OK);
			//return hr;
		}

		pMaterialList_[i].polygonCount = count / 3;
		ppIndexData_[i] = new DWORD[count];
		memcpy(ppIndexData_[i], index, sizeof(DWORD) * count);
	}
	if ((index) != nullptr)
	{
		delete[] index;
		index = nullptr;
	}
}

void Fbx::IntConstantBuffer()
{
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	HRESULT hr;
	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"コンスタントバッファの作成に失敗しました", L"エラー", MB_OK);
	}
}


void Fbx::InitMaterial(fbxsdk::FbxNode* pNode)
{

	for (int i = 0; i < materialCount_; i++)
	{
		//i番目のマテリアル情報を取得
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);

		//テクスチャ情報
		FbxProperty  lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);

		//テクスチャの数数
		int fileTextureCount = lProperty.GetSrcObjectCount<FbxFileTexture>();

		//テクスチャあり
		if (fileTextureCount != 0)
		{
			FbxFileTexture* textureInfo = lProperty.GetSrcObject<FbxFileTexture>(0);
			const char* textureFilePath = textureInfo->GetRelativeFileName();

			//ファイル名+拡張だけにする
			char name[_MAX_FNAME];	//ファイル名
			char ext[_MAX_EXT];	//拡張子
			_splitpath_s(textureFilePath, nullptr, 0, nullptr, 0, name, _MAX_FNAME, ext, _MAX_EXT);
			sprintf_s(name, "%s%s", name, ext);


			//ファイルからテクスチャ作成
			pMaterialList_[i].pTexture = new Texture;
			wchar_t wtext[FILENAME_MAX];
			size_t ret;
			mbstowcs_s(&ret, wtext, name, strlen(textureFilePath));

			pMaterialList_[i].pTexture->Load(wtext);
		}

		//テクスチャ無し
		else
		{
			pMaterialList_[i].pTexture = nullptr;

			//マテリアルの色
			FbxSurfaceLambert* pMaterial = (FbxSurfaceLambert*)pNode->GetMaterial(i);
			FbxDouble3  diffuse = pMaterial->Diffuse;
			pMaterialList_[i].diffuse = XMFLOAT4((float)diffuse[0], (float)diffuse[1], (float)diffuse[2], 1.0f);
		}
	}
}


void Fbx::Draw(Transform& transform, float alpha, XMFLOAT3 color, bool zBuffer, float brightness)
{
	Direct3D::SetShader(SHADER_3D);

	//ZバッファのON/OFF
	Direct3D::SetDepthBafferWriteEnable(zBuffer);



	for (int i = 0; i < materialCount_; i++)
	{
		CONSTANT_BUFFER cb;
		cb.matWVP = XMMatrixTranspose(transform.GetWorldMatrix() * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
		cb.matNormal = XMMatrixTranspose(transform.GetNormalMatrix());
		cb.diffuseColor = pMaterialList_[i].diffuse;
		cb.isTexture = pMaterialList_[i].pTexture != nullptr;
		cb.red_ = color.x;
		cb.green_ = color.y;
		cb.blue_ = color.z;
		cb.alpha_ = alpha;
		cb.brightness_ = brightness;

		D3D11_MAPPED_SUBRESOURCE pdata;
		Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
		memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る


		if (pMaterialList_[i].pTexture)
		{
			ID3D11SamplerState* pSampler = pMaterialList_[i].pTexture->GetSampler();
			Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);

			ID3D11ShaderResourceView* pSRV = pMaterialList_[i].pTexture->GetSRV();
			Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);
		}

		Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//再開

		//頂点バッファ
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

		// インデックスバッファーをセット
		stride = sizeof(int);
		offset = 0;
		Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_[i], DXGI_FORMAT_R32_UINT, 0);

		//コンスタントバッファ
		Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
		Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

		//描画
		Direct3D::pContext->DrawIndexed(indexCount_[i], 0, 0);
	}
	Direct3D::SetDepthBafferWriteEnable(true);
}

void Fbx::Release()
{
	/*SAFE_RELEASE(pConstantBuffer_);

	for (int i = 0; i < materialCount_; i++)
	{
		SAFE_DELETE(pIndexBuffer_[i]);
	}
	SAFE_DELETE_ARRAY(pIndexBuffer_);

	SAFE_RELEASE(pVertexBuffer_);*/
	for (int i = 0; i < materialCount_; i++)
	{
		SAFE_DELETE_ARRAY(ppIndexData_[i]);
	}
	SAFE_DELETE_ARRAY(ppIndexData_);
	SAFE_DELETE_ARRAY(vertices);
	SAFE_RELEASE(pConstantBuffer_);
	for (int i = 0; i < materialCount_; i++) {
		SAFE_DELETE_ARRAY(pIndexBuffer_);
	}
	SAFE_DELETE_ARRAY(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}

//レイキャスト
void Fbx::RayCast(RayCastData* data)
{
	data->hit = FALSE;

	//マテリアル毎
	for (DWORD i = 0; i < (unsigned)materialCount_; i++)
	{
		//そのマテリアルのポリゴン毎
		for (DWORD j = 0; j < pMaterialList_[i].polygonCount; j++)
		{
			//3頂点
			XMFLOAT3 ver[3];

			ver[0] = vertices[ppIndexData_[i][j * 3 + 0]].position;
			ver[1] = vertices[ppIndexData_[i][j * 3 + 1]].position;
			ver[2] = vertices[ppIndexData_[i][j * 3 + 2]].position;

			BOOL  hit = FALSE;
			float dist = 0.0f;

			hit = Direct3D::Intersect(data->start, data->dir, ver[0], ver[1], ver[2], &dist);

			if (hit && dist < data->dist)
			{
				data->hit = TRUE;
				data->dist = dist;
			}
		}
	}
}

void Fbx::PushOut(XMFLOAT3* position, float size, XMFLOAT3 dir)
{
	XMVECTOR vDir = XMLoadFloat3(&dir);
	vDir = -vDir;
	vDir = XMVector3Normalize(vDir);
	XMStoreFloat3(&dir, vDir);
	float dist1 = 9999.0f;
	float dist2 = 9999.0f;
	XMFLOAT3 pos1 = *position;
	XMFLOAT3 pos2 = XMFLOAT3(position->x + dir.x, position->y + dir.y, position->z + dir.z);

	float Storage = dist1;

	//マテリアル毎
	for (DWORD i = 0; i < (unsigned)materialCount_; i++)
	{
		//そのマテリアルのポリゴン毎
		for (DWORD j = 0; j < pMaterialList_[i].polygonCount; j++)
		{
			//3頂点
			XMFLOAT3 ver[3];

			ver[0] = vertices[ppIndexData_[i][j * 3 + 0]].position;
			ver[1] = vertices[ppIndexData_[i][j * 3 + 1]].position;
			ver[2] = vertices[ppIndexData_[i][j * 3 + 2]].position;


			Math::CircleToPlane(pos1, size, ver[0], ver[1], ver[2], &dist1);
			if (dist1 < Storage)
			{
				Storage = dist1;
				Math::CircleToPlane(pos2, size, ver[0], ver[1], ver[2], &dist2);
			}
			else
			{
				dist1 = Storage;
			}
			
		}
	}

	float ans = size / (dist2 - dist1);
	XMFLOAT3 adir = XMFLOAT3(dir.x * ans, dir.y * ans, dir.z * ans);
	*position = XMFLOAT3(position->x + adir.x, position->y + adir.y, position->z + adir.z);
}
