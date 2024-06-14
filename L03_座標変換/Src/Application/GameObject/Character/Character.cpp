#include "Character.h"
#include"Application/main.h"

void Character::Init()
{
	float moveSpd = 0.05f;
	result = {};
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

		//m_tex.Load("Asset/Data/LessonData/Character/zgmf-x2OA.png");
		//m_tex.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}
}

void Character::Update()
{
	m_mousePos = GetMousePos();
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		m_clickPos = m_mousePos;
	}

	Math::Vector3 pos;
	Math::Vector3 rayPos = { 0,6.0f,-5.0f };
	Math::Vector3 dir;
	float range;
	std::shared_ptr<KdCamera> camera = m_wpCamera.lock();
	if (camera)
	{
		pos = GetPos();
		result = Math::Vector3::Zero;

		camera->ConvertWorldToScreenDetail(pos, result);
		{
			camera->GenerateRayInfoFromClientPos(m_clickPos, rayPos, dir, range);
			KdCollider::RayInfo ray;
			ray.m_pos = { 0,6.0f,-5.0f };
			//ray.m_dir = Math::Vector3::Backward;
			ray.m_dir = dir;
			ray.m_range = range;
			ray.m_type = KdCollider::TypeGround;

			//レイに当たったobj情報を格納するリスト
			std::list<KdCollider::CollisionResult>retRayList;
			//作成したレイ情報でObjリストと当たり判定をする
			for (auto& obj : Application::Instance().GetObjList())
			{
				obj->Intersects(ray, &retRayList);
			}

			//レイに当たったリストから一番近いオブジェクトを検出
			bool hit = false;
			float maxOverLap = 0;
			Math::Vector3 groundPos = {};//レイが遮断された（Hitした）座標

			//
			for (auto& ret : retRayList)
			{
				//レイが当たった場合の貫通した長さが一番長いものを探す
				if (maxOverLap < ret.m_overlapDistance)
				{
					maxOverLap = ret.m_overlapDistance;
					groundPos = ret.m_hitPos;
					hit = true;
				}
			}

			if (hit)
			{
				//z方向無効
				//groundPos.z = 0;

				//nowPos.z = groundPos.z;
				//nowPos.y = groundPos.y;

				//nowPos.z = 5;
				//nowPos.x = 5;

				//nowPos = { 10,0,10 };
				Math::Vector3 groundVec = groundPos - nowPos;
				groundVec.Normalize();
				nowPos += groundVec * 0.01f;
			}
		}

	}


	Math::Vector3 moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('D')) { moveVec.x = 1.0f; }
	if (GetAsyncKeyState('A')) { moveVec.x = -1.0f; }
	if (GetAsyncKeyState('W')) { moveVec.z = 1.0f; }
	if (GetAsyncKeyState('S')) { moveVec.z = -1.0f; }
	moveVec.Normalize();
	moveVec *= moveSpd;
	nowPos += moveVec;

	// キャラクターのワールド行列を創る処理
	Math::Matrix trans01 = Math::Matrix::CreateTranslation(nowPos);
	m_mWorld = Math::Matrix::CreateTranslation(nowPos);
}

void Character::DrawLit()
{
	if (!m_spPoly) return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Character::DrawSprite()
{
	Math::Rectangle rect = { 0,0,834,792 };
	Math::Color color = { 1,1,1,1 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, result.x, result.y, 834, 792, &rect, &color);
	//KdShaderManager::Instance().m_spriteShader.DrawCircle(result.x, result.y, 100, &kRedColor);
}

POINT Character::GetMousePos()
{
	GetCursorPos(&m_mousePos);

	ScreenToClient(Application::Instance().GetWindowHandle(), &m_mousePos);

	m_mousePos.x = m_mousePos.x;
	m_mousePos.y = m_mousePos.y;
	//m_mousePos.y *= -1;

	return m_mousePos;
}
