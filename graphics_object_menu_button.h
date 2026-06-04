#ifndef CLASS_GRAPHICS_OBJECT_MENU_BUTTON
#define CLASS_GRAPHICS_OBJECT_MENU_BUTTON

#include "graphics_object.hpp"

/**
* Klasa obsługująca przyciski w menu głównym
*/
class graphics_object_menu_button: public graphics_object
{
    protected:
        sf::RectangleShape Button;
        std::string text_string;
        sf::Text Button_text;
    public:
        graphics_object_menu_button(std::string t, std::string name = "Menu Button", std::string path = "None", uint dim_x = 200, uint dim_y = 120, uint x = 0, uint y = 0); //konstruktor domyślny 
        ~graphics_object_menu_button();  //destruktor

        void set_button_position(uint x, uint y);
        void draw(sf::RenderWindow &window, sf::Font &font) override; //przeciążana funkcja rysująca
};

#endif