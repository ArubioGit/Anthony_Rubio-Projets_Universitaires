/*
 *
 * GAME.H
 * Moignot Nicolas, Rubio Anthony
 * S2A 2017 - Projet POO
 *
 */

#ifndef GAME_H
#define GAME_H

#include "Application.h"
#include "Button.h"
#include "Level.h"

class Game : public Application
{
    private:
        App m_app_current;
        App m_app_next;
        sf::Sprite m_background;
        std::map<std::string, Button *> m_buttons;
        sf::Font m_font;
        Level * m_level;
        sf::Text m_text;
        sf::Text m_text_score;
        sf::Texture m_texture_background;
    public:
        Game();
        ~Game();

        void loop() override;
        void mouse_button_pressed();
        void mouse_button_released();
        void mouse_moved();

        void delete_all();

        void init_MAIN();
        void mouse_released_MAIN();
        void draw_MAIN();

        void init_PLAY(std::string file);
        void mouse_moved_PLAY();
        void mouse_pressed_PLAY();
        void mouse_released_PLAY();
        void draw_PLAY();

        void init_EDIT(std::string file);
        void mouse_released_EDIT();
        void draw_EDIT();

        void init_SELECT(App next);
        void mouse_released_SELECT();
        void draw_SELECT();

        void init_END_LEVEL(int score);
        void mouse_released_END_LEVEL();
        void draw_END_LEVEL();
};

#endif // GAME_H
