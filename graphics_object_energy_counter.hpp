#ifndef CLASS_GRAPHICS_OBJECT_ENERGY_COUNTER
#define CLASS_GRAPHICS_OBJECT_ENERGY_COUNTER

#include"graphics_object.hpp"

/**
* Klasa rysująca licznik energii
*/
class graphics_object_energy_counter : public graphics_object{
protected:
    sf::CircleShape counter;
    int max_energy;
    int current_energy;
public:
    graphics_object_energy_counter(std::string name = "ENERGY COUNTER", std::string path = "None", uint dim_x = 40, uint dim_y = 40, uint x = 200, uint y = 400); //konstruktor domyślny (POZYCJA PRZYCISKU USTAWIONA NA STAŁE)
    ~graphics_object_energy_counter();  //destruktor

    void update_max_energy(int e_max);
    void update_current_energy(int e_current);
    void draw(sf::RenderWindow &window, sf::Font &font) override; //przeciążana funkcja rysująca kartę w podanym oknie SMFL, z użyciem podanej czcionki
};

#endif