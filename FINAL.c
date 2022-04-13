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
  int jumlah_beli;     // tambahan untuk menu pesanan
} menu_t;

menu_t *head = NULL, *db_record, *head_pesanan = NULL;

const char KATEGORI[3][15] = {"Makanan", "Minuman", "Snack"};
const char SPACE[] = "                                            ";
int count_list;

// PROTOTYPE
// ==> (GIANINAA) <==
// desaign
void gotoxy(int x, int y);
void header(char title[]);
// login
void password_hash(char pass[]);
void login();
// ==> (AGUNG) <==
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
void line(char print[], int ascii1, int ascii2, int ascii3);
void tabel(menu_t *list);
// sorting
void sort(menu_t **head_sort, char sort_mode[], char field[]);
// ==> (KIREY) <==
// pesan menu
void pesan();
void penghitungan();
void strukPembayaran(int harga_total, int bayar);

int main() {
	// LOADING
  system("color 60 ");
  printf("\n\n\n\n\n\t\t\t\t    Nungguin yaaa ...\n");
  printf("\n\t\t\t\t    ");
  for (int loading = 0; loading <= 50; loading++) {
    printf("%c", 219);
    Sleep(80);
    if (loading == 50) {
      printf("\n\n\t\t\t\t\t\t\t\t          Sabar sayang!");
      getch();
    }
  }

  // MENU UTAMA
  int choose;
  for (;;) {
    system("cls && color 6");
    Sleep(70);
    printf("\n\n\n\t\t\t   +========================================================+\n");
    Sleep(70);
    printf("\t\t\t   ||          MENU UTAMA RESTORAN 4 SEHAT 5 SEKARAT       ||\n");
    Sleep(70);
    printf("\t\t\t   ||                      KELOMPOK GOLD                   ||\n");
    Sleep(70);
    printf("\t\t\t   +========================================================+\n\n");
    Sleep(70);
    printf("%s 1. Pemesanan Menu\n%s 2. Menu Admin\n%s 3. Exit", SPACE, SPACE, SPACE);
    printf("\n\n%s Pilihan? ", SPACE);
    scanf("%d", &choose);

    if (choose == 1) {
      dbToLinked();
      pesan();
    } else if (choose == 2) 
      login();
     else if (choose == 3) 
      exit(0);
     else 
      printf("%s Pilihan Salah", SPACE);
    getch();
  }
}
void gotoxy(int x, int y) {   // fungsi untuk memindahkan kursor
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void header(char title[]) {   // fungsi untuk mencetak header
  printf("\n\n                       ****************************************************************************\n");
  gotoxy(48, 3);
  printf("%s\n", title);
  printf("                       ****************************************************************************\n\n");
}
void menuCrud() {     //menu untuk CRUD
  int pilihan;
  while (1) {
    system("cls");
    system("color 3");
    Sleep(70);
    printf("\n\n                       ****************************************************************************\n");
    gotoxy(45, 3);
    Sleep(70);
    printf("CREATE, READ, UPDATE, DELETE\n");
    gotoxy(53, 5);
    Sleep(70);
    printf("MENU RESTORAN\n");
    Sleep(70);
    printf("                       ****************************************************************************\n\n");
    Sleep(70);
    printf("%sMenu 1. Tambah Menu Restoran\n", SPACE);
    Sleep(70);
    printf("%sMenu 2. Edit Menu Restoran\n", SPACE);
    Sleep(70);
    printf("%sMenu 3. Hapus Menu Restoran\n", SPACE);
    Sleep(70);
    printf("%sMenu 4. Lihat Menu Restoran\n", SPACE);
    Sleep(70);
    printf("%sMenu 5. Search Menu Restoran\n", SPACE);
    Sleep(70);
    printf("%sMenu 6. Keluar \n\n", SPACE);
    Sleep(70);
    printf("%sPilihan: ", SPACE);
    fflush(stdin);
    scanf("%d", &pilihan);
    if (getchar() != '\n') {     // proteksi inputan, mengencek apakah inputan megandung karakter seperti (1j,abc,dll)
      fflush(stdin);
      system("color 04");
      printf("%sPilihan salah!", SPACE);
      getch();
      continue;
    }

    dbToLinked();   //ambil data dari database, dan convert ke linked list
    sort(&head, "asc", "nama");    //urutkan data secara ascending, berdasarkan nama
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
      char logout[] = "Sampai Jumpa Lagi :)";
      printf("%s", SPACE);
      for (int i = 0; logout[i] != '\0'; i++) {
        Sleep(30);
        printf("%c", logout[i]);
      }
      free(head);
      return;
    } else {
      system("color 04");
      printf("%sPilihan salah!", SPACE);
    }
    getch();
  }
}
void createData() {    // fungsi untuk create data pada CRUD
  menu_t *ptr, *temp;
  ptr = (menu_t *)malloc(sizeof(menu_t));
  header("**CREATE MENU RESTORAN**");   //mencetak header
  formCrud(ptr);    //memanggil fungsi form untuk input data
  srand(time(NULL));     //untuk membuat angka acak berdasarkan waktu yang selalu berubah
  ptr->kode = rand();     // mengacak nilai untuk kode
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
  system("color 02");
  printf("\n%sBerhasil memasukkan data!", SPACE);
}
void updateData() {       //fungsi untuk update data pada CRUD
  menu_t *ptr, *temp;
  char name[36], kategori[15];
  int diskon, harga, search_kode, pilihan;
  ptr = (menu_t *)malloc(sizeof(menu_t));
  header("**UPDATE MENU RESTORAN**");
  if (head == NULL) {
    system("color 04");
    printf("%s       Data masih kosong!", SPACE);
    return;
  }
  tabel(head);
  printf("\n\n%sMasukkan kode menu yang akan dirubah: ", SPACE);
  scanf("%d", &search_kode);

  temp = head;
  while (temp) {    //looping untuk menggulang data di linked list
    if (temp->kode == search_kode) {   //cek apakah kode sesuai
      formCrud(temp);
      system("color 02");
      printf("%sBerhasil merubah data!", SPACE);
      return;
    }
    temp = temp->next;
  }
  system("color 04");
  printf("%sData tidak ditemukkan", SPACE);
}
void deleteData() {     // fungsi untuk menhapus data pada linked list
  header("**DELETE MENU RESTORAN**");
  if (head == NULL) {
    system("color 04");
    printf("%s       Data masih kosong!", SPACE);
    return;
  }
  int search_kode;
  tabel(head);
  printf("\n%sMasukkan kode yang ingin dihapus: ", SPACE);
  scanf("%d", &search_kode);
  menu_t *temp = head;
  int get_data = 0;  // untuk menentukkan data ditemukkan pada index ke...
  while (temp) {     //looping untuk mengulang data pada linked list
    if (temp->kode == search_kode)
      break;
    get_data++;
    temp = temp->next;
  }

  if (get_data == 0) {   //hapus data pada posisi pertama
    head = temp->next;
    free(temp);
    remove("db.txt");
    system("color 02");
    printf("%sData berhasil dihapus!!", SPACE);
    return;
  }
  temp = head;
  for (int i = 0; temp && i < get_data - 1; i++)   // perulangan untuk menuju posisi data yg akan dihapus
    temp = temp->next;

  if (temp == NULL || temp->next == NULL) {     //kalau data tidak ditemukkan
    system("color 04");
    printf("%sData tidak ada!", SPACE);
  } else {                                    //hapus data
    menu_t *next = temp->next->next;
    free(temp->next);
    temp->next = next;
    system("color 02");
    printf("%sData berhasil dihapus!", SPACE);
  }
}
void readData() {
  int pilihan;
  header("**SORTING MENU RESTORAN**");
  if (!head) {        // jika head != NULL
    system("color 04");
    printf("%s       Data masih kosong", SPACE);
    return;
  }
  char mode_sort[5], field[7];
  printf("%sPilih metode sorting:\n%s1. Ascending\n%s2. Descending\n%sPilihan: ", SPACE, SPACE, SPACE,SPACE);
  scanf("%d", &pilihan);
  if (pilihan == 1)
    strcpy(mode_sort, "asc");
  else if (pilihan == 2)
    strcpy(mode_sort, "desc");
  else {
    system("color 04");
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
    system("color 04");
    printf("%sPilihan salah", SPACE);
    return;
  }
  system("cls");
  header("**READ MENU RESTORAN**");
  tabel(head);     //cetak data setelah diurutkan
}

