/*
 *
 * LEVEL.H
 * Moignot Nicolas, Rubio Anthony
 * S2A 2017 - Projet POO
 *
 */

#ifndef LEVEL_H
#define LEVEL_H

#include "Case.h"
#include "Case_Dock.h"
#include "Character.h"
#include "Process.h"

class Level
{
    private:
        std::array<std::array<Case *, 18>, 9> m_cases;
        Case_Dock * m_case_dock;
        Character * m_character;
        bool m_editing;
        bool m_executing = false;
        std::string m_file;
        bool m_finished = false;
        int m_goal = 0;
        int m_nb_case_ok = 0;
        std::map<Process_Type, Process *> m_process;
        int m_score;
        Action * m_selected_action = nullptr;
        Case * m_selected_case = nullptr;
        Process * m_selected_process;
    public:
        Level(std::string file, bool editing);
        ~Level();

        void draw(sf::RenderWindow & window);
        void mouse_moved(sf::Vector2f & mouse);
        void mouse_button_pressed(sf::Vector2f & mouse);
        void mouse_button_released(sf::Vector2f & mouse);

        void check_level();
        void execute();
        void execute_actions(std::vector<Action *> actions);
        void read(std::string file);
        void reset();
        void save();
        int score();
        void stop();

        bool is_executing()
            { return m_executing; }
        bool is_finished()
            { return m_finished; }
        std::string get_filename()
            { return m_file; }
        void set_editing(bool editing)
            { m_editing = editing; }
};

#endif // LEVEL_H
