#ifndef CLASS_GRAPHICS_OBJECT_CHARACTER
#define CLASS_GRAPHICS_OBJECT_CHARACTER

#include"graphics_object.hpp"

/**
* Klasa przechowująca dane i obsługująca wyświetlanie postaci
*/
class graphics_object_character : public graphics_object{
protected:
    sf::RectangleShape character_border; 
    sf::Texture character_texture;   //tekstura która jest wyświetlana na karcie, MUSI BYĆ bo sprite odwołuje się pointerem do tekstury
    sf::Sprite character_image;    //sprite wyświetlany na karcie
    uint max_hp;    
    int current_hp;
public:
    graphics_object_character(std::string name = "MISSING NAME", std::string file_path = "None", uint dim_x = 300, uint dim_y = 300, uint x = 0, uint y = 0); //konstruktor domyślno-parametryczny
    ~graphics_object_character();  //destruktor

    void set_max_hp(uint new_max_hp);
    void set_hp(int new_hp);
    void draw(sf::RenderWindow &window, sf::Font &font) override; //przeciążana funkcja rysująca kartę w podanym oknie SMFL, z użyciem podanej czcionki

    void update_texture();
};

#endif