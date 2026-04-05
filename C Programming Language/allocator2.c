
struct bloco_meta {
	size_t tamanho;
	int livre;
	struct bloco_meta* proximo;
}

struct bloco_meta* inicio_da_lista = NULL;
struct bloco_meta* ultimo_bloco = NULL;

void* alocar_espaco(size_t quantidade) {
	struct bloco_meta* bloco = encontrar_bloco_livre(quantidade); // Radar
	
	if (bloco != NULL) {
		bloco -> livre = 0;
		void* chave_do_cliente = (void*)(bloco + 1);
		return chave_do_cliente;
	}
	
	void* novo_terreno = sbrk(sizeof(struct bloco_meta) + quantidade);
	struct bloco_meta* novo_bloco = (struct bloco_meta*)novo_terreno;
	
	novo_bloco -> tamanho = quantidade;
	novo_bloco -> livre = 0;
	novo_bloco -> proximo = NULL;
	
	if (inicio_da_lista == NULL) {
		inicio_da_lista = novo_bloco;
	}
	else {
		ultimo_bloco -> proximo = novo_bloco;
	}
	
	ultimo_bloco = novo_bloco;
	
	void* chave_do_cliente = (void*)(novo_bloco + 1);
	return chave_do_cliente;
}

struct bloco_meta* encontrar_bloco_livre (size_t quantidade) {
	struct bloco_meta* atual = inicio_da_lista;
	
	while (atual != NULL) {
		if (atual -> livre == 1 && atual -> tamanho >= quantidade) {
			return atual;
		}
		atual = atual -> proximo;
	}
	return NULL;
}

