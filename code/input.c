typedef struct InputKey
{
    bool down;
    bool previous;
}
InputKey;

typedef struct Input
{
    InputKey *keys;
    int       keys_count;
    const u8 *keyboard_state;
    char     *text;
    int       text_size;
}
Input;

Input input = {0};

bool setup_input()
{
    input.keyboard_state = SDL_GetKeyboardState(&input.keys_count); 
    input.keys = malloc(input.keys_count * sizeof(*input.keys));
    memset(input.keys, 0, input.keys_count * sizeof(*input.keys));

    input.text_size = 64;
    input.text = malloc(input.text_size);

    return true;
}

void update_input()
{
    for (int i = 0; i < input.keys_count; ++i) {
        input.keys[i].previous = input.keys[i].down;
        input.keys[i].down = input.keyboard_state[i];
    }
}

void reset_text_input()
{
    input.text[0] = '\0';
}

bool key_down(const char *keyname) 
{
    int i = SDL_GetScancodeFromName(keyname);
    return input.keys[i].down;
}

bool key_up(const char *keyname) 
{
    int i = SDL_GetScancodeFromName(keyname);
    return !input.keys[i].down;
}

bool key_just_down(const char *keyname) 
{
    int i = SDL_GetScancodeFromName(keyname);
    return input.keys[i].down && !input.keys[i].previous;
}

bool key_just_up(const char *keyname) 
{
    int i = SDL_GetScancodeFromName(keyname);
    return !input.keys[i].down && input.keys[i].previous;
}

void start_text_input()
{
    SDL_StartTextInput();
}

char *get_text_input()
{
    return input.text;
}

void stop_text_input()
{
    SDL_StopTextInput();
}
