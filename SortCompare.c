#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <stdbool.h>
#include <time.h>

#define POTENCIA 3
#define EXPONENTE_MENOR 8
#define EXPONENTE_MAIOR 17
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
  if (tipoPreenchimento == 1) {
    // Preencher o vetor com números aleatórios
    for (long long int i = 0; i < tamanho; i++) {
      vetor[i] = rand() % tamanho;
    }
  } else if (tipoPreenchimento == 3) {
    // Preencher o vetor com números decrescentes
    for (long long int i = 0; i < tamanho; i++) {
        vetor[i] = tamanho - i - 1;
    }    
  }
}

void printaVetor(int* arr, int n) {
    long long int i;
    
    for (i = 0; i < 6; i++) {
        printf("%d ", arr[i]);
    }
    printf(" ... ");
    for (i = (n / 2) - 3; i < (n / 2) + 3; i++) {
        printf("%d ", arr[i]);
    }
    printf(" ... ");    
    for (int i = n - 6; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void ordenacaoEGravacao(char *nomeOrdenacao, void (*funcaoOrdenacao)(int *, long long int, long long int *, long long int *), int tipoPreenchimento, long long int tamanho, int* vetor) {
    FILE *arquivo;
    char nomeArquivo[35];
    construirNomeArquivo(nomeArquivo, nomeOrdenacao, tipoPreenchimento, tamanho);        

    long long int comparacoes = 0, mediaComparacoes = 0;
    long long int trocas = 0, mediaTrocas = 0;
    double tempoGasto = 0, mediaTempo = 0;
    int i;

    for(i = 0; i < QTD_EXECUCOES; i++) {           
      trocas = 0;
      comparacoes = 0;
      preencheVetor(vetor, tamanho, tipoPreenchimento);      

      struct timeval inicio, fim; 
      
      // puts("\nVetor antes e depois:");     
      // printaVetor(vetor, tamanho);
      gettimeofday(&inicio, NULL);
      funcaoOrdenacao(vetor, tamanho, &trocas, &comparacoes);
      gettimeofday(&fim, NULL);
      // printaVetor(vetor, tamanho);
      
      tempoGasto = (fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) / 1000000.0;
      
      arquivo = fopen(nomeArquivo, "a");      
      fprintf(arquivo, "%lld;%lld;%lf\n", trocas, comparacoes, tempoGasto);
      fclose(arquivo);

      mediaTrocas += trocas;
      mediaComparacoes += comparacoes;
      mediaTempo += tempoGasto;
    }
    mediaTrocas /= QTD_EXECUCOES;
    mediaComparacoes /= QTD_EXECUCOES;
    mediaTempo /= QTD_EXECUCOES;

    arquivo = fopen(nomeArquivo, "a");    
    fprintf(arquivo, "Médias finais:\n");
    fprintf(arquivo, "%lld;%lld;%lf\n", mediaTrocas, mediaComparacoes, mediaTempo);
    fclose(arquivo);

    printf("Ordenação com %lld valores concluída.\n\n", tamanho);     
}

// ---INSERTION SORT---
void insertionSort (int *arr, long long int n, long long int *trocas, long long int *comparacoes) {
  long long int i, j;
  int chave;
  for (i = 1; i < n; i++){
    chave = arr[i];
    j = i - 1;

    while(j >= 0 && arr[j] > chave) {
      (*comparacoes)++;
      arr[j + 1] = arr[j];
      j = j - 1;
      (*trocas)++;
    }
    (*comparacoes)++;

    arr[j + 1] = chave;
  }
}

// ---SELECTION SORT---
void selectionSort(int *arr, long long int n, long long int *trocas, long long int *comparacoes) {
  long long int i, j, minIndex;
  int aux;
  
  for (i = 0; i < n - 1; i++) {
    minIndex = i;
    for (j = i + 1; j < n; j++) {
      (*comparacoes)++;
      if (arr[j] < arr[minIndex]) {
        minIndex = j;
      }
    }

    (*trocas)++;
    aux = arr[i];
    arr[i] = arr[minIndex];
    arr[minIndex] = aux;
  }
}

// ---MERGE SORT---
void merge(int *arr, long long int comeco, long long int meio, long long int fim, long long int *trocas, long long int *comparacoes) {
    long long int com1 = comeco, com2 = meio+1, comAux = 0, tam = fim-comeco+1;
    int *arrAux;
    arrAux = (int*)malloc(tam * sizeof(int));

    while(com1 <= meio && com2 <= fim){
        (*comparacoes)++;
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
        (*trocas)++;
    }    
    free(arrAux);
}

void mergeSortAux(int *arr, long long int comeco, long long int fim, long long int *trocas, long long int *comparacoes) {
  if (comeco < fim) {
    long long int meio = (fim+comeco)/2;

    mergeSortAux(arr, comeco, meio, trocas, comparacoes);
    mergeSortAux(arr, meio+1, fim, trocas, comparacoes);
    merge(arr, comeco, meio, fim, trocas, comparacoes);
  }
}

void mergeSort(int *arr, long long int n, long long int *trocas, long long int *comparacoes) {
  mergeSortAux(arr, 0, n-1, trocas, comparacoes);
}

// ---HEAP SORT---
void heap(int *arr, long long int x, long long int i, long long int *trocas, long long int *comparacoes) {
  long long int maior = i;
  long long int esq = (2 * i) + 1;
  long long int dir = (2 * i) + 2;

  if (esq < x && arr[esq] > arr[maior]) {
    maior = esq;
  }
  if (dir < x && arr[dir] > arr[maior]) {
    maior = dir;
  }
  (*comparacoes) += 2;
  if (maior != i) {
    (*trocas)++;
    int valorTemp = arr[i];
    arr[i] = arr[maior];
    arr[maior] = valorTemp;
    heap(arr, x, maior, trocas, comparacoes);
  }
}

void heapSort(int *arr, long long int n, long long int *trocas, long long int *comparacoes) {
  long long int i;
  for (i = n / 2 - 1; i >= 0; i--) {
    heap(arr, n, i, trocas, comparacoes);
  }
  for (i = n - 1; i > 0; i--) {
    (*trocas)++;
    int valorTemp = arr[0];
    arr[0] = arr[i];
    arr[i] = valorTemp;

    heap(arr, i, 0, trocas, comparacoes);
  }
}

// ---QUICK SORT---
long long int particionaQS(int *arr, long long int menor, long long int maior, long long int *trocas, long long int *comparacoes) {
  int pivo = arr[maior];
  long long int aux = menor - 1, i;
  for(i = menor; i <= maior - 1; i++){
    (*comparacoes)++;
    if(arr[i] < pivo){
      aux++;
      (*trocas)++;
      int valorTemp = arr[aux];
      arr[aux] = arr[i];
      arr[i] = valorTemp;
    }
  }
  (*trocas)++;
  int valorTemp = arr[aux + 1];
  arr[aux + 1] = arr[maior];
  arr[maior] = valorTemp;
  return (aux + 1);
}

void quickSortAux (int *arr, long long int menor, long long int maior, long long int *trocas, long long int *comparacoes) {
  if(menor < maior){
    long long int pivo = particionaQS(arr, menor, maior, trocas, comparacoes);
    quickSortAux(arr, menor, pivo-1, trocas, comparacoes);
    quickSortAux(arr, pivo+1, maior, trocas, comparacoes);
  }
}

void quickSort (int *arr, long long int n, long long int *trocas, long long int *comparacoes) {
  quickSortAux(arr, 0, n-1, trocas, comparacoes);
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
  srand(time(NULL));
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
   int m;
   for(m = 1; m < 4; m++) {
    int expoenteAtual = EXPONENTE_MENOR;
    while(expoenteAtual <= EXPONENTE_MAIOR) {
      long long int tamanho = pow(POTENCIA, expoenteAtual);
    
      int *vetor = (int *)malloc(tamanho * sizeof(int));
      for (int i = 0; i < tamanho; i++) {
        vetor[i] = i;
      }
      ordenarVetor(vetor, m, tipoOrdenacao, tamanho);
      expoenteAtual++;
      free(vetor);
    }
   }
  }
}
