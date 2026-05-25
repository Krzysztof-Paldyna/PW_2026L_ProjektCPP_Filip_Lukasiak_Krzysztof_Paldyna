#ifndef CLASS_GRAPHICS_OBJECT_END_TURN
#define CLASS_GRAPHICS_OBJECT_END_TURN

#include"graphics_object.hpp"

/**
* Klasa rysująca przycisk końca tury i reagująca na jego kliknięcie
*/
class graphics_object_end_turn : public graphics_object{
protected:
    sf::RectangleShape end_turn_button;  //przycisk końca tury
    bool is_Player_turn;    //wartość informująca czy jest tura gracza
public:
    graphics_object_end_turn(std::string name = "END TURN", std::string path = "None", uint dim_x = 120, uint dim_y = 40, uint x = 1460, uint y = 400); //konstruktor domyślny (POZYCJA PRZYCISKU USTAWIONA NA STAŁE)
    ~graphics_object_end_turn();  //destruktor

    void draw(sf::RenderWindow &window, sf::Font &font) override; //przeciążana funkcja rysująca kartę w podanym oknie SMFL, z użyciem podanej czcionki
};

#endif