//===================================================
//
// オブジェクトの管理クラス [object_manager.h]
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
// 前方宣言
//***************************************************
class CObject;	// オブジェクトクラス

//***************************************************
// オブジェクトの管理クラスの定義
//***************************************************
class CObjectManager
{
public:
	// 優先順位
	enum PRIORITY
	{
		PRIORITY_NONE = 0,	// 無
		PRIORITY_MESH,		// メッシュ
		PRIORITY_MODEL,		// モデル
		PRIORITY_MAX
	};

	/// <summary>
	/// オブジェクトの追加
	/// </summary>
	/// <param name="pObject">オブジェクトのポインタ</param>
	/// <param name="nPriority">優先順位</param>
	static void Register	(CObject* pObject, const int nPriority = 0);

	/// <summary>
	/// 全てのオブジェクトの破棄
	/// </summary>
	static void ReleaseAll	(void);

	/// <summary>
	/// 全ての更新処理
	/// </summary>
	static void UpdateAll	(void);

	/// <summary>
	/// 全ての描画処理
	/// </summary>
	static void DrawAll		(void);
private:
	CObjectManager();
	~CObjectManager() {};
private:
	inline static std::array<std::list<CObject*>, PRIORITY_MAX> m_lpObject;	// オブジェクトのリスト
};