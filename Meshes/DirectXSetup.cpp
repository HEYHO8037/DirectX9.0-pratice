#include "DirectXSetup.h"

directXSetup::directXSetup()
{

}

directXSetup::~directXSetup()
{

}

HRESULT directXSetup::CreateD3DObj()
{
    if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
        return E_FAIL;
}
void directXSetup::SetupD3DDevice()
{
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
}
HRESULT directXSetup::CreateD3Ddevice(HWND hWnd)
{
    if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp, &g_pd3dDevice)))
    {
        return E_FAIL;
    }
}

void directXSetup::SetUpZbuffer()
{
    g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}

void directXSetup::SetUpAmbient()
{
    g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
}

HRESULT directXSetup::MeshLoadTest()
{
    // Load the mesh from the specified file
    if (FAILED(D3DXLoadMeshFromX(L"Tiger.x", D3DXMESH_SYSTEMMEM,
        g_pd3dDevice, NULL,
        &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
        &g_pMesh)))
    {
        // If model is not in current folder, try parent folder
        if (FAILED(D3DXLoadMeshFromX(L"..\\Tiger.x", D3DXMESH_SYSTEMMEM,
            g_pd3dDevice, NULL,
            &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
            &g_pMesh)))
        {
            MessageBox(NULL, L"Could not find tiger.x", L"Meshes.exe", MB_OK);
            return E_FAIL;
        }
    }
}

HRESULT directXSetup::InitMeshMaterialbuffer()
{
    g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
    if (g_pMeshMaterials == NULL)
    {
        return E_OUTOFMEMORY;
    }
}

HRESULT directXSetup::InitMeshTexturebuffer()
{
    g_pMeshTextures = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];
    if (g_pMeshTextures == NULL)
    {
        return E_OUTOFMEMORY;
    }
}

void directXSetup::CopyMaterial()
{
    for (DWORD i = 0; i < g_dwNumMaterials; i++)
    {
        g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
    }
}

void directXSetup::SetAmbientcolor()
{
    for (DWORD i = 0; i < g_dwNumMaterials; i++)
    {
        g_pMeshMaterials[i].Ambient = g_pMeshMaterials[i].Diffuse;
    }
}

void directXSetup::CreateTexture()
{
    for (DWORD i = 0; i < g_dwNumMaterials; i++)
    {
        g_pMeshTextures[i] = NULL;
        if (d3dxMaterials[i].pTextureFilename != NULL &&
            lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
        {
            // Create the texture
            if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice,
                d3dxMaterials[i].pTextureFilename,
                &g_pMeshTextures[i])))
            {
                // If texture is not in current folder, try parent folder
                const CHAR* strPrefix = "..\\";
                CHAR strTexture[MAX_PATH];
                strcpy_s(strTexture, MAX_PATH, strPrefix);
                strcat_s(strTexture, MAX_PATH, d3dxMaterials[i].pTextureFilename);
                // If texture is not in current folder, try parent folder
                if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice,
                    strTexture,
                    &g_pMeshTextures[i])))
                {
                    MessageBox(NULL, L"Could not find texture map", L"Meshes.exe", MB_OK);
                }
            }
        }
    }
}

void directXSetup::deleteMeshMaterials()
{
    if (g_pMeshMaterials != NULL)
        delete[] g_pMeshMaterials;
}

void directXSetup::deleteMeshTextures()
{
    if (g_pMeshTextures)
    {
        for (DWORD i = 0; i < g_dwNumMaterials; i++)
        {
            if (g_pMeshTextures[i])
                g_pMeshTextures[i]->Release();
        }
        delete[] g_pMeshTextures;
    }
}

void directXSetup::ReleaseMesh()
{
    if (g_pMesh != NULL)
        g_pMesh->Release();
}

void directXSetup::ReleaseD3DDevice()
{
    if (g_pd3dDevice != NULL)
        g_pd3dDevice->Release();
}
void directXSetup::ReleaseD3D()
{
    if (g_pD3D != NULL)
        g_pD3D->Release();
}

void directXSetup::SetUpWorldMatrix()
{
    D3DXMATRIXA16 matWorld;
    D3DXMatrixRotationY(&matWorld, timeGetTime() / 1000.0f);
    g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
}

void directXSetup::SetUpViewMatrix()
{
    D3DXVECTOR3 vEyePt(0.0f, 3.0f, -5.0f);
    D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
    D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
    g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);
}

void directXSetup::SetUpProjMatrix()
{
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
    g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void directXSetup::Clearbuffer()
{
    g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
        D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
}

void directXSetup::RenderingMeshes()
{
    for (DWORD i = 0; i < g_dwNumMaterials; i++)
    {
        // Set the material and texture for this subset
        g_pd3dDevice->SetMaterial(&g_pMeshMaterials[i]);
        g_pd3dDevice->SetTexture(0, g_pMeshTextures[i]);

        // Draw the mesh subset
        g_pMesh->DrawSubset(i);
    }
}

void directXSetup::RenderScene()
{
    if (SUCCEEDED(g_pd3dDevice->BeginScene()))
    {
        // Setup the world, view, and projection matrices
        SetupMatrices();

        // Meshes are divided into subsets, one for each material. Render them in
        // a loop
        RenderingMeshes();

        // End the scene
        g_pd3dDevice->EndScene();
    }
}

HRESULT directXSetup::InitD3D(HWND hWnd)
{
    // Create the D3D object.
    CreateD3DObj();

    // Set up the structure used to create the D3DDevice. Since we are now
    // using more complex geometry, we will create a device with a zbuffer.
    SetupD3DDevice();

    // Create the D3DDevice
    CreateD3Ddevice(hWnd);

    // Turn on the zbuffer
    SetUpZbuffer();

    // Turn on ambient lighting 
    SetUpAmbient();

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: InitGeometry()
// Desc: Load the mesh and build the material and texture arrays
//-----------------------------------------------------------------------------
HRESULT directXSetup::InitGeometry()
{
    MeshLoadTest();
    // We need to extract the material properties and texture names from the 
    // pD3DXMtrlBuffer
    d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
    
    InitMeshMaterialbuffer();
    InitMeshTexturebuffer();

    // Copy the material
    CopyMaterial();
    // Set the ambient color for the material (D3DX does not do this)
    SetAmbientcolor();

    CreateTexture();

    // Done with the material buffer
    pD3DXMtrlBuffer->Release();

    return S_OK;
}

//----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
void directXSetup::Cleanup()
{
    deleteMeshMaterials();
    deleteMeshTextures();
    ReleaseMesh();
    ReleaseD3DDevice();
    ReleaseD3D();
}

//-----------------------------------------------------------------------------
// Name: SetupMatrices()
// Desc: Sets up the world, view, and projection transform matrices.
//-----------------------------------------------------------------------------
void directXSetup::SetupMatrices()
{
    // Set up world matrix
    SetUpWorldMatrix();
    // Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we set the
    // eye five units back along the z-axis and up three units, look at the 
    // origin, and define "up" to be in the y-direction.
    SetUpViewMatrix();

    // For the projection matrix, we set up a perspective transform (which
    // transforms geometry from 3D view space to 2D viewport space, with
    // a perspective divide making objects smaller in the distance). To build
    // a perpsective transform, we need the field of view (1/4 pi is common),
    // the aspect ratio, and the near and far clipping planes (which define at
    // what distances geometry should be no longer be rendered).
    SetUpProjMatrix();
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
void directXSetup::Render()
{
    // Clear the backbuffer and the zbuffer
    Clearbuffer();

    // Begin the scene
    RenderScene();

    // Present the backbuffer contents to the display
    g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}