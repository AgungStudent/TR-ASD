#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>


//buat password bintang
void password_hash(char pass[])
{
    int key = 0, index = 0;
    do
    {
        key = getch();
        switch (key)
        {
        case 0:
            getch();
            break;
        case 224:
            getch();
            break;
        case 8:
            if (index > 0)
            {
                pass[index] = 0;
                index--;
                printf("\b \b");
            }
            break;
        default:
            if (key >= 32 && key <= 126)
            {
                pass[index] = key;
                index++;
                printf("*");
            }
        }
    } while (key != 13);
    pass[index] = '\0';
}


 //buat atur posisi kursor login
 void gotoxy(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

 //Loading
 int main() {
system("color 60 ");

    printf("\n\n\n\n\n\t\t\  Nungguin yaaa ...\n");
    printf("\n\t\t ");
    for(int loading = 0; loading <= 50; loading++){
            printf("%c",219);
        Sleep(80);
        if(loading == 50){
            printf("\n\n\t\t\t\t\t\t Sabar sayang!");
            getch();
        }
    }


  //MENU UTAMA
  const char SPACE[] = "                                            ";
    int choose;
    for(;;){

    system("cls && color 6");
    Sleep(70);
    printf("\n\t\t\t   +========================================================+\n");
    Sleep(70);
    printf("\t\t\t   ||          MENU UTAMA RESTORAN 4 SEHAT 5 SEKARAT       ||\n\n");
    Sleep(70);
    printf("\t\t\t   ||                      KELOMPOK GOLD                   ||\n");
    Sleep(70);
    printf("\t\t\t   +========================================================+\n\n");
    Sleep(70);
    printf("%s 1. Pemesanan Menu\n%s 2. Menu Admin\n%s 3. Exit",SPACE,SPACE,SPACE);
    printf("\n\n%s Pilihan? ", SPACE);
    scanf("%d", &choose);

    if(choose==1){
        //TUGAS KIREY
    }
    else if (choose==2){
        break;
    }
    else if (choose==3){
        exit(0);
    }
    else{
         printf("%s Pilihan Salah", SPACE);
    }
    getch();

    }


  //Menu agung
  int error=0;
  for (;;){


  system("cls && color 80");
  int kolom = 60;
  int space = 30;

  for (int i = 0; i < kolom; i++) {

    // 4+i => dimulai dari kolom ke 4, 2 => artinya dimulai dari baris ke 2
    // Atas
    gotoxy(space + i, 2);
    printf("=");

    // Bawah
    gotoxy(kolom+space - i, 12);
    printf("=");
    Sleep(30);
  }
  for (int i = 0; i < 9; i++) {
    gotoxy(kolom+space, 3 + i);
    printf("|");

    gotoxy(space, 11 - i);
    printf("|");
    Sleep(30);
  }

  char login[] = "LOGIN";
  for (int i = 0; login[i] != '\0'; i++) {
    gotoxy((kolom+space)/2+12+ i, 1);
    printf("%c", login[i]);
    Sleep(30);
  }
   char user[9]="admin",pass[9]="gold";
   char inputUsername[9],inputPassword[9];


    gotoxy(space+4,5);
    printf("Masukkan username : ");
    scanf("%s", &inputUsername);
    gotoxy(space+4,6);
    printf("Masukkan password : ");
    password_hash(inputPassword);
        // cek username and password
        if (strcmp(user, inputUsername) == 0 && strcmp(pass, inputPassword) == 0){


        printf("Login Berhasil!");
        break;
        }
        else
        {
            gotoxy(space+space+7,14);
            printf("ERROR!\n");
            gotoxy(space+space+7,15);
            printf("USERNAME DAN PASSWORD SALAH");
            getch();
            error++;
        }
        if (error>=3)
        {
            //perbaiki
            gotoxy(space,17);
            printf("MAAF ANDA MEMASUKKAN PASSWORD DAN USERNAME SALAH SEBANYAK 3x");
            getch();
            return 0;
        }

  }

}


























    /*
    // login
    for (int loop = 1; loop == 1;)
    {
        system("cls||clear");
        // layout login
        printf("\n\n\n\n\n\n");
        printf("\t\t***********************************");
        printf("\n\t\t            ; L O G I N\n")
        printf("\t\t***********************************");
        printf("\n\t\t Username : ");
        gets(inputUsername);
        printf("\n\t\t\t\t\tPassword : ");
        password_hash(inputPassword);
        // cek username and password
        if (strcmp(username, inputUsername) == 0 && strcmp(password, inputPassword) == 0)
            loop = 0;
        else
        {
            printf("\n\t\t\t\t\tERROR!\n");
            printf("\t\t\t\t\tUSERNAME DAN PASSWORD SALAH");
            getch();
            error++;
        }
        if (error >= 3)
        {
            printf("\n\t\t\t\t\tMAAF ANDA MEMASUKKAN PASSWORD DAN USERNAME SALAH SEBANYAK 3 KALI!!!");
            getch();
            return 0;
        }
    }
}





  getch();
}

*/
