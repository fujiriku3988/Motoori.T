#include "Sun.h"

void Sun::Update()
{
}

void Sun::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel);
}

void Sun::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Data/LessonData/Planets/sun.gltf");
	m_objType = KdGameObject::objType::Sun;
}
