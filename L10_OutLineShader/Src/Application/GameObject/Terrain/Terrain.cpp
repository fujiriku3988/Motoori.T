#include "Terrain.h"

void Terrain::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/LessonData/Stage/StageMap1.gltf");

		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("Ground", m_spModel, KdCollider::TypeGround);
	}
}

void Terrain::Update()
{
	if (GetAsyncKeyState('1') & 0x8000)
	{
		if (!a)
		{
			m_spModel->SetModelData("Asset/LessonData/Stage/StageMap.gltf");
			a = true;
		}
	}
	else
	{
		a = false;
	}
	if (GetAsyncKeyState('2') & 0x8000)
	{
		if (!b)
		{
			m_spModel->SetModelData("Asset/LessonData/Stage/StageMap1.gltf");
			b = true;
		}
	}
	else
	{
		b = false;
	}
}

void Terrain::DrawLesson()
{
	if (!m_spModel) return;

	KdShaderManager::Instance().m_LessonShader.DrawModel(*m_spModel->GetData());
}

