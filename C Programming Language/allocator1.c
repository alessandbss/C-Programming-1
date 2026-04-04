char galpao[10000];
int marcador_global = 0;

void* alocar_espaco(int quantidade) {
	int marcador_temp = marcador_global;
		
	if (marcador_temp + quantidade + sizeof(int) > 10000) {
		return NULL;
	} else {
		marcador_global += quantidade + sizeof(int);
		
		void* piso_atual = galpao + marcador_temp;
		int* esconderijo = piso_atual;
		esconderijo[0] = quantidade;
		
		void* piso_alocado = esconderijo + 1;
		return piso_alocado;	
	}
}

void limpar_galpao() {
	marcador_global = 0;
}

void* meu_terreno = alocar_espaco(150);
char* texto = meu_terreno;