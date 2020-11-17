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
   Funcion: gamestart
   Argumentos: (int) arr[][]. Arreglo de enteros.
               (int) size. La cantidad de elementos en arr.
   Objetivo: Iniciar el juego y reaccionar a los inputs del jugador
   Retorno: void
*/
void gamestart(int arr[][MAX], int size) {
   int key, moves = 0, x = size-1, y = size-1;
   int lastx = x, lasty = y;

   long starttime = time(NULL), finishtime;

   clrscr(); // Limpieza de la pantalla
   _setcursortype(0);
   do {
      cuadroOut(arr, size);

      finishtime = time(NULL);
      timeOut(starttime, finishtime, XOUT+(size*INBW)+2, YOUT);

      gotoxy(XOUT+(size*INBW)+2, YOUT+2);
      printf("Movimientos: %d", moves);

      if (checkOrden(arr, size)) {
         gotoxy(XOUT, YOUT+size+1);
         printf("FELICIDADES!! Ha ordenado el cuadro.");
         gotoxy(XOUT, YOUT+size+2);
         printf("Presione cualquier tecla para continuar.");

         key = getch();
         key = ESC;

      } else {

         do {
            key = getch();
         } while(key != UP && key != DOWN && key != LEFT && key != RIGHT && key != ESC);

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

         arr[lasty][lastx] = arr[y][x];
         arr[y][x] = 0;

         lastx = x;
         lasty = y;

      }

   } while(key == ESC ? confirm() : 1);
   _setcursortype(20);
}

/*
   Funcion: confirm
   Argumentos: None
   Objetivo: Habrir el menu para preguntarle al usuario si quiere un nuevo cuadro o salir del juego
   Retorno: (int) 1 o 0 dependiendo si desea continuar juagando o finalizar el juego (Para salir o jugar con otro cuadro).
*/
int confirm() {
   clrscr();

   int key, selected = 0, stay = 0;

   // Habre el Menu
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

   // Confirmación de salida
   if (selected) {
      clrscr();

      do {
         gotoxy(XOUT, YOUT);
         printf("Seguro que desea salir del juego?");

         if (!stay) {

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
            stay = 0;
         }

         if (key == RIGHT) {
            stay = 1;
         }

         colordefault();

      } while(key != ENTER);

      return !stay;
   }

   // Nuevo juego
   clrscr();
   main();
   return 0;
}

/*
   Funcion: timeOut
   Argumentos: (long) start. El tiempo de inicio
               (long) finish. El timepo final o hasta el momento
               (int) x. Localización de salida del tiempo en x
               (int) y. Localizacion de salida del tiempo en y
   Objetivo: Determinar cuanto tiempo ha transcurrido y imprimirlo en x,y
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
   Funcion: cuadroOut
   Argumentos: (int) arr[][]. Arreglo de enteros.
               (int) size. La cantidad de elementos en arr[].
   Objetivo: Imprimir el cuadro en la consola
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
   Argumentos: (int) arr[][MAX]. Arreglo de enteros.
               (int) size. La cantidad de elementos en arr[].
   Objetivo: Determinar si arr esta ordenado o no.
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
   Funcion: randrange
   Argumentos: (int) a. Limite menor
               (int) b. Limite mayor
   Objetivo: Encontrar un nuemero aleatorio entre los limites
   Retorno: (int) un numero aleatorio entre los limites
*/
int randrange(int a, int b) {
   return rand() % ( b - a + 1 ) + a;
}

/*
   Funcion: setcolor
   Argumentos: (int) ct. El color del texto.
               (int) cf. El color del fondo.
   Objetivo: Cambiar los colores al imprimir
   Retorno: void
*/
void setcolor(int ct,int cf) {
   textbackground(cf);
   textcolor(ct);
}

/*
   Funcion: colordefault
   Argumentos: None
   Objetivo: Cambiar los colores a los default
   Retorno: void
*/
void colordefault() {
   setcolor(LIGHTGRAY,BLACK);
}
