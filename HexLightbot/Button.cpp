/*
 *
 * BUTTON.CPP
 * Moignot Nicolas, Rubio Anthony
 * S2A 2017 - Projet POO
 *
 */

#include "Button.h"

using namespace std;

Button::Button(sf::Vector2f position, string image)
{
    m_type = Button_Type::IMAGE;
    m_display = true;
    m_texture.loadFromFile(image);
    m_texture_onclick.loadFromFile(image);
    m_button.setTexture(m_texture);
    m_button.setPosition(position);
}

Button::Button(sf::Vector2f position, sf::Vector2f size, string text, sf::Font & font)
{
    m_type = Button_Type::TEXT;
    m_display = true;
    m_rect.setPosition(position);
    m_rect.setSize(size);
    m_rect.setFillColor(sf::Color::White);
    m_text.setString(text);
    m_text.setFont(font);
    m_text.setCharacterSize(48);
    m_text.setColor(sf::Color(29, 216, 255));
    m_text.setPosition({ position.x + (size.x - m_text.getGlobalBounds().width) / 2, position.y + (size.y - m_text.getGlobalBounds().height) / 2 - 12 });
}

Button::Button(sf::Vector2f position, sf::Vector2i size, sf::Vector2i pos_on_image, sf::Image & image, bool display)
    : m_display { display }
{
    m_type = Button_Type::IMAGE;
    m_texture.loadFromImage(image, { pos_on_image.x, pos_on_image.y, size.x, size.y });
    m_texture_onclick.loadFromImage(image, { pos_on_image.x + size.x, pos_on_image.y, size.x, size.y });
    m_button.setTexture(m_texture);
    m_button.setPosition(position);
}

/* ========== COMMON ========== */

bool Button::contains(sf::Vector2f & mouse)
{
    if(m_type == Button_Type::IMAGE)
        return m_display && m_button.getGlobalBounds().contains(mouse);
    else
        return m_display && m_rect.getGlobalBounds().contains(mouse);
}

void Button::draw(sf::RenderWindow & window)
{
    if(m_display) {
        if(m_type == Button_Type::IMAGE) {
            window.draw(m_button);
        } else {
            window.draw(m_rect);
            window.draw(m_text);
        }
    }
}

bool Button::mouse_button_pressed(sf::Vector2f & mouse)
{
    if(contains(mouse)) {
        if(m_type == Button_Type::IMAGE)
            m_button.setTexture(m_texture_onclick);
        m_click = true;
    }
    return m_click;
}

bool Button::mouse_button_released(sf::Vector2f & mouse)
{
    if(!m_click || !contains(mouse))
        m_click = false;
    if(m_type == Button_Type::IMAGE)
        m_button.setTexture(m_texture);
    return m_click;
}
