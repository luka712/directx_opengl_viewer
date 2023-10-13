#include "DebugNormalMaterial.hpp"
#include "MatrixUtil.hpp"

namespace Viewer
{
	DebugNormalMaterial::DebugNormalMaterial(CComPtr<ID3D11Device> device, CComPtr<ID3D11DeviceContext> deviceContext)
		: m_device(device), m_deviceContext(deviceContext), m_viewModelBuffer(device, deviceContext)
	{
		m_shader = new DebugNormalShader(device, deviceContext);
	}

	DebugNormalMaterial::~DebugNormalMaterial()
	{
		delete m_shader;
	}

	void DebugNormalMaterial::Initialize()
	{
		m_shader->Initialize();
		m_viewModelBuffer.Initialize();
	}

	void DebugNormalMaterial::Use()
	{
		m_shader->Use();
	}

	void DebugNormalMaterial::UpdateProperties(Camera& camera, Transform& transform)
	{
		m_shader->SetProjectionMatrix(*camera.GetProjectionBuffer());

		ViewModelViewModelNormalData viewModelData;
		DirectX::XMMATRIX viewModelMatrix =  transform.ModelMatrix * camera.ViewMatrix;
		viewModelData.ViewModelMatrix = DirectX::XMMatrixTranspose(viewModelMatrix);
		// usually it needs to be transposed, but here it's fine since it direcx x tranposes when sending to shader.
		viewModelData.ViewModelNormalMatrix = DirectX::XMMatrixInverse(nullptr, viewModelMatrix);

		m_viewModelBuffer.Update(&viewModelData, 1);
		m_shader->SetViewModelMatrix(m_viewModelBuffer);
	}

}
