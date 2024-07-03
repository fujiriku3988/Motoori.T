#include "FPSCamera.h"

void FPSCamera::Init()
{
	CameraBase::Init();
	//基準点（ターゲット）からどれだけ離れているか
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 1.5f, 0.f);
	//マウスカーソルを画面中央値に固定する
	SetCursorPos(m_FixMousePos.x,m_FixMousePos.y);
}

void FPSCamera::Update()
{
	//Targetの行列（有効ンな場合利用する)
	Math::Matrix _targetMat = Math::Matrix::Identity;
	const std::shared_ptr<KdGameObject> _spTarget = m_spTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	//カメラ回転処理
	UpdateRotateByMouse();
	m_mRot = GetRotaionMatrix();
	

	//_targetMatこれを最後に書く
	m_mWorld = m_mRot * m_mLocalPos * _targetMat;

	//親呼び出し
	CameraBase::Update();


}
