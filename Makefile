# Compilateur
CC = gcc

# Chemins vers SDL
SDL_PATH = C:\Users\rapha\Documents\SDL\x86_64-w64-mingw32
CFLAGS = -I"$(SDL_PATH)\include"
LDFLAGS = -L"$(SDL_PATH)\lib" -lSDL3

# Fichiers source et exécutable
SRC = main.c   # ajoute ici tous tes fichiers .c
OUT = main.exe

# Règle principale
all:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(LDFLAGS)

# Lancer le programme après compilation
run: all
	./$(OUT)

# Supprimer l'exécutable
clean:
	del $(OUT)