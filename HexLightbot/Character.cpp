/*
 *
 * CHARACTER.CPP
 * Moignot Nicolas, Rubio Anthony
 * S2A 2017 - Projet POO
 *
 */

#include "Character.h"

using namespace std;

Character::Character(Case * position, Direction direction)
    : m_direction_start { direction }
    , m_position { position }
    , m_position_start { position }
{
    set_direction(direction);
}

/* ========== COMMON ========== */

bool Character::contains(sf::Vector2f & mouse)
{
    m_position_mouse_tmp = mouse;
    return m_position->contains(mouse) || m_sprite.getGlobalBounds().contains(mouse);
}

bool Character::contains_border(sf::Vector2f & mouse)
{
    return (mouse.x >= m_position_mouse_tmp.x - 8) && (mouse.x <= m_position_mouse_tmp.x + 8)
        && (mouse.y >= m_position_mouse_tmp.y - 8) && (mouse.y <= m_position_mouse_tmp.y + 8);
}

void Character::draw(sf::RenderWindow & window)
{
    window.draw(m_sprite);
}

bool Character::mouse_button_pressed(sf::Vector2f & mouse)
{
    if(contains(mouse)) {
        m_click = true;
    }
    return m_click;
}

bool Character::mouse_button_released(sf::Vector2f & mouse, array<array<Case *, 18>, 9> & cases)
{
    if(m_click) {
        if(contains_border(mouse)) {
            switch(m_direction) {
                case Direction::NORTH:
                    set_direction(Direction::NORTH_EAST);
                    break;
                case Direction::NORTH_EAST:
                    set_direction(Direction::SOUTH_EAST);
                    break;
                case Direction::SOUTH_EAST:
                    set_direction(Direction::SOUTH);
                    break;
                case Direction::SOUTH:
                    set_direction(Direction::SOUTH_WEST);
                    break;
                case Direction::SOUTH_WEST:
                    set_direction(Direction::NORTH_WEST);
                    break;
                case Direction::NORTH_WEST:
                    set_direction(Direction::NORTH);
                    break;
            }
        } else {
            bool next = true;
            for(int y = 15; y > 1 && next; y--) {
                for(int x = 6; x > 1 && next; x--) {
                    if(cases[x][y]->contains(mouse) && cases[x][y]->get_state() != Case_State::NONE) {
                        m_position = cases[x][y];
                        m_position_start = cases[x][y];
                        m_sprite.setPosition(m_position->get_position());
                        next = false;
                    }
                }
            }
            m_sprite.setPosition(m_position->get_position());
        }
        m_click = false;
        return true;
    }
    return false;
}

/* ========== SPECIAL ========== */

void Character::die()
{
    m_sprite.setColor(sf::Color(255, 255, 255, 100));
}

void Character::move_forward(array<array<Case *, 18>, 9> & cases)
{
    sf::Vector2f position = m_position->get_coordonates();
    switch(m_direction) {
        case Direction::NORTH:
            m_position = cases[position.x][position.y - 2];
            break;
        case Direction::NORTH_EAST:
            m_position = cases[position.x + ((int)position.y % 2)][position.y - 1];
            break;
        case Direction::SOUTH_EAST:
            m_position = cases[position.x + ((int)position.y % 2)][position.y + 1];
            break;
        case Direction::SOUTH:
            m_position = cases[position.x][position.y + 2];
            break;
        case Direction::SOUTH_WEST:
            m_position = cases[position.x - 1 + ((int)position.y % 2)][position.y + 1];
            break;
        case Direction::NORTH_WEST:
            m_position = cases[position.x - 1 + ((int)position.y % 2)][position.y - 1];
            break;
    }
    m_sprite.setPosition(m_position->get_position());
}

void Character::reset()
{
    m_position = m_position_start;
    set_direction(m_direction_start);
    m_sprite.setPosition(m_position->get_position());
}

void Character::set_direction(Direction direction)
{
    m_direction = direction;
    int x;
    switch(direction) {
        case Direction::NORTH:
            x = 0;
            break;
        case Direction::NORTH_EAST:
            x = 120;
            break;
        case Direction::SOUTH_EAST:
            x = 240;
            break;
        case Direction::SOUTH:
            x = 360;
            break;
        case Direction::SOUTH_WEST:
            x = 480;
            break;
        case Direction::NORTH_WEST:
            x = 600;
            break;
    }
    m_texture.loadFromFile("sprites/characters.png", { x, 0, 120, 120 });
    m_sprite.setTexture(m_texture);
    m_sprite.setColor(sf::Color::White);
    m_sprite.setOrigin({ 60, 95 });
    m_sprite.setScale({ .5, .5 });
    m_sprite.setPosition(m_position->get_position());
}
