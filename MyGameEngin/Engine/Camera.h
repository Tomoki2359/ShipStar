#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"

using namespace DirectX;

//-----------------------------------------------------------
//カメラ
//-----------------------------------------------------------
namespace Camera
{
	//初期化（プロジェクション行列作成）
	void Initialize(int WINDOW_WIDTH, int WINDOW_HEIGHT);

	//カメラの初期位置
	void InitCamera();

	//更新（ビュー行列作成）
	void Update();

	//視点（カメラの位置）を設定
	void SetPosition(XMVECTOR position);

	//焦点（見る位置）を設定
	void SetTarget(XMVECTOR target);

	//ビュー行列を取得
	XMMATRIX GetViewMatrix();

	//プロジェクション行列を取得
	XMMATRIX GetProjectionMatrix();
};