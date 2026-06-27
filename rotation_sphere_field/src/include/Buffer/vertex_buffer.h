//===================================================
//
// 頂点バッファを使いやすくするクラス [vertex_buffer.h]
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

//***************************************************
// 頂点バッファのクラスの定義
//***************************************************
class CVertexBuffer
{
public:
	CVertexBuffer();
	~CVertexBuffer();

	/// <summary>
	/// 頂点バッファの生成
	/// </summary>
	/// <returns>結果</returns>
	HRESULT CreateBuffer(const UINT stride, const UINT numVertex, DWORD fvf);

	/// <summary>
	/// ロック
	/// </summary>
	/// <param name="ppData">頂点のポインタ</param>
	/// <returns>結果</returns>
	HRESULT Lock(void** ppData);

	/// <summary>
	/// アンロック
	/// </summary>
	/// <returns>結果</returns>
	HRESULT UnLock(void);

	/// <summary>
	/// ストリームソース、フォーマっトの設定
	/// </summary>
	/// <param name="pDevice">デバイスのポインタ</param>
	/// <returns></returns>
	HRESULT Bind(LPDIRECT3DDEVICE9 pDevice);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pBuffer;	// 頂点バッファへのポインタ
	UINT m_stride;						// バッファのサイズ
	DWORD m_fvf;						// 頂点のフォーマっと
};