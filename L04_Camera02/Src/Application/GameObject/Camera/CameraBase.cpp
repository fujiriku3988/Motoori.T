#include "CameraBase.h"

void CameraBase::Init()
{
	if (!m_spCamera)
	{
		m_spCamera = std::make_shared<KdCamera>();
	}

	//マウスを固定させる座標値（中央）
	m_FixMousePos.x = 640;
	m_FixMousePos.y = 360;
}

void CameraBase::Update()
{
	ShowCursor(false);
	//ヌルチェック必須//
	if (!m_spCamera)return;

	m_spCamera->SetCameraMatrix(m_mWorld);
}

void CameraBase::PreDraw()
{
	if (!m_spCamera)return;
	m_spCamera->SetToShader();
}

void CameraBase::UpdateRotateByMouse()
{
	//マウスの現在の壱を取得する
	POINT _nowPos;
	GetCursorPos(&_nowPos);

	//②画面中央からの差分を算出する
	POINT _mouveMove{};
	_mouveMove.y = _nowPos.y - m_FixMousePos.y;
	_mouveMove.x = _nowPos.x - m_FixMousePos.x;

	//③カーソル中央値へ戻す
	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	//4差分を利用して回転角度を設定する
	m_DegAng.x += _mouveMove.y*0.1f;
	m_DegAng.y += _mouveMove.x*0.1f;

	//回転制御
	m_DegAng.x = std::clamp(m_DegAng.x, - 45.f, 45.f);
}

const Math::Matrix CameraBase::GetRotationYMatrix()const
{
	return Math::Matrix::CreateRotationY
	(
		DirectX::XMConvertToRadians(m_DegAng.y)
	);
}

const Math::Matrix CameraBase::GetRotaionMatrix() const
{
	return Math::Matrix::CreateFromYawPitchRoll
	(
		DirectX::XMConvertToRadians(m_DegAng.y),
		DirectX::XMConvertToRadians(m_DegAng.x),
		DirectX::XMConvertToRadians(m_DegAng.z)
	);
}
