#include <stdio.h>
#include <unistd.h>

int main (void) {
	// Encontrar o topo do heap
	void *topo_do_heap = sbrk(0);
	printf("O endereço atual do topo do heap é: %p \n", topo_do_heap);
	
	// Aumentar o heap e printar a diferença
	void *antes = sbrk(0);
	sbrk(1024); // Aumenta o heap em 1KB
	void *depois = sbrk(0);
	
	printf("Início: %p \n", antes);
	printf("Depois: %p \n", depois);
	printf("O heap cresceu em %ld bytes \n", (long)depois - (long)antes);
	
	return 0;
}