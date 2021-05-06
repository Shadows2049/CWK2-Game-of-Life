
#include "LGSDL.h"
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include "SDL.h"
#include <time.h>

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
    int oc = 0;
    int or = 0;
    int x = 0;

    SDL_Rect rect, darea;


    /* Get the Size of drawing surface */
    SDL_RenderGetViewport(renderer, &darea);

     c = darea.w/Width;
     r = darea.h/Height;
     oc = c;
     or = r;
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
                c=rect.w;
                r=rect.h;
                SDL_RenderFillRect(renderer, &rect);


            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 255, 182, 193, 0xFF);

                rect.w = darea.w/Width;
                rect.h = darea.h/Height;
                rect.x = (j-1) * rect.w;
                rect.y = (i-1)* rect.h;
                c=rect.w;
                r=rect.h;
                SDL_RenderFillRect(renderer, &rect);

            }


        }


    }
                for(int i=0; i<Height; ++i){

                SDL_SetRenderDrawColor(renderer,35,228,245,225);
                SDL_RenderDrawLine(renderer,0,or,5000,or);
                SDL_RenderPresent(renderer);

                or=or+r;

                }

                for(x=0; x<Width; ++x){

                SDL_SetRenderDrawColor(renderer,35,228,245,225);
                SDL_RenderDrawLine(renderer,oc,0,oc,5000);

                SDL_RenderPresent(renderer);
                oc=oc+c;

                }

}


void
loop()
{
    SDL_Event e;
    int pause_check;


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
            exit(0);
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
           exit(0);
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


void window_optimizer()
{
    rw=Width;
    rh = Height;
    if(rw<=100)
        rw=rw*10;
    else if(rw<=200)
        rw = rw*4;
    else if(rw<=350)
        rw=rw*3;
    else if(rw<=500)
        rw=rw*2;




    if(rh<=100)
        rh=rh*10;
    else if(rh<=200)
        rh = rh*4;
    else if(rh<=350)
        rh = rh*3;
    else if(rh<=500)
        rh = rh*2;


}

void respawn()
{
    int i=0;
    int j=0;
    i = m_x/c+1;
    j = m_y/r+1;
    //printf("%d,%d",c,r);
    cell[j][i] = 1;

}

void death()
{
    int i=0;
    int j=0;
    i = m_x/c+1;
    j = m_y/r+1;

    cell[j][i] = 0;

}
