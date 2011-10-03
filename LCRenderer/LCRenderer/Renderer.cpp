#include "Renderer.hpp"

Renderer::Renderer(HINSTANCE hInstance,
  HWND hWnd) :
    m_pDevice(NULL),
    m_pVB(NULL),
    m_pIB(NULL),
    m_pVBInstanceData(NULL),
    m_pVertexDeclHardware(NULL),
    m_pSphere(NULL)
{
  D3DXMatrixIdentity(&m_View);
  D3DXMatrixIdentity(&m_Projection);
  m_hInstance = hInstance;
  m_hWnd = hWnd;

  m_VecEye = D3DXVECTOR3(2.0f, 2.0f, 10.0f);

  D3DXVECTOR3 vecAt (0.0f, 0.0f, 0.0f);
  D3DXVECTOR3 vecUp (0.0f, 1.0f, 0.0f);

  D3DXMatrixPerspectiveFovLH(&m_Projection, (40.0f/180.0f)*D3DX_PI, 1.0f, 0.1f, 25.0f);
  D3DXMatrixLookAtLH( &m_View, &m_VecEye, &vecAt, &vecUp );
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


  D3DCOLOR color = D3DRGBA(0.0f,1.0f,0.0f,1.0f);
  // Clear the render target and the zbuffer 
  m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0 );

   //Render the scene
  if( SUCCEEDED( m_pDevice->BeginScene() ) )
  {
    // Get the projection & view matrix from the camera class

    // Update the effect's variables
    D3DXMATRIXA16 viewProjection = m_View * m_Projection;
    m_pEffect->SetMatrix( "g_mViewProjection" , &viewProjection);
    HRESULT hr;
    UINT iPass, cPasses;

    m_pDevice->SetVertexDeclaration( m_pVertexDeclHardware );

    // Stream zero is our model, and its frequency is how we communicate the number of instances required,
    // which in this case is the total number of boxes
    m_pDevice->SetStreamSource( 0, m_pVB, 0, D3DXGetDeclVertexSize( m_VertexDeclaration , 0) );
    m_pDevice->SetStreamSourceFreq( 0, D3DSTREAMSOURCE_INDEXEDDATA | m_Size);

    // Stream one is the instancing buffer, so this advances to the next value
    // after each box instance has been drawn, so the divider is 1.
    m_pDevice->SetStreamSource( 1, m_pVBInstanceData, 0, sizeof(InstanceData) );
    m_pDevice->SetStreamSourceFreq( 1, D3DSTREAMSOURCE_INSTANCEDATA | 1ul );

    m_pDevice->SetIndices( m_pIB ); 

    // Render the scene with this technique
    // as defined in the .fx file
    m_pEffect->SetTechnique( "RenderScene" );

    m_pEffect->Begin( &cPasses, 0 );
    for( iPass = 0; iPass < cPasses; iPass++ )
    {
      m_pEffect->BeginPass( iPass );

      // Render the boxes with the applied technique

      // The effect interface queues up the changes and performs them 
      // with the CommitChanges call. You do not need to call CommitChanges if 
      // you are not setting any parameters between the BeginPass and EndPass.
      m_pEffect->CommitChanges();

      //m_pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 4 * 6, 0, 6 * 2 );
      m_pSphere->DrawSubset(0);
      m_pEffect->EndPass();
    }
    m_pEffect->End();

    m_pDevice->SetStreamSourceFreq( 0, 1 );
    m_pDevice->SetStreamSourceFreq( 1, 1 );

    m_pDevice->EndScene();
  }

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
  D3DXCreateSphere(m_pDevice, 1.0f, 16, 16, &m_pSphere, NULL);


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

void Renderer::CreateBuffers(std::vector<DataPoint*> dataArray)
{
  m_Size = dataArray.size();
  m_pSphere->GetVertexBuffer(&m_pVB);
  //this is probably going to break but whatever
  m_pSphere->GetDeclaration(m_VertexDeclaration);

  m_pSphere->GetIndexBuffer(&m_pIB);
  m_pDevice->CreateVertexDeclaration( m_VertexDeclaration, &m_pVertexDeclHardware );

  m_pDevice->CreateVertexBuffer(m_Size * sizeof(InstanceData), 0, 0, D3DPOOL_MANAGED, &m_pVBInstanceData, 0);

  D3DXMATRIXA16 sphereTransform;
  D3DXMATRIXA16 ellipTransform;

  D3DXMatrixIdentity(&sphereTransform);
  D3DXMatrixIdentity(&ellipTransform);

  D3DXMATRIXA16 transform;
  D3DXMATRIXA16 rotate;

  InstanceData* pData;
  m_pVBInstanceData->Lock(0, NULL, (void**) &pData, 0);
  for(std::vector<DataPoint*>::iterator i = dataArray.begin();
    i != dataArray.end();
    i++)
  {
    D3DXMatrixIdentity(&sphereTransform);
    D3DXMatrixIdentity(&ellipTransform);
    D3DXMatrixIdentity(&transform);
    D3DXMatrixIdentity(&rotate);

    if(1 == (*i)->type)
    {
      D3DXMatrixTranslation(&transform, (*i)->x, (*i)->y, (*i)->z);
      sphereTransform = sphereTransform * transform; 
      pData->world = sphereTransform;
      pData->color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
      pData++;
    }
    else if(2 == (*i)->type)
    {
      D3DXMatrixTranslation(&transform, (*i)->x, (*i)->y, (*i)->z);
      D3DXMatrixRotationYawPitchRoll(&rotate, 0.0f, (*i)->ry, (*i)->rz);
      ellipTransform = ellipTransform * rotate * transform;
      pData->world = ellipTransform;
      pData->color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
      pData++;
    }
  }
  m_pVBInstanceData->Unlock();

}