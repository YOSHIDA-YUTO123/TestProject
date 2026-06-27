//===================================================
//
// カメラの処理 [camera.h]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// 多重インクルード防止
//***************************************************
#pragma once

//***************************************************
// インクルードファイル
//***************************************************
//#include "camera_system_base.h"
#include "DirectXMath.h"
#include "DirectXCollision.h"

//***************************************************
// カメラクラスの定義
//***************************************************
class CCamera
{
public:
	static constexpr float FOV = D3DXToRadian(45.0f);							// 視野角

	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	void SetCamera(const D3DXVECTOR3& posV, const D3DXVECTOR3& posR, const D3DXVECTOR3& rot);
	void SetFocus(const D3DXVECTOR3& pos);

	//void AddSystem(std::unique_ptr<CCameraSystemBase> pNewSystem);
	inline D3DXVECTOR3 GetRotation(void) const { return m_rot; }
	inline D3DXVECTOR3 GetPosV(void) const { return m_posV; }
	inline D3DXVECTOR3 GetPosR(void) const { return m_posR; }
	inline float GetDistance(void) const { return m_fDistance; }
	inline D3DXVECTOR3	GetRight(void) const { return D3DXVECTOR3(m_mtxView._11, m_mtxView._21, m_mtxView._31); }
	inline D3DXVECTOR3	GetUp(void) const { return D3DXVECTOR3(m_mtxView._12, m_mtxView._22, m_mtxView._32); }
	inline D3DXVECTOR3	GetForward(void) const { return D3DXVECTOR3(m_mtxView._13, m_mtxView._23, m_mtxView._33); }

private:
	void DebugCamera(void);
	void DebugCameraMove(void);
private:
	//std::vector<std::unique_ptr<CCameraSystemBase>> m_pSystem;	// 拡張機能
	D3DXMATRIX m_mtxView;										// ビューマトリックス
	D3DXMATRIX m_mtxProjection;									// プロジェクションマトリックス
	D3DXVECTOR3 m_posV;											// 視点の座標
	D3DXVECTOR3 m_posR;											// 注視点の座標
	D3DXVECTOR3 m_vecU;											// 上方向ベクトル
	D3DXVECTOR3 m_rot;											// 向き
	float m_fDistance;											// 距離
};