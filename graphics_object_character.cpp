#include"graphics_object_character.hpp"

graphics_object_character::graphics_object_character(std::string name, std::string file_path, uint dim_x, uint dim_y, uint x, uint y) : graphics_object(name, file_path, dim_x, dim_y, x, y){//konstruktor domyślno-parametryczny
    character_border.setSize({float(dim_x) + 5, float(dim_y) + 5});
    character_border.setFillColor(sf::Color(0, 0, 0, 0));
    character_border.setOutlineColor(sf::Color(0, 0, 0));
    character_border.setOutlineThickness(2);
    max_hp = 100;
    current_hp = max_hp;
    if(file_path != "None"){
        character_texture.loadFromFile(file_path, sf::IntRect({0, 0}, {int(dim_x), int(dim_y)}));  //ładujemy teksturę (pierwsza para argumentów pokazuje start tekstury, druga wycinany rozmiar)
        character_image.setTexture(character_texture);
    }
    is_highlighted = highlight::none;
}

graphics_object_character::~graphics_object_character(){//destruktor

}

void graphics_object_character::set_max_hp(uint new_max_hp){
    max_hp = new_max_hp;
}

void graphics_object_character::set_hp(int new_hp){
    current_hp = new_hp;
}

void graphics_object_character::set_shield(int new_shield){
    current_shield = new_shield;
}

void graphics_object_character::draw(sf::RenderWindow &window, sf::Font &font){//przeciążana funkcja rysująca kartę w podanym oknie SMFL, z użyciem podanej czcionki
    
    switch(is_highlighted){
        case highlight::positive:{
            character_border.setOutlineColor(sf::Color(255, 0, 0, 128));
            character_border.setOutlineThickness(4);
            break;
        }
        case highlight::negative:{
            character_border.setOutlineColor(sf::Color(255, 0, 0, 128));
            character_border.setOutlineThickness(4);
            break;
        }
        default:{
            character_border.setOutlineColor(sf::Color(0, 0, 0));
            character_border.setOutlineThickness(2);
            break;
        }
    }
    
    //rysuje prostokątną bazę pod postacią
    character_border.setPosition(x, y);
    window.draw(character_border);
    
    //rysuje sprite postaci
    if(file_path != "None"){
        character_image.setPosition(x, y);
        window.draw(character_image);
    }

    //rysowanie nazwy postaci:
    sf::Text character_name;    
    character_name.setFont(font);
    character_name.setString(name);
    character_name.setCharacterSize(20);
    character_name.setFillColor(sf::Color::Black);
    character_name.setPosition(x, y - 24);
    window.draw(character_name);

    //rysowanie paska hp:
    hp_bar_max.setSize({float(dim_x), 12});
    hp_bar_max.setPosition(x, y + dim_y + 4);
    hp_bar_max.setFillColor(sf::Color::Black);
    hp_bar_max.setOutlineColor(sf::Color(200, 200, 200));
    hp_bar_max.setOutlineThickness(2);
    window.draw(hp_bar_max);
    if(current_hp > 0){
        if(current_hp > max_hp){
        hp_bar_max.setSize({float(dim_x), 12});
    }
    else{
        hp_bar.setSize({dim_x * current_hp / float(max_hp), 12});
    }
    hp_bar.setPosition(x, y + dim_y + 4);
    hp_bar.setFillColor(sf::Color::Red);
    window.draw(hp_bar);
    }

    //rysowanie punktów tarczy:
    if(current_shield > 0){
        float s = 10;  //modyfikuje skalę ikony
        sf::ConvexShape shield_icon;
        shield_icon.setPointCount(5);
        shield_icon.setPoint(0, {0, 0});
        shield_icon.setPoint(1, {4*s, 0});
        shield_icon.setPoint(2, {4*s, 3*s});
        shield_icon.setPoint(3, {2*s, 5*s});
        shield_icon.setPoint(4, {0, 3*s});
        shield_icon.setFillColor(sf::Color(200, 200, 200));
        shield_icon.setOutlineColor(sf::Color(100, 100, 100));
        shield_icon.setOutlineThickness(2);
        shield_icon.setPosition({float(x - shield_icon.getGlobalBounds().width - 2), float(y + dim_y - shield_icon.getGlobalBounds().height/2)});
        window.draw(shield_icon);

        sf::Text shield_val;
        shield_val.setFont(font);
        shield_val.setString(std::to_string(current_shield));
        shield_val.setCharacterSize(s * 3);
        shield_val.setFillColor(sf::Color::Black);
        shield_val.setPosition(shield_icon.getPosition().x + 2*s - shield_val.getLocalBounds().width/1.6, shield_icon.getPosition().y);
        window.draw(shield_val);
    }
}

void graphics_object_character::update_texture(){
    if(file_path != "None"){
        character_texture.loadFromFile(file_path, sf::IntRect({0, 0}, {int(dim_x), int(dim_y)}));  //ładujemy teksturę (pierwsza para argumentów pokazuje start tekstury, druga wycinany rozmiar)
        character_image.setTexture(character_texture);
        hp_bar.setSize({dim_x * current_hp / float(max_hp), 12});
    }
}