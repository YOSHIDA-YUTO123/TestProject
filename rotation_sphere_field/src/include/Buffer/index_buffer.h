//===================================================
//
// インデックスバッファを使いやすくするクラス [index_buffer.h]
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
// インデックスバッファのクラスの定義
//***************************************************
class CIndexBuffer
{
public:
	CIndexBuffer();
	~CIndexBuffer();

	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="nNumIndex">インデックスの総数</param>
	/// <returns>結果</returns>
	HRESULT Create(const int nNumIndex);

	/// <summary>
	/// インデックスバッファのロック
	/// </summary>
	/// <param name="ppData">頂点のデータ</param>
	/// <returns>結果</returns>
	HRESULT Lock(void** ppData);

	/// <summary>
	/// インデックスバッファのアンロック
	/// </summary>
	/// <returns>結果</returns>
	HRESULT UnLock();

	/// <summary>
	/// インデックスバッファをバインドする
	/// </summary>
	/// <param name="pDevice">デバイスへのポインタ</param>
	/// <returns>結果</returns>
	HRESULT Bind(LPDIRECT3DDEVICE9 pDevice);

private:
	LPDIRECT3DINDEXBUFFER9 m_pBuffer;	// インデックスバッファへのポインタ
};