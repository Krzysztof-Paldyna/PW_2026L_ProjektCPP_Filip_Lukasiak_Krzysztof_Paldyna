#ifndef CLASS_GRAPHICS_OBJECT_CHOOSE_CHARACTER
#define CLASS_GRAPHICS_OBJECT_CHOOSE_CHARACTER

#include "graphics_object.hpp"
#include "Enemy.h"
/**
* Klasa obslugująca wybor postaci, ktora ktos bedzie gral
*/
class graphics_object_choose_character: public graphics_object
{
    protected:
        sf::RectangleShape Character_Choice_Boarder;
        sf::Texture Character_Choice_Texture;   
        sf::Sprite Character_Choice_Image;
        std::string Name_string;
        sf::Text Name_text;
        std::string Description_string;
        sf::Text Description_text;
        PlayerCharacter Choosen_Character;
    public:
        graphics_object_choose_character(PlayerCharacter& p, std::string name = "Character Sprite", std::string path = "None", uint dim_x = 300, uint dim_y = 300, uint x = 0, uint y = 0); //konstruktor domyślny 
        ~graphics_object_choose_character();  //destruktor

        void set_character(PlayerCharacter pc);
        void set_character_sprite_position(uint x, uint y);
        void draw(sf::RenderWindow &window, sf::Font &font) override; //przeciążana funkcja rysująca
};

#endif