#ifndef CLASS_GRAPHICS_OBJECT_DAMAGE_VAL
#define CLASS_GRAPHICS_OBJECT_DAMAGE_VAL

#include"graphics_object.hpp"

/**
* Klasa rysująca wartość zadanych obrażeń, zanikających po czasie
*/
class graphics_object_dmg_val: public graphics_object{
protected:
    sf::Text text;  //przycisk końca tury
    std::chrono::time_point<std::chrono::system_clock> start;    //start życia ikonki
    std::chrono::milliseconds lifetime;    //czas życia ikonki w milisekundach, po którym jest usuwana
    bool is_alive;
public:
    graphics_object_dmg_val(std::string name = "0", std::string path = "None", uint dim_x = 0, uint dim_y = 0, uint x = 0, uint y = 0); //konstruktor parametryczny
    ~graphics_object_dmg_val();  //destruktor

    void set_damage_text(std::string new_text);
    bool get_state();
    void draw(sf::RenderWindow &window, sf::Font &font) override; //przeciążana funkcja rysująca kartę w podanym oknie SMFL, z użyciem podanej czcionki
};

#endif