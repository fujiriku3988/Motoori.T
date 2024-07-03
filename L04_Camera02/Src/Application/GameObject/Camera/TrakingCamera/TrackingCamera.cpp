#include "TrackingCamera.h"

void TrackingCamera::Init()
{
	//親クラスの初期化呼び出し
	CameraBase::Init();
	//基準点（ターゲット）からどれだけ離れているか
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 6.f, -5.f);
	//どれだけ傾けているか
	m_mRot = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	
}

void TrackingCamera::Update()
{
	//Targetの行列（有効ンな場合利用する)
	Math::Matrix _targetMat = Math::Matrix::Identity;
	const std::shared_ptr<KdGameObject> _spTarget = m_spTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	//_targetMatこれを最後に書く
	m_mWorld = m_mRot * m_mLocalPos* _targetMat;

	//親呼び出し
	CameraBase::Update();
}
