//===================================================
//
// オブジェクトの抽象クラス [object.h]
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
// オブジェクトクラスの定義
//***************************************************
class CObject
{
public:
	CObject(const int nPriority = 0);
	virtual ~CObject();

	virtual HRESULT Init	(void) = 0;
	virtual void	Uninit	(void) = 0;
	virtual void	Update	(void) = 0;
	virtual void	Draw	(void) = 0;

	/// <summary>
	/// 死んでいるかどうか取得
	/// </summary>
	/// <returns>死んでいたらtrue</returns>
	inline bool IsDeath(void) const { return m_bDeath; }
protected:
	/// <summary>
	/// 自分自身の死亡フラグをオンにして破棄する準備
	/// </summary>
	void Release(void);
private:
	int m_nPriority;	// 優先順位
	bool m_bDeath;		// 死亡フラグ
};