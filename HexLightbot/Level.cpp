/*
 *
 * LEVEL.CPP
 * Moignot Nicolas, Rubio Anthony
 * S2A 2017 - Projet POO
 *
 */

#include "Level.h"

using namespace std;

Level::Level(string file, bool editing)
    : m_editing { editing }
{
    read(file);
    m_case_dock = new Case_Dock();
    m_process[Process_Type::DOCK] = new Process(Process_Type::DOCK, m_character);
    m_process[Process_Type::MAIN] = new Process(Process_Type::MAIN, m_character);
    m_process[Process_Type::PROC_1] = new Process(Process_Type::PROC_1, m_character);
    m_process[Process_Type::PROC_2] = new Process(Process_Type::PROC_2, m_character);
    m_selected_process = m_process[Process_Type::MAIN];
}

Level::~Level()
{
    for(int y = 0; y < 18; y++) {
        for(int x = 0; x < 9; x++)
            delete m_cases[x][y];
    }
    for(pair<Process_Type, Process *> object : m_process)
        delete object.second;
    m_process.clear();
    delete m_character;
}

/* ========== COMMON ========== */

void Level::draw(sf::RenderWindow & window)
{
    for(int y = 2; y < 16; y++) {
        for(int x = 2; x < 7; x++)
            m_cases[x][y]->draw(window, m_editing);
    }
    m_character->draw(window);
    if(m_editing) {
        m_case_dock->draw(window);
        if(m_selected_case != nullptr)
            m_selected_case->draw(window, true);
    } else {
        if(m_selected_process != nullptr)
            m_selected_process->draw_selection(window);
        for(pair<Process_Type, Process *> object : m_process)
            object.second->draw(window);
        if(m_selected_action != nullptr)
            m_selected_action->draw(window);
    }
}

void Level::mouse_moved(sf::Vector2f & mouse)
{
    if(m_editing) {
        if(m_selected_case != nullptr) {
            m_selected_case->set_coordonates(mouse, true);
        } else if(m_character->is_clicked()) {
            m_character->set_position_sprite(mouse);
        }
    } else {
        if(m_selected_action != nullptr)
            m_selected_action->set_position_sprite({ mouse.x - 35, mouse.y - 35 });
    }
}

void Level::mouse_button_pressed(sf::Vector2f & mouse)
{
    if(m_editing) {
        if(!m_character->mouse_button_pressed(mouse))
            m_case_dock->mouse_button_pressed(mouse, m_selected_case);
    } else if(!m_executing) {
        for(pair<Process_Type, Process *> object : m_process)
            object.second->mouse_button_pressed(mouse, m_selected_action, m_selected_process);
    }
}

void Level::mouse_button_released(sf::Vector2f & mouse)
{
    if(m_editing) {
        bool next = true;
        if(m_selected_case != nullptr) {
            for(int y = 15; y > 1 && next; y--) {
                for(int x = 6; x > 1 && next; x--) {
                    if(m_cases[x][y]->contains(mouse)) {
                        delete m_cases[x][y];
                        m_selected_case->set_coordonates({ (float)x, (float)y }, false);
                        m_cases[x][y] = m_selected_case;
                        next = false;
                    }
                }
            }
            if(next)
                delete m_selected_case;
            m_selected_case = nullptr;
        } else if(!m_character->mouse_button_released(mouse, m_cases)) {
            for(int y = 15; y > 1 && next; y--) {
                for(int x = 6; x > 1 && next; x--) {
                    if(m_cases[x][y]->contains(mouse)) {
                        delete m_cases[x][y];
                        m_cases[x][y] = new Case({ (float)x, (float)y }, Case_State::NONE, false);
                        next = false;
                    }
                }
            }
        }
    } else {
        if(m_selected_action == nullptr) {
            for(pair<Process_Type, Process *> object : m_process) {
                if(object.second->get_type() != Process_Type::DOCK && object.second->contains(mouse))
                    m_selected_process = object.second;
            }
        } else {
            if(m_selected_action->is_new()) {
                for(pair<Process_Type, Process *> object : m_process) {
                    if(object.second->get_type() != Process_Type::DOCK && object.second->contains(mouse))
                        m_selected_process = object.second;
                }
                if(m_selected_action->contains_border(mouse)) {
                    if(m_selected_process != nullptr) {
                        m_selected_process->add_action(m_selected_action);
                    }
                } else if(m_selected_process->contains(mouse)) {
                    m_selected_process->add_action(m_selected_action);
                } else {
                    delete m_selected_action;
                }
            } else {
                if(!m_selected_process->contains(mouse)) {
                    m_selected_process->remove_action(m_selected_action);
                    delete m_selected_action;
                } else {
                    m_selected_process->position_action(true);
                }
            }
            m_selected_action = nullptr;
        }
    }
}

