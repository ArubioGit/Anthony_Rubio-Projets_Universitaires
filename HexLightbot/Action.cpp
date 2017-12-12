/*
 *
 * ACTION.CPP
 * Moignot Nicolas, Rubio Anthony
 * S2A 2017 - Projet POO
 *
 */

#include "Action.h"

using namespace std;

Action::Action(Action * action, sf::Vector2f & mouse)
    : m_character { action->get_character() }
    , m_position { mouse }
    , m_texture { action->get_texture() }
    , m_type { action->get_type() }
{
    m_sprite.setPosition({ -100,-100 });
    m_sprite.setTexture(m_texture);
    m_new = true;
}

Action::Action(Action_Type type, Character * character)
    : m_character { character }
    , m_type { type }
{
    sf::Vector2i pos_on_image;
    switch(m_type) {
        case Action_Type::FORWARD:
            pos_on_image = { 0, 0 };
            break;
        case Action_Type::ROTATE_LEFT:
            pos_on_image = { 0, 77 };
            break;
        case Action_Type::ROTATE_RIGHT:
            pos_on_image = { 75, 77 };
            break;
        case Action_Type::SWITCH_ON:
            pos_on_image = { 75, 0 };
            break;
        case Action_Type::PROC_1:
            pos_on_image = { 0, 154 };
            break;
        case Action_Type::PROC_2:
            pos_on_image = { 75, 154 };
            break;
    }

    m_texture.loadFromFile("sprites/actions.png", { pos_on_image.x, pos_on_image.y, 75, 77 });
    m_sprite.setTexture(m_texture);
}

Action::~Action()
{}

/* ========== COMMON ========== */

void Action::draw(sf::RenderWindow & window)
{
    window.draw(m_sprite);
}

bool Action::contains(sf::Vector2f & mouse)
{
    return m_sprite.getGlobalBounds().contains(mouse);
}

bool Action::contains_border(sf::Vector2f & mouse)
{
    return (mouse.x >= m_position.x - 8) && (mouse.x <= m_position.x + 8)
        && (mouse.y >= m_position.y - 8) && (mouse.y <= m_position.y + 8);
}

/* ========== SPECIAL ========== */

void Action::make(array<array<Case *, 18>, 9> & cases)
{
    switch(m_type) {
        case Action_Type::FORWARD:
            make_forward(cases);
            break;
        case Action_Type::ROTATE_LEFT:
            make_rotate_left();
            break;
        case Action_Type::ROTATE_RIGHT:
            make_rotate_right();
            break;
        case Action_Type::SWITCH_ON:
            make_switch_on();
            break;
        default:
            break;
    }
}

/* ---------- FORWARD ---------- */

void Action::make_forward(std::array<std::array<Case *, 18>, 9> & cases)
{
    m_character->move_forward(cases);
}

/* ---------- ROTATE_LEFT ---------- */

void Action::make_rotate_left()
{
    switch (m_character->get_direction()) {
        case Direction::NORTH:
            m_character->set_direction(Direction::NORTH_WEST);
            break;
        case Direction::NORTH_WEST:
            m_character->set_direction(Direction::SOUTH_WEST);
            break;
        case Direction::SOUTH_WEST:
            m_character->set_direction(Direction::SOUTH);
            break;
        case Direction::SOUTH:
            m_character->set_direction(Direction::SOUTH_EAST);
            break;
        case Direction::SOUTH_EAST:
            m_character->set_direction(Direction::NORTH_EAST);
            break;
        case Direction::NORTH_EAST:
            m_character->set_direction(Direction::NORTH);
            break;
    }
}

/* ---------- ROTATE_RIGHT ---------- */

void Action::make_rotate_right()
{
    switch (m_character->get_direction()) {
        case Direction::NORTH:
            m_character->set_direction(Direction::NORTH_EAST);
            break;
        case Direction::NORTH_EAST:
            m_character->set_direction(Direction::SOUTH_EAST);
            break;
        case Direction::SOUTH_EAST:
            m_character->set_direction(Direction::SOUTH);
            break;
        case Direction::SOUTH:
            m_character->set_direction(Direction::SOUTH_WEST);
            break;
        case Direction::SOUTH_WEST:
            m_character->set_direction(Direction::NORTH_WEST);
            break;
        case Direction::NORTH_WEST:
            m_character->set_direction(Direction::NORTH);
            break;
    }
}

/* ---------- SWITCH_ON ---------- */

void Action::make_switch_on()
{
    m_character->get_position()->switch_on();
}
