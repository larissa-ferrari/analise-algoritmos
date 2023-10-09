#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <stdbool.h>
#include <time.h>
#include "utils/sorts.c"

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
   
    int expoenteAtual = EXPONENTE_MENOR;
    while(expoenteAtual <= EXPONENTE_MAIOR) {
      long long int tamanho = pow(POTENCIA, expoenteAtual);
    
      int *vetor = (int *)malloc(tamanho * sizeof(int));
      for (int i = 0; i < tamanho; i++) {
        vetor[i] = i;
      }
      ordenarVetor(vetor, tipoPreenchimento, tipoOrdenacao, tamanho);
      expoenteAtual++;
      free(vetor);
    }   
  }
}
