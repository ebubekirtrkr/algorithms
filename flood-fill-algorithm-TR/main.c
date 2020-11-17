#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#define True 1
#define False 0
#define GrupYok -1
#define YildizYok 0
#define YildizVar 1

typedef struct hucre
{
    int yildizVarMi, grupNo;
} Hucre;
int SATIR, SUTUN, GRUPINDEX=0;
Hucre **GRID;
int GRUPLAR[200] = {0};


Hucre **gridOlustur(int w, int h)
{
    Hucre **grid = (Hucre **)malloc(sizeof(Hucre *) * w);
    for (int i = 0; i < w; i++)
        grid[i] = (Hucre *)malloc(sizeof(Hucre) * h);

    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
        {
            grid[i][j].yildizVarMi = YildizYok;
            grid[i][j].grupNo = GrupYok;
        }
    return grid;
}

void gridiAl()
{

    while (True)
    {
        int x, y;
        scanf("%d", &x);
        if (x == -1)
            break;
        scanf("%d", &y);
        GRID[x][y].yildizVarMi = YildizVar;
    }
}

void gridiYazdir()
{
    for (int i = 0; i < SATIR; i++)
    {
        for (int j = 0; j < SUTUN; j++)
            printf("%c ", GRID[i][j].yildizVarMi ? '*' : '_');
        printf("\n");
    }
}

void gruplaYazdir()
{
    for (int i = 0; i < SATIR; i++)
    {
        for (int j = 0; j < SUTUN; j++)
        {
            if (GRID[i][j].grupNo == GrupYok)
                printf("%c ", '_');
            else
                printf("%d ", GRID[i][j].grupNo);
        }
        printf("\n");
    }
}

int yildizKontrol(int x, int y)
{
    return (!(x >= SATIR || x < 0) &&
            !(y >= SUTUN || y < 0) &&
            GRID[x][y].yildizVarMi &&
            GRID[x][y].grupNo == GrupYok);
}

void grubaEkle(int x, int y)
{
    GRID[x][y].grupNo = GRUPINDEX;
    GRUPLAR[GRUPINDEX]++;
}

void etrafKontrol(int x, int y)
{
    Queue *Q = createQueue(100);
    int directions[8][2] = {
        {-1, -1}, //sol üst
        {-1, 0},  //üst
        {-1, 1},  //sağ üst
        {0, -1},  //sol
        {0, 1},   //sağ
        {1, -1},  //sol alt
        {1, 0},   //alt
        {1, 1}    //sağ alt
    };

    enqueue(Q, x, y);
    while (!isEmpty(Q))
    {
        Nokta n = dequeue(Q);

        for (int i = 0; i < 8; i++)
        {
            int dx = n.x + directions[i][0], dy = n.y + directions[i][1];
            if (yildizKontrol(dx, dy))
            {
                enqueue(Q, dx, dy);
                grubaEkle(dx, dy);
            }
        }
    }
}

void gridiIsle()
{
    for (int i = 0; i < SATIR; i++)
    {
        for (int j = 0; j < SUTUN; j++)
        {
            if (yildizKontrol(i, j))
            {
                grubaEkle(i, j);
                etrafKontrol(i, j);
                GRUPINDEX++;
            }
        }
    }
}

void grupSirala()
{
    for (int i = 0; i < GRUPINDEX; i++)
    {
        for (int j = i + 1; j < GRUPINDEX; j++)
        {
            if (GRUPLAR[i] > GRUPLAR[j])
            {
                int temp = GRUPLAR[j];
                GRUPLAR[j] = GRUPLAR[i];
                GRUPLAR[i] = temp;
            }
        }
    }
}

void grupYazdir()
{
    printf("%d ", GRUPINDEX);

    for (int i = 0; i < GRUPINDEX; i++)
        printf("%d ", GRUPLAR[i]);
    printf("\n");
}

int main()
{
    scanf("%d %d", &SATIR, &SUTUN);

    GRID = gridOlustur(SATIR, SUTUN);
    gridiAl();
    gridiYazdir();
    gridiIsle();
    gruplaYazdir();
    grupSirala();
    grupYazdir();
    return 0;
}