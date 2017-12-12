/*
 *
 * BUTTON.H
 * Moignot Nicolas, Rubio Anthony
 * S2A 2017 - Projet POO
 *
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "Application.h"

class Button
{
    private:
        bool m_click = false;
        bool m_display;
        sf::Sprite m_button;
        sf::RectangleShape m_rect;
        sf::Text m_text;
        sf::Texture m_texture;
        sf::Texture m_texture_onclick;
        Button_Type m_type;
    public:
        Button(sf::Vector2f position, std::string image);
        Button(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Font & font);
        Button(sf::Vector2f position, sf::Vector2i size, sf::Vector2i pos_on_image, sf::Image & image, bool display);

        bool contains(sf::Vector2f & mouse);
        void draw(sf::RenderWindow & window);
        bool mouse_button_pressed(sf::Vector2f & mouse);
        bool mouse_button_released(sf::Vector2f & mouse);

        void set_display(bool display)
            { m_display = display; }
};

#endif // BUTTON_H
