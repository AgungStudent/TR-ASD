#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/* 
 NAMA KELOMPOK GOLD: 
 1. Agung Prasetyo Nugroho (672021077)
 2. Gianina Dea Aneria (672021210)
 3. Kirey Challom Magdalena bee (672021216)
 */

typedef struct Menu {
  int diskon, harga;
  char kode[5], kategori[15], name[36];
} menu_t;

void gotoxy(int x, int y);

menu_t *head = NULL, *curr = NULL;

int main() {
	// contoh animasi
  for (int i = 0; i < 20; i++) {
    gotoxy(2 + i, 2);
    printf("-");
    Sleep(30);
  }
  for (int i = 0; i < 5; i++) {
    gotoxy(22, 3 + i);
    printf("|");
    Sleep(30);
  }

  gotoxy(50, 10);
  printf("Hello World");
	 
	// Bukak otomatis
	system("notepad bukti_pembayaran.txt");
  getch();
}
void gotoxy(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}