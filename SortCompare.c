#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <stdbool.h>
#include <time.h>

#define POTENCIA 3
#define EXPONENTE_MENOR 8
#define EXPONENTE_MAIOR 8
#define QTD_EXECUCOES 50

void construirNomeArquivo(char *nome, char *ordenacao, int tipoPreenchimento, long long int tamanho) {
    char tipoPreenchimentoString[12];

    if (tipoPreenchimento == 1) {
      strcpy(tipoPreenchimentoString, "ALEATORIO");
    } else if (tipoPreenchimento == 2) {
      strcpy(tipoPreenchimentoString, "CRESCENTE");
    } else {
      strcpy(tipoPreenchimentoString, "DECRESCENTE");
    }
    sprintf(nome, "%s_%s_%lld", ordenacao, tipoPreenchimentoString, tamanho);
}

void preencheVetor(int* vetor, long long int tamanho, int tipoPreenchimento) {
  srand(time(NULL));

  if (tipoPreenchimento == 1) {
    // Preencher o vetor com números aleatórios
    for (long long int i = 0; i < tamanho; i++) {
      vetor[i] = rand();
    }
  } else if (tipoPreenchimento == 3) {
    // Preencher o vetor com números decrescentes
    for (long long int i = 0; i < tamanho; i++) {
        vetor[i] = tamanho - i - 1;
    }    
  }
}

void printaVetor(int* arr, int n) {
    puts("Ordenacao executada, vetor:\n");
    long long int i;
    
    for (i = 0; i < 20; i++) {
        printf("%d ", arr[i]);
    }
    printf(" ... ");
    for (i = (n / 2) - 10; i < (n / 2) + 10; i++) {
        printf("%d ", arr[i]);
    }
    printf(" ... ");    
    for (int i = n - 20; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}

void ordenacaoEGravacao(char *nomeOrdenacao, void (*funcaoOrdenacao)(int *, long long int), int tipoPreenchimento, long long int tamanho, int* vetor) {
    char nomeArquivo[35];
    construirNomeArquivo(nomeArquivo, nomeOrdenacao, tipoPreenchimento, tamanho);    

    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
      printf("Erro ao criar o arquivo: %s\n", nomeArquivo);
      exit(1);
    }

    long long int comparacoes = 0, mediaComparacoes = 0;
    long long int trocas = 0, mediaTrocas = 0;
    double tempoGasto = 0, mediaTempo = 0;
    int i;

    for(i = 0; i < QTD_EXECUCOES; i++) {           
      preencheVetor(vetor, tamanho, tipoPreenchimento);      

      struct timeval inicio, fim;        
      gettimeofday(&inicio, NULL);
      funcaoOrdenacao(vetor, tamanho);
      gettimeofday(&fim, NULL);
      
      tempoGasto = (fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) / 1000000.0;
      fprintf(arquivo, "%lld;%lld;%lf\n", comparacoes, trocas, tempoGasto);

      printaVetor(vetor, tamanho);

      mediaTrocas += trocas;
      mediaComparacoes += comparacoes;
      mediaTempo += mediaTempo;
    }
    mediaTrocas /= QTD_EXECUCOES;
    mediaComparacoes /= QTD_EXECUCOES;
    mediaTempo /= QTD_EXECUCOES;

    fprintf(arquivo, "Médias finais:\n");
    fprintf(arquivo, "%lld;%lld;%lf\n", comparacoes, trocas, tempoGasto);
    fclose(arquivo);
}

