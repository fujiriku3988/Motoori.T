#pragma once

class Water : public KdGameObject
{
public:
	Water() {}
	virtual ~Water()		override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()		override;
	void DrawLesson()		override;

private:
	std::shared_ptr<KdModelWork> m_spModel = nullptr;
	bool a = false;
	bool b = false;
	Math::Vector2 m_UVOffSet;
};