/* ========== SPECIAL ========== */

void Level::check_level()
{
    if(m_character->get_position()->get_state() == Case_State::NONE) {
        m_character->die();
    } else if(m_nb_case_ok == m_goal) {
        m_finished = true;
    }
}

void Level::execute()
{
    m_executing = true;
    execute_actions(m_process[Process_Type::MAIN]->get_actions());
}

void Level::execute_actions(vector<Action *> actions) {
    for(Action * object : actions) {
        if(m_executing && !m_finished) {
            if(object->get_type() == Action_Type::PROC_1) {
                execute_actions(m_process[Process_Type::PROC_1]->get_actions());
            } else if(object->get_type() == Action_Type::PROC_2) {
                execute_actions(m_process[Process_Type::PROC_2]->get_actions());
            } else if(object->get_type() == Action_Type::SWITCH_ON) {
                object->make(m_cases);
                if(m_character->get_position()->get_state() == Case_State::ON)
                    m_nb_case_ok++;
                else if(m_character->get_position()->get_state() == Case_State::OFF)
                    m_nb_case_ok--;
            } else {
                object->make(m_cases);
            }
            check_level();
        }
    }

}

void Level::read(string file)
{
    m_file = file;
    string file_stream = file;
    fstream stream;
    stream.open(file_stream.c_str(), ios::in);
    if(stream.fail())
        cerr << "ERROR. Can't load \"" + file + "\"." << endl;

    for(int y = 0; y < 18; y++) {
        for(int x = 0; x < 9; x++)
            m_cases[x][y] = new Case({ (float)x, (float)y }, Case_State::NONE, false);
    }

    pair<int, int> position;
    int direction_int;
    stream >> position.first;
    stream >> position.second;
    stream >> direction_int;
//    pair<int, int> size;
//    stream >> size.first;
//    stream >> size.second;

    int nb_cases;
    stream >> nb_cases;

//    pair<int, int> position_origin;
//    position_origin.first = (9 - size.first) / 2;
//    position_origin.second = (18 - size.second) / 2 + (size.second % 2);

    for(int i = 0; i < nb_cases; i++) {
        int x, y, state_id;
        stream >> x;
        stream >> y;
        stream >> state_id;
        Case_State state;
        switch(state_id) {
            case 0:
                state = Case_State::NONE;
                break;
            case 1:
                state = Case_State::NORMAL;
                break;
            case 2:
                state = Case_State::ON;
                break;
            case 3:
                state = Case_State::OFF;
                m_goal++;
                break;
        }
//        delete m_cases[x + position_origin.first][y + position_origin.second];
//        m_cases[x + position_origin.first][y + position_origin.second]
//                = new Case({ (float)(x + position_origin.first), (float)(y + position_origin.second) }, state, false);
        delete m_cases[x + 2][y + 2];
        m_cases[x + 2][y + 2] = new Case({ (float)(x + 2), (float)(y + 2) }, state, false);
    }

    Direction direction;
    switch(direction_int) {
        case 0:
            direction = Direction::NORTH;
            break;
        case 1:
            direction = Direction::NORTH_EAST;
            break;
        case 2:
            direction = Direction::SOUTH_EAST;
            break;
        case 3:
            direction = Direction::SOUTH;
            break;
        case 4:
            direction = Direction::SOUTH_WEST;
            break;
        case 5:
            direction = Direction::NORTH_WEST;
            break;
    }

//    m_character = new Character(m_cases[position.first + position_origin.first][position.second + position_origin.second], direction);
    m_character = new Character(m_cases[position.first + 2][position.second + 2], direction);
}

