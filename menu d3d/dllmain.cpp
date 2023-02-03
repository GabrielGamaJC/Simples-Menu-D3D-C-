// dllmain.cpp : Defines the entry point for the DLL application.
#include "header.h"
#include "Hook.h"
#include "Draw.h"
#include "Menu.h"
#include "funções.h"
#include "vector.h"
#include <time.h>

void CreateDevice(DWORD * dVTable) {

	LPDIRECT3D9 mD3D = NULL;
	mD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (mD3D == NULL)
	return;
	D3DPRESENT_PARAMETERS pPresentParameters;
	ZeroMemory(&pPresentParameters, sizeof(pPresentParameters));
	pPresentParameters.Windowed = true;
	pPresentParameters.BackBufferFormat = D3DFMT_UNKNOWN;
	pPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;


	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (FAILED(mD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetDesktopWindow(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pPresentParameters, &pDevice)))

		
		return;
	DWORD *vTable = (DWORD*)pDevice;
	vTable = (DWORD*)vTable[0];

	dVTable[0] = vTable[16];//reset
	dVTable[1] = vTable[17];//present
	dVTable[2] = vTable[42];//endscene
//	dVTable[3] = vTable[82];//drawindex

}



void createmenu() {

	DWORD vTbable[3] = { 0 };
	CreateDevice(vTbable);
	Original_EndScene = (_EndScene)vTbable[2];
	//Original_DrawIndexedPrimitive = (_DrawIndexedPrimitive)vTbable[3];

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	
	DetourAttach(&(PVOID&)Original_EndScene,(PVOID)My_EndScene);
	//DetourAttach(&(PVOID&)Original_DrawIndexedPrimitive, (PVOID)My_DrawIndexedPrimitive);
	DetourTransactionCommit();
	//HookFunction((void*)Original_EndScene, (void*)My_EndScene, 5, EndScene_bytes);

   }
DWORD WINAPI mThread(PVOID tantofaz) {
	
	while (!GetModuleHandle("d3d9.dll")) {
		Sleep(100);


	}

	createmenu();
	while(1){
		ativa();
		Sleep(100);

	}
	return 0;

}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		CreateThread(0, 0, mThread, nullptr, 0, 0);

	}
		
   
    return TRUE;
}

