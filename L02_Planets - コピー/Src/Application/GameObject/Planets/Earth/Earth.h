#pragma once
class Earth :public KdGameObject
{
public:
	Earth() {};
	~Earth() {};

	void Update()override;
	void DrawLit()override;
	void Init()override;
private:
	std::shared_ptr<KdModelData>m_spModel = nullptr;
	//ベクトル=必ず「長さ（力）」が１出なければならない
	Math::Vector3 pos = m_mWorld.Translation();//x,y,zを返す
	float m_rotY;
};
