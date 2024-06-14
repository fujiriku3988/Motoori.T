#include "Terrain.h"

void Terrain::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Data/LessonData/Terrain/Terrain.gltf");
	}
	//コライダー（当たり判定情報）の初期化（登録）
	m_pCollider = std::make_unique<KdCollider>();
	//								登録名		モデルデータ	判定種類
	m_pCollider->RegisterCollisionShape("Ground", m_spModel, KdCollider::TypeGround);
}

void Terrain::Update()
{
}

void Terrain::DrawLit()
{
	if (!m_spModel) return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel);
}

