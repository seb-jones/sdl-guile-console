Font    *font   = NULL;

bool setup_game()
{
    // Font
    font = load_bitmap_font("assets/font.bmp", 6, 8, 16, 6, ' ');
    if (!font)
        return false;

    if (!setup_console(font))
        return false;

    return true;
}

void destroy_game()
{
    destroy_console();
    destroy_font(font);
}

// Returns false when the program should end
bool update_game()
{
    if (key_just_down(quit_key))
        return false;

    if (console.is_open)
        update_console(font);
    else if (key_just_down(console_key))
        open_console();

    return true;
}
