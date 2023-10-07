#include <stdio.h>
#include <stdlib.h>
#include <stdmath.h>

int ordenarVetor ( int tipoOrdenacao ) {

  switch(tipoOrdenacao) {
    case 1:

      //  cria um arquivo com o nome do algoritmo, tipo do preenchimento e o tamanho do vetor

      // LEMBRETE, O NUMERO DE COMPARAÇÕES EH COLOCAR PARA SOMAR ANTES
      // REPITO, ANTES, DO IF/WHILE/SWITCH ACONTECER


      //for de 100 execuções
        // variavel para o numero de comparações (long long int) começa zerado
        // variavel para o numero de trocas (long long int) começa zerado
        // preenche o vetor
        // inicia o contador
        insertionSort();
        // finaliza o contador
        // salva o tempo de execução no arquivo + uma virgula ou ponto e virgula
        // salva o numero de comparações no arquivo
        // salva o numero de trocas no arquivo

      // calcula a media do tempo
      // salva a media no arquivo

      // calcula a media de comparações
      // salva a media no arquivo

      // calcula a media de trocas
      // salva a media no arquivo

      break;
    case 2:
      // incializa contador
      selectionSort();
      // finaliza contador
      break;
    case 3:
      // incializa contador
      mergeSort();
      // finaliza contador
      break;
    case 4:
      // incializa contador
      heapSort();
      // finaliza contador
      break;
    case 5:
      // incializa contador
      quickSort();
      // finaliza contador
      break;
    default:
      printf("Opcao invalida");
  }

}

int insertionSort () {
  
}

int selectionSort () {

}

int mergeSort () {

}
void heap(int *arr, int x, int i){

  int maior = i;
  int esq = (2*i)+1;
  int dir = (2*i)+1;

  if(esq < x && arr[esq] > arr[maior]){
    maior = esq;
  }
  if(dir < x && arr[dir] > arr[maior]){
    maior = dir;
  }
  if ( maior != i){
    int valorTemp = arr[i];
    arr[i] = arr[maior];
    arr[maior] = valorTemp;
    heapSort(arr, x, maior);
  }

}
int heapSort (int *arr, int x) {
  for(int i = n/2 - 1; i >= 0; i--){
    heap(arr, n, i);
  }
  for(int j = n-1; j > 0 j--){
    int valorTemp = arr[j];
    arr[0] = arr[j];
    arr[j] = temp;

    heap(arr, j, 0);
  }

}

int quickSort () {

}

int preencherVetor ( int tipoPreenchimento ) {

}

int main () {
  int POTENCIA = 3;
  int EXPONENTE_MENOR = 8;
  int EXPONENTE_MAIOR = 20;

  int tamanhoInicial = pow;
  int *vetor = (int *)malloc(tamanho * sizeof(int));

  for (int i = 0; i < tamanho; i++) {
      vetor[i] = i;
  }

  while(true) {  
    int tipoPreenchimento = 0; 
    
    while(tipoPreenchimento < 1 || tipoPreenchimento > 3) {
      puts("De que maneira o vetor estará preenchido:");
      puts("1. Aleatorio");
      puts("2. Crescente");
      puts("3. Decrescente");
      scanf("%d", &tipoPreenchimento);
      
      if(tipoPreenchimento < 1 || tipoPreenchimento > 3) {
          puts("Escolha uma opção válida!");
      }
    }

  }

  // 1 - Preencher vetor 
    // 1.1 - Aleatorio
    // 1.2 - Crescente
    // 1.3 - Decrescente

    // apos escolher qual o tipo de preenchimento, salva isso numa variavel (pode ser um enum ou so um int mesmo)

  // 2 - Ordenar Vetor
    // 2.1 - Insertion Sort
    // 2.2 - Selection Sort
    // 2.3 - Merge Sort
    // 2.4 - Heap Sort
    // 2.5 - Quick Sort

  // 3 - Mostrar Vetor

  // 4 - Mudar tamanho do vetor

}