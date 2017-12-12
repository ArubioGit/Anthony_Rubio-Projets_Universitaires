/*
 *
 * ACTION.H
 * Moignot Nicolas, Rubio Anthony
 * S2A 2017 - Projet POO
 *
 */

#ifndef ACTION_H
#define ACTION_H

#include "Character.h"

class Action
{
    private:
        Character * m_character;
        sf::Vector2f m_position;
        sf::Sprite m_sprite;
        sf::Texture m_texture;
        Action_Type m_type;
        bool m_new = false;

        void make_forward(std::array<std::array<Case *, 18>, 9> & cases);
        void make_rotate_left();
        void make_rotate_right();
        void make_switch_on();
    public:
        Action(Action * action, sf::Vector2f & mouse);
        Action(Action_Type type, Character * character);
        ~Action();

        void draw(sf::RenderWindow & window);
        bool contains(sf::Vector2f & mouse);
        bool contains_border(sf::Vector2f & mouse);

        void make(std::array<std::array<Case *, 18>, 9> & cases);

        Character * get_character()
            { return m_character; }
        sf::Vector2f get_position()
            { return m_position; }
        sf::Texture get_texture()
            { return m_texture; }
        Action_Type get_type()
            { return m_type; }
        bool is_new()
            { return m_new; }
        void set_added()
            { m_new = false; }
        void set_position(sf::Vector2f position)
            { m_position = position; m_sprite.setPosition(position); }
        void set_position_sprite(sf::Vector2f position)
            { m_sprite.setPosition(position); }
};

#endif // ACTION_H
