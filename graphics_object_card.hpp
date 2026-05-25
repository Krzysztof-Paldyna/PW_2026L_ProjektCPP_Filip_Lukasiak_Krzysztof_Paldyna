#ifndef CLASS_GRAPHICS_OBJECT_CARD
#define CLASS_GRAPHICS_OBJECT_CARD

#include"graphics_object.hpp"

/**
* Klasa przechowująca dane i obsługująca wyświetlanie kart 
*/
class graphics_object_card : public graphics_object{
protected:
    sf::RectangleShape card_border;  //ramka na której rysowana jest karta
    sf::Texture card_texture;   //tekstura która jest wyświetlana na karcie, MUSI BYĆ bo sprite odwołuje się pointerem do tekstury
    sf::Sprite card_image;    //sprite wyświetlany na karcie
    std::string cost;  //wyświetlany koszt użycia karty
    std::string text;  //treść tekstowa karty - informuje użytkownika co karta robi
public:
    graphics_object_card(std::string name = "MISSING NAME", std::string cost = "0", std::string text = "MISSING CARD TEXT", std::string file_path = "None", uint x = 0, uint y = 0, uint red = 128, uint green = 128, uint blue = 128, uint alpha = 255); //konstruktor domyślno-parametryczny (WYMIAR KARTY USTAWIONY NA STALE)
    ~graphics_object_card();  //destruktor

    void draw(sf::RenderWindow &window, sf::Font &font) override; //przeciążana funkcja rysująca kartę w podanym oknie SMFL, z użyciem podanej czcionki
};

#endif