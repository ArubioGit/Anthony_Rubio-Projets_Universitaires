/*
 *
 * PROCESS.CPP
 * Moignot Nicolas, Rubio Anthony
 * S2A 2017 - Projet POO
 *
 */

#include "Process.h"

using namespace std;

Process::Process(Process_Type type, Character * character)
    : m_character { character }
    , m_type { type }
{
    m_rect.setFillColor(sf::Color(255, 255, 255, 80));
    m_rect.setOutlineColor(sf::Color(255, 255, 255, 150));
    m_rect.setOutlineThickness(4);
    switch(type) {
        case Process_Type::DOCK:
            m_position = { 100, 700 };
            m_rect.setPosition(m_position);
            m_rect.setFillColor(sf::Color(255, 255, 255, 230));
            m_actions.push_back(new Action(Action_Type::FORWARD, m_character));
            m_actions.push_back(new Action(Action_Type::ROTATE_LEFT, m_character));
            m_actions.push_back(new Action(Action_Type::ROTATE_RIGHT, m_character));
            m_actions.push_back(new Action(Action_Type::SWITCH_ON, m_character));
            m_actions.push_back(new Action(Action_Type::PROC_1, m_character));
            m_actions.push_back(new Action(Action_Type::PROC_2, m_character));
            m_rect.setSize({ (float)(85 * m_actions.size() + 10), 100 });
            position_action(false);
            break;
        case Process_Type::MAIN:
            m_size = 12;
            m_position = { 900, 20 };
            m_rect.setPosition({ 895, 15 });
            m_rect.setSize({ 370, 312 });
            m_texture.loadFromFile("sprites/process.png", { 0, 0, 360, 302 });
            m_sprite.setTexture(m_texture);
            m_sprite.setPosition(m_position);
            position_action(true);
            break;
        case Process_Type::PROC_1:
            m_size = 8;
            m_position = { 900, 335 };
            m_rect.setPosition({ 895, 330 });
            m_rect.setSize({ 370, 222 });
            m_texture.loadFromFile("sprites/process.png", { 0, 302, 360, 212 });
            m_sprite.setTexture(m_texture);
            m_sprite.setPosition(m_position);
            position_action(true);
            break;
        case Process_Type::PROC_2:
            m_size = 8;
            m_position = { 900, 560 };
            m_rect.setPosition({ 895, 555 });
            m_rect.setSize({ 370, 222 });
            m_texture.loadFromFile("sprites/process.png", { 0, 514, 360, 212 });
            m_sprite.setTexture(m_texture);
            m_sprite.setPosition(m_position);
            position_action(true);
            break;
    }
}

Process::~Process()
{
    for(Action * object : m_actions)
        delete object;
}

/* ========== COMMON ========== */


bool Process::contains(sf::Vector2f & mouse)
{
    if(m_type == Process_Type::DOCK)
        return m_rect.getGlobalBounds().contains(mouse);
    else
        return m_sprite.getGlobalBounds().contains(mouse);
}

void Process::draw(sf::RenderWindow & window)
{
    if(m_type == Process_Type::DOCK)
        window.draw(m_rect);
    else
        window.draw(m_sprite);
    for(Action * object : m_actions)
        object->draw(window);
}

void Process::mouse_button_pressed(sf::Vector2f & mouse, Action * & m_selected_action, Process * & m_selected_process)
{
    for(Action * object : m_actions) {
        if(object->contains(mouse)) {
            if(m_type == Process_Type::DOCK) {
                m_selected_action = new Action(object, mouse);
            } else {
                m_selected_action = object;
                m_selected_process = this;
            }
        }
    }
}

/* ========== SPECIAL ========== */

void Process::add_action(Action * action)
{
    if(m_type != Process_Type::DOCK) {
        if(m_actions.size() < m_size) {
            m_actions.push_back(action);
            position_action(true);
            action->set_added();
        } else {
            delete action;
        }
    }
}

void Process::draw_selection(sf::RenderWindow & window) {
    window.draw(m_rect);
}

void Process::position_action(bool limited_size)
{
    int x = 0;
    int y = 0;
    if(limited_size) {
        for(Action * object : m_actions) {
            if(x == 4) {
                x = 0;
                y++;
            }
            object->set_position({ (float)(m_position.x + x * 85 + 15), (float)(m_position.y + y * 85 + 35) });
            x++;
        }
    } else {
        for(Action * object : m_actions) {
            object->set_position({ (float)(m_position.x + x * 85 + 10), (float)(m_position.y + 10) });
            x++;
        }
    }
}

void Process::remove_action(Action * action)
{
    vector<Action *> actions;
    for(Action * object : m_actions) {
        if(object != action)
            actions.push_back(object);
    }
    m_actions = actions;
    position_action(true);
}

void Process::reset()
{
    if(m_type != Process_Type::DOCK) {
        for(Action * object : m_actions)
            delete object;
        m_actions.clear();
    }
}
