#include <stdio.h>  // Necessário para o printf
#include <unistd.h> // Necessário para o sbrk no Linux

struct bloco_meta {
	size_t tamanho;
	int livre;
	struct bloco_meta* proximo;
};

struct bloco_meta* inicio_da_lista = NULL;
struct bloco_meta* ultimo_bloco = NULL;

struct bloco_meta* encontrar_bloco_livre(size_t quantidade) {
	struct bloco_meta* atual = inicio_da_lista;
	
	while (atual != NULL) {
		if (atual -> livre == 1 && atual -> tamanho >= quantidade) {
			return atual;
		}
		atual = atual -> proximo;
	}
	return NULL;
}

void* alocar_espaco(size_t quantidade) {
	struct bloco_meta* bloco = encontrar_bloco_livre(quantidade);
	
	if (bloco != NULL) {
		bloco -> livre = 0;
		printf("\n--- BLOCO RECICLADO ---");
		
	} else {
		void* novo_terreno = sbrk(sizeof(struct bloco_meta) + quantidade);
		bloco = (struct bloco_meta*)novo_terreno;
		
		bloco -> tamanho = quantidade;
		bloco -> livre = 0;
		bloco -> proximo = NULL;
		
		printf("\n--- NOVO BLOCO CRIADO ---\n");
		
		if (inicio_da_lista == NULL) {
			inicio_da_lista = bloco;
		} else {
			ultimo_bloco -> proximo = bloco;
			printf("O bloco anterior na fila aponta para: %p\n", (void*)ultimo_bloco -> proximo);
		}

		ultimo_bloco = bloco;
	}
	void* chave_do_cliente = (void*)(bloco + 1);
		
	printf("Coordenada do Bloco (struct): %p\n", (void*)bloco);
	printf("Tamanho Solicitado: %zu bytes\n", bloco -> tamanho);
	printf("Coordenada da Chave do Cliente: %p\n", (void*)chave_do_cliente);
	
	printf("-------------------------\n");
	return chave_do_cliente;
}

// Para testar
int main() {
    printf("Iniciando o sistema...\n");
    
    void* espaco1 = alocar_espaco(50);
    void* espaco2 = alocar_espaco(100);
    void* espaco3 = alocar_espaco(20);
    
    return 0;
}