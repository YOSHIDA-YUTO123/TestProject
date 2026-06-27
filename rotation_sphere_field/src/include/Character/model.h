//===================================================
//
// キャラクターのモデルのクラス [model.h]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// 多重インクルード防止
//***************************************************
#pragma once

//***************************************************
// キャラクターのモデルのクラスの定義
//***************************************************
class CModel
{
public:
	CModel();
	~CModel();

	static CModel* Create(const char* pModelFilePath);

	HRESULT Init	(const char* pModelFilePath);
	void	Uninit	(void);
	void	Update	(void);
	void	Draw	(void);

	inline void SetPosition			(const D3DXVECTOR3& pos)	{ m_pos = pos; }
	inline void SetRotation			(const D3DXVECTOR3& rot)	{ m_rot = rot; }

	inline void SetOffSetPosition	(const D3DXVECTOR3& pos)	{ m_offPos = pos; }
	inline void SetOffSetRotation	(const D3DXVECTOR3& rot)	{ m_offRot = rot; }

	inline void SetParent			(CModel* pModel)			{ m_pParent = pModel; }
	inline void SetParentID			(const int nParentID)		{ m_nParentID = nParentID; }
	inline void SetModelPath		(const char* pPath)			{ m_modelPath = pPath; }

	inline int	GetParentID			(void) const { return m_nParentID; }
	inline const char* GetModelPath	(void) const { return m_modelPath.c_str(); }

	inline const D3DXVECTOR3& GetPosition(void) const { return m_pos; }
	inline const D3DXVECTOR3& GetRotation(void) const { return m_rot; }
	inline const D3DXMATRIX& GetMatrix	 (void)	const { return m_mtxWorld; }
	inline CModel* GetParent			(void)	const { return m_pParent; }
	void		SetOffset				(const CModel* pOther);

	bool CollisionMouse(float* pOutDistance);
	void SetLowAlv(const bool bAvl) { m_bDrawLowAlv = bAvl; }
private:
	D3DXVECTOR3			m_size;			// 大きさ
	D3DXVECTOR3			m_offPos;		// 基準の位置
	D3DXVECTOR3			m_offRot;		// 基準の向き
	D3DXVECTOR3			m_pos;			// 位置
	D3DXVECTOR3			m_rot;			// 向き
	D3DXMATRIX			m_mtxWorld;		// ワールドマトリックス
	CModel*				m_pParent;		// 親モデルへのポインタ
	std::vector<int>	m_vnTextureID;	// テクスチャのID
	std::string			m_modelPath;	// モデルのファイルパス
	int					m_nParentID;	// 親のインデックス
	int					m_nModelID;		// モデルのインデックス
	bool				m_bDrawLowAlv;	// 透明度を下げる
};