void Level::reset()
{
    stop();
    for(pair<Process_Type, Process *> object : m_process)
        object.second->reset();
}

void Level::save()
{
    string file = m_file;
    fstream stream;
    stream.open(file.c_str(), fstream::out);

    sf::Vector2f position;
    position = m_character->get_position()->get_coordonates();
    int direction;
    switch(m_character->get_direction()) {
        case Direction::NORTH:
            direction = 0;
            break;
        case Direction::NORTH_EAST:
            direction = 1;
            break;
        case Direction::SOUTH_EAST:
            direction = 2;
            break;
        case Direction::SOUTH:
            direction = 3;
            break;
        case Direction::SOUTH_WEST:
            direction = 4;
            break;
        case Direction::NORTH_WEST:
            direction = 5;
            break;
    }

    int tmp_int;
    string tmp_str = "";
//    sf::Vector2f begin = { 9, 18 };
//    sf::Vector2f end = { -1, -1 };
//    for(int y = 2; y < 16; y++) {
//        for(int x = 2; x < 7; x++) {
//            if(m_cases[x][y]->get_state() != Case_State::NONE) {
//                if(x < begin.x)
//                    begin.x = x;
//                if(y < begin.y)
//                    begin.y = y;
//                if(x > end.x)
//                    end.x = x;
//                if(y > end.y)
//                    end.y = y;
//            }
//        }
//    }

    stream << (position.x - 2) << ' ' << (position.y - 2) << ' ' << direction << endl << endl;

//    stream << (position.x - begin.x) << ' ' << (position.y - begin.y) << ' ' << direction << endl << endl;
//    stream << (end.x - begin.x + 1) << ' ' << (end.y - begin.y + 1) << endl << endl;

    tmp_int = 0;
//    for(int y = begin.y - 1; y <= end.y; y++) {
//        for(int x = begin.x - 1; x <= end.x; x++) {
    for(int y = 2; y < 16; y++) {
        for(int x = 2; x < 7; x++) {
            if(m_cases[x][y]->get_state() != Case_State::NONE) {
                string tmp_str_2;
                switch(m_cases[x][y]->get_state()) {
                    case Case_State::NONE:
                        break;
                    case Case_State::NORMAL:
                        tmp_str_2 = "1";
                        break;
                    case Case_State::ON:
                        tmp_str_2 = "2";
                        break;
                    case Case_State::OFF:
                        tmp_str_2 = "3";
                        break;
                }
                tmp_str += to_string(x - 2) + ' ' + to_string(y - 2) + ' ' + tmp_str_2 + '\n';
//                tmp_str += to_string(x - (int)begin.x) + ' ' + to_string(y - (int)begin.y) + ' ' + tmp_str_2 + '\n';
                tmp_int++;
            }
        }
    }
    stream << tmp_int << endl << tmp_str;
    stream.close();
}

int Level::score()
{
    return 60000 - (3000 * (int)m_process[Process_Type::MAIN]->count()) - (1500 * m_process[Process_Type::PROC_1]->count()) - (1500 * m_process[Process_Type::PROC_2]->count());
}

void Level::stop()
{
    m_executing = false;
    m_character->reset();
    for(int y = 2; y < 16; y++) {
        for(int x = 2; x < 7; x++)
            m_cases[x][y]->reset();
    }
}
