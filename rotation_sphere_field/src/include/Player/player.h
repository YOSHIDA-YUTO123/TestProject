//===================================================
//
// プレイヤーのクラス [player.h]
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
#include "ObjectBase/object.h"
#include "Transform/transform3d.h"

//***************************************************
// 前方宣言
//***************************************************
class CCharacter3D;	// 3Dキャラクタークラス

//***************************************************
// プレイヤーのクラスの定義
//***************************************************
class CPlayer : public CObject
{
public:
	// モーションの種類
	enum MOTIONTYPE
	{
		MOTIONTYPE_NEUTRAL = 0,	// ニュートラル
		MOTIONTYPE_MOVE,		// 移動
		MOTIONTYPE_ACTION,		// アクション
		MOTIONTYPE_JUMP,		// ジャンプ
		MOTIONTYPE_LANDING,		// 着地
		MOTIONTYPE_MAX
	};

	CPlayer();
	~CPlayer();

	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="pos">位置</param>
	/// <param name="rot">向き</param>
	/// <returns>Playerのポインタ</returns>
	static CPlayer* Create(const D3DXVECTOR3& pos = Const::VEC3_NULL, const D3DXVECTOR3& rot = Const::VEC3_NULL);

	HRESULT Init	(void) override;
	void	Uninit	(void) override;
	void	Update	(void) override;
	void	Draw	(void) override;
private:
	/// <summary>
	/// キーボード移動
	/// </summary>
	bool KeyboardMove(Transform3D& transformParam);
private:
	std::unique_ptr<CCharacter3D> m_pCharacter;	// キャラクタークラス
	CTransform3D m_transform;					// 空間情報
	D3DXVECTOR3 m_offsetPos;					// オフセット
	D3DXVECTOR3 m_move;							// 移動量
	float m_fSpeed;								// 速さ
};