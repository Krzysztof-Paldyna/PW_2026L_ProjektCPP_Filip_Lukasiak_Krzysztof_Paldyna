#include"graphics_object_damage_val.hpp"

/**
* Klasa rysująca wartość zadanych obrażeń, zanikających po czasie
*/

graphics_object_dmg_val::graphics_object_dmg_val(std::string name, std::string path, uint dim_x, uint dim_y, uint x, uint y) : graphics_object(name, path, dim_x, dim_y, x, y){//konstruktor domyślny (POZYCJA PRZYCISKU USTAWIONA NA STAŁE)
    text.setString(name);
    text.setCharacterSize(80);
    text.setFillColor(sf::Color(255, 0, 0));
    text.setOutlineColor(sf::Color(255, 255, 255));
    text.setOutlineThickness(2);
    text.setPosition(x, y);
    is_alive = true;
    lifetime = std::chrono::milliseconds(1500);
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
        int alpha = int(255 * (1 - exp(5 * (time_alive.count() / 1e9) - 7.5)));
        text.setFillColor(sf::Color(255, 0, 0, alpha));
        text.setOutlineColor(sf::Color(255, 255, 255, alpha));
        window.draw(text);
    }
    else{
        is_alive = false;
    }
}