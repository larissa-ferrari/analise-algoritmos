#include <stdio.h>
#include <stdlib.h>
#include <stdmath.h>
#define POTENCIA 3
#define EXPONENTE_MENOR 8
#define EXPONENTE_MAIOR 8

int ordenarVetor (int *vetor, int tipoPreenchimento, int tipoOrdenacao, long long int tamanho) {
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

void insertionSort (int *arr, int n) {
  int i, chave, j;
  for (i = 1; i < n; i++){
    chave = arr[i];
    j = i - 1;
  }
  while( j >= 0 && arr[j] > chave) {
    arr[j + 1] = arr[j];
    j = j - 1;
  }
  arr[j + 1] = chave;
}

int selectionSort () {


}

int mergeSort () {

}


// arruma o heap, mantendo os filhos menores que o pai;
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

// chama a função heap em si;
int heapSort (int *arr, int x) {
  for(int i = n/2 - 1; i >= 0; i--){
    heap(arr, n, i);
  }
  for(int j = n-1; j > 0 j--){
    int valorTemp = arr[j];
    arr[0] = arr[j];
    arr[j] = Valortemp;

    heap(arr, j, 0);
  }

}

// part
int particionaQS(int *arr, int menor, int maior){
  int pivo = arr[maior];
  int aux = menor - 1;
  for(int i = arr[menor]; i <= maior - 1; i++){
    if(arr[i] < pivo){
      aux++;
      int valorTemp = arr[aux];
      arr[aux] = arr[i];
      arr[i] = valorTemp;
    }
  }
  int valorTemp = arr[aux];
  arr[aux] = arr[i];
  arr[i] = valorTemp;
}
int quickSort (int *arr, int menor, int maior {

    
}

tor ( int tipoPreenchimento ) {

}

int main () {
  while(true) {  
    int tipoPreenchimento = 0; 
    int tipoOrdenacao = 0; 
    
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

    while(tipoOrdenacao < 1 || tipoOrdenacao > 5) {
      puts("De que maneira o vetor estará preenchido:");
      puts("1. Insertion Sort");
      puts("2. Selection Sort");
      puts("3. Merge Sort");
      puts("4. Heap Sort");
      puts("5. Quick Sort");
      scanf("%d", &tipoOrdenacao);
      
      if(tipoOrdenacao < 1 || tipoOrdenacao > 5) {
          puts("Escolha uma opção válida!");
      }
    }

    int expoenteAtual = EXPONENTE_MENOR;

    while(expoenteAtual <= EXPONENTE_MAIOR) {
      long long int tamanho = pow(POTENCIA, expoenteAtual);
    
      int *vetor = (int *)malloc(tamanho * sizeof(int));
      for (int i = 0; i < tamanho; i++) {
        vetor[i] = i;
      }
      ordenarVetor(vetor, tipoPreenchimento, tipoOrdenacao, tamanho);
      expoenteAtual++;
    }
  }
}
