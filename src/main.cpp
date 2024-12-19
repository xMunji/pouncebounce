#include "bn_core.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"
#include "bn_bg_palettes.h"
#include "bn_keypad.h"
#include "bn_sprite_items_pounce.h"
#include "bn_sprite_items_platform.h"
#include "bn_sprite_items_bomb.h"
#include "bn_sprite_items_apple.h"
#include "common_variable_8x16_sprite_font.h"
#include "bn_random.h" // Include Butano random header
#include "bn_string.h" // For string conversions

// Enum for managing game states
enum class GameState
{
    MAIN_MENU,
    GAME_SCREEN,
    GAME_OVER
};

// Constants
constexpr int gravity = 1;
constexpr int jump_strength = -10;
constexpr int platform_spacing = 32;
constexpr int screen_bottom = 72;
constexpr int screen_top = -72;
constexpr int move_speed = 2;
constexpr int platform_margin = 20;

// Function to handle the Main Menu screen
void main_menu_screen(bn::sprite_text_generator& text_generator)
{
    bn::vector<bn::sprite_ptr, 32> text_sprites;
    text_generator.generate(0, 0, "Main Menu", text_sprites);
    text_generator.generate(0, 32, "Press START", text_sprites);

    // Wait for the user to press START
    while(!bn::keypad::start_pressed())
    {
        bn::core::update();
    }
}

// Function to handle the Game Over screen
void game_over_screen(bn::sprite_text_generator& text_generator, int score)
{
    bn::vector<bn::sprite_ptr, 32> text_sprites;
    text_generator.generate(0, 0, "Game Over", text_sprites);

    // Safely construct the "Apples" string
    bn::string<16> apples_text = "Apples: ";
    apples_text.append(bn::to_string<8>(score));
    text_generator.generate(0, 32, apples_text, text_sprites);

    text_generator.generate(0, 64, "Play again?", text_sprites);

    // Highlight "Play again?" text
    for(auto& sprite : text_sprites)
    {
        if(sprite.position().y() == 64)
        {
            sprite.set_blending_enabled(true); // Add visual emphasis instead of a red palette
        }
    }

    // Wait for the user to press START
    while(!bn::keypad::start_pressed())
    {
        bn::core::update();
    }
}

