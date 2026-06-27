//===================================================
//
// 計算 [utility_math.h]
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
#include "random"

//***************************************************
// 計算用namespaceの定義
//***************************************************
namespace math
{
	/// <summary>
	/// 範囲内に値を制限する
	/// </summary>
	/// <typeparam name="T">変数の型</typeparam>
	/// <param name="value">現在の値</param>
	/// <param name="min">最小</param>
	/// <param name="max">最大</param>
	/// <returns>制限された値</returns>
	template <class T> T Clamp(const T value, const T min, const T max)
	{
		if (value < min) return min;

		if (value > max) return max;

		return value;
	};
	/// <summary>
	/// 値を範囲内をループさせる
	/// </summary>
	/// <typeparam name="T">変数の型</typeparam>
	/// <param name="value">現在の値</param>
	/// <param name="min">最小</param>
	/// <param name="max">最大</param>
	/// <returns>ループされた値</returns>
	template <class T> T Wrap(const T value, const T min, const T max)
	{
		if (value < min) return max;

		if (value > max) return min;

		return value;
	};

	/// <summary>
	/// 目的まで線形補完
	/// </summary>
	/// <typeparam name="T">変数の型</typeparam>
	/// <param name="dest">目的</param>
	/// <param name="value">現在値</param>
	/// <param name="fCoef">係数</param>
	/// <returns>目的までの割合</returns>
	template <class T> T LerpDest(const T dest, const T value, const float fCoef)
	{
		T out = value + (dest - value) * fCoef;

		return out;
	};

	/// <summary>
	/// 目的までの線形補間
	/// </summary>
	/// <typeparam name="T">変数の型</typeparam>
	/// <param name="offset">基準値</param>
	/// <param name="Diff">目的までの差分</param>
	/// <param name="fRate">割合</param>
	/// <returns>目的までの割合</returns>
	template <class T> T LerpDiff(const T offset, const T Diff, const float fRate)
	{
		T out = offset + (Diff * fRate);

		return out;
	};

	/// <summary>
	/// 範囲内かどうか
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="現在の値"></param>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns>判定結果</returns>
	template <class T> bool IsInRange(const T value, const T min, const T max)
	{
		if (value >= min && value <= max)
		{
			return true;
		}

		return false;
	};

	/// <summary>
	/// ランダムな値を取得する関数
	/// </summary>
	/// <typeparam name="int型以外"></typeparam>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns>範囲内の値</returns>
	template <class T> T Random(T min, T max)
	{
		if (min > max) std::swap(min, max);

		// int型は使えません
		static_assert(!std::is_same<T, int>::value, "********************<int> type is not allowrd use ***********************");

		std::random_device randomDevice;
		static std::mt19937 mt(randomDevice());

		// ランダムな範囲の指定
		std::uniform_real_distribution<T> dist(min, max);

		return dist(mt);
	}

	/// <summary>
	/// 距離を求める関数
	/// </summary>
	/// <param name="diff">目的までの差分</param>
	/// <returns>距離</returns>
	float GetDistance(const D3DXVECTOR3& diff);

	/// <summary>
	/// 正規化されたベクトルを取得するクラス
	/// </summary>
	/// <param name="dest">終点</param>
	/// <param name="pos">始点</param>
	/// <returns>ベクトルの取得</returns>
	D3DXVECTOR3 GetVector(const D3DXVECTOR3& dest, const D3DXVECTOR3& pos);

	/// <summary>
	/// 目的の位置までの角度の取得
	/// </summary>
	/// <param name="dest">目的の位置</param>
	/// <param name="pos">自分の位置</param>
	/// <returns>目的までの角度</returns>
	float GetTargetAngle(const D3DXVECTOR3& dest, const D3DXVECTOR3& pos);

	/// <summary>
	/// ワールドマトリックスから41_42_43成分を取得しD3DXVECTOR3型に変換する
	/// </summary>
	/// <param name="mtxWorld">ワールドマトリックス</param>
	/// <returns>変換した位置</returns>
	D3DXVECTOR3 GetPositionFromMatrix(const D3DXMATRIX& mtxWorld);

	/// <summary>
	/// クォータニオンの作成処理
	/// </summary>
	/// <param name="pOut">計算結果の</param>
	/// <param name="axis">軸</param>
	/// <param name="fAngle">角度</param>
	/// <returns>クォータニオンの作成</returns>
	D3DXQUATERNION CreateQuaternion(D3DXQUATERNION* pOut, D3DXVECTOR3& axis, float fAngle);
	D3DXMATRIX SetMatrixRotationQuaternion(D3DXMATRIX* pOut, D3DXQUATERNION& quaternion);
	D3DXVECTOR3 MatrixToEulerXYZ(const D3DXMATRIX& mtxWorld);
	D3DXVECTOR3 GetForward(const D3DXQUATERNION& quat);
	bool InTriangle(const D3DXVECTOR3& pos, const D3DXVECTOR3& vtx0, const D3DXVECTOR3& vtx1, const D3DXVECTOR3& vtx2);
	float Dot(const D3DXVECTOR3& v1, const D3DXVECTOR3& v2);
	D3DXVECTOR3 Cross(const D3DXVECTOR3& v1, const D3DXVECTOR3& v2);

	/// <summary>
	/// 角度をデグリー変換する
	/// </summary>
	/// <param name="rot">角度</param>
	/// <returns>変換後の値</returns>
	D3DXVECTOR3 ToDegree(const D3DXVECTOR3& rot);

	/// <summary>
	/// 角度をラジアンに変換する
	/// </summary>
	/// <param name="rot">角度</param>
	/// <returns>変換後の値</returns>
	D3DXVECTOR3 ToRadian(const D3DXVECTOR3& rot);

	/// <summary>
	/// マウスのレイの取得
	/// </summary>
	/// <param name="pRayOrigin"></param>
	/// <param name="OutDir"></param>
	void GetMouseRay(D3DXVECTOR3* pRayOrigin, D3DXVECTOR3* pOutDir);

	int Random(const int nMin,const int nMax);
	/// <summary>
	/// スクリーン座標をワールド座標に変換
	/// </summary>
	/// <param name="screen"></param>
	/// <param name="fWorldY"></param>
	/// <param name="vp"></param>
	/// <param name="view"></param>
	/// <param name="proj"></param>
	/// <returns>変換座標</returns>
	D3DXVECTOR3 ScreenToWorld(const D3DXVECTOR2& screen, const float fWorldY, const D3DVIEWPORT9& vp, const D3DXMATRIX& view, const D3DXMATRIX& proj);

	/// <summary>
	/// スナップ移動の値
	/// </summary>
	/// <param name="fValue">現在の位置</param>
	/// <param name="fGridSize">グリッドのサイズ</param>
	/// <returns>スナップ移動の位置</returns>
	float Snap(const float fValue, const float fGridSize);

	void NormalizeRot(D3DXVECTOR3* pRot);
	void NormalizeRot(float* pRot);
	void NormalizeDiffRot(const float fDiff, float* pRot);

	D3DXMATRIX Inverse(const D3DXMATRIX& mtxWorld);
	D3DXVECTOR3 Bound(const D3DXVECTOR3& move, const D3DXVECTOR3& normal, const float fRestitution);
};