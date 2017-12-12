/*
 *
 * GAME.CPP
 * Moignot Nicolas, Rubio Anthony
 * S2A 2017 - Projet POO
 *
 */


#include "Game.h"

using namespace std;

Game::Game()
    : Application { 1280, 800, L"Hex LightBot" }
{
    m_font.loadFromFile("fonts/Lato-Black.ttf");
    init_MAIN();
}

Game::~Game()
{
    if(m_level != nullptr)
        delete m_level;
    delete_all();
}

/* ========== COMMON ========== */

void Game::loop()
{
    switch(m_app_current) {
        case App::MAIN:
            draw_MAIN();
            break;
        case App::PLAY:
            draw_PLAY();
            break;
        case App::EDIT:
            draw_EDIT();
            break;
        case App::SELECT:
            draw_SELECT();
            break;
        case App::END_LEVEL:
            draw_END_LEVEL();
            break;
        case App::QUIT:
            delete_all();
            stop();
            break;
    }
}

void Game::mouse_button_pressed()
{
    for(pair<string, Button *> object : m_buttons)
        object.second->mouse_button_pressed(m_mouse);
    if(m_app_current == App::PLAY || m_app_current == App::EDIT)
        mouse_pressed_PLAY();
}

void Game::mouse_button_released()
{
    switch(m_app_current) {
        case App::MAIN:
            mouse_released_MAIN();
            break;
        case App::PLAY:
            mouse_released_PLAY();
            break;
        case App::EDIT:
            mouse_released_EDIT();
            break;
        case App::SELECT:
            mouse_released_SELECT();
            break;
        case App::END_LEVEL:
            mouse_released_END_LEVEL();
            break;
        case App::QUIT:
            break;
    }
}

void Game::mouse_moved()
{
    if(m_app_current == App::PLAY || m_app_current == App::EDIT) {
        mouse_moved_PLAY();
        if(m_level->is_finished())
            init_END_LEVEL(m_level->score());
    }
}

/* ========== SPECIAL ========== */

void Game::delete_all()
{
    for(pair<string, Button *> object : m_buttons)
        delete object.second;
    m_buttons.clear();
}

/* ---------- MAIN ---------- */

void Game::init_MAIN()
{
    delete_all();
    m_app_current = App::MAIN;
    m_texture_background.loadFromFile("sprites/background.png");
    m_background.setTexture(m_texture_background);
    m_buttons["play"] = new Button({ 320, 500 }, "sprites/button_play.png");
    m_buttons["edit"] = new Button({ 660, 500 }, "sprites/button_edit.png");
    m_buttons["quit"] = new Button({ 490, 600 }, "sprites/button_quit.png");
}

void Game::mouse_released_MAIN()
{
    if(m_buttons["play"]->mouse_button_released(m_mouse))
        init_SELECT(App::PLAY);
    else if(m_buttons["edit"]->mouse_button_released(m_mouse))
        init_SELECT(App::EDIT);
    else if(m_buttons["quit"]->mouse_button_released(m_mouse))
        m_app_current = App::QUIT;
}

void Game::draw_MAIN()
{
    m_window.clear(sf::Color(206, 246, 245));
    m_window.draw(m_background);
    for(pair<string, Button *> object : m_buttons)
        object.second->draw(m_window);
    m_window.display();
}

/* ---------- PLAY ---------- */

void Game::init_PLAY(string file)
{
    delete_all();
    if(m_app_current == App::EDIT)
        m_level->set_editing(false);
    else
        m_level = new Level(file, false);
    m_app_current = App::PLAY;
    sf::Image buttons;
    buttons.loadFromFile("sprites/buttons.png");
    m_buttons["back"] = new Button({ 20, 20 }, { 100, 80 }, { 0, 0 }, buttons, true);
    m_buttons["play"] = new Button({ 660, 20 }, { 100, 80 }, { 0, 80 }, buttons, true);
    m_buttons["stop"] = new Button({ 660, 20 }, { 100, 80 }, { 0, 160 }, buttons, false);
    m_buttons["reset"] = new Button({ 780, 20 }, { 100, 80 }, { 0, 240 }, buttons, true);
}

