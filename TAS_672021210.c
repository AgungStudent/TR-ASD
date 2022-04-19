#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 5
#define MAX 3

struct node
{
    int data;
    struct node *next;
};

struct node *head;

void inputAwal()
{
    struct node *ptr;
    int item;
    ptr = (struct node *)malloc(sizeof(struct node));
    if (!ptr)
    {
        printf("\n OVERFLOW");
    }
    else
    {
        printf("Input Data: ");
        scanf("%d", &item);
        ptr->data = item;
        ptr->next = head;
        head = ptr;
        printf("berhasil!");
    }
}

void inputAkhir()
{
    struct node *ptr, *temp;
    int item;
    ptr = (struct node *)malloc(sizeof(struct node));
    if (!ptr)
    {
        printf("\n OVERFLOW");
    }
    else
    {
        printf("Input Data: ");
        scanf("%d", &item);
        ptr->data = item;
        if (head == NULL)
        {
            ptr->next = NULL;
            head = ptr;
            printf("Sukses gaiss!");
        }
        else
        {
            temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = ptr;
            ptr->next = NULL;
            printf("Sukses gaiss!");
        }
    }
}

void tentukkanLokasi()
{
    int i, loc, item;
    struct node *ptr, *temp;
    ptr = (struct node *)malloc(sizeof(struct node));
    if (ptr == NULL)
    {
        printf("\n OVERFLOW");
    }
    else
    {
        printf("Input Data: ");
        scanf("%d", &item);
        ptr->data = item;
        printf("Mau simpan dimana? ");
        scanf("%d", &loc);
        temp = head;
        for (i = 0; i < loc; i++)
        {
            temp = temp->next;
            if (temp == NULL)
            {
                printf("\n  Tidak bisa simpan data");
                return;
            }
        }
        ptr->next = temp->next;
        temp->next = ptr;
        printf("Sukses gaiss!");
    }
}

void cetak()
{
    struct node *ptr;
    ptr = head;
    if (ptr == NULL)
    {
        printf("No Data!");
    }
    else
    {
        printf("Cetak Data");
        while (ptr != NULL)
        {
            printf("\n%d ", ptr->data);
            ptr = ptr->next;
        }
    }
}

void programLinkedList()
{
    int choice = 0;
    while (choice != 5)
    {
        system("cls");
        printf("\n Menu Linked List\n");
        printf("\n1. Input Data First Node");
        printf("\n2. Input Data Last Node");
        printf("\n3. Input Data Unknown Node");
        printf("\n4. Show Linked List Data");
        printf("\n5. Exit");
        printf("\nPilihan: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            inputAwal();
            getch();
            break;
        case 2:
            inputAkhir();
            getch();
            break;
        case 3:
            tentukkanLokasi();
            getch();
            break;
        case 4:
            cetak();
            getch();
            break;
        case 5:
            return;
            break;
        default:
            printf("Masukkan pilihan yang benar");
        }
    }
}

typedef struct
{
    int top;
    char data[5][5];
} STACK;

STACK tumpuk;

void inisialisasi()
{
    tumpuk.top = -1;
}

int IsFull()
{
    if (tumpuk.top == MAX_STACK - 1)
        return 1;
    else
        return 0;
}

int IsEmpty()
{
    if (tumpuk.top == -1)
        return 1;
    else
        return 0;
}

void Push(char d[5])
{
    tumpuk.top++;
    strcpy(tumpuk.data[tumpuk.top], d);
}

void Pop()
{
    printf("Data yang diambil = %s\n", tumpuk.data[tumpuk.top]);
    tumpuk.top--;
}

void TampilStack()
{
    for (int i = tumpuk.top; i >= 0; i--)
    {
        printf("Data: %s\n", tumpuk.data[i]);
    }
}

void Bersihkan()
{
    tumpuk.top = -1;
}

