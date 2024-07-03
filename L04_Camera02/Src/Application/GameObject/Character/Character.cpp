#include "Character.h"
#include "../../main.h"
#include"../Camera/CameraBase.h"
#include"Application/GameObject/Camera/CameraBase.h"
void Character::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}
}

void Character::Update()
{
	// キャラクターの移動速度(真似しちゃダメですよ)
	float moveSpd = 0.05f;
	Math::Vector3 nowPos = m_mWorld.Translation();

	Math::Vector3 moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('D')) { moveVec.x = 1.0f; }
	if (GetAsyncKeyState('A')) { moveVec.x = -1.0f; }
	if (GetAsyncKeyState('W')) { moveVec.z = 1.0f; }
	if (GetAsyncKeyState('S')) { moveVec.z = -1.0f; }

	const std::shared_ptr<CameraBase> _spCamera = m_wpCamera.lock();
	if (_spCamera)
	{
		moveVec = moveVec.TransformNormal(moveVec, _spCamera->GetRotationYMatrix());
	}
	moveVec.Normalize();
	moveVec *= moveSpd;

	//characterの回転角度を計算
	UpdateRotate(moveVec);

	nowPos += moveVec;
	// キャラクターのワールド行列を創る処理
	Math::Matrix _rotation = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_WprldRot.y));

	m_mWorld = _rotation *Math::Matrix::CreateTranslation(nowPos);
}

void Character::DrawLit()
{
	if (!m_spPoly) return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Character::UpdateRotate(const Math::Vector3& srcMoveVec)
{
	//何も入力がない場合は処理しない
	if (srcMoveVec .LengthSquared()==0.f)return;
	//レングスは平方根の計算してるから重い
	//長さだけならレングススクエアがいい

	//キャラの正面方向のベクトル
	Math::Vector3 _nowDir = GetMatrix().Backward();//バックワードで正面を持ってくる**Forwardが本当は前やけどこの環境は違う
	_nowDir.Normalize();

	//移動方向のベクトル
	Math::Vector3 _targetDir = srcMoveVec;
	_targetDir.Normalize();

	float _nowAng = atan2(_nowDir.x, _nowDir.z);
	_nowAng = DirectX::XMConvertToDegrees(_nowAng);

	float _targetAng = atan2(_targetDir.x, _targetDir.z);
	_targetAng = DirectX::XMConvertToDegrees(_targetAng);

	//角度の差分を求める
	float _betweenAng = _targetAng - _nowAng;
	if (_betweenAng > 180)
	{
		_betweenAng -= 360;
	}
	else if(_betweenAng<-180)
	{
		_betweenAng += 360;
	}
	float _rotateAng = std::clamp(_betweenAng, - 8.f, 8.f);
	m_WprldRot.y += _rotateAng;
}

