#include "Earth.h"

void Earth::Update()
{
	m_rotY += 1.0f;
	Math::Matrix _mScale = Math::Matrix::CreateScale(1);
	//どれだけ傾けているか
	Math::Matrix _mRoatationY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotY));

	//基準点（ターゲット）からどれだけ離れているか
	Math::Matrix _mTrans = Math::Matrix::CreateTranslation(pos);

	//キャラクターのワールド行列を作成
	// 回転＊移動で自転ができる
	//回転＊移動＊回転で自転と公転ができる
	m_mWorld = _mScale * _mRoatationY * _mTrans * _mRoatationY;
}

void Earth::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Earth::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Data/LessonData/Planets/earth.gltf");
	pos = { 0,0,-20 };
	m_rotY = 0;
	m_objType = KdGameObject::objType::Earth;
}
