/*
 *
 * CHARACTER.H
 * Moignot Nicolas, Rubio Anthony
 * S2A 2017 - Projet POO
 *
 */

#ifndef CARACTERE_H
#define CARACTERE_H

#include "Application.h"
#include "Case.h"

class Character
{
    private:
        bool m_click = false;
        sf::Sprite m_sprite;
        Direction m_direction;
        Direction m_direction_start;
        Case * m_position;
        Case * m_position_start;
        sf::Vector2f m_position_mouse_tmp;
        sf::Texture m_texture;
    public:
        Character(Case * position, Direction direction);

        bool contains(sf::Vector2f & mouse);
        bool contains_border(sf::Vector2f & mouse);
        void draw(sf::RenderWindow & window);
        bool mouse_button_pressed(sf::Vector2f & mouse);
        bool mouse_button_released(sf::Vector2f & mouse, std::array<std::array<Case *, 18>, 9> & cases);

        void die();
        void move_forward(std::array<std::array<Case *, 18>, 9> & cases);
        void reset();

        bool is_clicked()
            { return m_click; }
        Direction get_direction()
            { return m_direction; }
        Case * get_position()
            { return m_position; }
        void set_direction(Direction direction);
        void set_position_sprite(sf::Vector2f & mouse)
            { m_sprite.setPosition(mouse); }
};

#endif // CARACTERE_H
