#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "constants.hpp"

struct GameState
{
    int game_is_running = FALSE;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    int last_frame_time = 0;
} GameState;

// Sample ball to fuck around.
struct ball
{
    float x;
    float y;
    float width;
    float height;
} ball;

int initialize_window(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Error initializing SDL: \n";
        return FALSE;
    }

    GameState.window = SDL_CreateWindow(
        "Game Title",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS);

    if (!GameState.window)
    {
        std::cout << "Error creating SDL window.\n";
        return FALSE;
    }

    GameState.renderer = SDL_CreateRenderer(GameState.window, -1, 0);

    if (!GameState.renderer)
    {
        std::cout << "Error creating SDL renderer.\n";
        return FALSE;
    }

    return TRUE;
}

void process_input()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        GameState.game_is_running = FALSE;
        break;

    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
            GameState.game_is_running = FALSE;
        break;
    }
}

void setup()
{
    ball.x = 20;
    ball.y = 20;
    ball.width = 15;
    ball.height = 15;
}

void update()
{
    // Waste some time / sleep until we reach the target frame time length
    // while (!SDL_TICKS_PASSED(SDL_GetTicks(), last_frame_time + FRAME_TARGET_TIME))
    //     ;

    // Calculate how much we have to wait until we reach the target frame time
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - GameState.last_frame_time);

    // Only call delay if we are too fast to process this frame
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
        SDL_Delay(time_to_wait);

    // Get a delta time factor converted to seconds to be used to update my objects
    float delta_time = (SDL_GetTicks() - GameState.last_frame_time) / 1000.0f;

    // Logic to keep a fixed timestamp
    GameState.last_frame_time = SDL_GetTicks();

    ball.x += 50 * delta_time;
    ball.y += 50 * delta_time;
}

void render()
{
    SDL_SetRenderDrawColor(GameState.renderer, 0, 0, 0, 255);
    SDL_RenderClear(GameState.renderer);

    // Draw the game here
    SDL_Rect ball_rect = {
        (int)ball.x,
        (int)ball.y,
        (int)ball.width,
        (int)ball.height};

    SDL_SetRenderDrawColor(GameState.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(GameState.renderer, &ball_rect);

    SDL_RenderPresent(GameState.renderer);
}

void destroy_window()
{
    SDL_DestroyRenderer(GameState.renderer);
    SDL_DestroyWindow(GameState.window);
    SDL_Quit();
}

int main()
{
    GameState.game_is_running = initialize_window();

    setup();

    while (GameState.game_is_running)
    {
        process_input();
        update();
        render();
    }

    destroy_window();

    return TRUE;
}