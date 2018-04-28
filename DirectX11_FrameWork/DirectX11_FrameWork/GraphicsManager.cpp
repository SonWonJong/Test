#include "stdafx.h"
#include "GraphicsManager.h"
#include "DirectXManager.h"
#include "CameraClass.h"
#include "ModelClass.h"
#include "ColorShader.h"

GraphicsManager::GraphicsManager()
{
}


GraphicsManager::~GraphicsManager()
{
}

bool GraphicsManager::Initialize(int InScreenWidth, int InScreenHeight, HWND InHwnd)
{
	m_Direct3D = new DirectXManager;
	if (!m_Direct3D)
		return false;

	if (!m_Direct3D->Initialize(InScreenWidth, InScreenHeight, VSYNC_ENABLED, InHwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR))
		return false;

	m_Camera = new CameraClass;
	if (!m_Camera)
		return false;

	// ī�޶� ������ ����
	m_Camera->SetPosition(0.0f, 0.0f, -15.0f);

	// m_Model ��ü ����
	m_Model = new ModelClass;
	if (!m_Model)
		return false;

	// m_Model ��ü �ʱ�ȭ
	if (!m_Model->Initialize(m_Direct3D->GetDevice()))
	{
		MessageBox(InHwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// m_ColorShader ��ü ����
	m_ColorShader = new ColorShader;
	if (!m_ColorShader)
	{
		return false;
	}

	// m_ColorShader ��ü �ʱ�ȭ
	if (!m_ColorShader->Initialize(m_Direct3D->GetDevice(), InHwnd))
	{
		MessageBox(InHwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicsManager::Shutdown()
{
	// m_ColorShader ��ü ��ȯ
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = nullptr;
	}

	// m_Model ��ü ��ȯ
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = nullptr;
	}

	// m_Camera ��ü ��ȯ
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = nullptr;
	}

	// Direct3D ��ü ��ȯ
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = nullptr;
	}
}

bool GraphicsManager::Frame()
{
	return Render();
}

bool GraphicsManager::Render()
{
	m_Direct3D->BeginScene(0.0f, 1.0f, 1.0f, 1.0f);

	//static float a = 0.0f;
	//static float b = 0.0f;
	//static float c = 0.0f;

	////if (a > 360.0f)
	////	a = 0.0f;

	////if (b > 360.0f)
	////	b = 0.0f;
	////
	////if (c > 360.0f)
	////	c = 0.0f;
	//a += 1.f;

	//m_Camera->SetRotation(a, b, c);
	// ī�޶��� ��ġ�� ���� �� ����� �����մϴ�
	m_Camera->Render();

	// ī�޶� �� d3d ��ü���� ����, �� �� ���� ����� �����ɴϴ�
	XMMATRIX WorldMatrix, ViewMatrix, ProjectionMatrix;
	m_Direct3D->GetWorldMatrix(WorldMatrix);
	m_Camera->GetViewMatrix(ViewMatrix);
	m_Direct3D->GetProjectionMatrix(ProjectionMatrix);

	// �� ���ؽ��� �ε��� ���۸� �׷��� ������ ���ο� ��ġ�Ͽ� ������� �غ��մϴ�.
	m_Model->Render(m_Direct3D->GetDeviceContext());

	//// ���� ���̴��� ����Ͽ� ���� ������
	if (!m_ColorShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), WorldMatrix, ViewMatrix, ProjectionMatrix))
	{
		return false;
	}
	
	// ������ ������ ȭ�鿡 ���
	m_Direct3D->EndScene();

	return true;
}