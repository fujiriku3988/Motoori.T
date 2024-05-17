#include"HamuHamu.h"

HamuHamu::HamuHamu()
{
}

HamuHamu::~HamuHamu()
{
}

void HamuHamu::Init()
{
	m_spPoly = std::make_shared<KdSquarePolygon>();
	m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
	m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_objType = ObjectType::Hamu;
}

void HamuHamu::Update()
{
	//ベクトル=必ず「長さ（力）」が１出なければならない
	Math::Vector3 pos = m_mWorld.Translation();//x,y,zを返す
	Math::Vector3 moveVec = Math::Vector3::Zero;

	if (GetAsyncKeyState('W'))
	{
		moveVec.z = 1.0f;
	}
	if (GetAsyncKeyState('A'))moveVec.x = -1.0f;
	if (GetAsyncKeyState('S'))moveVec.z = -1.0f;
	if (GetAsyncKeyState('D'))moveVec.x = 1.0f;

	moveVec *= m_movePow;
	pos += moveVec;

	//キャラクターのワールド行列を作成
	m_mWorld = Math::Matrix::CreateTranslation(pos);
	//m_spPoly->SetMaterial()
}

void HamuHamu::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}
