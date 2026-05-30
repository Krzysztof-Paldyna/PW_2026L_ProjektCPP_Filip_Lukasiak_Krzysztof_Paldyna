#include "graphics_object_energy_counter.hpp"
graphics_object_energy_counter::graphics_object_energy_counter(std::string name, std::string path, uint dim_x, uint dim_y, uint, uint y) : graphics_object(name, path, dim_x, dim_y, x, y){//konstruktor domyślny (POZYCJA PRZYCISKU USTAWIONA NA STAŁE)
    counter.setPosition(x, y);
    counter.setRadius(float(dim_x));
    counter.setFillColor(sf::Color(0, 200, 40));
    counter.setOutlineColor(sf::Color::Black);
    counter.setOutlineThickness(4);
    max_energy = 0;
    current_energy = 0;
}

graphics_object_energy_counter::~graphics_object_energy_counter(){//destruktor

}

void graphics_object_energy_counter::update_max_energy(int e_max){
    max_energy = e_max;
}

void graphics_object_energy_counter::update_current_energy(int e_current){
    current_energy = e_current;
}

void graphics_object_energy_counter::draw(sf::RenderWindow &window, sf::Font &font){//przeciążana funkcja rysująca kartę w podanym oknie SMFL, z użyciem podanej czcionki
    window.draw(counter);

    //rysowanie tekstu na liczniku:
    sf::Text text;
    text.setFont(font);
    text.setString(std::to_string(current_energy) + "/" + std::to_string(max_energy));
    text.Bold;
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Black);
    text.setOutlineColor(sf::Color::White);
    text.setOutlineThickness(2);
    text.setPosition(x + dim_x/2 - 8, y + dim_y/2);
    window.draw(text);
}