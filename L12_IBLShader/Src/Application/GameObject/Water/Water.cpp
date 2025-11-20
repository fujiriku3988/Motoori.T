#include "Water.h"

void Water::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/LessonData/Stage/Water/Water.gltf");
		//m_spModel->SetModelData("Asset/LessonData/Stage/test/Conver1.gltf");

		SetPos({ 0,0.5f,0 });
		//m_mWorld.Translation({ 0,0.1f,0 });

		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("Water", m_spModel, KdCollider::TypeGround);
	}
}

void Water::Update()
{
	m_UVOffSet.x -= 0.0001f;
	m_UVOffSet.y += 0.0001f;
}

void Water::DrawLit()	
{
	if (!m_spModel) return;

	//KdShaderManager::Instance().m_LessonShader.DrawModel(*m_spModel,m_mWorld);
	KdShaderManager::Instance().m_StandardShader.SetUVOffset(m_UVOffSet);
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Water::DrawLesson()
{
	//if (!m_spModel) return;

	//KdShaderManager::Instance().m_LessonShader.SetUVOffset(m_UVOffSet);
	//KdShaderManager::Instance().m_LessonShader.DrawModel(*m_spModel, m_mWorld);
}
