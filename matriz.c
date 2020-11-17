#include <stdio.h>
#include <stdlib.h>
// #include <conio.c>

#define MAX 15
#define MIN 3

#define XOUT 1
#define YOUT 1
#define INBW 3

// #define CB BLUE
// #define CF LIGHTGRAY
//
// #define CBA LIGHTBLUE
// #define CFA DARKGRAY


int checkOrden(int[], int);
// void cuadroOut(int [], int, int);
// void setcolor(int, int);
// void colordefault();

int main() {
   srand(time(NULL));
   
   int size;

   do {
      printf("Ingrese el tama%co deseado para el cuadro. (%d-%d)\n", 164, MIN, MAX);
      scanf("%d", &size);

      if (size < MIN || size > MAX) {
         printf("El tama%co debe encontrarse entre %d y %d.\n", 164, MIN, MAX);
      }

   } while(size < MIN || size > MAX);

   int nums[size][size];

   // lim = (size*size)-1;

   // for (int i = 0; i < lim; i++) {
   //    do {
   //       n = rand() % lim;
   //    } while(selected[n]);
   //
   //    nums[i] = n+1;
   //    selected[n] = 1;
   // }

   // cuadroOut(nums, lim, size);

   // for (int i = 0; i < lim; i++) {
   //    if (!(i % size)) {
   //       printf("\n");
   //    }
   //    printf("%3d ", nums[i]);
   // }


   // int arr1[9] = {1,2,3,4,5,6,7,8,9};
   // int arr2[9] = {0,2,3,4,5,6,7,8,9};
   // int arr3[9] = {1,2,4,7,5,6,3,8,9};
   // int arr4[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
   //
   // printf("1: %d\n", checkOrden(arr1, 9));
   // printf("0: %d\n", checkOrden(arr2, 9));
   // printf("0: %d\n", checkOrden(arr3, 9));
   // printf("1: %d\n", checkOrden(arr4, 12));

   return 0;
}

// void cuadroOut(int arr[], int n, int size) {
//    clrscr();
//
//    for (int i = 0; i < n; i++) {
//       if (!(i % size)) {
//          printf("\n");
//       }
//       if (i % 2) {
//          setcolor(CB,CF);
//       } else {
//          setcolor(CBA, CFA);
//       }
//       printf("%3d ", arr[i]);
//    }
//    colordefault();
// }

/*
   Funcion: checkOrden
   Argumentos: (int) arr[]. Arreglo de enteros.
               (int) n. La cantidad de elementos en arr[].
   Objetivo: Determinar so arr[] esta ordenado o no.
   Retorno: (int) 1 si el arreglo esta ordenado, 0 si no lo esta.
*/
int checkOrden(int arr[], int n) {
   int last = arr[0];
   for (int i = 1; i < n; i++) {
      if (arr[i] != last+1) {
         return 0;
      }
      last = arr[i];
   }
   return 1;
}

int randrange(int a,int b) {
   return rand() % ( b - a + 1 ) + a;
}

/*
   Funcion: checkOrden
   Argumentos: (int) arr[]. Arreglo de enteros.
               (int) n. La cantidad de elementos en arr[].
   Objetivo: Determinar so arr[] esta ordenado o no.
   Retorno: (int) 1 si el arreglo esta ordenado, 0 si no lo esta.
*/
// void setcolor(int ct,int cf) {
//    textbackground(cf);
//    textcolor(ct);
// }

/*
   Funcion: checkOrden
   Argumentos: (int) arr[]. Arreglo de enteros.
               (int) n. La cantidad de elementos en arr[].
   Objetivo: Determinar so arr[] esta ordenado o no.
   Retorno: (int) 1 si el arreglo esta ordenado, 0 si no lo esta.
*/
// void colordefault() {
//    setcolor(LIGHTGRAY,BLACK);
// }
