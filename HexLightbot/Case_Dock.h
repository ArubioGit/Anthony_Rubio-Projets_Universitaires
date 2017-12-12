/*
 *
 * CASE_DOCK.H
 * Moignot Nicolas, Rubio Anthony
 * S2A 2017 - Projet POO
 *
 */

#ifndef CASE_DOCK_H
#define CASE_DOCK_H

#include "Case.h"
#include "Character.h"

class Case_Dock
{
    private:
        std::vector<Case *> m_cases;
        sf::RectangleShape m_rect;
    public:
        Case_Dock();
        ~Case_Dock();

        bool contains(sf::Vector2f & mouse);
        void draw(sf::RenderWindow & window);
        void mouse_button_pressed(sf::Vector2f & mouse, Case * & m_selected_case);
};

#endif // CASE_DOCK_H
