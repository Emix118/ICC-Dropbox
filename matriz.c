#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.c>

#define MAX 15
#define MIN 3

#define XOUT 2
#define YOUT 2
#define INBW 4

#define CB BLUE
#define CLG LIGHTGRAY

#define SELECT YELLOW

#define ESC 27
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75



int checkOrden(int[], int);
void populate(int[][MAX], int);
int randrange(int, int);
int inArr(int[][MAX], int, int);
void cuadroOut(int [][MAX], int);
void setcolor(int, int);
void colordefault();
void gamestart(int[][MAX], int);

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

   int nums[size][MAX];
   nums[size-1][size-1] = 0;

   populate(nums, size);

   gamestart(nums, size);

   return 0;
}

/*
   Funcion: populate
   Argumentos: (int) arr[][]. Arreglo de enteros.
               (int) size. La cantidad de elementos en arr[].
   Objetivo: Popular el arreglo con numeros aleatorios del 1 a su limite
   Retorno: void
*/
void gamestart(int arr[][MAX], int size) {
   int key, x = size-1, y = size-1;
   int lastx = x, lasty = y;

   clrscr();
   do {
      cuadroOut(arr, size);

      key = getch();

      if (key == UP) {
         y--;
      }

      if (key == DOWN) {
         y++;
      }

      if (key == LEFT) {
         x--;
      }

      if (key == RIGHT) {
         x++;
      }

      arr[lasty][lastx] = arr[y][x];
      arr[y][x] = 0;

      lastx = x;
      lasty = y;

   } while(key != ESC);
}

/*
   Funcion: populate
   Argumentos: (int) arr[][]. Arreglo de enteros.
               (int) size. La cantidad de elementos en arr[].
   Objetivo: Popular el arreglo con numeros aleatorios del 1 a su limite
   Retorno: void
*/
void cuadroOut(int arr[][MAX], int size) {
   int y = YOUT;
   clrscr();

   for (int i=0; i < size; i++) {
      for (int e=0; e < size; e++) {
         if (!e) {
            gotoxy(XOUT, y);
         } else {
            gotoxy(XOUT+(e*INBW), y);
         }

         if (arr[i][e]) {
            setcolor(CB, CLG);
         } else {
            setcolor(SELECT, SELECT);
         }

         printf("%3d ", arr[i][e]);
      }
      y++;
   }
   colordefault();
}

/*
   Funcion: populate
   Argumentos: (int) arr[][]. Arreglo de enteros.
               (int) size. La cantidad de elementos en arr[].
   Objetivo: Popular el arreglo con numeros aleatorios del 1 a su limite
   Retorno: void
*/
void populate(int arr[][MAX], int size) {
   int n;

   for (int i=0; i < size; i++) {
      for (int e=0; e < size; e++) {
         if (!(i == size-1 && e == size-1 )) {
            do {
               n = randrange(1, (size*size)-1);
            } while(inArr(arr, size, n));
            arr[i][e] = n;
         }
      }
   }
}

/*
   Funcion: inArr
   Argumentos: (int) arr[][]. Arreglo de enteros
               (int) size. Tamaño del arreglo
               (int) n. numero a buscar en arr
   Objetivo: Determinar si un numero esta en un arreglo
   Retorno: 1 o 0 dependiendo si el numero esta en el arreglo o no
*/
int inArr(int arr[][MAX], int size, int n) {
   for (int i=0; i < size; i++) {
      for (int e=0; e < size; e++) {
         if (arr[i][e] == n) {
            return 1;
         }
      }
   }
   return 0;
}

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

/*
   Funcion: checkOrden
   Argumentos: (int) arr[]. Arreglo de enteros.
               (int) n. La cantidad de elementos en arr[].
   Objetivo: Determinar so arr[] esta ordenado o no.
   Retorno: (int) 1 si el arreglo esta ordenado, 0 si no lo esta.
*/
int randrange(int a, int b) {
   return rand() % ( b - a + 1 ) + a;
}

/*
   Funcion: checkOrden
   Argumentos: (int) arr[]. Arreglo de enteros.
               (int) n. La cantidad de elementos en arr[].
   Objetivo: Determinar so arr[] esta ordenado o no.
   Retorno: (int) 1 si el arreglo esta ordenado, 0 si no lo esta.
*/
void setcolor(int ct,int cf) {
   textbackground(cf);
   textcolor(ct);
}

/*
   Funcion: checkOrden
   Argumentos: (int) arr[]. Arreglo de enteros.
               (int) n. La cantidad de elementos en arr[].
   Objetivo: Determinar so arr[] esta ordenado o no.
   Retorno: (int) 1 si el arreglo esta ordenado, 0 si no lo esta.
*/
void colordefault() {
   setcolor(LIGHTGRAY,BLACK);
}
