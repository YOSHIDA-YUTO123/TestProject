//===================================================
//
// カメラの処理 [camera.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// インクルードファイル
//***************************************************
#include "Base/camera.h"
#include "Base/renderer.h"
#include "Base/manager.h"
#include "Base/utility_math.h"
#include "Base/input.h"

//#ifdef _DEBUG
//#include "debug_proc.h"
//#endif // _DEBUG

//***************************************************
// カメラの情報
//***************************************************
namespace CameraInfo
{
	constexpr const char* LOAD_JSON_PATH	= "data/SYSTEM/scene_camera_animation.json";	// 読み込むファイルのパス
	constexpr float MAX_VIEW_TOP			= D3DX_PI;										// カメラの制限(上)
	constexpr float MAX_VIEW_BOTTOM			= 0.0f;											// カメラの制限(下)
	constexpr float VIEW_SPEED_ALPHA		= 0.01f;										// カメラのスピード
	constexpr float ZOOM_SPEED_ALPHA		= 0.1f;											// カメラのズームスピード
	constexpr float NEAR_PLANE				= 10.0f;										// カメラの近平面
	constexpr float FAR_PLANE				= 50000.0f;									// カメラの遠平面
};

//===================================================
// コンストラクタ
//===================================================
CCamera::CCamera() :
	m_fDistance(0.0f),
	m_mtxProjection(),
	m_mtxView(),
	m_posR(Const::VEC3_NULL),
	m_posV(Const::VEC3_NULL),
	m_rot(Const::VEC3_NULL),
	m_vecU(Const::VEC3_NULL)
{
}

//===================================================
// デストラクタ
//===================================================
CCamera::~CCamera()
{
}

//===================================================
// 初期化処理
//===================================================
HRESULT CCamera::Init(void)
{
	// 定数の名前空間
	using namespace CameraInfo;

	// 初期化する
	m_posV = Const::VEC3_NULL;
	m_posR = Const::VEC3_NULL;
	m_rot = Const::VEC3_NULL;
	m_vecU = Const::VEC_U;

	return S_OK;
}

//===================================================
// 終了処理
//===================================================
void CCamera::Uninit(void)
{
	//// 機能分回す
	//for (auto& system : m_pSystem)
	//{
	//	// 破棄
	//	system.reset();
	//}

	//// 要素をクリア
	//m_pSystem.clear();
}

//===================================================
// 更新処理
//===================================================
void CCamera::Update(void)
{
	// 定数の名前空間
	using namespace CameraInfo;

	//// 機能分回す
	//for (auto& system : m_pSystem)
	//{
	//	// 更新処理
	//	system->Update(m_posV, m_posR, m_rot);
	//}

	// 角度の正規化
	math::NormalizeRot(&m_rot.x);
	math::NormalizeRot(&m_rot.y);
	math::NormalizeRot(&m_rot.z);

	DebugCamera();

	DebugCameraMove();
}

//===================================================
// 描画処理
//===================================================
void CCamera::SetCamera(void)
{
	// 定数の名前空間
	using namespace CameraInfo;

	CRenderer* pRenderer = CManager::Instance().GetRenderer();

	//// レンダラーがnullだったら処理しない
	//if (pRenderer == nullptr)
	//{
	//	assert(false && "Camera_GetRenderer");
	//}

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		FOV,
		static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT),
		NEAR_PLANE,
		FAR_PLANE);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//===================================================
// カメラの設定処理
//===================================================
void CCamera::SetCamera(const D3DXVECTOR3& posV, const D3DXVECTOR3& posR, const D3DXVECTOR3& rot)
{
	// 初期化処理
	Init();

	m_posV = posV;
	m_posR = posR;
	m_rot = rot;

	float fRotX = m_posV.x - m_posR.x;
	float fRotY = m_posV.y - m_posR.y;
	float fRotZ = m_posV.z - m_posR.z;

	// 距離を求める
	m_fDistance = sqrtf((fRotX * fRotX) + (fRotY * fRotY) + (fRotZ * fRotZ));

	//カメラの注視点初期座標を設定
	m_posR.x = m_posV.x + sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
	m_posR.y = m_posV.y + cosf(m_rot.x) * m_fDistance;
	m_posR.z = m_posV.z + sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;

	// カメラの視点の情報
	m_posV.x = m_posR.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
	m_posV.y = m_posR.y - cosf(m_rot.x) * m_fDistance;
	m_posV.z = m_posR.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
}

//===================================================
// 選択中のオブジェクトにフォーカス処理
//===================================================
void CCamera::SetFocus(const D3DXVECTOR3& pos)
{
	//カメラの注視点初期座標を設定
	m_posR = pos;

	// カメラの視点の情報
	m_posV.x = m_posR.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
	m_posV.y = m_posR.y - cosf(m_rot.x) * m_fDistance;
	m_posV.z = m_posR.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
}

////===================================================
//// カメラのシステムの追加
////===================================================
//void CCamera::AddSystem(std::unique_ptr<CCameraSystemBase> pNewSystem)
//{
//	// 要素の追加
//	m_pSystem.push_back(std::move(pNewSystem));
//}