// Function to handle the Game Screen
void game_screen(bn::sprite_text_generator& text_generator, int& score)
{
    // Player sprite
    bn::sprite_ptr pounce_sprite = bn::sprite_items::pounce.create_sprite(0, screen_bottom - 16);
    int velocity_y = 0; // Initial velocity
    bool on_platform = false;

    // Platforms
    bn::vector<bn::sprite_ptr, 10> platforms;
    bn::random random_generator;
    for(int i = 0; i < 10; ++i)
    {
        int x = (i == 0) ? 0 : random_generator.get_int(platform_margin, 96 - platform_margin) * (random_generator.get_int() % 2 == 0 ? -1 : 1);
        int y = screen_bottom - (i * platform_spacing);
        platforms.push_back(bn::sprite_items::platform.create_sprite(x, y));
    }

    // Ensure pounce starts on the center platform
    pounce_sprite.set_y(platforms.front().y() - 12);

    // Bomb and apple spawn setup
    bn::optional<bn::sprite_ptr> bomb;
    bn::optional<bn::sprite_ptr> apple;

    auto spawn_item = [&](bn::optional<bn::sprite_ptr>& item, const bn::sprite_item& sprite_item) {
        int platform_index = random_generator.get_int(1, platforms.size() - 1);
        int x = int(platforms[platform_index].x());
        int y = int(platforms[platform_index].y()) - 16;
        item = sprite_item.create_sprite(x, y);
    };

    // Spawn initial bomb and apple
    spawn_item(bomb, bn::sprite_items::bomb);
    spawn_item(apple, bn::sprite_items::apple);

    // Game loop
    while(true)
    {
        on_platform = false;

        // Handle left and right movement
        if(bn::keypad::left_held())
        {
            pounce_sprite.set_x(pounce_sprite.x() - move_speed);
        }
        if(bn::keypad::right_held())
        {
            pounce_sprite.set_x(pounce_sprite.x() + move_speed);
        }

        // Check for collision with platforms
        for(auto& platform : platforms)
        {
            if(pounce_sprite.y() + 8 >= platform.y() - 8 && pounce_sprite.y() <= platform.y() &&
               pounce_sprite.x() + 8 >= platform.x() - 16 && pounce_sprite.x() <= platform.x() + 16)
            {
                on_platform = true;
                pounce_sprite.set_y(platform.y() - 12); // Align pounce on top of the platform
                break;
            }
        }

        // Handle jumping
        if(bn::keypad::up_pressed())
        {
            velocity_y = jump_strength;
            on_platform = false; // Leave platform when jumping
        }

        // Apply gravity if not on a platform
        if(!on_platform)
        {
            velocity_y += gravity;
        }

        // Update pounce position based on velocity
        pounce_sprite.set_y(pounce_sprite.y() + velocity_y);

        // Check for collision with bomb
        if(bomb && pounce_sprite.y() + 8 >= bomb->y() - 8 && pounce_sprite.y() <= bomb->y() + 8 &&
           pounce_sprite.x() + 8 >= bomb->x() - 8 && pounce_sprite.x() <= bomb->x() + 8)
        {
            return; // End the game
        }

        // Check for collision with apple
        if(apple && pounce_sprite.y() + 8 >= apple->y() - 8 && pounce_sprite.y() <= apple->y() + 8 &&
           pounce_sprite.x() + 8 >= apple->x() - 8 && pounce_sprite.x() <= apple->x() + 8)
        {
            apple->set_visible(false); // Collect the apple
            apple.reset(); // Remove apple from screen
            ++score; // Increase score
        }

        // Respawn bomb if it goes off-screen
        if(bomb && bomb->y() > screen_bottom)
        {
            bomb.reset();
            spawn_item(bomb, bn::sprite_items::bomb);
        }

        // Respawn apple if it goes off-screen or collected
        if(!apple)
        {
            spawn_item(apple, bn::sprite_items::apple);
        }

        // Check if the player falls off the screen
        if(pounce_sprite.y() > screen_bottom)
        {
            return; // End the game
        }

        // Scroll platforms if player moves up
        if(pounce_sprite.y() < screen_top)
        {
            int delta_y = int(screen_top) - int(pounce_sprite.y().right_shift_integer());
            pounce_sprite.set_y(screen_top);

            for(auto& platform : platforms)
            {
                platform.set_y(platform.y() + delta_y);

                // Respawn platform if it goes off-screen
                if(platform.y() > screen_bottom)
                {
                    int x = random_generator.get_int(platform_margin, 96 - platform_margin) * (random_generator.get_int() % 2 == 0 ? -1 : 1);
                    platform.set_y(screen_top);
                    platform.set_x(x);
                }
            }

            // Scroll bomb and apple
            if(bomb)
            {
                bomb->set_y(bomb->y() + delta_y);

                if(bomb->y() > screen_bottom)
                {
                    bomb.reset();
                    spawn_item(bomb, bn::sprite_items::bomb);
                }
            }

            if(apple)
            {
                apple->set_y(apple->y() + delta_y);

                if(apple->y() > screen_bottom)
                {
                    apple.reset();
                    spawn_item(apple, bn::sprite_items::apple);
                }
            }
        }

        bn::core::update();
    }
}

int main()
{
    bn::core::init();
    bn::bg_palettes::set_transparent_color(bn::color(16, 16, 16));

    // Initialize the text generator
    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    text_generator.set_center_alignment();

    // State management loop
    GameState state = GameState::MAIN_MENU;
    int score = 0;

    while(true)
    {
        if(state == GameState::MAIN_MENU)
        {
            main_menu_screen(text_generator);
            state = GameState::GAME_SCREEN;
        }
        else if(state == GameState::GAME_SCREEN)
        {
            game_screen(text_generator, score);
            state = GameState::GAME_OVER;
        }
        else if(state == GameState::GAME_OVER)
        {
            game_over_screen(text_generator, score);
            score = 0; // Reset score for the next game
            state = GameState::MAIN_MENU;
        }
    }
}