void Game::mouse_moved_PLAY()
{
    m_level->mouse_moved(m_mouse);
}

void Game::mouse_pressed_PLAY()
{
    m_level->mouse_button_pressed(m_mouse);
}

void Game::mouse_released_PLAY()
{
    m_level->mouse_button_released(m_mouse);
    if(m_level->is_executing()) {
        if(m_buttons["stop"]->mouse_button_released(m_mouse)) {
            m_buttons["stop"]->set_display(false);
            m_buttons["play"]->set_display(true);
            m_level->stop();
        }
    } else {
        if(m_buttons["play"]->mouse_button_released(m_mouse)) {
            m_buttons["play"]->set_display(false);
            m_buttons["stop"]->set_display(true);
            m_level->execute();
        }
    }
    if(m_buttons["reset"]->mouse_button_released(m_mouse)) {
        m_buttons["stop"]->set_display(false);
        m_buttons["play"]->set_display(true);
        m_level->reset();
    }
    if(m_buttons["back"]->mouse_button_released(m_mouse)) {
        if(m_app_next == App::EDIT) {
            m_level->stop();
            init_EDIT(m_level->get_filename());
        } else {
            init_SELECT(App::PLAY);
        }
    }
}

void Game::draw_PLAY()
{
    sf::Vertex rectangle[] = { sf::Vertex({ 0, 0 }, sf::Color(108, 219, 251)),
                               sf::Vertex({ 0, 800 }, sf::Color(189, 243, 255)),
                               sf::Vertex({ 1280, 800 }, sf::Color(189, 243, 255)),
                               sf::Vertex({ 1280, 0 }, sf::Color(108, 219, 251)) };
    m_window.draw(rectangle, 4, sf::Quads);
    m_level->draw(m_window);
    for(pair<string, Button *> object : m_buttons)
        object.second->draw(m_window);
    m_window.display();
}

/* ---------- EDIT ---------- */

void Game::init_EDIT(string file)
{
    delete_all();
    if(m_app_current == App::PLAY)
        m_level->set_editing(true);
    else
        m_level = new Level(file, true);
    m_app_current = App::EDIT;
    sf::Image buttons;
    buttons.loadFromFile("sprites/buttons.png");
    m_buttons["back"] = new Button({ 20, 20 }, { 100, 80 }, { 0, 0 }, buttons, true);
    m_buttons["play"] = new Button({ 660, 20 }, { 100, 80 }, { 0, 80 }, buttons, true);
    m_buttons["save"] = new Button({ 780, 20 }, { 100, 80 }, { 0, 320 }, buttons, true);
}

void Game::mouse_released_EDIT()
{
    m_level->mouse_button_released(m_mouse);
    if(m_buttons["save"]->mouse_button_released(m_mouse))
        m_level->save();
    if(m_buttons["play"]->mouse_button_released(m_mouse))
        init_PLAY(m_level->get_filename());
    if(m_buttons["back"]->mouse_button_released(m_mouse))
        init_SELECT(App::EDIT);
}

void Game::draw_EDIT()
{
    sf::Vertex rectangle[] = { sf::Vertex({ 0, 0 }, sf::Color(90, 90, 90)),
                               sf::Vertex({ 0, 800 }, sf::Color(150, 150, 150)),
                               sf::Vertex({ 1280, 800 }, sf::Color(150, 150, 150)),
                               sf::Vertex({ 1280, 0 }, sf::Color(90, 90, 90)) };
    m_window.draw(rectangle, 4, sf::Quads);
    m_level->draw(m_window);
    for(pair<string, Button *> object : m_buttons)
        object.second->draw(m_window);
    m_window.display();
}

/* ---------- SELECT ---------- */

