#include "graphics_object_deck_info.hpp"

graphics_object_deck_info::graphics_object_deck_info(std::string name, std::string path, uint dim_x, uint dim_y, uint x, uint y): graphics_object(name, path, dim_x, dim_y, x, y)
{
    Discard_Pile.setPosition(x, y + 150);
    Discard_Pile.setSize({float(dim_x), float(dim_y)});
    Discard_Pile.setFillColor(sf::Color(128, 0, 255));
    Discard_Pile.setOutlineColor(sf::Color::Black);
    Discard_Pile.setOutlineThickness(5);
    Draw_Pile.setPosition(x, y);
    Draw_Pile.setSize({float(dim_x), float(dim_y)});
    Draw_Pile.setFillColor(sf::Color(200, 0, 255));
    Draw_Pile.setOutlineColor(sf::Color::Black);
    Draw_Pile.setOutlineThickness(5);
}
graphics_object_deck_info::~graphics_object_deck_info()
{

}

void graphics_object_deck_info::update_discard_info(int d)
{
    Discard_Card_Amount = d;
}
void graphics_object_deck_info::update_draw_info(int d)
{
    Draw_Card_Amount = d;
}
void graphics_object_deck_info::draw(sf::RenderWindow &window, sf::Font &font)
{
    window.draw(Discard_Pile);
    window.draw(Draw_Pile);
    sf::Text discard_text, draw_text;

    discard_text.setFont(font);
    discard_text.setString(std::to_string(Discard_Card_Amount));
    discard_text.setCharacterSize(40);
    discard_text.setFillColor(sf::Color::White);
    discard_text.setOutlineColor(sf::Color::Black);
    discard_text.setOutlineThickness(2);
    discard_text.setPosition(x + 35, y + 20 + 150);

    draw_text.setFont(font);
    draw_text.setString(std::to_string(Draw_Card_Amount));
    draw_text.setCharacterSize(40);
    draw_text.setFillColor(sf::Color::White);
    draw_text.setOutlineColor(sf::Color::Black);
    draw_text.setOutlineThickness(2);
    draw_text.setPosition(x + 35, y + 20);

    window.draw(discard_text);
    window.draw(draw_text);
}