#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>

class Renderer
{
public:
	Renderer(HINSTANCE hInstance, HWND hWnd);
	~Renderer();

	void		CloseDevice();
	void		UpdateScene(float dt);
	void		DrawScene();
	int 		InitDirect3D();
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	int			Run();
private:
	IDirect3DDevice9* m_pDevice;
	HINSTANCE					m_hInstance;
	HWND							m_hWnd;
	ID3DXEffect*			m_pEffect;
};