/*
 *
 * PROCESS.H
 * Moignot Nicolas, Rubio Anthony
 * S2A 2017 - Projet POO
 *
 */

#ifndef PROCESS_H
#define PROCESS_H

#include "Action.h"

class Process
{
    private:
        std::vector<Action *> m_actions;
        Character * m_character;
        sf::Vector2f m_position;
        bool m_process_running = false;
        sf::RectangleShape m_rect;
        sf::Sprite m_sprite;
        sf::Texture m_texture;
        unsigned int m_size;
        Process_Type m_type;
    public:
        Process(Process_Type type, Character * character);
        ~Process();

        bool contains(sf::Vector2f & mouse);
        void draw(sf::RenderWindow & window);
        void mouse_button_pressed(sf::Vector2f & mouse, Action * & m_selected_action, Process * & m_selected_process);

        void add_action(Action * action);
        void draw_selection(sf::RenderWindow & window);
        void position_action(bool limited_size);
        void remove_action(Action * action);
        void reset();

        int count()
            { return m_actions.size(); }
        std::vector<Action *> get_actions()
            { return m_actions; }
        bool get_process_state()
            { return m_process_running; }
        Process_Type get_type()
            { return m_type; }
};

#endif // PROCESS_H
