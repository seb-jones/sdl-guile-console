Font    *font   = NULL;

bool setup_game()
{
    // Font
    font = load_bitmap_font("assets/font.bmp", 6, 8, 16, 6, ' ');
    if (!font)
        return false;

    return true;
}

// Returns false when the program should end
bool update_game()
{
    if (key_just_down(quit_key))
        return false;

    draw_string(font, "Hello", 10, 10);

    return true;
}

void destroy_game()
{
    destroy_font(font);
}
