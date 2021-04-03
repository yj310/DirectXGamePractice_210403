
#include "DXUT.h"
#include "resource.h"
#include "global.h"

PageManager pageManager; 
int floorP[FLOOR_WIDTH * FLOOR_HEIGHT];
int maskP[FLOOR_WIDTH * FLOOR_HEIGHT];
int mapP[FLOOR_WIDTH * FLOOR_HEIGHT];
int map[FLOOR_WIDTH * FLOOR_HEIGHT];


bool CALLBACK IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat,
                                      bool bWindowed, void* pUserContext )
{
    // Typically want to skip back buffer formats that don't support alpha blending
    IDirect3D9* pD3D = DXUTGetD3D9Object();
    if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
                                         AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
                                         D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
        return false;

    return true;
}


bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext )
{
    return true;
}

// init
HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{

    pageManager.createMainPage();
   
    return S_OK;
}


HRESULT CALLBACK OnD3D9ResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                    void* pUserContext )
{
    return S_OK;
}


// Update
void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{

    
    if ((GetAsyncKeyState(VK_F1) & 0x8000) != 0)
    {
        pageManager.deleteCurrent();
        
        PostQuitMessage(0);
    }
    pageManager.Update();
}


// Render
void CALLBACK OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    HRESULT hr;


    V( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 45, 50, 170 ), 1.0f, 0 ) );


    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
        pageManager.Render();
        V( pd3dDevice->EndScene() );
    }
}



LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
                          bool* pbNoFurtherProcessing, void* pUserContext )
{
    return 0;
}



void CALLBACK OnD3D9LostDevice( void* pUserContext )
{
}



void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{
    pageManager.deleteCurrent();
}



INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
{

#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif


    DXUTSetCallbackD3D9DeviceAcceptable( IsD3D9DeviceAcceptable );
    DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );
    DXUTSetCallbackD3D9DeviceReset( OnD3D9ResetDevice );
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
    DXUTSetCallbackD3D9DeviceLost( OnD3D9LostDevice );
    DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );
    DXUTSetCallbackDeviceChanging( ModifyDeviceSettings );
    DXUTSetCallbackMsgProc( MsgProc );
    DXUTSetCallbackFrameMove( OnFrameMove );



    DXUTInit( true, true ); // Parse the command line and show msgboxes
    DXUTSetHotkeyHandling( true, true, true );  // handle the default hotkeys
    DXUTSetCursorSettings( true, true ); // Show the cursor and clip it when in full screen
    DXUTCreateWindow( L"¶¥µû¸Ô±â °ÔÀÓ" );
    DXUTCreateDevice( true, 1920, 1080 );

    // Start the render loop
    DXUTMainLoop();




    return DXUTGetExitCode();
}


