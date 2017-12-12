/*
 *
 * APPLICATION.CPP
 * Moignot Nicolas, Rubio Anthony (source fournie)
 * S2A 2017 - Projet POO
 *
 */

#include "Application.h"

using namespace std;

Application::Application(unsigned int w, unsigned int h, const wstring & title)
    : m_window { { w, h }, title }
{}

float Application::distance(const sf::Vector2f & p1, const sf::Vector2f & p2)
{
    return module(p1 - p2);
}

float Application::module(const sf::Vector2f & v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

void Application::process_events()
{
    if(!m_window.isOpen()) {
        stop();
        return;
    }
    sf::Event event;
    while(m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed :
                stop();
                break;
            case sf::Event::MouseButtonPressed :
                set_mouse_coord(event.mouseButton.x, event.mouseButton.y);
                mouse_button_pressed();
                break;
            case sf::Event::MouseButtonReleased :
                set_mouse_coord(event.mouseButton.x, event.mouseButton.y);
                mouse_button_released();
                break;
            case sf::Event::MouseMoved :
                set_mouse_coord(event.mouseMove.x, event.mouseMove.y);
                mouse_moved();
                break;
            default:
                break;
        }
    }
}

void Application::run()
{
    m_window.setFramerateLimit(60);
    m_running = true;
    init();
    while(m_running) {
        process_events();
        loop();
    }
}

void Application::set_mouse_coord(int x, int y)
{
    auto pos = m_window.mapPixelToCoords({ x, y });
    m_mouse = { pos.x, pos.y };
}

void Application::stop()
{
    m_running = false;
}
