#include "TPSCamera.h"

void TPSCamera::Init()
{
	CameraBase::Init();
	//基準点（ターゲット）からどれだけ離れているか
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 1.5f, -10.f);
	//マウスカーソルを画面中央値に固定する
	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);
}

void TPSCamera::Update()
{
	//Targetの行列（有効な場合利用する)
	Math::Matrix _targetMat = Math::Matrix::Identity;
	Math::Vector3 targetPos = Math::Vector3::Zero;
	const std::shared_ptr<KdGameObject> _spTarget = m_spTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
		targetPos = _spTarget->GetPos();
		targetPos.y += 0.1f;
	}

	//カメラ回転処理
	UpdateRotateByMouse();
	m_mRot = GetRotaionMatrix();

	//_targetMatこれを最後に書く
	m_mWorld = m_mLocalPos * m_mRot * _targetMat;

	//めり込み防止の為の座標補正計算↓
	//①当たり判定（レイ判定）用の情報を作成
	KdCollider::RayInfo rayInfo;//構造体
	//レイの発射位置を設定
	rayInfo.m_pos = GetPos();
	//レイの長さ
	rayInfo.m_range = 1000.0f;
	//レイの発射方向
	rayInfo.m_dir = targetPos - GetPos();//キャラの座標ーカメラの座標
	rayInfo.m_range = rayInfo.m_dir.Length();//キャラの位置までの長さ
	rayInfo.m_dir.Normalize();
	//レイの当たり判定したいタイプ設定
	rayInfo.m_type = KdCollider::TypeGround;

	//②HIT判定対象オブジェクトに総当たり
	for (std::weak_ptr<KdGameObject> wpGameObj : m_wpHitObjectList)
	{
		std::shared_ptr<KdGameObject>spGameObj = wpGameObj.lock();
		if (spGameObj)
		{
			std::list<KdCollider::CollisionResult>retResultList;
			spGameObj->Intersects(rayInfo, &retResultList);

			//③結果を利用して座標を補完する
			//レイに当たったリストから一番近いオブジェクトを検出
			float maxOverLap = 0;
			Math::Vector3 hitPos = {};
			bool hit = false;

			for (auto& ret : retResultList)
			{
				//レイを遮断しオーバーした長さが
				//一番長い物を探す
				if (maxOverLap < ret.m_overlapDistance)
				{
					maxOverLap = ret.m_overlapDistance;
					hitPos = ret.m_hitPos;
					hit = true;
				}
			}

			//何かしらの障害物に当たっている
			if (hit)
			{
				//カメラの位置を設定
				//補正する
				Math::Vector3 reviPos = hitPos;//revisionPos
				reviPos += rayInfo.m_dir * 0.4f;
				SetPos(reviPos);
			}
		}
	}

	//親呼び出し
	CameraBase::Update();


}
