#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;
int done;
int quit_all;

int pau;
int mode;
int auto_check;
int method;
int rw;
int rh;
int r,c;
int m_x;
int m_y;

int Height;
int Width;
int cell[8000][8000];



int Height;
int Width;
void HideCursor();
void gotoxy(int x,int y);
void startup();
void evo();
void store(const char *filename);
void load(const char *filename);
void DrawChessBoard(SDL_Renderer * renderer);
void loop();
void window_optimizer();
void respawn();
void death();
