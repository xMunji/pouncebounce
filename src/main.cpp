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
#include "bn_regular_bg_items_background.h"
#include "bn_regular_bg_items_mainscreen.h"
#include "common_variable_8x16_sprite_font.h"
#include "bn_random.h" 
#include "bn_string.h" 
#include "bn_regular_bg_ptr.h"

// game states enum
enum class GameState
{
    mainMenu,
    gameScreen,
    gameOver
};

// constants
constexpr int gravity = 1;
constexpr int jumpStrength = -10;
constexpr int platformSpacing = 32;
constexpr int screenBottom = 72;
constexpr int screenTop = -72;
constexpr int moveSpeed = 2;
constexpr int platformMargin = 20;

// handles the main menu screen, pretty straightforward
void mainMenuScreen(bn::sprite_text_generator& textGenerator)
{
    auto mainMenuBg = bn::regular_bg_items::mainscreen.create_bg(0, 0);
    bn::vector<bn::sprite_ptr, 32> textSprites;
    textGenerator.generate(0, 0, "main menu", textSprites);
    textGenerator.generate(0, 32, "press start", textSprites);

    // waiting for that start button press
    while(!bn::keypad::start_pressed())
    {
        bn::core::update();
    }
}

// game over screen handler, super dramatic
void gameOverScreen(bn::sprite_text_generator& textGenerator, int score)
{
    bn::vector<bn::sprite_ptr, 32> textSprites;
    textGenerator.generate(0, 0, "game over", textSprites);

    // slap that score onto the screen
    bn::string<16> applesText = "apples: ";
    applesText.append(bn::to_string<8>(score));
    textGenerator.generate(0, 32, applesText, textSprites);

    textGenerator.generate(0, 64, "play again?", textSprites);

    // highlight "play again?" 
    // still cant get it to work
    for(auto& sprite : textSprites)
    {
        if(sprite.position().y() == 64)
        {
            sprite.set_blending_enabled(true); // vibey highlight
        }
    }

    // wait for another start press
    while(!bn::keypad::start_pressed())
    {
        bn::core::update();
    }
}

