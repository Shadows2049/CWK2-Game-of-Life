#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include <time.h>

//#define Height 5                    //Predefine game size
//#define Width 5

int Height;
int Width;
int cell[1000][1000];
 //1 for life, 0 for death
int pau;
void HideCursor()
{
 CONSOLE_CURSOR_INFO cursor_info = {1,0};
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);

}
void gotoxy(int x,int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}


void startup()  //data initialization
{
    int i,j;
    for(i=0;i<=Height+1;i++)
        for(j=0;j<=Width+1;j++)
            cell[i][j]=0;
    cell[3][1] = 1;
    cell[4][2] = 1;
    cell[2][3] = 1;
    cell[3][3] = 1;
    cell[4][3] = 1;

    HideCursor();
}


void display()     //display game
{   //int pau;
    gotoxy(0,20);
    int i,j;
    for(i=1;i<Height+1;i++)
    {
        for(j=1;j<Width+1;j++)
        {
            if(cell[i][j]==1)
                printf("O");
            else
                printf(" ");
        }
        printf("\n");
    }

   //system("pause");

    //Sleep(1220);             //refresh rate control
    pau = getchar();


}


void evo()
{   int x;
    int y;
    int sum;
    int marker[Height+2][Width+2];
    for(x=1;x<Height+1;++x)
    {
        for(y=1; y<Width+1;++y)
        {
            sum = cell[x-1][y-1]+cell[x-1][y]+cell[x-1][y+1]+cell[x][y-1]+cell[x][y+1]+cell[x+1][y-1]+cell[x+1][y]+cell[x+1][y+1]; //count the number of lives among the surrounding 8 positions


                if(cell[x][y]==1)
                {
                    if(sum==3)
                        marker[x][y]=1;
                    else if(sum==2)
                        marker[x][y]=1;
                    else
                        marker[x][y]=0;
                }

                 if(cell[x][y]==0)
                {
                    if(sum==3)
                        marker[x][y]=1;
                    else
                        marker[x][y]=0;
                }


        }

    }

    for(x=1;x<Height+1;x++)
        for(y=1;y<Width+1;y++)
            cell[x][y]=marker[x][y];




}

void store(const char *filename)
{

	FILE *file;

    if((file = fopen(filename,"a"))==NULL)
    {
        printf("\nSave error\n\n");
            exit(-99);
    }
    fclose(file);
    file = fopen(filename,"w+");
    fprintf(file,"%d\n",Width);
    fprintf(file,"%d\n",Height);
    for (int i=1; i<Height+1;++i)
    {
        for(int j=1; j<Width+1; ++j)
        {
            fprintf(file,"%d\n",cell[i][j]);
        }

    }

    fclose(file);
    printf("\nsave complete\n");

    //return 0;
}

void load(const char *filename)
{
    int k;
    int w;
    int h;
    FILE *file;
    file = fopen(filename, "r");
    fscanf(file,"%d",&w);
    fscanf(file,"%d",&h);
    printf("\nWidth is %d",w);
    printf("\nHeight is %d\n",h);
    Width  = w;
    Height = h;

    for(int i=1; i<Height+1;++i)
    {
        for(int j=1; j<Width+1;++j)
        {
            fscanf(file,"%d",&k);
            cell[i][j] = k;
            //printf("%d",cell[i][j]);
        }
    }

    fclose(file);
    printf("\n\nload complete\n");

}

int main()     //test main function
{
    time_t t;
    srand((unsigned) time(&t));
    int check=0;
    startup();
    printf("\n2 for default, 3 for load file, 4 for modify size\n");
    scanf("%d",&check);
    if(check == 3)
    {
      load("testsave2.txt");
    }
    else if(check == 2)
    {
        printf("\nLoading default...");
        Height = 5;
        Width  = 5;

    }
    else if(check == 4)
    {
        printf("\nEnter Width");
        scanf("%d",&Width);
        printf("\nEnter Height");
        scanf("%d",&Height);
        int i,j;
        for(i=0;i<=Height+1;i++)
        for(j=0;j<=Width+1;j++)
            cell[i][j]=rand() % 2;
    }
    else
    {printf("\nWrong command");
        return 0;
    }
    fflush(stdin);
    //startup();
    //store("testsave.txt");
    printf("\npress 1 to quit program, press 'enter' to continue\n");
    while(1)
    {   printf("\n\n");
        display();
        store("testsave2.txt");
        evo();
        if(pau==49)
            return 0;   //quit
    }
}