//===================================================
// カメラのデバッグの設定
//===================================================
void CCamera::DebugCamera(void)
{
	// 定数の名前空間
	using namespace CameraInfo;

	// マウスの取得
	CInputMouse* pMouse = CManager::Instance().GetInputMouse();

	//// マウスホイール
	//CCamera::MouseWheel();

	// キーボードの取得
	CInputKeyboard* pKeyboard = CManager::Instance().GetInputKeyboard();

	// マウスホイールの回転量の取得
	int nMouseWeel = pMouse->GetMouseWeel();

	// 手前に回していたら
	if (nMouseWeel < 0.0f)
	{
		m_fDistance += m_fDistance * ZOOM_SPEED_ALPHA;
	}
	// 奥に回したていたら
	else if (nMouseWeel > 0.0f)
	{
		m_fDistance -= m_fDistance * ZOOM_SPEED_ALPHA;
	}

	// ホイールを回しているなら
	if (nMouseWeel != 0)
	{
		// カメラの視点の情報
		m_posV.x = m_posR.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posV.y = m_posR.y - cosf(m_rot.x) * m_fDistance;
		m_posV.z = m_posR.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
	}

	// LALTを押していないなら処理しない
	if (pKeyboard->GetPress(DIK_LALT) == false) return;

	D3DXVECTOR2 Move = pMouse->GetPosition();
	D3DXVECTOR2 MoveOld = pMouse->GetOldPosition();

	D3DXVECTOR2 fAngle = Move - MoveOld;

	// 同時押し
	if (pMouse->OnMousePress(pMouse->LEFT) && pMouse->OnMousePress(pMouse->RIGHT))
	{
		D3DXVECTOR3 eye = m_posR - m_posV;
		D3DXVec3Normalize(&eye, &eye);

		D3DXVECTOR3 cross, cameraUp;
		D3DXVec3Cross(&cross, &m_vecU, &eye);

		D3DXVec3Cross(&cameraUp, &eye, &cross);
		D3DXVECTOR3 move = cross * (-fAngle.x);

		// 縦移動
		move += cameraUp * fAngle.y;

		// カメラの位置更新
		m_posV += move;
		m_posR += move;
	}
	else if (pMouse->OnMousePress(pMouse->RIGHT))
	{
		// 回転量を更新
		m_rot.y += fAngle.x * VIEW_SPEED_ALPHA;
		m_rot.x += fAngle.y * VIEW_SPEED_ALPHA;

		// 回転量を制限
		if (m_rot.x > CameraInfo::MAX_VIEW_TOP)
		{
			m_rot.x -= fAngle.y * VIEW_SPEED_ALPHA;
		}
		else if (m_rot.x < CameraInfo::MAX_VIEW_BOTTOM)
		{
			m_rot.x -= fAngle.y * VIEW_SPEED_ALPHA;
		}

		// カメラの注視点初期座標を設定
		m_posR.x = m_posV.x + sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posR.y = m_posV.y + cosf(m_rot.x) * m_fDistance;
		m_posR.z = m_posV.z + sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
	}
	else if (pMouse->OnMousePress(pMouse->LEFT))
	{
		//回転量を更新
		m_rot.y += fAngle.x * VIEW_SPEED_ALPHA;
		m_rot.x += fAngle.y * VIEW_SPEED_ALPHA;

		//回転量を制限
		if (m_rot.x > CameraInfo::MAX_VIEW_TOP)
		{
			m_rot.x -= fAngle.y * VIEW_SPEED_ALPHA;
		}
		else if (m_rot.x < CameraInfo::MAX_VIEW_BOTTOM)
		{
			m_rot.x -= fAngle.y * VIEW_SPEED_ALPHA;
		}

		// カメラの視点の情報
		m_posV.x = m_posR.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posV.y = m_posR.y - cosf(m_rot.x) * m_fDistance;
		m_posV.z = m_posR.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
	}
}

//===================================================
// デバッグのカメラの移動
//===================================================
void CCamera::DebugCameraMove(void)
{
	// キーボードの取得
	CInputKeyboard* pKeyboard = CManager::Instance().GetInputKeyboard();

	// LALTを押しているなら処理しない
	if (pKeyboard->GetPress(DIK_LALT)) return;

	// マウスの取得
	CInputMouse* pMouse = CManager::Instance().GetInputMouse();

	D3DXVECTOR2 mouseMove = pMouse->GetPosition();
	D3DXVECTOR2 mouseMoveOld = pMouse->GetOldPosition();

	D3DXVECTOR2 move = mouseMove - mouseMoveOld;

	float fSpeed = 10.0f;

	// 右クリックを押している間
	if (pMouse->OnMousePress(pMouse->RIGHT))
	{
		D3DXVECTOR3 forward =
		{
			sinf(m_rot.y),
			0.0f,
			cosf(m_rot.y)
		};

		D3DXVECTOR3 right =
		{
			cosf(m_rot.y),
			0.0f,
			sinf(m_rot.y)
		};

		m_posV += -forward * (move.y * fSpeed);
		m_posV += -right * (move.x * fSpeed);

		m_posR += -forward * (move.y * fSpeed);
		m_posR += -right * (move.x * fSpeed);
	}
}