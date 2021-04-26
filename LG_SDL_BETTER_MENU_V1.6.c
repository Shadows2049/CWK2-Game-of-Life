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
int cell[8000][8000];
 //1 for life, 0 for death
int pau;
int mode = 0;
int auto_check;
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
            quit_all=1;
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


                if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_RETURN)) {
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

}





int main(int argc, char *argv[])    //test main function
{   int step=0;
    int step_d=0;
    int step_choice=0;

    time_t t;
    srand((unsigned) time(&t));
    int check=0;
    startup();
    printf("***Game of life***");
    printf("\nStill under development, might crush your device");
    printf("\n\n***Please follow the instructions below carefully for your own safety***");
    printf("\n\npress 2 for default case(5x5)\npress 3 for load file\npress 4 for modify size(randomized cells)\n\n\n");
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
        printf("\nEnter Width: ");
        scanf("%d",&Width);
        printf("\nEnter Height: ");
        scanf("%d",&Height);
        int i,j;
        for(i=1;i<=Height;i++)
        for(j=1;j<=Width;j++)
            cell[i][j]=rand() % 2;
    }
    else
    {printf("\nOps, Wrong Command, clearly this game does not suit you...:(\n\n\n");
        return 0;
    }
    fflush(stdin);
    //startup();
    //store("testsave.txt");

    printf("\n\nPress 1 for unlimited steps, press 2 to customize step count\n");
    scanf("%d",&step_choice);
    if(step_choice==2)
    {
        printf("Enter designated count: ");
        scanf("%d",&step);
        if(step<1)
        {
            printf("\nInvalid count, switching to unlimited steps...\n");
            step_choice=1;
        }
    }

    printf("\npress 1 to quit program, click LEFT mouse or press ENTER to continue\n");

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init fail : %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Game of Life Alpha", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 1000, SDL_WINDOW_RESIZABLE);


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

     SDL_SetRenderDrawColor(renderer, 255, 182, 193, 0xFF);
    SDL_RenderClear(renderer);


    while(1)
    {
        store("testsave3.txt");



    /* Draw the Image on rendering surface */
        done = 0;
        while (!done) {
                loop();
                if(mode==1)
                SDL_Delay(1000);

            }


    /* Got everything on rendering surface,
       now Update the drawing image on window screen */

        //SDL_Quit();
        if(quit_all==1)                                          //quit
            return 0;
          /* Clear the rendering surface with the specified color */
    SDL_SetRenderDrawColor(renderer, 255, 182, 193, 0xFF);
    SDL_RenderClear(renderer);

        if(step_d==step&&step_choice==2)
        {
            printf("\n\nStep has reached designated count, program terminate");

            goto end;
        }

        evo();                                                  //evloution
        step_d++;

    }
    end:
    SDL_Quit();
}
