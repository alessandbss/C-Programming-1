char galpao[10000];
int marcador_global = 0;

int alocar_espaco(int quantidade) {
	var int marcador_temp = marcador_global;
	marcador_global += quantidade;
	
	if (marcador_temp + quantidade > 10000):
		return -1;
	else:
		return marcador_temp;	
}