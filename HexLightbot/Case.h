/*
 *
 * CASE.H
 * Moignot Nicolas, Rubio Anthony
 * S2A 2017 - Projet POO
 *
 */

#ifndef CASE_H
#define CASE_H

#include "Application.h"

class Case
{
    private:
        sf::Vector2f m_coordonates;
        sf::Sprite m_sprite;
        Case_State m_state;
        Case_State m_state_start;
        sf::Texture m_texture;
    public:
        Case(sf::Vector2f coordonates, Case_State state, bool pixel_position);
        ~Case();

        bool contains(sf::Vector2f & mouse);
        void draw(sf::RenderWindow & window, bool editing);

        sf::Vector2f coordonates_to_pixels(sf::Vector2f coordonates);
        void switch_on();
        void reset();

        sf::Vector2f get_coordonates()
            { return m_coordonates; }
        sf::Vector2f get_position()
            { return m_sprite.getPosition(); }
        Case_State get_state()
            { return m_state; }
        void set_coordonates(sf::Vector2f coordonates, bool pixel_position);
        void set_state(Case_State state);
};

#endif // CASE_H
