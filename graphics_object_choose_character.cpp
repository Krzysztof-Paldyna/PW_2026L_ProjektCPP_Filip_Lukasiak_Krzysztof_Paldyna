#include"graphics_object_choose_character.h"

graphics_object_choose_character::graphics_object_choose_character(PlayerCharacter& p, std::string name, std::string path, uint dim_x, uint dim_y, uint x, uint y) : graphics_object(name, path, dim_x, dim_y, x, y)
{
    Choosen_Character = p;
    Character_Choice_Boarder.setPosition(x, y);
    Character_Choice_Boarder.setSize({float(dim_x), float(dim_y)});
    Character_Choice_Boarder.setFillColor(sf::Color(0, 0, 0, 0));
    Character_Choice_Boarder.setOutlineColor(sf::Color(0, 0, 0, 0));

    file_path = Choosen_Character.get_file_path();

    if(file_path != "None"){
        Character_Choice_Texture.loadFromFile(file_path, sf::IntRect({0, 0}, {int(dim_x), int(dim_y)}));  //ładujemy teksturę (pierwsza para argumentów pokazuje start tekstury, druga wycinany rozmiar)
        Character_Choice_Image.setTexture(Character_Choice_Texture);
    }

    Name_text.setString(Choosen_Character.Return_Name());
    Name_text.setCharacterSize(30);
    Name_text.setFillColor(sf::Color::Black);
    Name_text.setOutlineColor(sf::Color::White);
    Name_text.setOutlineThickness(2);
    Name_text.setPosition(x + 150, y + 300);

    Description_text.setString(Choosen_Character.Return_Player_Character_Description());
    Description_text.setCharacterSize(30);
    Description_text.setFillColor(sf::Color::Black);
    Description_text.setOutlineColor(sf::Color::White);
    Description_text.setOutlineThickness(2);
    Description_text.setPosition(x, y + 350);
}

graphics_object_choose_character::~graphics_object_choose_character(){//destruktor

}

void graphics_object_choose_character::set_character(PlayerCharacter pc)
{
    Choosen_Character = pc;
}
void graphics_object_choose_character::set_character_sprite_position(uint x, uint y)
{
    graphics_object::set_position(x, y); 
    Character_Choice_Boarder.setPosition(x, y);
    Name_text.setPosition(x + 150, y + 300);
    Description_text.setPosition(x, y + 350);
}
void graphics_object_choose_character::draw(sf::RenderWindow &window, sf::Font &font){//przeciążana funkcja rysująca kartę w podanym oknie SMFL, z użyciem podanej czcionki
    
    window.draw(Character_Choice_Boarder);
    
    if(file_path != "None")
    {
        Character_Choice_Image.setPosition(x + 10, y);
        window.draw(Character_Choice_Image);
    }
    Name_text.setFont(font);
    window.draw(Name_text);
    Description_text.setFont(font);
    window.draw(Description_text);
}