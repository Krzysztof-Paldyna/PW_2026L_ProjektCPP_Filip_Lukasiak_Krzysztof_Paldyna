#include"graphics_object_damage_val.hpp"

/**
* Klasa rysująca wartość zadanych obrażeń, zanikających po czasie
*/

graphics_object_dmg_val::graphics_object_dmg_val(bool HP_damage, std::string name, std::string path, uint dim_x, uint dim_y, uint x, uint y) : graphics_object(name, path, dim_x, dim_y, x, y){//konstruktor domyślny (POZYCJA PRZYCISKU USTAWIONA NA STAŁE)
    is_HP_damage = HP_damage;
    text.setString(name);
    if(is_HP_damage){
        text.setCharacterSize(80);
        text.setOutlineThickness(2);
        lifetime = std::chrono::milliseconds(1500);
    }
    else{
        text.setCharacterSize(60);
        text.setOutlineThickness(3);
        lifetime = std::chrono::milliseconds(1000);
    }
    text.setPosition(x, y);
    is_alive = true;
    start = std::chrono::system_clock::now();
}

graphics_object_dmg_val::~graphics_object_dmg_val(){//destruktor

}

void graphics_object_dmg_val::set_damage_text(std::string new_text){
    text.setString(new_text);
}

bool graphics_object_dmg_val::get_state(){
    return is_alive;
}

void graphics_object_dmg_val::draw(sf::RenderWindow &window, sf::Font &font){//przeciążana funkcja rysująca kartę w podanym oknie SMFL, z użyciem podanej czcionki
    text.setFont(font);
    auto time_alive = std::chrono::system_clock::now() - start;
    if(lifetime > time_alive){
        if(is_HP_damage){
            int alpha = int(255 * (1 - exp(5 * (time_alive.count() / 1e9) - 7.5)));
            text.setFillColor(sf::Color(255, 0, 0, alpha));
            text.setOutlineColor(sf::Color(255, 255, 255, alpha));
        }
        else{
            int alpha = int(255 * (1 - exp(5 * (time_alive.count() / 1e9) - 5)));
            text.setFillColor(sf::Color(200, 200, 200, alpha));
            text.setOutlineColor(sf::Color(0, 0, 0, alpha));
        }
        
        window.draw(text);
    }
    else{
        is_alive = false;
    }
}