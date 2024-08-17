#include <iostream>
#include <SDL2/SDL.h>

constexpr uint32_t SCREEN_WIDTH = 800;
constexpr uint32_t SCREEN_HEIGHT = 600;

struct Input {
    bool keyState[SDL_NUM_SCANCODES];
};

struct Engine {
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    Input input = {};
    bool windowShouldClose = false;
};

// Init
bool initEngine(Engine &engine);

// I/O Related
void handleEvents(Engine &engine);
void updateKeyState(Input &input, const SDL_Event &event);
bool isKeyPressed(const Engine &engine, SDL_Scancode key);

// Rendering
void render(const Engine &engine);

// Quit
void quitEngine(Engine &engine);

int main(int argc, char* args[])
{
    Engine engine;
    if (!initEngine(engine)) {
        return -1;
    };

    while (!engine.windowShouldClose) {
        handleEvents(engine);
        render(engine);

        if (isKeyPressed(engine, SDL_SCANCODE_W)) {
            std::cout << "W key is being pressed." << std::endl;
        }
    }

    quitEngine(engine);
    return 0;
}

bool initEngine(Engine &engine) {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    engine.window = SDL_CreateWindow("Pong Powered By SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        800, 600, SDL_WINDOW_SHOWN);
    if (!engine.window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        return false;
    }

    engine.renderer = SDL_CreateRenderer(engine.window, -1, SDL_RENDERER_ACCELERATED);
    if (!engine.renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        return false;
    }

    return true;
}

void handleEvents(Engine &engine) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            engine.windowShouldClose = true;
        }
        updateKeyState(engine.input, event);
    }
}

void updateKeyState(Input &input, const SDL_Event &event) {
    if (event.type == SDL_KEYDOWN) {
        input.keyState[event.key.keysym.scancode] = true;
    } else if (event.type == SDL_KEYUP) {
        input.keyState[event.key.keysym.scancode] = false;
    }
}

bool isKeyPressed(const Engine &engine, const SDL_Scancode key) {
    return engine.input.keyState[key];
}


void render(const Engine &engine) {
    SDL_SetRenderDrawColor(engine.renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(engine.renderer);
    SDL_RenderPresent(engine.renderer);
}


void quitEngine(Engine &engine) {
    SDL_DestroyRenderer(engine.renderer);
    engine.renderer = nullptr;
    SDL_DestroyWindow(engine.window);
    engine.window = nullptr;
    SDL_Quit();
}