void programStack()
{
    int pilihan;
    inisialisasi();
    char dt[5];
    do
    {
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Cetak isi array stack!\n");
        printf("4. Hapus isi array stack!\n");
        printf("5. Keluar\n");
        printf("Pilihan Anda? ");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
            if (IsFull() != 1)
            {
                printf("Data yang ingin diinputkan = ");
                scanf("%s", dt);
                Push(dt);
            }
            else
                printf("Stack sudah penuh!");
            break;
        case 2:
            if (IsEmpty() != 1)
                Pop();
            else
                printf("Stack masih kosong!\n");
            break;
        case 3:
            if (IsEmpty() != 1)
                TampilStack();
            else
                printf("\n Tidak ada data!");
            break;
        case 4:
            Bersihkan();
            printf("Data sudah dihapus\n");
            break;
        }
        getch();
    }
    while (pilihan != 5);
    printf("Keluar program!\n");
    getch();
}

typedef struct
{
    int data[MAX];
    int head;
    int tail;
} queue;

queue antrian;

void awal()
{
    antrian.head = antrian.tail = -1;
}

int kosong()
{
    if (antrian.tail == -1)
        return 1;
    else
        return 0;
}

int penuh()
{
    if (antrian.tail == MAX - 1)
        return 1;
    else
        return 0;
}

int enqueue(int data)
{
    if (kosong() == 1)
    {
        antrian.head = antrian.tail = 0;
        antrian.data[antrian.tail] = data;
        printf("%d masuk!\n", antrian.data[antrian.tail]);
        void tampil();
        {
            if (kosong() == 0)
            {
                for (int i = antrian.head; i <= antrian.tail; i++)
                {
                    printf("%d", antrian.data[i]);
                }
            }
            else
                printf("Isi antrian kosong!");
        }
    }
    else if (penuh() == 0)
    {
        antrian.tail++;
        antrian.data[antrian.tail] = data;
        printf("%d masuk!\n", antrian.data[antrian.tail]);
    }
}

int dequeue()
{
    int antri = antrian.data[antrian.head];
    for (int i = antrian.head; i <= antrian.tail; i++)
    {
        antrian.data[i] = antrian.data[i + 1];
    }
    antrian.tail--;
    return antri;
}
void cetakQueue()
{
    if (kosong())
    {
        printf("Data masih kosong!");
        return;
    }
    for (int i = 0; i <= antrian.tail; i++)
    {
        printf("%d\n", antrian.data[i]);
    }
}
void clearQueue()
{
    antrian.head = antrian.tail = -1;
    printf("Data sudah kosong!");
}

void programQueue()
{
    int pilihan, data;
    do
    {
        printf("\n");
        printf("1. Masuk Satu Data\n");
        printf("2. Keluarkan Satu Data\n");
        printf("3. Lihat isi Antrian\n");
        printf("4. Hapus isi Antrian\n");
        printf("5. Keluar\n");
        printf("Pilihan Anda? ");
        scanf("%d", &pilihan);
        switch (pilihan)
        {
        case 1:
            printf("Data = ");
            scanf("%d", &data);
            enqueue(data);
            break;
        case 2:
            if (kosong())
                dequeue();
            else
                printf("Queue masih kosong");
            break;
        case 3:
            cetakQueue();
            break;
        case 4:
            clearQueue();
            break;
        case 5:
            return;
            break;
        default:
            printf("Pilihan salah");
            break;
        }
    }
    while (pilihan != 5);
}

int main()
{
    for (;;)
    {
        int a;
        puts("MENU:");
        puts("1. Linked list");
        puts("2. Stack");
        puts("3. Queue");
        puts("4. keluar");
        printf("Masukkan menu: ");
        scanf("%d", &a);
        switch (a)
        {
        case 1:
            system("cls");
            programLinkedList();
            break;
        case 2:
            system("cls");
            programStack();
            break;
        case 3:
            system("cls");
            programQueue();
            break;
        case 4:
            exit(0);
            break;
        default:
            printf("\ninput yang benar dong!");
            break;
        }
    }
}
