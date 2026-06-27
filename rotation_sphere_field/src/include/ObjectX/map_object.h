//===================================================
//
// マップオブジェクト [map_object.h]
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
#include "ObjectBase/objectX.h"

//***************************************************
// 前方宣言
//***************************************************

//***************************************************
// マップオブジェクトのクラスの定義
//***************************************************
class CMapObject : public CObjectX
{
public:
	CMapObject();
	~CMapObject();

	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="pos">位置</param>
	/// <param name="pModelFilePath">モデルのパス</param>
	/// <returns>MapObjectへのポインタ</returns>
	static CMapObject* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& sphereCenter,const D3DXQUATERNION& sphereQuat, const D3DXMATRIX& sphereMatrix, const char* pModelFilePath);

	HRESULT Init	(void) override;
	void	Uninit	(void) override;
	void	Update	(void) override;
	void	Draw	(void) override;
private:
	D3DXVECTOR3 m_createPos;	// 生成時の位置
	D3DXQUATERNION m_parentQuat;
	D3DXVECTOR3 m_offset;
	D3DXVECTOR3 m_sphereCenter;
};