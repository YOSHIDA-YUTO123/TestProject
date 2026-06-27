//===================================================
//
// プレイヤーのクラス [player.h]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// インクルードファイル
//***************************************************
#include "Player/player.h"
#include "Character/character.h"
#include "System/input_system.h"
#include "Base/manager.h"
#include "Base/camera.h"
#include "Base/renderer.h"
#include "System/motion.h"
#include "Scene/title.h"
#include "ObjectX/rotation_sphere_field.h"
#include "ObjectX/map_object.h"

//===================================================
// コンストラクタ
//===================================================
CPlayer::CPlayer() : 
	m_pCharacter(nullptr),
	m_transform(),
	m_move(Const::VEC3_NULL),
	m_fSpeed(5.0f)
{
}

//===================================================
// デストラクタ
//===================================================
CPlayer::~CPlayer()
{
	m_pCharacter.reset();
}

//===================================================
// 生成処理
//===================================================
CPlayer* CPlayer::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	CPlayer* pInstance = new CPlayer;

	Transform3D transformParam = {};
	transformParam.pos = pos;

	pInstance->m_pCharacter = 
		std::make_unique<CCharacter3D>("data/MOTION/motion.txt");

	// パラメータの設定
	pInstance->m_transform.SetParam(transformParam);

	pInstance->m_offsetPos = pos;

	// 初期化処理
	if (FAILED(pInstance->Init()))
	{
		// 終了処理
		pInstance->Uninit();
		pInstance = nullptr;
		return nullptr;
	}
	return pInstance;
}

//===================================================
// 初期化処理
//===================================================
HRESULT CPlayer::Init(void)
{

	return S_OK;
}

//===================================================
// 終了処理
//===================================================
void CPlayer::Uninit(void)
{
	// 自分自身の破棄
	Release();
}

//===================================================
// 更新処理
//===================================================
void CPlayer::Update(void)
{
	if (m_pCharacter != nullptr)
	{
		// 更新処理
		m_pCharacter->Update();
	}

	// パラメータの取得
	Transform3D transformParam = m_transform.GetParam();

	// モーションのクラスの取得
	CMotion* pMotion = m_pCharacter->GetMotion();

	// キーボード移動
	if (KeyboardMove(transformParam))
	{
		if (pMotion != nullptr)
		{
			// モーションの再生
			pMotion->Play(MOTIONTYPE_MOVE, true, 10);
		}
	}
	else
	{
		if (pMotion != nullptr)
		{
			// モーションの再生
			pMotion->Play(MOTIONTYPE_NEUTRAL, true, 10);
		}
	}

	m_move.x *= 0.5f;
	m_move.z *= 0.5f;

	//transformParam.pos += m_move;

	transformParam.pos = CTitle::GetRotationSphereField()->OnTopPosition();

	// パラメータの設定
	m_transform.SetParam(transformParam);

	// ワールドマトリックスの計算胥吏
	m_transform.CalculationMatrix();
}

//===================================================
// 描画処理
//===================================================
void CPlayer::Draw(void)
{
	// マネージャー
	CManager& manager = CManager::Instance();

	// レンダラーの取得
	CRenderer* pRenderer = manager.GetRenderer();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// マトリックスの設定
	m_transform.BindMatrix(pDevice);

	if (m_pCharacter != nullptr)
	{
		// 更新処理
		m_pCharacter->Draw();
	}
}

//===================================================
// キーボード移動
//===================================================
bool CPlayer::KeyboardMove(Transform3D& transformParam)
{
	// カメラの取得
	CCamera* pCamera = CManager::Instance().GetCamera();

	// 取得できないなら処理を飛ばす
	if (pCamera == nullptr)
	{
		return false;
	}

	// カメラの向きの取得
	float fCameraRotY = pCamera->GetRotation().y;

	// 目的の向き
	float fRotDest = 0.0f;

	// 移動したかどうか
	bool bMove = false;

	// 左移動
	if (InputSystem::MoveLeft())
	{
		// 正面移動
		if (InputSystem::MoveForward())
		{
			m_move.x += sinf(fCameraRotY - D3DX_PI * 0.25f) * m_fSpeed;
			m_move.z += cosf(fCameraRotY - D3DX_PI * 0.25f) * m_fSpeed;

			bMove = true;
		}
		// 後ろ移動
		else if (InputSystem::MoveBack())
		{
			m_move.x += sinf(fCameraRotY - D3DX_PI * 0.75f) * m_fSpeed;
			m_move.z += cosf(fCameraRotY - D3DX_PI * 0.75f) * m_fSpeed;

			bMove = true;
		}
		else
		{
			m_move.z += sinf(fCameraRotY) * m_fSpeed;
			m_move.x -= cosf(fCameraRotY) * m_fSpeed;

			bMove = true;
		}
	}
	// 右移動
	else if (InputSystem::MoveRight())
	{
		// 正面移動
		if (InputSystem::MoveForward())
		{
			m_move.x += sinf(fCameraRotY + D3DX_PI * 0.25f) * m_fSpeed;
			m_move.z += cosf(fCameraRotY + D3DX_PI * 0.25f) * m_fSpeed;

			bMove = true;
		}
		// 後ろ移動
		else if (InputSystem::MoveBack())
		{
			m_move.x += sinf(fCameraRotY + D3DX_PI * 0.75f) * m_fSpeed;
			m_move.z += cosf(fCameraRotY + D3DX_PI * 0.75f) * m_fSpeed;

			bMove = true;
		}
		else
		{
			m_move.z -= sinf(fCameraRotY) * m_fSpeed;
			m_move.x += cosf(fCameraRotY) * m_fSpeed;

			bMove = true;
		}
	}
	else if (InputSystem::MoveForward())
	{
		m_move.x += sinf(fCameraRotY) * m_fSpeed;
		m_move.z += cosf(fCameraRotY) * m_fSpeed;

		bMove = true;
	}
	else if (InputSystem::MoveBack())
	{
		m_move.x -= sinf(fCameraRotY) * m_fSpeed;
		m_move.z -= cosf(fCameraRotY) * m_fSpeed;

		bMove = true;
	}

	// 移動していないなら
	if (!bMove)
	{
		return false;
	}

	fRotDest = D3DX_PI + atan2f(m_move.x, m_move.z);

	D3DXQUATERNION rotDest = Const::QUATERNION_IDENTITY;

	D3DXQuaternionRotationAxis(&rotDest, &Const::AXIS_Y, fRotDest);

	// 目的の角度の設定
	transformParam.quaternion = rotDest;

	return bMove;
}