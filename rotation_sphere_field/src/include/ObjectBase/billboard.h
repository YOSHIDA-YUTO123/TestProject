//===================================================
//
// ビルボードオブジェクトの描画クラス [billboard.h]
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
#include "Buffer/vertex_buffer.h"
#include "Transform/transform3d.h"

//***************************************************
// ビルボードのクラスの定義
//***************************************************
class CBillboard : public CObject
{
public:
	CBillboard();
	~CBillboard();

	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="pos">位置</param>
	/// <param name="size">大きさ</param>
	/// <param name="col">色</param>
	/// <param name="pTexturePath">テクスチャのパス</param>
	/// <returns>Billboardのポインタ</returns>
	static CBillboard* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const D3DXCOLOR& col, const char* pTexturePath);

	HRESULT Init	(void) override;
	void	Uninit	(void) override;
	void	Update	(void) override;
	void	Draw	(void) override;

	/// <summary>
	/// テクスチャのIDの設定処理
	/// </summary>
	/// <param name="pTexturePath">テクスチャのパス</param>
	void SetTextureID(const char* pTexturePath);
private:
	CTransform3D m_transform;		// ワールド情報
	CVertexBuffer m_vertexBuffer;	// 頂点バッファ
	D3DXCOLOR m_col;				// 色
	D3DXVECTOR3 m_size;				// 大きさ
	int m_nTextureID;				// テクスチャのID
};