#ifndef CLASS_GRAPHICS_OBJECT_DECK_INFO
#define CLASS_GRAPHICS_OBJECT_DECK_INFO

#include"graphics_object.hpp"

/**
* Klasa wypisująca ile kart jest na poszczegolnych kupkach kart 
*/
class graphics_object_deck_info : public graphics_object{
protected:
    sf::RectangleShape Draw_Pile;
    sf::RectangleShape Discard_Pile;
    int Draw_Card_Amount = 0;
    int Discard_Card_Amount = 0;
public:
    graphics_object_deck_info(std::string name = "Deck info", std::string path = "None", uint dim_x = 120, uint dim_y = 120, uint x = 20, uint y = 650); //konstruktor domyślny 
    ~graphics_object_deck_info();  //destruktor

    void update_discard_info(int d);
    void update_draw_info(int d);

    void draw(sf::RenderWindow &window, sf::Font &font) override; //przeciążana funkcja rysująca
};

#endif