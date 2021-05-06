Main: FINAL.o logic.o
	gcc -o Main FINAL.o logic.o -L E:\CODEBLOCKS\SDL\SDL2-2.0.14\x86_64-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 

FINAL.o: FINAL.c LGSDL.h
	gcc -c FINAL.c -I E:\CODEBLOCKS\SDL\SDL2-2.0.14\x86_64-w64-mingw32\include\SDL2

logic.o: logic.c LGSDL.h
	gcc -c logic.c -I E:\CODEBLOCKS\SDL\SDL2-2.0.14\x86_64-w64-mingw32\include\SDL2