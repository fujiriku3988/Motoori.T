#include "CCTVCamera.h"
#include "../../../main.h"
//定点カメラ


void CCTVCamera::Init()
{
	CameraBase::Init();
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 5.0f, -10.0f);
	m_mWorld = m_mLocalPos;

}

void CCTVCamera::PostUpdate()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix								_targetMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject>	_spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}
	//カメラの回転
	UpdateLookRotate(_targetMat.Translation());
}

void CCTVCamera::UpdateLookRotate(const Math::Vector3 _targetPos)
{
													//自分の座標、見たい座標　　方向かな？
	Math::Matrix _shadowVP = DirectX::XMMatrixLookAtLH(GetPos(), _targetPos, Math::Vector3::Up);

	//逆行列（Invert関数）
	//逆行列しないと自分から見たカメラになるからおかしくなる

	m_mWorld = _shadowVP.Invert();
}
