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
#define SFONT BLACK

#define ESC 27
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ENTER 13



int checkOrden(int[][MAX], int);
void populate(int[][MAX], int);
int randrange(int, int);
int inArr(int[][MAX], int, int);
void cuadroOut(int [][MAX], int);
void setcolor(int, int);
void colordefault();
void gamestart(int[][MAX], int);
void timeOut(long, long, int, int);
int confirm();

int ordenarcuadro(int [][MAX], int);

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

int ordenarcuadro(int cuadro[][MAX],int dim)
{
   int indfil, indcol, orden = 1;

   for ( indfil = 0; indfil < dim; indfil ++ )
      for (indcol = 0; indcol < dim; indcol ++ )
      {
         cuadro[indfil][indcol] = orden++;
      }

   cuadro[dim-1][dim-1] = 0;

   return 1;
}

/*
   Funcion: populate
   Argumentos: (int) arr[][]. Arreglo de enteros.
               (int) size. La cantidad de elementos en arr[].
   Objetivo: Popular el arreglo con numeros aleatorios del 1 a su limite
   Retorno: void
*/
void gamestart(int arr[][MAX], int size) {
   int key, moves = 0, x = size-1, y = size-1;
   int lastx = x, lasty = y;

   long starttime = time(NULL), finishtime;

   clrscr();
   _setcursortype(0);
   do {
      cuadroOut(arr, size);

      finishtime = time(NULL);
      timeOut(starttime, finishtime, XOUT+(size*INBW)+2, YOUT);

      gotoxy(XOUT+(size*INBW)+2, YOUT+2);
      printf("Movimientos: %d", moves);

      if (checkOrden(arr, size)) {
         gotoxy(XOUT, YOUT+size+2);
         printf("FELICIDADES!! Ha ordenado el cuadro.");
         gotoxy(XOUT, YOUT+size+3);
         printf("Presione cualquier tecla para continuar.");
         
         key = getch();
         key = ESC;

      } else {

         do {
            key = getch();
         } while(key != UP && key != DOWN && key != LEFT && key != RIGHT && key != ESC && key != 'O');

         if (key == UP) {
            if (!(y-1 < 0)) {
               y--;
               moves++;
            }
         }

         if (key == DOWN) {
            if (!(y+1 > size-1)) {
               y++;
               moves++;
            }
         }

         if (key == LEFT) {
            if (!(x-1 < 0)) {
               x--;
               moves++;
            }
         }

         if (key == RIGHT) {
            if (!(x+1 > size-1)) {
               x++;
               moves++;
            }
         }

         if (key == 'O') {
            ordenarcuadro(arr, size);
         }

         arr[lasty][lastx] = arr[y][x];
         arr[y][x] = 0;

         lastx = x;
         lasty = y;

      }

   } while(key == ESC ? confirm() : 1);
   _setcursortype(20);
}

/*
   Funcion: populate
   Argumentos: (int) arr[][]. Arreglo de enteros.
               (int) size. La cantidad de elementos en arr[].
   Objetivo: Popular el arreglo con numeros aleatorios del 1 a su limite
   Retorno: void
*/
int confirm() {
   clrscr();

   int key, selected = 0, salir = 0;
   do {
      gotoxy(XOUT,YOUT);
      printf("Menu");

      if (!selected) {
         setcolor(SFONT, SELECT);
         gotoxy(XOUT,YOUT+2);
         printf("Nuevo cuadro");

         colordefault();
         gotoxy(XOUT+14,YOUT+2);
         printf("Salir");

      } else {

         colordefault();
         gotoxy(XOUT,YOUT+2);
         printf("Nuevo cuadro");

         setcolor(SFONT, SELECT);
         gotoxy(XOUT+14,YOUT+2);
         printf("Salir");
      }

      key = getch();

      if (key == LEFT) {
         selected = 0;
      }

      if (key == RIGHT) {
         selected = 1;
      }

      colordefault();

   } while(key != ENTER);

   if (selected) {
      clrscr();

      do {
         gotoxy(XOUT, YOUT);
         printf("Seguro que desea salir del juego?");

         if (salir) {
            setcolor(SFONT, SELECT);
            gotoxy(XOUT, YOUT+2);
            printf("NO");

            colordefault();
            gotoxy(XOUT+4, YOUT+2);
            printf("SI");

         } else {

            colordefault();
            gotoxy(XOUT, YOUT+2);
            printf("NO");

            setcolor(SFONT, SELECT);
            gotoxy(XOUT+4, YOUT+2);
            printf("SI");
         }

         key = getch();

         if (key == LEFT) {
            salir = 1;
         }

         if (key == RIGHT) {
            salir = 0;
         }

         colordefault();

      } while(key != ENTER);

      return salir;
   }

   clrscr();
   main();
   return 0;
}

/*
   Funcion: populate
   Argumentos: (int) arr[][]. Arreglo de enteros.
               (int) size. La cantidad de elementos en arr[].
   Objetivo: Popular el arreglo con numeros aleatorios del 1 a su limite
   Retorno: void
*/
void timeOut(long start, long finish, int x, int y) {
   int hours = 0, mins = 0;
   int secs = finish - start;

   while (secs >= 60) {
      secs -= 60;
      mins += 1;
   }

   while (mins >= 60) {
      mins -= 60;
      hours += 1;
   }

   gotoxy(x,y);
   printf("Tiempo: %02d:%02d:%02d", hours, mins, secs);
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
int checkOrden(int arr[][MAX], int size) {
   int last = arr[0][0];
   for (int i=0; i < size; i++) {
      for (int e=0; e < size; e++) {
         if (!(i == size-1 && e == size-1 )) {
            if (last > arr[i][e]) {
               return 0;
            }
         }
         last = arr[i][e];
      }
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
