#pragma once
class Application;
class Moon :public KdGameObject
{
public:
	Moon() {};
	~Moon() {};

	void Update()override;
	void DrawLit()override;
	void Init()override;
	void SetOwner(Application* owner) { m_Owner = owner; }
private:
	std::shared_ptr<KdModelData>m_spModel = nullptr;
	//ベクトル=必ず「長さ（力）」が１出なければならない
	Math::Vector3 pos = m_mWorld.Translation();//x,y,zを返す
	float m_rotY;
	Application* m_Owner = nullptr;
	std::vector<std::shared_ptr<KdGameObject>> m_obj;
};