void searchData() {      //cari data pada CRUD
  header("**SEARCH MENU RESTORAN**");
  if (!head) {
    system("color 04");
    printf("%s      data masih kosong!", SPACE);
    return;
  }
  menu_t *head_search = NULL, *ptr = head;
  char search[36];
  int found = 0;
  printf("%sMasukkan (Nama/Kategori): ", SPACE);
  fflush(stdin);
  scanf("%35[^\n]", search);
  while (ptr) {
    if (strcmpi(ptr->name, search) == 0 || strcmpi(ptr->kategori, search) == 0) {
      found = 1;
      db_record = (menu_t *)malloc(sizeof(menu_t));
      *db_record = *ptr;
      db_record->next = head_search;
      head_search = db_record;
    }
    ptr = ptr->next;
  }
  if (found)
    tabel(head_search);
  else {
    system("color 04");
    printf("\n%s  Data tidak ditemukkan!", SPACE);
  }
  free(head_search);
}

void formCrud(menu_t *ptr) {    //form untuk input data
  char name[36], kategori[15];
  int diskon, harga, pilihan;
  // name
  fflush(stdin);
  printf("%sMasukkan Nama Menu: ", SPACE);
  scanf("%35[^\n]", &name);
// kategori
kategori:
  fflush(stdin);
  printf("\n%sOpsi Kategori:\n", SPACE);
  int size = sizeof(KATEGORI) / sizeof(KATEGORI[0]);
  for (int i = 0; i < size; i++) 
    printf("%s%d. %s\n", SPACE, i + 1, KATEGORI[i]);
  printf("%sPilihan: ", SPACE);
  scanf("%d", &pilihan);
  if (pilihan > size || pilihan <= 0) {
    system("color 04");
    printf("%sKategori tidak ditemukkan!\n", SPACE);
    getch();
    system("color 03");
    goto kategori;
  }
  strcpy(kategori, KATEGORI[pilihan - 1]);
// diskon
diskon:
  fflush(stdin);
  printf("%sMasukkan diskon menu(0-100): ", SPACE);
  scanf("%d", &diskon);
  if (diskon > 100 || diskon < 0) {
    system("color 04");
    printf("%sDiskon tidak valid!\n", SPACE);
    getch();
    system("color 03");
    goto diskon;
  }
  // harga
  fflush(stdin);
  printf("%sMasukkan Harga Menu: ", SPACE);
  scanf("%d", &harga);

  // pindahkan data ke struct
  strcpy(ptr->name, name);
  strcpy(ptr->kategori, kategori);
  ptr->diskon = diskon;
  ptr->harga = harga;
}

