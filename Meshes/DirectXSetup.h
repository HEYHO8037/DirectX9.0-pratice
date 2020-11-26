#pragma once
#include "total.h"

class directXSetup
{
protected:
	LPDIRECT3D9         g_pD3D = NULL; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9   g_pd3dDevice = NULL; // Our rendering device

	LPD3DXMESH          g_pMesh = NULL; // Our mesh object in sysmem
	D3DMATERIAL9*		g_pMeshMaterials = NULL; // Materials for our mesh
	LPDIRECT3DTEXTURE9* g_pMeshTextures = NULL; // Textures for our mesh
	DWORD               g_dwNumMaterials = 0L;   // Number of mesh materials

	D3DPRESENT_PARAMETERS d3dpp; // d3ddevice parameters
	LPD3DXBUFFER pD3DXMtrlBuffer; // d3d material buffer
	D3DXMATERIAL* d3dxMaterials; // d3d materials(buffer)
public:
	//������ �Ҹ���
	directXSetup();
	~directXSetup();

	//��ɺ� �Լ�(����)
protected:
	//Setting and Create
	HRESULT CreateD3DObj(); //d3dobj�� ����
	void SetupD3DDevice(); //d3ddevice ����
	HRESULT CreateD3Ddevice(HWND hWnd); // d3ddevice ����
	void SetUpZbuffer(); //z���� ����
	void SetUpAmbient(); // �����Ʈ ����Ʈ ����
	HRESULT MeshLoadTest(); // �޽� ��������
	HRESULT InitMeshMaterialbuffer(); // �޽� ���� ���� ���� �� �ʱ�ȭ
	HRESULT InitMeshTexturebuffer(); // �޽� �ؽ��� ���� ���� �� �ʱ�ȭ
	void CopyMaterial(); // ���� ���� ����
	void SetAmbientcolor(); // �������۷κ��� �����Ʈ �÷� ����
	void CreateTexture(); // �ؽ�ó ����
	void SetUpWorldMatrix(); //���� ��Ʈ����(��ǥ��) ����
	void SetUpViewMatrix(); //�� ��Ʈ����(��ǥ��) ����
	void SetUpProjMatrix(); //�������� ��Ʈ����(��ǥ��) ����



	//delete and clear
	void deleteMeshMaterials(); // �޽� ���� ���� ����
	void deleteMeshTextures(); // �޽� �ؽ�ó ���� ����
	void ReleaseMesh(); // �޽� ������
	void ReleaseD3DDevice(); // D3D ����̽� ������
	void ReleaseD3D(); // D3D ������
	void Clearbuffer(); // �����,z���� �ʱ�ȭ

	//Render
	void RenderScene(); //���� ������ �Ѵ�.
	void RenderingMeshes(); //������ ������ �ؽ��ĵ��� ������ �Ѵ�.



public:
	//�⺻�����Լ�
	HRESULT InitD3D(HWND hWnd);
	HRESULT InitGeometry();
	void Cleanup();
	void SetupMatrices();
	void Render();
};