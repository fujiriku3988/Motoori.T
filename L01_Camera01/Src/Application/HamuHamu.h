﻿#pragma once

class HamuHamu :public KdGameObject
{
public:
	HamuHamu();
	~HamuHamu()override;

	void Init()override;
	void Update()override;
	void DrawLit()override;

	

private:
	std::shared_ptr< KdSquarePolygon>m_spPoly = nullptr;
	float m_movePow = 0.05f;
	void Release();
};