void updateDB() {           // mengubah data pada database setelah CRUD
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

void dbToLinked() {     // menconvert data dari database ke linked list
  head = NULL;
  FILE *read_file;
  if ((read_file = fopen("db.txt", "r")) == NULL) 
    return;
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

void tabel(menu_t *list) {       //cetak data dalam bentuk tabel
  menu_t *curr = list;
  char print[150];
  if (list == NULL) {
    system("color 04");
    printf("%s       Data masih kosong", SPACE);
    return;
  }

  line(print, 201, 203, 187);     //201,203,187 merupakan ascii untuk membuat tabel 
  printf("              %s", print);
  printf("\n              %c %-7s%c %-34s%c %-14s%c %-10s%c %-14s %c\n", 186, "KODE", 186, "NAMA MENU", 186, "HARGA", 186, "DISKON(%)", 186, "KATEGORI", 186);
  while (curr) {
    line(print, 204, 206, 185);
    printf("              %s", print);
    printf("\n              %c %-7d%c %-34s%c Rp.%-11d%c %-9d %c %-14s %c\n", 186, curr->kode, 186, curr->name, 186, curr->harga, 186, curr->diskon, 186, curr->kategori); curr = curr->next;
  }
  line(print, 200, 202, 188);
  printf("              %s", print);
}

void line(char print[], int ascii1, int ascii2, int ascii3) {     //untuk mencetak baris dalam membentuk tabel
  int index = 0;
  print[index] = (char)ascii1;
  // kode
  for (int i = 0; i < 8; i++)
    print[++index] = (char)205;
  print[++index] = (char)ascii2;
  // nama
  for (int i = 0; i < 35; i++)
    print[++index] = (char)205;
  print[++index] = (char)ascii2;
  // harga
  for (int i = 0; i < 15; i++)
    print[++index] = (char)205;
  print[++index] = (char)ascii2;
  // diskon
  for (int i = 0; i < 11; i++)
    print[++index] = (char)205;
  print[++index] = (char)ascii2;
  // Keterangan
  for (int i = 0; i < 16; i++)
    print[++index] = (char)205;
  print[++index] = (char)ascii3;
}
void sort(menu_t **head_sort, char sort_mode[], char field[]) {    //untuk sorting data, dengan metode BUBBLE SORT
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

      if (do_swap) {   // swap node pada linked list
        menu_t *temp = next->next;
        next->next = curr;
        curr->next = temp;
        *h = next;
        sorted = 0;
      }
      h = &(*h)->next;
    }
    if (sorted)   // jika data sudah berurutan
      break;
  }
}
void password_hash(char pass[]) {     // membuat password menjadi bintang-bintang
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
void login() {           //login
  int error = 0;
  for (;;) {
    system("cls && color 30");
    int kolom = 60;
    int space = 30;

    for (int i = 0; i < kolom; i++) {
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
      menuCrud();
      return;
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
      exit(0);
    }
  }
}
void pesan() {     //fungsi untuk memesan menu makanan
memesan_menu: // goto untuk mengulang pesanan
  system("color 71 && cls");
  header( "**PESAN MENU RESOTRAN**"); // panggil fungsi header untuk mencetak title
  if (!head) {
    system("color 74");
    printf("%s     Menu tidak tersedia!", SPACE);
    return;
  }
  int kode_menu, jumlah_pesan, success = 0, pilihan;
  char yakin[3];

  sort(&head, "asc", "nama"); // sorting data secara ascending berdasarkan nama
  tabel(head);                // cetak tabel menu makanan
  printf("\n%sMasukkan kode menu yang dipilih: ", SPACE); // input untuk masukkan kode menu
  scanf("%d", &kode_menu);
  menu_t *temp = head, *ptr;
  while (temp) { // loop untuk menggulang linked list yang berisi data-data menu
    if (temp->kode == kode_menu) { // jika kode yang diinputkan ditemukkan
      printf("\n%sMenu yang dipilih\t= %s\n", SPACE, temp->name);
      printf("%sjumlah pesan\t= ", SPACE);
      scanf("%d", &jumlah_pesan);
      printf("%s===============================================\n", SPACE);
      // membuat linked list untuk data pesanan
      ptr = (menu_t *)malloc(sizeof(menu_t));
      *ptr = *temp;
      ptr->jumlah_beli = jumlah_pesan;
      ptr->next = head_pesanan;
      head_pesanan = ptr;
      printf("%sPesanan berhasil ditambahkan!\n", SPACE);
      success = 1;
      break;
    }
    temp = temp->next;
  }
  if (!success) { // jika kode yang diinputkan tidak ditemukkan
    system("color 74");
    printf("%sKode menu tidak ditemukkan!\n", SPACE);
  }
peyakinan: // goto untuk mengulang peyakinan
  fflush(stdin);
  printf("\n%sApakah anda ingin memesan lagi?\n%s[input Y untuk Ya]\t[input T untuk Tidak] ", SPACE, SPACE); // ulang pesanan
  scanf("%s", &yakin);
  if (strcmpi("T", yakin) == 0) {    // jika tidak ingin pesan lagi
    penghitungan();   // fungsi untuk hitung pesanan
    return;
  } else if (strcmpi("Y", yakin) == 0) {
    goto memesan_menu;   // goto memesan, artinya kembali memesan menu lagi
  } else {
    system("color 74");
    printf("\n%sKesalahan inputan\n\n", SPACE);
    getch();
    system("cls && color 71");
    header("**PESAN MENU RESOTRAN**"); // panggil fungsi header untuk mencetak title
    goto peyakinan;
  }
}
void penghitungan() {      //menghitung harga pesanan 
  int pilihan, harga_bersih, harga_total = 0, bayar, i;   
bayar:
  system("cls && color F1");
  header("**DAFTAR MENU YANG DIPESAN**");
  // TABEL PESANAN
  if (head_pesanan == NULL) {
    printf("%s       Data masih kosong\n", SPACE);
    return;
  }
  for (i = 0; i < 119; i++)
    printf("=");
  printf("\n%c %-7s%c %-34s%c %-14s%c %-10s%c %-14s%c %-10s%c %-15s%c\n", '|', "KODE", '|', "NAMA MENU", '|', "HARGA", '|', "DISKON(%)", '|', "KATEGORI", '|', "JUMLAH", '|', "HARGA TOTAL", '|'); menu_t *curr = head_pesanan;
  while (curr) {
    for (i = 0; i < 119; i++)
      printf("=");
    harga_bersih = (curr->harga - (curr->harga * curr->diskon / 100)) * curr->jumlah_beli;
    printf( "\n%c %-7d%c %-34s%c Rp.%-11d%c %-9d %c %-14s%c %-10d%c Rp.%-12d%c\n", '|', curr->kode, '|', curr->name, '|', curr->harga, '|', curr->diskon, '|', curr->kategori, '|', curr->jumlah_beli, '|', harga_bersih);
    curr = curr->next;
  }
  for (i = 0; i < 119; i++)
    printf("=");
  // TABEL END
  printf("\n\n%s1. Bayar menu \n%s2. Keluar (batal memesan) \n%sPilihan: ", SPACE, SPACE, SPACE);
  scanf("%d", &pilihan);
  if (pilihan == 1) {
    menu_t *temp = NULL;
    temp = head_pesanan;
    while (temp) {
      harga_bersih = (temp->harga - (temp->harga * temp->diskon / 100)) * temp->jumlah_beli;
      harga_total += harga_bersih;
      temp = temp->next;
    }
    printf("\n\n%sHarga yang harus dibayar Rp. %d\n", SPACE, harga_total);
    printf("%sMasukkan uang: ", SPACE);
    scanf("%d", &bayar);
    if (bayar >= harga_total) {
      system("color F2");
      printf("%sPembayaran sukses", SPACE);
      strukPembayaran(harga_total, bayar);
      head_pesanan = NULL;
      system("cls && color 70");
      char message[] = "TERIMAKASIH ATAS PESANANNYA, SELAMAT MENIKMATI...!!!";
      gotoxy(35, 12);
      for (i = 0; i < sizeof(message); i++) {
        printf("%c", message[i]);
        Sleep(30);
      }
			getch();
      return;
    } else {
      system("color F4");
      printf("%sUang Anda tidak cukup! Silakan input ulang!", SPACE);
      getch();
      harga_total = 0;
      goto bayar;
    }
  } else if (pilihan == 2) {
    head_pesanan = NULL;
    printf("%sPesanan dibatalkan", SPACE);
    return;
  } else {
    printf("%sPilihan salah!", SPACE);
    getch();
    goto bayar;
  }
}
void strukPembayaran(int harga_total, int bayar) {    // cetak struk pebayaran menggunakan file handling
  int harga_bersih, i;
  time_t ambil_waktu;
  time(&ambil_waktu);
  FILE *struk_file = fopen("struk.txt", "w");
  fprintf(struk_file, "\n\t\t\t\t!!..STRUK PEMBAYARAN..!!\n\n");
  for (i = 0; i < 119; i++)
    fprintf(struk_file, "=");
  fprintf(struk_file, "\n| \t     Gold restaurant\t\t\t\t\t\t\t\t\t\t\t      |\n"); fprintf(struk_file, "| \t     Jawa Tengah\t\t\t\t\t\t\t\t\t\t\t      |\n");
  fprintf( struk_file, "| \t     Telp : (0283)521414 / 085432167890\t\t\t\t\t\t\t\t\t      |\n");
  // TABEL PESANAN
  for (i = 0; i < 119; i++)
    fprintf(struk_file, "=");
  fprintf(struk_file, "\n%c %-7s%c %-34s%c %-14s%c %-10s%c %-14s%c %-10s%c %-15s%c\n", '|', "KODE", '|', "NAMA MENU", '|', "HARGA", '|', "DISKON(%)", '|', "KATEGORI", '|', "JUMLAH", '|', "HARGA TOTAL", '|');
  menu_t *curr = head_pesanan;
  while (curr) {
    for (i = 0; i < 119; i++)
      fprintf(struk_file, "=");
    harga_bersih = (curr->harga - (curr->harga * curr->diskon / 100)) * curr->jumlah_beli;
    fprintf( struk_file, "\n%c %-7d%c %-34s%c Rp.%-11d%c %-9d %c %-14s%c %-10d%c Rp.%-12d%c\n", '|', curr->kode, '|', curr->name, '|', curr->harga, '|', curr->diskon, '|', curr->kategori, '|', curr->jumlah_beli, '|', harga_bersih);
    curr = curr->next;
  }
  for (i = 0; i < 119; i++)
    fprintf(struk_file, "=");
  // TABEL END
  fprintf( struk_file, "\n\n=================================================================");
  fprintf(struk_file, "\n| Total Keseluruhan \t\t\t\t= Rp.%d\t|", harga_total);
  fprintf(struk_file, "\n| Uang bayar        \t\t\t\t= Rp.%d\t|", bayar);
  fprintf(struk_file, "\n| Kembalian         \t\t\t\t= Rp.%d\t|", bayar - harga_total);
  fprintf( struk_file, "\n|                                                               |");
  fprintf( struk_file, "\n|                                                               |");
  fprintf(struk_file, "\n| Waktu/Hari : %s", ctime(&ambil_waktu));
  fprintf(struk_file, "| Perhatian : Barang yang dibeli tidak bisa dikembalikan!\t|");
  fprintf( struk_file, "\n|                                                               |\n");
  fprintf( struk_file, "=================================================================\n");
  fclose(struk_file);
  system("notepad struk.txt");
}
