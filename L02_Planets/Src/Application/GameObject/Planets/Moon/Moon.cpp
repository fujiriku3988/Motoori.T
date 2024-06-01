#include "Moon.h"
#include"Application/main.h"

void Moon::Update()
{
	m_rotY += 5.0f;
	m_obj = m_Owner->GetObjList();
	for (int i = 0; i < m_Owner->GetObjList().size(); i++)
	{
		if (m_obj[i]->GetObjType() == KdGameObject::objType::Earth)
		{
			//地球の行列
			Math::Matrix earthWorld = m_obj[i]->GetMatrix();
			//月スケール
			Math::Matrix _mScale = Math::Matrix::CreateScale(2);
			//どれだけ傾けているか
			Math::Matrix _mRoatationY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotY));

			//基準点（ターゲット）からどれだけ離れているか
			Math::Matrix _mTrans = Math::Matrix::CreateTranslation(pos.x,pos.y,pos.z + 5);

			//キャラクターのワールド行列を作成
			// 回転＊移動で自転ができる
			//回転＊移動＊回転で自転と公転ができる
			m_mWorld = _mScale * _mRoatationY * _mTrans * _mRoatationY * earthWorld;
		}
	}
}

void Moon::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel,m_mWorld);
}

void Moon::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Data/LessonData/Planets/moon.gltf");
	pos = {};
	m_rotY = 0;
	m_objType = KdGameObject::objType::Moon;
}
