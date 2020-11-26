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
	//생성자 소멸자
	directXSetup();
	~directXSetup();

	//기능별 함수(만듬)
protected:
	//Setting and Create
	HRESULT CreateD3DObj(); //d3dobj를 생성
	void SetupD3DDevice(); //d3ddevice 설정
	HRESULT CreateD3Ddevice(HWND hWnd); // d3ddevice 생성
	void SetUpZbuffer(); //z버퍼 설정
	void SetUpAmbient(); // 엠비션트 라이트 설정
	HRESULT MeshLoadTest(); // 메쉬 가져오기
	HRESULT InitMeshMaterialbuffer(); // 메쉬 물질 버퍼 선언 및 초기화
	HRESULT InitMeshTexturebuffer(); // 메쉬 텍스쳐 버퍼 선언 및 초기화
	void CopyMaterial(); // 물질 버퍼 복사
	void SetAmbientcolor(); // 물질버퍼로부터 엠비션트 컬러 복사
	void CreateTexture(); // 텍스처 생성
	void SetUpWorldMatrix(); //월드 매트릭스(좌표계) 설정
	void SetUpViewMatrix(); //뷰 매트릭스(좌표계) 설정
	void SetUpProjMatrix(); //프로젝션 매트릭스(좌표계) 설정



	//delete and clear
	void deleteMeshMaterials(); // 메쉬 물질 버퍼 삭제
	void deleteMeshTextures(); // 메쉬 텍스처 버퍼 삭제
	void ReleaseMesh(); // 메쉬 릴리즈
	void ReleaseD3DDevice(); // D3D 디바이스 릴리즈
	void ReleaseD3D(); // D3D 릴리즈
	void Clearbuffer(); // 백버퍼,z버퍼 초기화

	//Render
	void RenderScene(); //씬을 렌더링 한다.
	void RenderingMeshes(); //설정한 물질과 텍스쳐들을 렌더링 한다.



public:
	//기본생성함수
	HRESULT InitD3D(HWND hWnd);
	HRESULT InitGeometry();
	void Cleanup();
	void SetupMatrices();
	void Render();
};