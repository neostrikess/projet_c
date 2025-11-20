#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT *kbd = (KBDLLHOOKSTRUCT *)lParam;

        // Autoriser uniquement F12 pour quitter
        if (kbd->vkCode == VK_F12) {
            return CallNextHookEx(NULL, nCode, wParam, lParam);
        }

        // Bloquer toutes les autres touches
        return 1;  
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    if (result < 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("SDL3 Window", 0, 0, 1);
    if (window == NULL) {
        SDL_Log("Could not create window: %s", SDL_GetError());
        return -2;
    }
    renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) {
        SDL_Log("Could not create renderer: %s", SDL_GetError());
        return -3;
    }

    SDL_Log("SDL3 initialized successfully");

    SDL_Event event;
    int quit = 0;
    while (!quit) { 
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_QUIT:
                SDL_Log("SDL3 event quit");
                quit = 1;
                break;
        }
    }
    SDL_SetRenderDrawColor(renderer, 21, 13, 247, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(1); 
    }
     HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook, NULL, 0);

    if (!hook) {
        printf("Erreur lors de l'installation du hook.\n");
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {}

    UnhookWindowsHookEx(hook);
    return 0;

}