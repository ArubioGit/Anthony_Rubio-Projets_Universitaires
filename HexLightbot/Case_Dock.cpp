/*
 *
 * CASE_DOCK.CPP
 * Moignot Nicolas, Rubio Anthony
 * S2A 2017 - Projet POO
 *
 */

#include "Case_Dock.h"

Case_Dock::Case_Dock()
{
    m_cases.push_back(new Case({ 1080, 250 }, Case_State::NORMAL, true));
    m_cases.push_back(new Case({ 1080, 350 }, Case_State::ON, true));
    m_cases.push_back(new Case({ 1080, 450 }, Case_State::OFF, true));
    m_rect.setPosition({ 900, 20 });
    m_rect.setSize({ 360, 755 });
    m_rect.setFillColor(sf::Color(0, 0, 0, 100));
}

Case_Dock::~Case_Dock()
{
    for(Case * object : m_cases)
        delete object;
}

/* ========== COMMON ========== */

bool Case_Dock::contains(sf::Vector2f & mouse)
{
    return m_rect.getGlobalBounds().contains(mouse);
}

void Case_Dock::draw(sf::RenderWindow & window)
{
    window.draw(m_rect);
    for(Case * object : m_cases)
        object->draw(window, true);
}

void Case_Dock::mouse_button_pressed(sf::Vector2f & mouse, Case * & m_selected_case)
{
    for(Case * object : m_cases) {
        if(object->contains(mouse))
            m_selected_case = new Case(mouse, object->get_state(), true);
    }
}
