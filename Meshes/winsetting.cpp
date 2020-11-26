#include "DirectXSetup.h"

directXSetup DS;
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        DS.Cleanup();
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}


//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
    UNREFERENCED_PARAMETER(hInst);

    // Register the window class
    WNDCLASSEX wc =
    {
        sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
        L"D3D Tutorial", NULL
    };
    RegisterClassEx(&wc);

    // Create the application's window
    HWND hWnd = CreateWindow(L"D3D Tutorial", L"D3D Tutorial 06: Meshes",
        WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
        NULL, NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    if (SUCCEEDED(DS.InitD3D(hWnd)))
    {
        // Create the scene geometry
        if (SUCCEEDED(DS.InitGeometry()))
        {
            // Show the window
            ShowWindow(hWnd, SW_SHOWDEFAULT);
            UpdateWindow(hWnd);

            // Enter the message loop
            MSG msg;
            ZeroMemory(&msg, sizeof(msg));
            while (msg.message != WM_QUIT)
            {
                if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
                else
                    DS.Render();
            }
        }
    }

    UnregisterClass(L"D3D Tutorial", wc.hInstance);
    return 0;
}