// ---INSERTION SORT---
void insertionSort (int *arr, long long int n) {
  long long int i, j;
  int chave;
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

// ---SELECTION SORT---
void selectionSort(int *arr, long long int n) {
  long long int i, j, minIndex;
  int aux;
  
  for (i = 0; i < n - 1; i++) {
    minIndex = i;
    for (j = i + 1; j < n; j++) {
      if (arr[j] < arr[minIndex]) {
        minIndex = j;
      }
    }

    aux = arr[i];
    arr[i] = arr[minIndex];
    arr[minIndex] = aux;
  }
}

// ---MERGE SORT---
void merge(int *arr, long long int comeco, long long int meio, long long int fim) {
    long long int com1 = comeco, com2 = meio+1, comAux = 0, tam = fim-comeco+1;
    int *arrAux;
    arrAux = (int*)malloc(tam * sizeof(int));

    while(com1 <= meio && com2 <= fim){
        if(arr[com1] < arr[com2]) {
            arrAux[comAux] = arr[com1];
            com1++;
        } else {
            arrAux[comAux] = arr[com2];
            com2++;
        }
        comAux++;
    }

    while(com1 <= meio){  
        arrAux[comAux] = arr[com1];
        comAux++;
        com1++;
    }

    while(com2 <= fim) {   
        arrAux[comAux] = arr[com2];
        comAux++;
        com2++;
    }

    for(comAux = comeco; comAux <= fim; comAux++){  
        arr[comAux] = arrAux[comAux-comeco];
    }
    
    free(arrAux);
}

void mergeSortAux(int *arr, long long int comeco, long long int fim){
  if (comeco < fim) {
    long long int meio = (fim+comeco)/2;

    mergeSortAux(arr, comeco, meio);
    mergeSortAux(arr, meio+1, fim);
    merge(arr, comeco, meio, fim);
  }
}

void mergeSort(int *arr, long long int n){
  mergeSortAux(arr, 0, n-1);
}

// ---HEAP SORT---
void heap(int *arr, long long int x, long long int i) {
  long long int maior = i;
  long long int esq = (2 * i) + 1;
  long long int dir = (2 * i) + 2;

  if (esq < x && arr[esq] > arr[maior]) {
    maior = esq;
  }
  if (dir < x && arr[dir] > arr[maior]) {
    maior = dir;
  }
  if (maior != i) {
    int valorTemp = arr[i];
    arr[i] = arr[maior];
    arr[maior] = valorTemp;
    heap(arr, x, maior);
  }
}

void heapSort(int *arr, long long int n) {
  long long int i, j;
  for (i = n / 2 - 1; i >= 0; i--) {
    heap(arr, n, i);
  }
  for (j = n - 1; j > 0; j--) {
    int valorTemp = arr[0];
    arr[0] = arr[j];
    arr[j] = valorTemp;

    heap(arr, j, 0);
  }
}

// ---QUICK SORT---
long long int particionaQS(int *arr, long long int menor, long long int maior){
  int pivo = arr[maior];
  long long int aux = menor - 1, i;
  for(i = menor; i <= maior - 1; i++){
    if(arr[i] < pivo){
      aux++;
      int valorTemp = arr[aux];
      arr[aux] = arr[i];
      arr[i] = valorTemp;
    }
  }
  int valorTemp = arr[aux + 1];
  arr[aux + 1] = arr[maior];
  arr[maior] = valorTemp;
  return (aux + 1);
}

void quickSortAux (int *arr, long long int menor, long long int maior) {
  if(menor < maior){
    long long int pivo = particionaQS(arr, menor, maior);
    quickSortAux(arr, menor, pivo-1);
    quickSortAux(arr, pivo+1, maior);
  }
}

void quickSort (int *arr, long long int n) {
  quickSortAux(arr, 0, n-1);
}

void ordenarVetor (int *vetor, int tipoPreenchimento, int tipoOrdenacao, long long int tamanho) {
  switch(tipoOrdenacao) {
    case 1:
      ordenacaoEGravacao("INSERTION", insertionSort, tipoPreenchimento, tamanho, vetor);
      break;
    case 2:
      ordenacaoEGravacao("SELECTION", selectionSort, tipoPreenchimento, tamanho, vetor);
      break;
    case 3:
      ordenacaoEGravacao("MERGE", mergeSort, tipoPreenchimento, tamanho, vetor);
      break;
    case 4:
      ordenacaoEGravacao("HEAP", heapSort, tipoPreenchimento, tamanho, vetor);      
      break;
    case 5:
      ordenacaoEGravacao("QUICK", quickSort, tipoPreenchimento, tamanho, vetor);
      break;
    default:
      printf("Opcao invalida");
  }
}

int main () {
  while(true) {  
    int tipoPreenchimento = 0; 
    int tipoOrdenacao = 0; 
    
    while(tipoPreenchimento < 1 || tipoPreenchimento > 3) {
      puts("Selecione a forma o vetor estará preenchido:");
      puts("1. Aleatorio");
      puts("2. Crescente");
      puts("3. Decrescente");
      scanf("%d", &tipoPreenchimento);
      
      if(tipoPreenchimento < 1 || tipoPreenchimento > 3) {
          puts("Escolha uma opção válida!");
      }
    }

    while(tipoOrdenacao < 1 || tipoOrdenacao > 5) {
      puts("\nSelecione qual tipo de ordenação será usado:");
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
