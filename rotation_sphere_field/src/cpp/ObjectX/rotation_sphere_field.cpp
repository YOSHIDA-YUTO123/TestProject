//===================================================
//
// 回転する球体のステージ [rotation_sphere_field.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// インクルードファイル
//***************************************************
#include "ObjectX/rotation_sphere_field.h"
#include "System/input_system.h"
#include "Base/manager.h"
#include "Base/camera.h"
#include "Base/utility_math.h"
#include "Constants/color_constants.h"
#include "ObjectX/map_object.h"

#include "Debug/line.h"
#include "Debug/debug_proc.h"
#include "Debug/debug_parameter.h"

//===================================================
// コンストラクタ
//===================================================
CRotationSphereField::CRotationSphereField() : 
	m_baseMatrixWorld(Const::MTX_IDENTITY),
	m_dir(Const::VEC3_NULL),
	m_fCircumference(0.0f),
	m_fRadius(0.0f),
	m_fAngleValue(0.0f)
{
}

//===================================================
// デストラクタ
//===================================================
CRotationSphereField::~CRotationSphereField()
{
}

//===================================================
// 生成処理
//===================================================
CRotationSphereField* CRotationSphereField::Create(const D3DXVECTOR3& pos)
{
	CRotationSphereField* pInstance = new CRotationSphereField;

	// ワールド情報の取得
	CTransform3D* pTransform = pInstance->GetTransform();

	Transform3D transformParam = {};
	transformParam.pos = pos;

	pTransform->SetParam(transformParam);

	pInstance->RegisterModelID("sphere.x");

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
HRESULT CRotationSphereField::Init(void)
{
	// 初期化処理
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	// 半径の取得
	m_fRadius = CObjectX::GetSize().x * 0.5f;

	return S_OK;
}

//===================================================
// 終了処理
//===================================================
void CRotationSphereField::Uninit(void)
{
	// 終了処理
	CObjectX::Uninit();
}

//===================================================
// 更新処理
//===================================================
void CRotationSphereField::Update(void)
{
	KeyboardMove();

	CDebugParameter::Param debugParam = CDebugParameter::Instance().GetParam();

	// 回転量の減衰処理
	m_fAngleValue *= CDebugParameter::Instance().GetParam().rotationSphere.fRotDamp;

	// ワールド情報の取得
	CTransform3D* pTransform = CObjectX::GetTransform();

	// パラメータの取得
	Transform3D transformParam = pTransform->GetParam();

	// 拡大率
	float fScaling = debugParam.rotationSphere.fScaling;

	// 拡大なら
	if (InputSystem::ScalingSphere() == InputSystem::SPHERE_SCALING::EXPAND)
	{
		transformParam.scale.x += fScaling;
		transformParam.scale.y += fScaling;
		transformParam.scale.z += fScaling;
	}
	// 縮小なら
	else if (InputSystem::ScalingSphere() == InputSystem::SPHERE_SCALING::REDUCTION)
	{
		transformParam.scale.x -= fScaling;
		transformParam.scale.y -= fScaling;
		transformParam.scale.z -= fScaling;
	}

	// 拡大率の設定
	transformParam.scale.x = math::Clamp(transformParam.scale.x, 2.0f, 999999.0f);
	transformParam.scale.y = math::Clamp(transformParam.scale.y, 2.0f, 999999.0f);
	transformParam.scale.z = math::Clamp(transformParam.scale.z, 2.0f, 999999.0f);

	CDebugProc::Print("球体のスケール : [ %.2f ] [ %.2f ] [ %.2f ] ( +↑ / -↓ )", transformParam.scale.x, transformParam.scale.y, transformParam.scale.z);

	if (InputSystem::CreateMapObject())
	{
		CMapObject::Create(
			D3DXVECTOR3(transformParam.pos.x, transformParam.pos.y + m_fRadius, transformParam.pos.z),
			transformParam.pos,
			transformParam.quaternion,
			transformParam.mtxWorld, 
			"tree.x");
	}

	// パラメータの設定
	pTransform->SetParam(transformParam);

	// 回転を計算する
	CalculationRotationQuaternion();

	// 更新処理
	CObjectX::Update();
}

//===================================================
// 描画処理
//===================================================
void CRotationSphereField::Draw(void)
{
	// 描画
	CObjectX::Draw();
}

//===================================================
// トップの位置の取得
//===================================================
D3DXVECTOR3 CRotationSphereField::OnTopPosition(void)
{
	// ワールド情報の取得
	CTransform3D* pTransform = CObjectX::GetTransform();

	// パラメータの取得
	Transform3D transformParam = pTransform->GetParam();

	D3DXVECTOR3 centerPos = transformParam.pos;
	centerPos.y += m_fRadius * transformParam.scale.x;
	
	D3DXVECTOR3 topPos = centerPos;
	return centerPos;
}

//===================================================
// 回転後の姿勢、位置を取得
//===================================================
void CRotationSphereField::OnRotate(Transform3D& transform, const D3DXVECTOR3& offset, const D3DXQUATERNION& offsetQuat)
{
	// ワールド情報の取得
	CTransform3D* pTransform = CObjectX::GetTransform();

	// パラメータの取得
	Transform3D transformParam = pTransform->GetParam();

	D3DXQUATERNION invQuat,diff;
	D3DXMATRIX mtxScaleRot, mtxRot;
	D3DXVECTOR3 rotateOffset;

	// 生成時のクォータニオンを逆にする
	D3DXQuaternionInverse(&invQuat, &offsetQuat);

	// 現在のクォータニオンと生成時のクォータニオンの差分を求めてどれくらい回転したかを求める
	D3DXQuaternionMultiply(&diff, &invQuat, &transformParam.quaternion);

	// 拡大行列を求める
	D3DXMatrixScaling(&mtxScaleRot, transformParam.scale.x, transformParam.scale.y, transformParam.scale.z);

	// 回転量を回転行列に変換する
	D3DXMatrixRotationQuaternion(&mtxRot, &diff);

	// 拡大行列に回転行列を掛ける
	mtxScaleRot *= mtxRot;

	// 拡大後と回転後のオフセットを求める
	D3DXVec3TransformCoord(&rotateOffset, &offset, &mtxScaleRot);

	// 球体の中心位置から回転したオフセット分移動させた場所をオブジェクトの位置として設定する
	transform.pos = transformParam.pos + rotateOffset;

	// 親の回転に合わせる
	transform.quaternion = diff;
}

//===================================================
// キーボードの回転移動
//===================================================
void CRotationSphereField::KeyboardMove(void)
{
	// カメラの取得
	CCamera* pCamera = CManager::Instance().GetCamera();

	// 取得できないなら処理を飛ばす
	if (pCamera == nullptr)
	{
		return;
	}

	// カメラの向きの取得
	float fCameraRotY = pCamera->GetRotation().y;

	bool bMove = false;

	// 左移動
	if (InputSystem::MoveLeft())
	{
		// 正面移動
		if (InputSystem::MoveForward())
		{
			m_dir.x = sinf(fCameraRotY - D3DX_PI * 0.25f);
			m_dir.z = cosf(fCameraRotY - D3DX_PI * 0.25f);

			bMove = true;
		}
		// 後ろ移動
		else if (InputSystem::MoveBack())
		{
			m_dir.x = sinf(fCameraRotY - D3DX_PI * 0.75f);
			m_dir.z = cosf(fCameraRotY - D3DX_PI * 0.75f);

			bMove = true;
		}
		else
		{
			m_dir.x = sinf(fCameraRotY - D3DX_PI * 0.5f);
			m_dir.z = cosf(fCameraRotY - D3DX_PI * 0.5f);

			bMove = true;
		}
	}
	// 右移動
	else if (InputSystem::MoveRight())
	{
		// 正面移動
		if (InputSystem::MoveForward())
		{
			m_dir.x = sinf(fCameraRotY + D3DX_PI * 0.25f);
			m_dir.z = cosf(fCameraRotY + D3DX_PI * 0.25f);

			bMove = true;
		}
		// 後ろ移動
		else if (InputSystem::MoveBack())
		{
			m_dir.x = sinf(fCameraRotY + D3DX_PI * 0.75f);
			m_dir.z = cosf(fCameraRotY + D3DX_PI * 0.75f);

			bMove = true;
		}
		else
		{
			m_dir.x = sinf(fCameraRotY + D3DX_PI * 0.5f);
			m_dir.z = cosf(fCameraRotY + D3DX_PI * 0.5f);

			bMove = true;
		}
	}
	else if (InputSystem::MoveForward())
	{
		m_dir.x = sinf(fCameraRotY);
		m_dir.z = cosf(fCameraRotY);

		bMove = true;
	}
	else if (InputSystem::MoveBack())
	{
		m_dir.x = sinf(fCameraRotY + D3DX_PI);
		m_dir.z = cosf(fCameraRotY + D3DX_PI);

		bMove = true;
	}

	if (bMove)
	{
		m_fAngleValue += CDebugParameter::Instance().GetParam().rotationSphere.fRotSpeed;
	}
}

//===================================================
// 回転の計算処理
//===================================================
void CRotationSphereField::CalculationRotationQuaternion(void)
{
	// ワールド情報の取得
	CTransform3D* pTransform = CObjectX::GetTransform();

	// パラメータの取得
	Transform3D transformParam = pTransform->GetParam();

	D3DXVECTOR3 rotationAxis;

	D3DXVECTOR3 dir = m_dir;
	float fLength = D3DXVec3Length(&m_dir);
	dir = m_dir / fLength;	// ベクトルを正規化

	// 移動方向と上方向ベクトルから回転軸を求める
	rotationAxis = math::Cross(Const::VEC_U, dir);

	D3DXQUATERNION quat;

	//// 乗算され続けるため初期化
	//transformParam.quaternion = Const::QUATERNION_IDENTITY;

	// クォータニオンの作成
	D3DXQuaternionRotationAxis(&quat, &rotationAxis, -m_fAngleValue);

	// 現在のクォータニオンと合成する
	transformParam.quaternion = transformParam.quaternion * quat;

	CDebugProc::Print("クォータニオン : [ %.2f ] [ %.2f ] [ %.2f ] [ %.2f ]",transformParam.quaternion.x, transformParam.quaternion.y, transformParam.quaternion.z, transformParam.quaternion.w);
	CDebugProc::Print("回転量 : [ %.2f ]", m_fAngleValue);

	// パラメータの設定
	pTransform->SetParam(transformParam);
}