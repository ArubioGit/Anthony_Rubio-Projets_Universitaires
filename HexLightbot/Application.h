/*
 *
 * APPLICATION.H
 * Moignot Nicolas, Rubio Anthony (source fournie)
 * S2A 2017 - Projet POO
 *
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include <array>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

enum class Action_Type { FORWARD, ROTATE_LEFT, ROTATE_RIGHT, SWITCH_ON, PROC_1, PROC_2 };
enum class Button_Type { IMAGE, TEXT };
enum class App { MAIN, PLAY, EDIT, QUIT, SELECT, END_LEVEL };
enum class Case_State { NONE, NORMAL, ON, OFF };
enum class Direction { NORTH, NORTH_EAST, SOUTH_EAST, SOUTH, SOUTH_WEST, NORTH_WEST };
enum class Process_Type { DOCK, MAIN, PROC_1, PROC_2 };

class Application
{
    private:
        bool m_running;
        void process_events();
        void set_mouse_coord(int x, int y);
    protected:
        sf::RenderWindow m_window;
        sf::Vector2f m_mouse;

        virtual void init() {}
        virtual void loop() = 0;
        virtual void mouse_button_pressed() {}
        virtual void mouse_button_released() {}
        virtual void mouse_moved() {}

        void stop();
    public:
        Application(unsigned int w, unsigned int h, const std::wstring & title);
        virtual ~Application() = default;

        static float distance(const sf::Vector2f & p1, const sf::Vector2f & p2);
        static float module(const sf::Vector2f & v);
        void run();
};

#endif // APPLICATION_H
