#include "Transform.hpp"

namespace Viewer
{

	Transform::Transform(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext)
		: m_buffer(device, deviceContext)
	{
		Scale = { 1.0f, 1.0f, 1.0f };
		Position = { 0.0f, 0.0f, 0.0f };
		Rotation = { 0.0f, 0.0f, 0.0f };
	}

	void Transform::Initialize()
	{
		// 2, for model and normal matrix.
		m_buffer.Initialize(2);
	}

	void Transform::Update()
	{
		// Create matrix from position, rotation and scale.
		DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(Position.x, Position.y, Position.z);
		DirectX::XMMATRIX rotationX = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(Rotation.x));
		DirectX::XMMATRIX rotationY = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(Rotation.y));
		DirectX::XMMATRIX rotationZ = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(Rotation.z));
		DirectX::XMMATRIX rotation = rotationZ * rotationY * rotationX;
		DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(Scale.x, Scale.y, Scale.z);

		DirectX::XMMATRIX modelMatrix = DirectX::XMMatrixTranspose(
			scale * rotation * translation
		);
		DirectX::XMMATRIX normalMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, modelMatrix));

		DirectX::XMMATRIX matrices[2] = { modelMatrix, normalMatrix };
		m_buffer.Update(&matrices[0], 2);
	}
}
