/* Display [Kanizsa square](https://puzzlewocky.com/optical-illusions/kanizsa-square-and-triangle-illusions/) */

/* Copyright © Christophe Pallier

   Time-stamp: <2021-06-09 11:45:43 christophe@pallier.org> 

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
   The Software is provided "as is", without warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose and noninfringement. In no event shall the authors or copyright holders be liable for any claim, damages or other liability, whether in an action of contract, tort or otherwise, arising from, out of or in connection with the software or the use or other dealings in the Software.
*/


/* Compile with:

   cc -I/usr/include/SDL2 -D_REENTRANT    kanisza_square.c  -lSDL2  -lSDL2_gfx -o kanisza_square

*/


#include <stdio.h>
#include <stdlib.h>             // exit
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

SDL_Window *sdlWindow;
SDL_Renderer *sdlRenderer;

void create_window(char *title, int width, int height, Uint32 background_color);
void fill_window(Uint32 background_color);
void update_window();
void destroy_window();
void wait_for_key_press();

int main()
{
        // ARGB codes for colors
        Uint32 BLACK = 0xFF000000;
        Uint32 WHITE = 0xFFFFFFFF;

        int WINDOW_WIDTH = 1280;
        int WINDOW_HEIGHT = 1280;

        create_window("Kanizsa square", WINDOW_WIDTH, WINDOW_HEIGHT, WHITE);
        fill_window(WHITE);

        // Circles' size and positions
        int radius = 150;
        int shift = 200;

        int center_x = WINDOW_WIDTH / 2;
        int center_y = WINDOW_HEIGHT / 2;

        int left = center_x - shift;
        int right = center_x + shift;
        int top = center_y - shift;
        int bottom = center_y + shift;

        if (filledCircleColor(sdlRenderer, left, top, radius, BLACK) ||
            filledCircleColor(sdlRenderer, right, top, radius, BLACK) ||
            filledCircleColor(sdlRenderer, left, bottom, radius, BLACK) ||
            filledCircleColor(sdlRenderer, right, bottom, radius, BLACK) ||
            boxColor(sdlRenderer, left, top, right, bottom, WHITE)) {
              printf("SDL_gfx drawing failed: %s\n", SDL_GetError());
            }

        update_window();
        wait_for_key_press();
        destroy_window();
        return EXIT_SUCCESS;
}

/***************** support functions *************************************/
int is_relevant_event(void *nada, SDL_Event * event)
/* we want to filter out any event which is not  Close window or keypress */
{
        if (event->type == SDL_QUIT || event->type == SDL_KEYDOWN)
                return 1;
        return 0;
}

void create_window(char* title, int width, int height, Uint32 background_color)
{

        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
                printf("SDL initialization failed: %s", SDL_GetError());
                exit(EXIT_FAILURE);
        }

        sdlWindow =
            SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, width, height, 0);

        if (sdlWindow == NULL) {
                printf("SDL_CreateWindow failed: %s", SDL_GetError());
                exit(EXIT_FAILURE);
        }

        sdlRenderer =
            SDL_CreateRenderer(sdlWindow, -1,
                               SDL_RENDERER_ACCELERATED |
                               SDL_RENDERER_PRESENTVSYNC);

        if (sdlRenderer == NULL) {
                printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
                exit(EXIT_FAILURE);
        }


        uint8_t byte3 = (uint8_t) (background_color >> 24);
        uint8_t byte2 = (uint8_t) (background_color >> 16);
        uint8_t byte1 = (uint8_t) (background_color >> 8);
        uint8_t byte0 = (uint8_t) background_color;

        SDL_SetRenderDrawColor(sdlRenderer, byte0, byte1, byte2, byte3);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderPresent(sdlRenderer);

        SDL_SetEventFilter(is_relevant_event, NULL);
}

void update_window()
{
        SDL_RenderPresent(sdlRenderer);
}

void fill_window(Uint32 background_color)
{
        uint8_t byte3 = (uint8_t) (background_color >> 24);
        uint8_t byte2 = (uint8_t) (background_color >> 16);
        uint8_t byte1 = (uint8_t) (background_color >> 8);
        uint8_t byte0 = (uint8_t) background_color;

        SDL_SetRenderDrawColor(sdlRenderer, byte0, byte1, byte2, byte3);
        SDL_RenderClear(sdlRenderer);
}

void destroy_window()
{
        SDL_DestroyRenderer(sdlRenderer);
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
}

void wait_for_key_press()
{
        SDL_Event event;
        int running = 1;

        while (running) {
                while (SDL_PollEvent(&event)) {
                        switch (event.type) {
                        case SDL_QUIT:
                                running = 0;
                                break;
                        case SDL_KEYDOWN:
                                running = 0;
                                break;
                        }

                }
                SDL_Delay(100);
        }
}
