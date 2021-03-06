#pragma once


const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


class GraphicsManager
{
public:
	GraphicsManager();
	~GraphicsManager();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

	void SetFps(int InFps) { m_fps = InFps; }
	void SetCpu(int InCpu) { m_cpu = InCpu; }
private:
	bool Render();

	bool CubeAndTextureRender();
	bool FrustumRender();

private:
	class DirectXManager * m_Direct3D = nullptr;
	class CameraClass* m_Camera = nullptr;
	class ModelClass* m_Model = nullptr;
	class ModelClass* m_Model2 = nullptr;
	class ModelClass* m_Model3 = nullptr;
	class ColorShader* m_ColorShader = nullptr;
	class TextureShader* m_TextureShader = nullptr;
	class LightClass* m_LightClass;
	class LightShader* m_LightShader;
	class BitmapClass* m_Bitmap = nullptr;
	class TextClass* m_Text = nullptr;
	class ModelListClass* m_ModelList = nullptr;
	class FrustumClass* m_Frustum = nullptr;

	int m_fps;
	int m_cpu;
};

