#include "main.h"

int main(void)
{
    // Initialize SDL's video subsystem
    (void) fprintf(stdout, "[SDL] Initializing video system...\n");
    
    if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
    {
        (void) fprintf(stderr, "SDL_InitSubSystem() failed\n");
        return EXIT_FAILURE;
    }

    (void) fprintf(stdout, "\t-> Success!\n");


    // Create window
    (void) fprintf(stdout, "[SDL] Creating window...\n");

    SDL_Window *window = SDL_CreateWindow("SDL Test", 800, 600, 0);
    if (window == NULL)
    {
        (void) fprintf(stderr, "\t-> Error! SDL_CreateWindow() failed\n");
        (void) SDL_QuitSubSystem(SDL_INIT_VIDEO);
        (void) SDL_Quit();
        return EXIT_FAILURE;
    }

    (void) fprintf(stdout, "\t-> Success!\n");

    // Create renderer
    (void) fprintf(stdout, "[SDL] Creating renderer...\n");

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL)
    {
        (void) SDL_DestroyRenderer(renderer);
        (void) fprintf(stderr, "\t-> Error! SDL_CreateRenderer() failed\n");
        (void) SDL_QuitSubSystem(SDL_INIT_VIDEO);
        (void) SDL_Quit();
        return EXIT_FAILURE;
    }

    (void) fprintf(stdout, "\t->Success!\n");


    // Load texture
    SDL_Surface *surface = SDL_LoadBMP("data/spaceship.bmp");
    if (surface == NULL)
    {
        (void) fprintf(stderr, "SDL_LoadBMP() failed\n");
        (void) SDL_DestroyRenderer(renderer);
        (void) SDL_DestroyWindow(window);
        (void) SDL_QuitSubSystem(SDL_INIT_VIDEO);
        (void) SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        (void) fprintf(stderr, "SDL_CreateTextureFromSurface() failed\n");
        (void) SDL_DestroySurface(surface);
        (void) SDL_DestroyRenderer(renderer);
        (void) SDL_DestroyWindow(window);
        (void) SDL_QuitSubSystem(SDL_INIT_VIDEO);
        (void) SDL_Quit();
        return EXIT_FAILURE;
    }

    // The texture sprite is 128x128
    SDL_FRect srcrect = {0, 0, 128, 128};
    SDL_FRect dstrect = {0, 0, 128, 128};

    // Main game loop
    SDL_Event e;
    bool is_running = true;
    while (is_running)
    {
        // Update


        // Render
        if (!SDL_RenderClear(renderer))
        {
            // TODO: update me
            (void) fprintf(stderr, "SDL_RenderClear() failed\n");
        }

        if (!SDL_RenderTexture(renderer, texture, &srcrect, &dstrect))
        {
            // TODO: update me
            (void) fprintf(stderr, "SDL_RenderTexture() failed\n");
        }


        if (!SDL_RenderPresent(renderer))
        {
            // TODO: update me
            (void) fprintf(stderr, "SDL_RenderPresent() failed\n");
        }

        // Events
        while (SDL_PollEvent(&e))
        {
            // Exit the loop if the user presses Alt+F4, or the 'x' button
            if (e.type == SDL_EVENT_QUIT)
            {
                is_running = false;
            }

            // Handle keypresses
            // TODO: Replace arrow keys with rotate (transform?)
            else if (e.type == SDL_EVENT_KEY_DOWN)
            {
                switch (e.key.key)
                {
                    case SDLK_W:
                    case SDLK_UP:
                        dstrect.y -= 5;
                        break;
                    case SDLK_A:
                    case SDLK_LEFT:
                        dstrect.x -= 5;
                        break;
                    case SDLK_S:
                    case SDLK_DOWN:
                        dstrect.y += 5;
                        break;
                    case SDLK_D:
                    case SDLK_RIGHT:
                        dstrect.x += 5;
                        break;
                }
            }
        }
    }

    // Clean up & exit
    (void) fprintf(stdout, "[SDL] Cleaning up & shutting down...\n");
    (void) SDL_DestroyTexture(texture);
    (void) SDL_DestroySurface(surface);
    (void) SDL_DestroyRenderer(renderer);
    (void) SDL_DestroyWindow(window);
    (void) SDL_QuitSubSystem(SDL_INIT_VIDEO);
    (void) SDL_Quit();
    
    return EXIT_SUCCESS;
}