void Game::init_SELECT(App next)
{
    delete_all();
    m_app_current = App::SELECT;
    m_app_next = next;
    sf::Image buttons;
    buttons.loadFromFile("sprites/buttons.png");
    m_buttons["back"] = new Button({ 20, 20 }, { 100, 80 }, { 0, 0 }, buttons, true);

    DIR * directory;
    struct dirent * file;
    int x = 0;
    int y = 0;
    string repertory;
    if(next == App::PLAY) {
        repertory = "levels/play/";
        directory = opendir("levels/play/");
    } else if(next == App::EDIT) {
        repertory = "levels/edit/";
        directory = opendir("levels/edit/");
    }
    vector<string> filenames;
    while((file = readdir(directory)) != NULL) {
        if(file->d_type == DT_REG)
            filenames.push_back(file->d_name);
    }
    sort(filenames.begin(), filenames.end());
    for(string filename : filenames) {
        m_buttons[repertory + filename] = new Button({ (float)(x * 320 + 200), (float)(y * 120 + 30) }, { 300, 100 }, filename, m_font);
        if(x > 1) {
            x = 0;
            y++;
        } else {
            x++;
        }
    }
    closedir(directory);
}

void Game::mouse_released_SELECT() {
    for(pair<string, Button *> object : m_buttons) {
        if(object.first != "back") {
            if(object.second->mouse_button_released(m_mouse)) {
                if(m_app_next == App::PLAY)
                    init_PLAY(object.first);
                if(m_app_next == App::EDIT)
                    init_EDIT(object.first);
                return;
            }
        }
    }
    if(m_buttons["back"]->mouse_button_released(m_mouse)) {
        init_MAIN();
    }
}

void Game::draw_SELECT() {
    m_window.clear(sf::Color(206, 246, 245));
    for(pair<string, Button *> object : m_buttons)
        object.second->draw(m_window);
    m_window.display();
}

/* ---------- END_LEVEL ---------- */

void Game::init_END_LEVEL(int score)
{
    delete_all();
    m_app_current = App::END_LEVEL;
    sf::Image buttons;
    buttons.loadFromFile("sprites/buttons.png");
    m_buttons["back"] = new Button({ 20, 20 }, { 100, 80 }, { 0, 0 }, buttons, true);
    m_buttons["play"] = new Button({ 980, 360 }, { 100, 80 }, { 0, 80 }, buttons, true);
    m_text.setString("Level done");
    m_text.setFont(m_font);
    m_text.setCharacterSize(72);
    m_text.setColor(sf::Color::White);
    m_text.setPosition({ 250, 320 });
    m_text_score.setString(to_string(score) + " pts");
    m_text_score.setFont(m_font);
    m_text_score.setCharacterSize(52);
    m_text_score.setColor(sf::Color::White);
    m_text_score.setPosition({ 250, 400 });
}

void Game::mouse_released_END_LEVEL()
{
    if(m_buttons["play"]->mouse_button_released(m_mouse)) {
        DIR * directory;
        struct dirent * file;
        directory = opendir("levels/play/");
        vector<string> filenames;
        while((file = readdir(directory)) != NULL) {
            if(file->d_type == DT_REG)
                filenames.push_back(file->d_name);
        }
        sort(filenames.begin(), filenames.end());
        closedir(directory);

        unsigned int i = 0;
        for(string file : filenames) {
            i++;
            if(("levels/play/" + file) == m_level->get_filename())
                break;
        }
        if(i < filenames.size())
            init_PLAY("levels/play/" + filenames[i]);
        else
            init_MAIN();
    } else if(m_buttons["back"]->mouse_button_released(m_mouse)) {
        init_PLAY(m_level->get_filename());
    }
}

void Game::draw_END_LEVEL()
{
    sf::Vertex rectangle[] = { sf::Vertex({ 0, 0 }, sf::Color(108, 219, 251)),
                               sf::Vertex({ 0, 800 }, sf::Color(189, 243, 255)),
                               sf::Vertex({ 1280, 800 }, sf::Color(189, 243, 255)),
                               sf::Vertex({ 1280, 0 }, sf::Color(108, 219, 251)) };
    m_window.draw(rectangle, 4, sf::Quads);
    for(pair<string, Button *> object : m_buttons)
        object.second->draw(m_window);
    m_window.draw(m_text);
    m_window.draw(m_text_score);
    m_window.display();
}
