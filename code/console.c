typedef struct Console
{
    Font  *font;
    char  *input;
    char  *output;
    size_t input_size;
    bool   is_open;
}
Console;

Console console = {0};

bool setup_console(Font *font)
{
    console.font = font;

    console.input_size = 100;
    console.input = malloc(console.input_size + 1);
    console.input[0] = '\0';

    return true;
}

void destroy_console()
{
    free(console.input);
}

void reset_console_input()
{
    strcpy(console.input, "$ ");
}

void open_console()
{
    reset_console_input();
    console.is_open = true;
    start_text_input();
}

void close_console()
{
    stop_text_input();
    console.is_open = false;
}

void update_console()
{
    char *input_text = get_text_input();

    if (*input_text > '\0' && *input_text != '`') {
        strcat(console.input, input_text);
        reset_text_input();
    }

    int console_input_length = strlen(console.input);
    if (key_just_down(backspace_key) && console_input_length > 2)
        console.input[console_input_length - 1] = '\0';
    else if (key_just_down(okay_key)) {
        SCM result = scm_c_eval_string(console.input + 2);

        console.output = scm_to_locale_string(
            scm_object_to_string(
                result,
                SCM_UNDEFINED
                )
            );

        reset_console_input();
    }

    draw_wrapped_string(console.font, console.input, 0, 0,
            render_width);

    if (console.output) {
        draw_wrapped_string(console.font, console.output,
                0, console.font->glyph_height + 2, render_width);
    }

    if (key_just_down(console_key))
        close_console();
}
