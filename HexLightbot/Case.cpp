/*
 *
 * CASE.CPP
 * Moignot Nicolas, Rubio Anthony
 * S2A 2017 - Projet POO
 *
 */

#include "Case.h"

using namespace std;

Case::Case(sf::Vector2f coordonates, Case_State state, bool pixel_position)
    : m_coordonates { coordonates }
    , m_state_start { state }
{
    set_state(state);
    set_coordonates(coordonates, pixel_position);
    if(m_state == Case_State::NONE)
        m_sprite.setColor(sf::Color(255, 255, 255, 50));
}

Case::~Case()
{}

/* ========== COMMON ========== */

bool Case::contains(sf::Vector2f & mouse)
{
    sf::FloatRect rect = { m_sprite.getPosition().x - 45, m_sprite.getPosition().y - 30, 90, 60 };
    return rect.contains(mouse);
}

void Case::draw(sf::RenderWindow & window, bool editing)
{
    if(m_state != Case_State::NONE || editing)
        window.draw(m_sprite);
}

/* ========== SPECIAL ========== */

sf::Vector2f Case::coordonates_to_pixels(sf::Vector2f coordonates)
{
    return { (float)(140 * (coordonates.x - 2) + (70 * ((int)coordonates.y % 2)) + 130), (float)(30 * (coordonates.y - 2) + 180) };
}

void Case::switch_on()
{
    if(m_state == Case_State::OFF)
        set_state(Case_State::ON);
    else if(m_state == Case_State::ON)
        set_state(Case_State::OFF);
}

void Case::reset()
{
    set_state(m_state_start);
}

void Case::set_coordonates(sf::Vector2f coordonates, bool pixel_position)
{
    m_coordonates = coordonates;
    if(pixel_position)
        m_sprite.setPosition(coordonates);
    else
        m_sprite.setPosition(coordonates_to_pixels(coordonates));
}

void Case::set_state(Case_State state)
{
    m_state = state;
    int x;
    switch(state) {
        case Case_State::ON:
            x = 200;
            break;
        case Case_State::OFF:
            x = 400;
            break;
        default:
            x = 0;
            break;
    }
    m_texture.loadFromFile("sprites/cases.png", { x, 0, 200, 180 });
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin({ 100, 90 });
    m_sprite.setScale({ .5, .5 });
}
