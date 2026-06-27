//===================================================
//
// タイトルクラス [title.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// インクルードファイル
//***************************************************
#include "Scene/title.h"
#include "Base/manager.h"
#include "Base/camera.h"

#include "ObjectBase/object2d.h"
#include "ObjectBase/objectx.h"
#include "Mesh/mesh_field.h"
#include "ObjectBase/object3d.h"
#include "ObjectBase/billboard.h"
#include "Player/player.h"
#include "ObjectX/rotation_sphere_field.h"

#include "Debug/line.h"
#include "Constants/color_constants.h"
#include "Debug/debug_parameter.h"

//===================================================
// コンストラクタ
//===================================================
CTitle::CTitle()
{
}

//===================================================
// デストラクタ
//===================================================
CTitle::~CTitle()
{
}

//===================================================
// 初期化処理
//===================================================
HRESULT CTitle::Init(void)
{
	//CObject2D::Create(
	//	{ 640.0f,360.0f,0.0f },
	//	{ 100.0f,100.0f,0.0f });

	// カメラのクラス
	CCamera* pCamera = CManager::Instance().GetCamera();

	pCamera->SetCamera(
		{ 0.0f,300.0f,-300.0f },
		{ 0.0f,1.0f,0.0f },
		{ D3DX_PI * 0.65f,0.0f,0.0f });

	// モデルのXファイルの生成
	CMeshField::Create(Const::VEC3_NULL, { 500.0f,0.0f,500.0f }, { 50,50 }, "data/TEXTURE/field.png");
	CPlayer::Create({ 0.0f,100.0f,0.0f});

	// 生成処理
	m_pRotationSphereField = CRotationSphereField::Create({ 0.0f,100.0f,0.0f});

	// 線の描画クラスの初期化処理
	CLineRenderer::Instance().Init();

	return S_OK;
}

//===================================================
// 終了処理
//===================================================
void CTitle::Uninit(void)
{
	// 終了処理
	CLineRenderer::Instance().Uninit();
}

//===================================================
// 更新処理
//===================================================
void CTitle::Update(void)
{
	// 更新処理
	CLineRenderer::Instance().Update();

	CDebugParameter::Instance().UpdateParameter();

	CDebugParameter::Instance().PrintDebug();
}

//===================================================
// 描画処理
//===================================================
void CTitle::Draw(void)
{
	// 線の描画クラスの取得
	CLineRenderer& line = CLineRenderer::Instance();

	// 軸の描画
	line.AddLine(D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(5000.0f, 0.0f, 0.0f), Color::RED);
	line.AddLine(D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 5000.0f, 0.0f), Color::GREEN);
	line.AddLine(D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 5000.0f), Color::BLUE);

	D3DXVECTOR3 size = PLANE_SIZE;

	float fRateSizeX = size.x / NUM_PLANE_LINE;
	float fRateSizeZ = size.z / NUM_PLANE_LINE;

	// 分割数回す
	for (int nCnt = 0; nCnt <= NUM_PLANE_LINE; nCnt++)
	{
		// 基準の位置
		D3DXVECTOR3 basePos = size * 0.5f;

		// 割合に基づいた位置
		D3DXVECTOR3 ratePos = { nCnt * fRateSizeX , 0.0f, nCnt * fRateSizeZ };

		// 横の線の追加
		line.AddLine(D3DXVECTOR3(-basePos.x, 0.0f, basePos.z - ratePos.z), D3DXVECTOR3(basePos.x, 0.0f, basePos.z - ratePos.z), Const::WHITE);

		// 縦の線の追加
		line.AddLine(D3DXVECTOR3(-basePos.x + ratePos.x, 0.0f, -basePos.z), D3DXVECTOR3(-basePos.x + ratePos.x, 0.0f, basePos.z), Const::WHITE);
	}

	// 描画処理
	CLineRenderer::Instance().Draw();
}
