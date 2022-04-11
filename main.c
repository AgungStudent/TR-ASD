#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

/*
 NAMA KELOMPOK GOLD:
 1. Agung Prasetyo Nugroho (672021077)
 2. Gianina Dea Aneria (672021210)
 3. Kirey Challom Magdalena bee (672021216)
 */

typedef struct Menu {
  int diskon, harga, kode;
  char kategori[15], name[36];
  struct Menu *next;
} menu_t;

menu_t *head = NULL, *db_record;

const char KATEGORI[3][15] = {"Makanan", "Minuman", "Snack"};
const char SPACE[] = "                                            ";
int count_list;

// PROTOTYPE
// desaign
void gotoxy(int x, int y);
// login
void password_hash(char pass[]);
// BAGIAN CRUD
void menuCrud();
void createData();
void readData();
void updateData();
void deleteData();
void formCrud(menu_t *ptr);
void searchData();
// Database
void dbToLinked();
void updateDB();
// table
void line(int ascii1, int ascii2, int ascii3);
void tabel(menu_t *list);
// sorting
void sort(menu_t **head_sort, char sort_mode[], char field[]);

int main() {
  system("color 60 ");

  printf("\n\n\n\n\n\t\t\  Nungguin yaaa ...\n");
  printf("\n\t\t ");
  for (int loading = 0; loading <= 50; loading++) {
    printf("%c", 219);
    Sleep(80);
    if (loading == 50) {
      printf("\n\n\t\t\t\t\t\t Sabar sayang!");
      getch();
    }
  }

  // MENU UTAMA
  int choose;
  for (;;) {
    system("cls && color 6");
    Sleep(70);
    printf("\n\t\t\t   "
           "+========================================================+\n");
    Sleep(70);
    printf("\t\t\t   ||          MENU UTAMA RESTORAN 4 SEHAT 5 SEKARAT       "
           "||\n");
    Sleep(70);
    printf("\t\t\t   ||                      KELOMPOK GOLD                   "
           "||\n");
    Sleep(70);
    printf("\t\t\t   "
           "+========================================================+\n\n");
    Sleep(70);
    printf("%s 1. Pemesanan Menu\n%s 2. Menu Admin\n%s 3. Exit", SPACE, SPACE,
           SPACE);
    printf("\n\n%s Pilihan? ", SPACE);
    scanf("%d", &choose);

    if (choose == 1) {
      // TUGAS KIREY
    } else if (choose == 2) {
      break;
    } else if (choose == 3) {
      exit(0);
    } else {
      printf("%s Pilihan Salah", SPACE);
    }
    getch();
  }

  // login
  int error = 0;
  for (;;) {

    system("cls && color 80");
    int kolom = 60;
    int space = 30;

    for (int i = 0; i < kolom; i++) {

      // 4+i => dimulai dari kolom ke 4, 2 => artinya dimulai dari baris ke 2
      // Atas
      gotoxy(space + i, 2);
      printf("=");

      // Bawah
      gotoxy(kolom + space - i, 12);
      printf("=");
      Sleep(30);
    }
    for (int i = 0; i < 9; i++) {
      gotoxy(kolom + space, 3 + i);
      printf("|");
      gotoxy(space, 11 - i);
      printf("|");
      Sleep(30);
    }

    char login[] = "LOGIN";
    for (int i = 0; login[i] != '\0'; i++) {
      gotoxy((kolom + space) / 2 + 12 + i, 1);
      printf("%c", login[i]);
      Sleep(30);
    }
    char user[9] = "admin", pass[9] = "gold";
    char inputUsername[9], inputPassword[9];

    gotoxy(space + 4, 5);
    printf("Masukkan username : ");
    scanf("%s", &inputUsername);
    gotoxy(space + 4, 6);
    printf("Masukkan password : ");
    password_hash(inputPassword);
    // cek username and password
    if (strcmp(user, inputUsername) == 0 && strcmp(pass, inputPassword) == 0) {
      // printf("Login Berhasil!");
      // getch();
      menuCrud();
    } else {
      gotoxy(space + space + 7, 14);
      printf("ERROR!\n");
      gotoxy(space + space + 7, 15);
      printf("USERNAME DAN PASSWORD SALAH");
      getch();
      error++;
    }
    if (error >= 3) {
      gotoxy(space, 17);
      printf("MAAF ANDA MEMASUKKAN PASSWORD DAN USERNAME SALAH SEBANYAK 3x");
      getch();
      return 0;
    }
  }
}
void gotoxy(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void menuCrud() {
  int pilihan;
  while (1) {
    system("cls");
    system("color F1");
    Sleep(70);
    printf("                       "
           "*******************************************************************"
           "*********\n");
    gotoxy(45, 1);
    Sleep(70);
    printf("CREATE, READ, UPDATE, DELETE\n");
    gotoxy(53, 2);
    Sleep(70);
    printf("MENU RESTORAN\n");
    Sleep(70);
    printf("                       "
           "*******************************************************************"
           "*********\n\n");
    Sleep(70);
    printf("%sMenu 1. untuk tambah menu resotran\n", SPACE);
    Sleep(70);
    printf("%sMenu 2. untuk edit menu resotran\n", SPACE);
    Sleep(70);
    printf("%sMenu 3. untuk delete menu resotran\n", SPACE);
    Sleep(70);
    printf("%sMenu 4. untuk melihat menu resotran\n", SPACE);
    Sleep(70);
    printf("%sMenu 5. untuk search menu restoran\n", SPACE);
    Sleep(70);
    printf("%sMenu 6. untuk keluar \n\n", SPACE);
    Sleep(70);
    printf("%sPilihan: ", SPACE);
    fflush(stdin);
    scanf("%d", &pilihan);
    if (getchar() != '\n') {
      fflush(stdin);
      system("color F4");
      printf("%sPilihan salah!", SPACE);
      getch();
      continue;
    }

    dbToLinked();
    sort(&head, "asc", "nama");
    if (pilihan == 1) {
      system("cls");
      createData();
      updateDB();
    } else if (pilihan == 2) {
      system("cls");
      updateData();
      updateDB();
    } else if (pilihan == 3) {
      system("cls");
      deleteData();
      updateDB();
    } else if (pilihan == 4) {
      system("cls");
      readData();
    } else if (pilihan == 5) {
      system("cls");
      searchData();
    } else if (pilihan == 6) {
      free(head);
      return;
    } else {
      system("color F4");
      printf("%sPilihan salah!", SPACE);
    }

    getch();
  }
}
void createData() {
  menu_t *ptr, *temp;
  ptr = (menu_t *)malloc(sizeof(menu_t));
  printf("                       "
         "*********************************************************************"
         "*******\n");
  gotoxy(48, 1);
  printf("**CREATE MENU RESOTRAN**\n");
  printf("                       "
         "*********************************************************************"
         "*******\n\n");
  formCrud(ptr);
  srand(time(NULL));
  int kode = rand();
  ptr->kode = kode;
  ptr->next = NULL;
  // masukkan data ke linked list, pada data paling akhir
  if (head) {
    temp = head;
    while (temp->next)
      temp = temp->next;
    temp->next = ptr;
  } else {
    head = ptr;
  }
  system("color F2");
  printf("\n%sBerhasil memasukkan data!", SPACE);
}
void updateData() {
  menu_t *ptr, *temp;
  char name[36], kategori[15];
  int diskon, harga, search_kode, pilihan;
  ptr = (menu_t *)malloc(sizeof(menu_t));

  printf("                       "
         "*********************************************************************"
         "*******\n");
  gotoxy(48, 1);
  printf("**UPDATE MENU RESOTRAN**\n");
  printf("                       "
         "*********************************************************************"
         "*******\n\n");
  if (head == NULL) {
    system("color F4");
    printf("%s       Data masih kosong!", SPACE);
    return;
  }
  tabel(head);
  printf("\n\n%sMasukkan kode menu yang akan dirubah: ", SPACE);
  scanf("%d", &search_kode);

  temp = head;
  while (temp) {
    if (temp->kode == search_kode) {
      formCrud(temp);
      system("color F2");
      printf("%sBerhasil merubah data!", SPACE);
      // temp = ptr;
      return;
    }
    temp = temp->next;
  }
  system("color F4");
  printf("%sData tidak ditemukkan", SPACE);
}
void deleteData() {
  printf("                       "
         "*********************************************************************"
         "*******\n");
  gotoxy(48, 1);
  printf("**DELETE MENU RESOTRAN**\n");
  printf("                       "
         "*********************************************************************"
         "*******\n\n");
  if (head == NULL) {
    system("color F4");
    printf("%s       Data masih kosong!", SPACE);
    return;
  }
  menu_t *temp = head;
  int search_kode;
  tabel(head);
  printf("\n%sMasukkan kode yang ingin dihapus: ", SPACE);
  scanf("%d", &search_kode);
  int get_data = 0;
  while (temp) {
    if (temp->kode == search_kode)
      break;
    get_data++;
    temp = temp->next;
  }

  if (get_data == 0) {
    head = temp->next;
    free(temp);
    remove("db.txt");
    system("color F2");
    printf("%sData berhasil dihapus!", SPACE);
    return;
  }
  for (int i = 0; temp && i < get_data - 1; i++)
    temp = temp->next;

  if (temp == NULL || temp->next == NULL) {
    system("color F4");
    printf("%sData tidak ada!", SPACE);
  } else {
    menu_t *next = temp->next->next;
    free(temp->next);
    temp->next = next;
    system("color F2");
    printf("%sData berhasil dihapus!", SPACE);
  }
}
void readData() {
  int pilihan;
  printf("                       "
         "*********************************************************************"
         "*******\n");
  gotoxy(48, 1);
  printf("**SORTING MENU RESOTRAN**\n");
  printf("                       "
         "*********************************************************************"
         "*******\n\n");
  if (!head) {
    system("color F4");
    printf("%s       Data masih kosong", SPACE);
    return;
  }
  char mode_sort[5], field[7];
  printf("%sPilih metode sorting:\n", SPACE);
  printf("%s1. Ascending\n", SPACE);
  printf("%s2. Descending\n", SPACE);
  printf("%sPilihan: ", SPACE);
  scanf("%d", &pilihan);

  if (pilihan == 1)
    strcpy(mode_sort, "asc");
  else if (pilihan == 2)
    strcpy(mode_sort, "desc");
  else {
    system("color F4");
    printf("%sPilihan salah", SPACE);
    return;
  }

  printf("\n%sSorting bedasarkan: \n", SPACE);
  printf("%s1. Kode\n", SPACE);
  printf("%s2. Nama\n", SPACE);
  printf("%s3. Harga\n", SPACE);
  printf("%s4. Kategori\n", SPACE);
  printf("%s5. Diskon\n", SPACE);
  printf("%sPilihan: ", SPACE);
  scanf("%d", &pilihan);

  if (pilihan == 1)
    sort(&head, mode_sort, "kode");
  else if (pilihan == 2)
    sort(&head, mode_sort, "nama");
  else if (pilihan == 3)
    sort(&head, mode_sort, "harga");
  else if (pilihan == 4)
    sort(&head, mode_sort, "kategori");
  else if (pilihan == 5)
    sort(&head, mode_sort, "diskon");
  else {
    system("color F4");
    printf("%sPilihan salah", SPACE);
    return;
  }

  system("cls");
  printf("                       "
         "*********************************************************************"
         "*******\n");
  gotoxy(48, 1);
  printf("**READ MENU RESOTRAN**\n");
  printf("                       "
         "*********************************************************************"
         "*******\n\n");
  tabel(head);
}

void searchData() {
  printf("                       "
         "*********************************************************************"
         "*******\n");
  gotoxy(46, 1);
  printf("**SEARCH MENU RESOTRAN**\n");
  printf("                       "
         "*********************************************************************"
         "*******\n\n");
  if (!head) {
    system("color F4");
    printf("%s      data masih kosong!", SPACE);
    return;
  }
  menu_t *head_search = NULL, *ptr = head;
  char search[36];
  int found = 0;
  printf("%smasukkan (nama/kategori): ", SPACE);
  fflush(stdin);
  scanf("%35[^\n]", search);
  while (ptr) {
    if (strcmpi(ptr->name, search) == 0 ||
        strcmpi(ptr->kategori, search) == 0) {
      found = 1;
      db_record = (menu_t *)malloc(sizeof(menu_t));
      db_record = ptr;
      db_record->next = head_search;
      head_search = db_record;
    }
    ptr = ptr->next;
  }
  if (found)
    tabel(head_search);
  else {
    system("color F4");
    printf("\n%s  Data tidak ditemukkan!", SPACE);
  }
  free(head_search);
}

void formCrud(menu_t *ptr) {
  char name[36], kategori[15];
  int diskon, harga, pilihan;
  // name
  fflush(stdin);
  printf("%sMasukkan Nama menu: ", SPACE);
  scanf("%35[^\n]", &name);
// kategori
kategori:
  fflush(stdin);
  printf("\n%sOpsi Kategori:\n", SPACE);
  int size = sizeof(KATEGORI) / sizeof(KATEGORI[0]);
  for (int i = 0; i < size; i++) {
    printf("%s%d. %s\n", SPACE, i + 1, KATEGORI[i]);
  }
  printf("%sPilihan: ", SPACE);
  scanf("%d", &pilihan);
  if (pilihan > size || pilihan <= 0) {
    system("color F4");
    printf("%sKategori tidak ditemukkan!\n", SPACE);
    getch();
    system("color F1");
    goto kategori;
  }
  strcpy(kategori, KATEGORI[pilihan - 1]);
// diskon
diskon:
  fflush(stdin);
  printf("%sMasukkan diskon menu(0-100): ", SPACE);
  scanf("%d", &diskon);
  if (diskon > 100 || diskon < 0) {
    system("color F4");
    printf("%sDiskon tidak valid!\n", SPACE);
    getch();
    system("color F1");
    goto diskon;
  }
  // harga
  fflush(stdin);
  printf("%sMasukkan harga menu: ", SPACE);
  scanf("%d", &harga);

  // pindahkan data ke struct
  strcpy(ptr->name, name);
  strcpy(ptr->kategori, kategori);
  ptr->diskon = diskon;
  ptr->harga = harga;
}

void updateDB() {
  if (head == NULL) {
    return;
  }
  FILE *fp;
  fp = fopen("db_new.txt", "a");

  menu_t *ptr = head;

  while (ptr) {
    fwrite(ptr, sizeof(menu_t), 1, fp);
    ptr = ptr->next;
  }
  fclose(fp);
  remove("db.txt");
  rename("db_new.txt", "db.txt");
}

void dbToLinked() {
  head = NULL;
  FILE *read_file;
  if ((read_file = fopen("db.txt", "r")) == NULL) {
    return;
  }
  fseek(read_file, 0, SEEK_END);
  count_list = ftell(read_file) / sizeof(menu_t);
  fseek(read_file, 0, SEEK_SET);
  db_record = (menu_t *)malloc(sizeof(menu_t));
  while (fread(db_record, sizeof(menu_t), 1, read_file)) {
    db_record->next = head;
    head = db_record;
    db_record = (menu_t *)malloc(sizeof(menu_t));
  }
  fclose(read_file);
}

// cetak tabel data
void tabel(menu_t *list) {
  menu_t *curr = list;
  if (list = NULL) {
    system("color F4");
    printf("%s       Data masih kosong", SPACE);
    return;
  }
  printf("              ");
  line(201, 203, 187);
  printf("\n              %c %-7s%c %-34s%c %-14s%c %-10s%c %-14s %c\n", 186,
         "KODE", 186, "NAMA MENU", 186, "HARGA", 186, "DISKON(%)", 186,
         "KATEGORI", 186);

  while (curr) {
    printf("              ");
    line(204, 206, 185);
    printf("\n              %c %-7d%c %-34s%c Rp.%-11d%c %-9d %c %-14s %c\n",
           186, curr->kode, 186, curr->name, 186, curr->harga, 186,
           curr->diskon, 186, curr->kategori);
    curr = curr->next;
  }
  printf("              ");
  line(200, 202, 188);
}

void line(int ascii1, int ascii2, int ascii3) {
  printf("%c", ascii1);
  // kode
  for (int i = 0; i < 8; i++) {
    printf("%c", 205);
  }
  printf("%c", ascii2);
  // nama
  for (int i = 0; i < 35; i++) {
    printf("%c", 205);
  }
  printf("%c", ascii2);
  // harga
  for (int i = 0; i < 15; i++) {
    printf("%c", 205);
  }
  printf("%c", ascii2);
  // diskon
  for (int i = 0; i < 11; i++) {
    printf("%c", 205);
  }
  // Keterangan
  printf("%c", ascii2);
  for (int i = 0; i < 16; i++) {
    printf("%c", 205);
  }
  printf("%c", ascii3);
}
void sort(menu_t **head_sort, char sort_mode[], char field[]) {
  int do_swap, sorted, i, j;
  for (i = 0; i <= count_list; i++) {
    menu_t **h = head_sort;
    sorted = 1;

    for (j = 0; j < count_list - 1; j++) {
      menu_t *curr = *h, *next = curr->next;
      // tentukkan asc/desc
      if (strcmpi(sort_mode, "asc") == 0) {
        if (strcmpi(field, "kode") == 0)
          do_swap = curr->kode > next->kode;
        else if (strcmpi(field, "diskon") == 0)
          do_swap = curr->diskon > next->diskon;
        else if (strcmpi(field, "harga") == 0)
          do_swap = curr->harga > next->harga;
        else if (strcmpi(field, "nama") == 0)
          do_swap = strcmpi(curr->name, next->name) > 0;
        else if (strcmpi(field, "kategori") == 0)
          do_swap = strcmpi(curr->kategori, next->kategori) > 0;
        else
          do_swap = 0;
      } else {
        if (strcmpi(field, "kode") == 0)
          do_swap = curr->kode < next->kode;
        else if (strcmpi(field, "diskon") == 0)
          do_swap = curr->diskon < next->diskon;
        else if (strcmpi(field, "harga") == 0)
          do_swap = curr->harga < next->harga;
        else if (strcmpi(field, "nama") == 0)
          do_swap = strcmpi(curr->name, next->name) < 0;
        else if (strcmpi(field, "kategori") == 0)
          do_swap = strcmpi(curr->kategori, next->kategori) < 0;
        else
          do_swap = 0;
      }

      if (do_swap) {
        menu_t *temp = next->next;
        next->next = curr;
        curr->next = temp;
        *h = next;
        sorted = 0;
      }
      h = &(*h)->next;
    }
    if (sorted)
      break;
  }
}
void password_hash(char pass[]) {
  int key = 0, index = 0;
  do {
    key = getch();
    switch (key) {
    case 0:
      getch();
      break;
    case 224:
      getch();
      break;
    case 8:
      if (index > 0) {
        pass[index] = 0;
        index--;
        printf("\b \b");
      }
      break;
    default:
      if (key >= 32 && key <= 126) {
        pass[index] = key;
        index++;
        printf("*");
      }
    }
  } while (key != 13);
  pass[index] = '\0';
}
