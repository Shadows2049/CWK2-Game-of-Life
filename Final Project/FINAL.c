#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include "SDL.h"
#include <time.h>
#include "LGSDL.h"








int main(int argc, char *argv[])    //test main function
{   int step=0;
    int step_d=0;
    int step_choice=0;
    int ret;
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
    {   int rm=0;
        printf("\nEnter Width: ");
        scanf("%d",&Width);
        printf("\nEnter Height: ");
        scanf("%d",&Height);

        printf("1 for random status, 2 for manual operation: ");
        scanf("%d",&rm);
        if(rm==1)
        {
            printf("\nRandomized live and death...");
            int i,j;
            for(i=1;i<=Height;i++)
            for(j=1;j<=Width;j++)
            cell[i][j]=rand() % 2;
        }

        if(rm==2)
        {
            printf("\nManual operation...");
            printf("\nLeft click foe live, right click for death, ESC for quit&save");
        for(int i=0;i<=Height+1;i++)
        for(int j=0;j<=Width+1;j++)
           cell[i][j]=0;


            window_optimizer();
            window = SDL_CreateWindow("Manual initialization", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, rh,rw, SDL_WINDOW_RESIZABLE);
            surface = SDL_GetWindowSurface(window);
            renderer = SDL_CreateSoftwareRenderer(surface);
              SDL_SetRenderDrawColor(renderer, 255, 182, 193, 0xFF);

                SDL_RenderClear(renderer);
            while(1){
                    loop();
                    SDL_Event e;
                while (SDL_PollEvent(&e)){
                                 if ((e.type == SDL_WINDOWEVENT) && (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)) {

                              SDL_DestroyRenderer(renderer);

                              surface = SDL_GetWindowSurface(window);
                              renderer = SDL_CreateSoftwareRenderer(surface);
                              SDL_SetRenderDrawColor(renderer, 255, 182, 193, 0xFF);

                                SDL_RenderClear(renderer);


                           }

                                if ((e.type == SDL_MOUSEBUTTONUP) && (e.button.button == SDL_BUTTON_LEFT)) {
                                               //done = 1;
                                                m_x = e.motion.x;
                                                m_y = e.motion.y;
                                                respawn();
                                        #ifdef __EMSCRIPTEN__
                                                    emscripten_cancel_main_loop();
                                        #endif

                                }


                                 if ((e.type == SDL_MOUSEBUTTONUP) && (e.button.button == SDL_BUTTON_RIGHT)) {
                                               //done = 1;
                                               //printf("rmpd");
                                                m_x = e.motion.x;
                                                m_y = e.motion.y;
                                                death();
                                        #ifdef __EMSCRIPTEN__
                                                    emscripten_cancel_main_loop();
                                        #endif

                                }


                                 if (e.type == SDL_QUIT) {
                                        store("testsave3.txt");
                                        SDL_Quit();
                                        goto run;
                            #ifdef __EMSCRIPTEN__
                                        emscripten_cancel_main_loop();
                            #endif

                                    }

                                 if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_ESCAPE)) {
                                        store("testsave3.txt");
                                        SDL_Quit();
                                        goto run;
                            #ifdef __EMSCRIPTEN__
                                        emscripten_cancel_main_loop();
                            #endif

                                }

                                        }
                    SDL_RenderPresent(renderer);

            }


        }




    }
    else
    {printf("\nOps, Wrong Command, clearly this game does not suit you...:(\n\n\n");
        return 0;
    }
    fflush(stdin);
    //startup();
    //store("testsave.txt");
run:
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


    printf("\n\nPress 1 for automatic evolution, press 2 for single step evolution: ");
    scanf("%d",&method);
    if(method==1){
        printf("\nCustomize refresh rate(seconds): ");
        scanf("%d",&ret);
    }


    printf("\npress 1 to quit program, click LEFT mouse or press ENTER to continue\n");

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init fail : %s\n", SDL_GetError());
        return 1;
    }



    window_optimizer();

    window = SDL_CreateWindow("Game of Life Alpha", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, rw, rh, SDL_WINDOW_RESIZABLE);


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
        go:
            if(method==1)
            {
                printf("Press p to pause and continue...");
            }
        while (!done) {
                if(method==2)
                loop();
                if(method==1){
                   loop();
                   done = 1;
                   SDL_Delay(ret*1000);
                   SDL_Event k;
                   while (SDL_PollEvent(&k)){
                           if ((k.type == SDL_KEYDOWN) && (k.key.keysym.sym == SDLK_p)) {
                                printf("paused");
                                   while(1){
                                    loop();
                                    SDL_Event f;
                                    while (SDL_PollEvent(&f)){
                                       if ((f.type == SDL_KEYDOWN) && (f.key.keysym.sym == SDLK_p)) {
                                            printf("continue");
                                               goto go;

                                    }

                                         if ((f.type == SDL_WINDOWEVENT) && (f.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)) {

                                          SDL_DestroyRenderer(renderer);

                                          surface = SDL_GetWindowSurface(window);
                                          renderer = SDL_CreateSoftwareRenderer(surface);
                                          /* Clear the rendering surface with the specified color */
                                          SDL_SetRenderDrawColor(renderer, 255, 182, 193, 0xFF);
                                          SDL_RenderClear(renderer);

                                       }

                                              if ((f.type == SDL_KEYDOWN) && (f.key.keysym.sym == SDLK_ESCAPE)) {
                                                       exit(0);
                                            #ifdef __EMSCRIPTEN__
                                                        emscripten_cancel_main_loop();
                                            #endif
                                                        return 0;
                                                    }

                                              if (f.type == SDL_QUIT) {
                                                        exit(0);
                                            #ifdef __EMSCRIPTEN__
                                                        emscripten_cancel_main_loop();
                                            #endif
                                                    }


                                    }


                                   }

                        }


                            if ((k.type == SDL_KEYDOWN) && (k.key.keysym.sym == SDLK_ESCAPE)) {
                                           exit(0);
                                #ifdef __EMSCRIPTEN__
                                            emscripten_cancel_main_loop();
                                #endif
                                            return 0;
                                        }

                                   if (k.type == SDL_QUIT) {
                                            exit(0);
                                #ifdef __EMSCRIPTEN__
                                            emscripten_cancel_main_loop();
                                #endif

                                        }

                            if ((k.type == SDL_WINDOWEVENT) && (k.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)) {

                                          SDL_DestroyRenderer(renderer);

                                          surface = SDL_GetWindowSurface(window);
                                          renderer = SDL_CreateSoftwareRenderer(surface);
                                          /* Clear the rendering surface with the specified color */
                                          SDL_SetRenderDrawColor(renderer, 255, 182, 193, 0xFF);
                                          SDL_RenderClear(renderer);
                                       }

                   }


                }

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
            printf("\n\nStep has reached designated count, program terminate\n");
            while(1){loop();
            }

            //system("pause");
            goto end;
        }

        evo();                                                  //evloution
        step_d++;

    }
    end:
    SDL_Quit();
}