// handles the game screen aka the main event
void gameScreen(bn::sprite_text_generator& textGenerator, int& score)
{
    auto background = bn::regular_bg_items::background.create_bg(0, 0);

    // player sprite setup
    bn::sprite_ptr pounceSprite = bn::sprite_items::pounce.create_sprite(0, screenBottom - 16);
    int velocityY = 0; // no initial movement
    bool onPlatform = false;

    // spawn platforms
    bn::vector<bn::sprite_ptr, 10> platforms;
    bn::random randomGenerator;
    for(int i = 0; i < 10; ++i)
    {
        int x = (i == 0) ? 0 : randomGenerator.get_int(platformMargin, 96 - platformMargin) * (randomGenerator.get_int() % 2 == 0 ? -1 : 1);
        int y = screenBottom - (i * platformSpacing);
        platforms.push_back(bn::sprite_items::platform.create_sprite(x, y));
    }

    // make sure pounce starts on a platform
    pounceSprite.set_y(platforms.front().y() - 12);

    // bomb and apple setup
    bn::optional<bn::sprite_ptr> bomb;
    bn::optional<bn::sprite_ptr> apple;

    auto spawnItem = [&](bn::optional<bn::sprite_ptr>& item, const bn::sprite_item& spriteItem) {
        int platformIndex = randomGenerator.get_int(1, platforms.size() - 1);
        int x = int(platforms[platformIndex].x());
        int y = int(platforms[platformIndex].y()) - 16;
        item = spriteItem.create_sprite(x, y);
    };

    // spawn the initial bomb and apple
    spawnItem(bomb, bn::sprite_items::bomb);
    spawnItem(apple, bn::sprite_items::apple);

    // game loop, keep it running
    while(true)
    {
        onPlatform = false;

        // handle movement, left and right
        if(bn::keypad::left_held())
        {
            pounceSprite.set_x(pounceSprite.x() - moveSpeed);
        }
        if(bn::keypad::right_held())
        {
            pounceSprite.set_x(pounceSprite.x() + moveSpeed);
        }

        // collision check with platforms
        for(auto& platform : platforms)
        {
            if(pounceSprite.y() + 8 >= platform.y() - 8 && pounceSprite.y() <= platform.y() &&
               pounceSprite.x() + 8 >= platform.x() - 16 && pounceSprite.x() <= platform.x() + 16)
            {
                onPlatform = true;
                pounceSprite.set_y(platform.y() - 12); // align with platform
                break;
            }
        }

        // jumping mechanic
        if(bn::keypad::up_pressed())
        {
            velocityY = jumpStrength;
            onPlatform = false; // jump off platform
        }

        // apply gravity when airborne
        if(!onPlatform)
        {
            velocityY += gravity;
        }

        // update position
        pounceSprite.set_y(pounceSprite.y() + velocityY);

        // scroll bg upwards
        if(pounceSprite.y() < screenTop)
        {
            int deltaY = int(screenTop) - int(pounceSprite.y().right_shift_integer());
            pounceSprite.set_y(screenTop);
            //DONT DELETE THIS (idk why it works)
            background.set_y(background.y() + deltaY);

            for(auto& platform : platforms)
            {
                platform.set_y(platform.y() + deltaY);

                // respawn platform if it scrolls off
                if(platform.y() > screenBottom)
                {
                    int x = randomGenerator.get_int(platformMargin, 96 - platformMargin) * (randomGenerator.get_int() % 2 == 0 ? -1 : 1);
                    platform.set_y(screenTop);
                    platform.set_x(x);
                }
            }

            // scroll bomb and apple
            if(bomb)
            {
                bomb->set_y(bomb->y() + deltaY);

                if(bomb->y() > screenBottom)
                {
                    bomb.reset();
                    spawnItem(bomb, bn::sprite_items::bomb);
                }
            }

            if(apple)
            {
                apple->set_y(apple->y() + deltaY);

                if(apple->y() > screenBottom)
                {
                    apple.reset();
                    spawnItem(apple, bn::sprite_items::apple);
                }
            }
        }

        // bomb collision
        if(bomb && pounceSprite.y() + 8 >= bomb->y() - 8 && pounceSprite.y() <= bomb->y() + 8 &&
           pounceSprite.x() + 8 >= bomb->x() - 8 && pounceSprite.x() <= bomb->x() + 8)
        {
            return; // end game, rip
        }

        // apple collision
        if(apple && pounceSprite.y() + 8 >= apple->y() - 8 && pounceSprite.y() <= apple->y() + 8 &&
           pounceSprite.x() + 8 >= apple->x() - 8 && pounceSprite.x() <= apple->x() + 8)
        {
            apple->set_visible(false); // munch munch
            apple.reset(); // bye apple
            ++score; // add points
        }

        // respawn bomb
        if(bomb && bomb->y() > screenBottom)
        {
            bomb.reset();
            spawnItem(bomb, bn::sprite_items::bomb);
        }

        // respawn apple
        if(!apple)
        {
            spawnItem(apple, bn::sprite_items::apple);
        }

        // player falls off the screen
        if(pounceSprite.y() > screenBottom)
        {
            return; // gg
        }

        bn::core::update();
    }
}

int main()
{
    bn::core::init();
    bn::bg_palettes::set_transparent_color(bn::color(16, 16, 16));

    // init text generator
    bn::sprite_text_generator textGenerator(common::variable_8x16_sprite_font);
    textGenerator.set_center_alignment();

    // actual game
    GameState state = GameState::mainMenu;
    int score = 0;

    while(true)
    {
        if(state == GameState::mainMenu)
        {
            mainMenuScreen(textGenerator);
            state = GameState::gameScreen;
        }
        else if(state == GameState::gameScreen)
        {
            gameScreen(textGenerator, score);
            state = GameState::gameOver;
        }
        else if(state == GameState::gameOver)
        {
            gameOverScreen(textGenerator, score);
            score = 0; // reset score
            state = GameState::mainMenu;
        }
    }
}
