#pragma once

void Menu(LPDIRECT3DDEVICE9 pDevice){

	
	DrawBox(Esquerda, Topo-34, largura, 30, azull, pDevice);
	DrawBox(Esquerda + 2, (Topo -34 ) + 2, largura - 4, 30 - 4, azull, pDevice);
	Text(Esquerda + 50, (Topo - 34) + 8, "Gama Sistemas", VERMELHO);


	DrawBox(Esquerda, Topo, largura, Altura, azull, pDevice);
	DrawBox(Esquerda + 2, Topo + 2, largura - 4, Altura - 4, azull, pDevice);
	DrawItem(itens[0],"CrossHair", pDevice);
	DrawItem(itens[1],"ESP Name", pDevice);
	//DrawItem(itens[2],"paraquedas", pDevice);
	//DrawItem(itens[3],"vida infinita", pDevice);

}

HRESULT WINAPI My_EndScene(LPDIRECT3DDEVICE9 pDevice) {

	HRESULT ret;

	CreatFont(pDevice);
	if (bShow)
	Menu(pDevice);

	if (itens[0].on_off)
		crosshair(pDevice);

	keyboard();
	y = (Topo + 6);
	total_itens = 0;
	ResetFont();
	//UnHookFunction((void*)Original_EndScene, EndScene_bytes, 5);
	ret = Original_EndScene(pDevice);
	//HookFunction((void*)Original_EndScene, (void*)My_EndScene, 5, EndScene_bytes);
	return ret;


}


/*
HRESULT WINAPI My_DrawIndexedPrimitive(
	LPDIRECT3DDEVICE9 pDevice,
	D3DPRIMITIVETYPE Type,
	INT              BaseVertexIndex,
	UINT             MinVertexIndex,
	UINT             NumVertices,
	UINT             startIndex,
	UINT             primitiveCount
) {

	HRESULT ret;
	//UnHookFunction((void*)Original_DrawIndexedPrimitive, DrawIndexedPrimitive_bytes, 5);
	ret = Original_DrawIndexedPrimitive(pDevice,Type,BaseVertexIndex,MinVertexIndex,NumVertices,startIndex,primitiveCount);
//HookFunction((void*)Original_EndScene, (void*)My_EndScene, 5, EndScene_bytes);
	return ret;

 }
 */