
DWORD DLL = (DWORD)GetModuleHandle("engine.dll");
class PlayerInfo
{
public:
	char pad_0000[456]; //0x0000
	float PosX; //0x01C8
	float PosY; //0x01CC
	float PosZ; //0x01D0
	char pad_01D4[620]; //0x01D4
}; //Size: 0x0440

struct glmatrixf 
{
	float v[16];
	float operator [](int i)const { return v[i]; }
	float &operator [](int i) { return v[i]; }
	
};
glmatrixf* GetViewMatrix()
{

	return(glmatrixf*)(0x243F90FC); //falta matrix);
}
 D3DXVECTOR3 W2S(glmatrixf* mvmatrix, D3DXVECTOR3 vPlayerLoc)
{
	 D3DXVECTOR4 ClipCoord;
	ClipCoord.x = vPlayerLoc.x * mvmatrix ->v[0] + vPlayerLoc.y * mvmatrix ->v[4] + vPlayerLoc.z * mvmatrix ->v[8] + mvmatrix ->v[12];
	ClipCoord.y = vPlayerLoc.x * mvmatrix ->v[1] + vPlayerLoc.y * mvmatrix ->v[5] + vPlayerLoc.z * mvmatrix ->v[9] + mvmatrix ->v[13];
	ClipCoord.z = vPlayerLoc.x * mvmatrix ->v[2] + vPlayerLoc.y * mvmatrix ->v[6] + vPlayerLoc.z * mvmatrix ->v[10] + mvmatrix ->v[14];
	ClipCoord.w = vPlayerLoc.x * mvmatrix ->v[3] + vPlayerLoc.y * mvmatrix ->v[7] + vPlayerLoc.z * mvmatrix ->v[11] + mvmatrix ->v[15];
	if (ClipCoord.w < 0)
		return D3DXVECTOR3(-1, -1, -1);
	D3DXVECTOR3 normalizar;
	normalizar.x = ClipCoord.x / ClipCoord.w;
	normalizar.y = ClipCoord.y / ClipCoord.w;
	normalizar.z = ClipCoord.z / ClipCoord.w;

	int ViewPort[4] = { 0,0,1280,600 };
	
	D3DXVECTOR3 PlayerScreen;
	PlayerScreen.x = (ViewPort[2] / 2 * normalizar.x) + (normalizar.x + ViewPort[2] / 2);
	PlayerScreen.y = -(ViewPort[3] / 2 * normalizar.x) + (normalizar.x + ViewPort[3] / 2);
	PlayerScreen.z = 0;
	return PlayerScreen;

}
void esp()
{

	for (int i = 0; i < 24; i++)
	{
		DWORD Jogadores = (*(DWORD*)(DLL + 0x005393DC) + 0x0030);
		DWORD Jogadores1 = (*(DWORD*)(Jogadores + (i * 0x14)));
		
		PlayerInfo *Player = (PlayerInfo*)Jogadores1;

		if (Player != 0);
		{


			D3DXVECTOR3 FootPos = D3DXVECTOR3(Player->PosX, Player->PosY, Player->PosZ);
			D3DXVECTOR3 FootPosition = W2S(GetViewMatrix(), FootPos);
			D3DXVECTOR3 HeadPos = D3DXVECTOR3(Player->PosX, Player->PosY, Player->PosZ + 5);
			D3DXVECTOR3 HeadPosition = W2S(GetViewMatrix(), HeadPos);

			int heigth = FootPosition.y - HeadPosition.y;
			int Width = heigth / 2;
			int x = HeadPosition.x - Width / 2;
			int y = HeadPosition.y;
			Text(x,y, "inimigo", VERMELHO);
		}
	}
}


void ativa() {


	crossh = itens[0].on_off;


	if (itens[1].on_off &1)  {
	//	*(DWORD*)0x1234 = 20;
		//*(DWORD*)((int)("client.dll") + 0x3B0C9C) = 2;
		*(BYTE*)((int)0x969162) = 1;
	//	*(DWORD*)((int)GetModuleHandle("client.dll") + 0x3B0C9C) = 2;

	}//quando &1 faz apenas uma vez

   
	if (itens[2].on_off &1) {
		//*(BYTE*)(0x969170) = 1;

		//*(DWORD*)((int)GetModuleHandleA("client.dll") + 0x3B0C9C) = 2;
		esp();
	}
	if (itens[3].on_off) {

		//*(BYTE*)(0x96916D + value) =  10000000;
		//*(DWORD*)(((int)GetModuleHandle("server.dll") + 0x30056365C) + 0x4B4) = 80;


	}

}
