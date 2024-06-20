#pragma once
class CameraBase:public KdGameObject
{
public:
	CameraBase() {};
	virtual  ~CameraBase()override {};

	void Init()override;
	void Update()override;
	void PreDraw();
	void SetTarget(const std::shared_ptr<KdGameObject>& target)
	{
		m_spTarget = target;
	}

	const Math::Matrix GetRotationMatrix() const
	{
		return Math::Matrix::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(m_DegAng.y),
		DirectX::XMConvertToRadians(m_DegAng.x),
		DirectX::XMConvertToRadians(m_DegAng.z)
		);
	}

	const Math::Matrix GetRotationYMatrix() const
	{
		return Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_DegAng.y));
	}

private:
	//カメラの回転角度
	Math::Vector3 m_DegAng = Math::Vector3::Zero;
protected:
	void UpdateRotateByMouse();

	std::weak_ptr<KdGameObject>m_spTarget;
	std::shared_ptr<KdCamera> m_spCamera = nullptr;

	Math::Matrix m_mLocalPos=Math::Matrix::Identity;
	Math::Matrix m_mRot = Math::Matrix::Identity;

	//カメラ回転用マウス座標
	POINT m_FixMousePos = {};
};

