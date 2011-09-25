#include "Renderer.hpp"

Renderer::Renderer(HINSTANCE hInstance,
	HWND hWnd)
{
	m_hInstance = hInstance;
	m_hWnd = hWnd;
}

Renderer::~Renderer()
{
	CloseDevice();
}

void Renderer::UpdateScene(float dt)
{
}

void Renderer::DrawScene()
{
	m_pDevice->Clear(0,
		0, 
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0,255,0),
		1.0f,
		0);

	m_pDevice->Present( NULL, NULL, 0, NULL);
}

int Renderer::InitDirect3D()
{
	BOOL result = TRUE;
	HRESULT hr;
	RECT rc;
	GetClientRect( m_hWnd, &rc );
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;
	UINT createDeviceFlags = 0;
	IDirect3D9 *pD3D9 = NULL;
	D3DPRESENT_PARAMETERS d3dpp;
	D3DVIEWPORT9 vp;

	//Create the D3D9 Object
	pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	//Set the Present Parameters
	memset(&d3dpp, 0, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	//Create the D3D9 Device
	pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, 
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pDevice);

	//Load the effect file and the texture maps
	DWORD dwShaderFlags = D3DXFX_NOT_CLONEABLE;
	hr = D3DXCreateEffectFromFile( m_pDevice, L".\\Tech.fx", NULL, NULL, dwShaderFlags, 
		NULL, &m_pEffect, NULL );

	// Set the viewport
	RECT rect;
	GetClientRect(m_hWnd, &rect);
	vp.X = 0;
	vp.Y = 0;
	vp.Width = rect.right - rect.left;
	vp.Height = rect.bottom - rect.top;
	vp.MinZ = 0.0f;
	vp.MaxZ = 1.0f;
	m_pDevice->SetViewport(&vp);


	// Setup timer to refresh window
	if (FALSE == result)
	{
		CloseDevice();
	}

	return (result);
}

LRESULT CALLBACK Renderer::WndProc(HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

int Renderer::Run()
{
	MSG msg = {0};

	msg.message = WM_NULL;
	while( WM_QUIT != msg.message )
	{
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			DrawScene();
		}
	}

	return (int)msg.wParam;
}

void Renderer::CloseDevice()
{
	if(m_pEffect)
	{
		m_pEffect->Release();
		m_pEffect = 0;
	}

	if(m_pDevice)
	{
		m_pDevice->Release();
		m_pDevice = 0;
	}
}