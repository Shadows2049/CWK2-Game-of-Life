#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include "SDL.h"
#include <time.h>

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;
int done;
int quit_all;
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
           // printf("%d",cell[i][j]);
        }
    }

    fclose(file);
    printf("\n\nload complete\n");

}



void
DrawChessBoard(SDL_Renderer * renderer)
{
    int row = 0,column = 0,x = 0;
    SDL_Rect rect, darea;

    /* Get the Size of drawing surface */
    SDL_RenderGetViewport(renderer, &darea);

    /*
    for( ; row < Height; row++)
    {
        //column = row%2;
        //x = column;
        for( ; column < Width; column++)
        {
                SDL_SetRenderDrawColor(renderer, 0, 211, 0, 0xFF);

                rect.w = darea.w/Width;
                rect.h = darea.h/Height;
                rect.x = x * rect.w;
                rect.y = row * rect.h;
                x = x + 2;
                SDL_RenderFillRect(renderer, &rect);
        }
    } */

    for(int i=1;i<Height+1;++i)
    {
        for(int j=1; j<Width+1;++j)
        {
            if(cell[i][j]==1)
            {
                SDL_SetRenderDrawColor(renderer, 0, 211, 0, 0xFF);

                rect.w = darea.w/Width;
                rect.h = darea.h/Height;
                rect.x = (j-1) * rect.w;
                rect.y = (i-1)* rect.h;

                SDL_RenderFillRect(renderer, &rect);

            }
        }
    }


}
//void SDL_UpdateRect(SDL_Surface *screen, Sint32 x, Sint32 y, Sint32 w, Sint32 h);

void
loop()
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {

       /* Re-create when window has been resized */
       if ((e.type == SDL_WINDOWEVENT) && (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)) {

          SDL_DestroyRenderer(renderer);

          surface = SDL_GetWindowSurface(window);
          renderer = SDL_CreateSoftwareRenderer(surface);
          /* Clear the rendering surface with the specified color */
          SDL_SetRenderDrawColor(renderer, 255, 182, 193, 0xFF);
          SDL_RenderClear(renderer);
       }

       if (e.type == SDL_QUIT) {
            done = 1;
#ifdef __EMSCRIPTEN__
            emscripten_cancel_main_loop();
#endif
            return;
        }

        if ((e.type == SDL_MOUSEBUTTONUP) && (e.button.button == SDL_BUTTON_LEFT)) {
            done = 1;
#ifdef __EMSCRIPTEN__
            emscripten_cancel_main_loop();
#endif
            return;
        }

         if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_1)) {
            done = 1;
            quit_all=1;
#ifdef __EMSCRIPTEN__
            emscripten_cancel_main_loop();
#endif
            return;
        }
        if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_ESCAPE)) {
            done = 1;
            quit_all=1;
#ifdef __EMSCRIPTEN__
            emscripten_cancel_main_loop();
#endif
            return;
        }
    }

    DrawChessBoard(renderer);

    /* Got everything on rendering surface,
       now Update the drawing image on window screen */
    SDL_UpdateWindowSurface(window);
    //SDL_UpdateRect(surface,0,0,0,0);
}





int main(int argc, char *argv[])    //test main function
{
    time_t t;
    srand((unsigned) time(&t));
    int check=0;
    startup();
    printf("\n2 for default, 3 for load file, 4 for modify size\n");
    scanf("%d",&check);
    if(check == 3)
    {
      load("testsave3.txt");
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

    printf("\npress 1 to quit program, click right mouse to continue\n");


    while(1)
    {
        store("testsave3.txt");

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init fail : %s\n", SDL_GetError());
        return 1;
    }


    /* Create window and renderer for given surface */
    window = SDL_CreateWindow("Chess Board", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 700, 700, SDL_WINDOW_RESIZABLE);
    if(!window)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window creation fail : %s\n",SDL_GetError());
        return 1;
    }
    surface = SDL_GetWindowSurface(window);
    renderer = SDL_CreateSoftwareRenderer(surface);
    if(!renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Render creation for surface fail : %s\n",SDL_GetError());
        return 1;
    }

    /* Clear the rendering surface with the specified color */
    SDL_SetRenderDrawColor(renderer, 255, 182, 193, 0xFF);
    SDL_RenderClear(renderer);


    /* Draw the Image on rendering surface */
        done = 0;
        while (!done) {
                loop();
            }


        SDL_Quit();
        if(quit_all==1)                                          //quit
            return 0;


        evo();                                                  //evloution

        //if(pau==49)
            //return 0;
    }
}
