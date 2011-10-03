#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include "DataParser.hpp"
#include <vector>
#include <iterator>

#ifndef D3DRGBA
#define D3DRGBA(r, g, b, a) \
  (   (((long)((a) * 255)) << 24) | (((long)((r) * 255)) << 16) \
  |   (((long)((g) * 255)) << 8) | (long)((b) * 255) \
  )
#endif 

const D3DVERTEXELEMENT9 g_VBDecl_Geometry[] =
{
{0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
D3DDECL_END()
};

typedef struct InstanceData
{
  D3DXMATRIXA16 world; 
  D3DCOLOR color;
} InstanceData;

//const D3DVERTEXELEMENT9 g_VBDecl_InstanceData[] =
//{
//{1, 0,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1},
//{1, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2},
//{1, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3},
//{1, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4},
//{1, 64, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0},
//D3DDECL_END()
//};


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
  void CreateBuffers(std::vector<DataPoint*> dataArray);
private:
  D3DXVECTOR3             m_VecEye;
  D3DXMATRIXA16           m_View;
  D3DXMATRIXA16           m_Projection;
  int                    m_Size;
  IDirect3DDevice9*        m_pDevice;
  IDirect3DVertexBuffer9*   m_pVB;
  IDirect3DIndexBuffer9*    m_pIB;
  IDirect3DVertexBuffer9*   m_pVBInstanceData;
  IDirect3DVertexDeclaration9*    m_pVertexDeclHardware;
  HINSTANCE               m_hInstance;
  HWND                    m_hWnd;
  D3DVERTEXELEMENT9       m_VertexDeclaration[MAXD3DDECLLENGTH];
  ID3DXEffect*			      m_pEffect;
  ID3DXMesh*              m_pSphere;
};