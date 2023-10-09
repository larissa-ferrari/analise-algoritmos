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
