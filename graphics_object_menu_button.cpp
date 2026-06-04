#include"graphics_object_menu_button.h"

graphics_object_menu_button::graphics_object_menu_button(std::string t, std::string name, std::string path, uint dim_x, uint dim_y, uint x, uint y) : graphics_object(name, path, dim_x, dim_y, x, y)
{
    Button.setPosition(x, y);
    Button.setSize({float(dim_x), float(dim_y)});
    Button.setFillColor(sf::Color(128, 100, 0));
    Button.setOutlineColor(sf::Color::Black);
    Button_text.setString(t);
    Button_text.setCharacterSize(40);
    Button_text.setFillColor(sf::Color::Black);
    Button_text.setOutlineColor(sf::Color::White);
    Button_text.setOutlineThickness(2);
    Button_text.setPosition(x + 60, y + 50);
}

graphics_object_menu_button::~graphics_object_menu_button(){//destruktor

}

void graphics_object_menu_button::set_button_position(uint x, uint y)
{
    graphics_object::set_position(x, y); 
    Button.setPosition(x, y);
    Button_text.setPosition(x + 30, y + 10);
}
void graphics_object_menu_button::draw(sf::RenderWindow &window, sf::Font &font){//przeciążana funkcja rysująca kartę w podanym oknie SMFL, z użyciem podanej czcionki
    
    window.draw(Button);
    Button_text.setFont(font);
    window.draw(Button_text);
}