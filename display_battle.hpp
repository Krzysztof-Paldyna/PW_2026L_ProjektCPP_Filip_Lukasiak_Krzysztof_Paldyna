#ifndef CLASS_DISPLAY_BATTLE
#define CLASS_DISPLAY_BATTLE

#include "display_virtual.hpp"
#include"graphics_object_card.hpp"
#include"graphics_object_end_turn.hpp"

/**
* Klasa zarządzająca wyświetlaniem interfejsu walki, dziedzicząca po klasie display_virtual
*/
class display_battle : public display_virtual{
    
private:
    sf::RenderWindow window;    //okno w którym wyświetlana jest walka

    //vectory przechowujące informacje o wyświetlanych obiektach:
    std::vector<graphics_object_card> full_deck;        //WSZYSTKIE karty zawarte w talii
    std::vector<graphics_object_card> current_deck;     //karty obecnie w talii
    std::vector<graphics_object_card> hand;             //karty obecnie na ręku
    std::vector<graphics_object_card> discard_pile;     //karty wykorzystane, które po opróżnieniu current_deck są tam losowo wtasowywane
    //std::vector<graphics_object_character> player;      //postać lub postaci gracza
    //std::vector<graphics_object_character> enemy;       //przeciwnik lub przeciwnicy

    //inne wyświetlane obiekty:
    //graphics_object_deck deck_button;   //przycisk pokazujący talię OPCJONALNE
    graphics_object_end_turn end_turn_button;   //przycisk pozwalający zakończyć turę

    //zmienne służące interakcji z grą:
    static uint turn_counter;   //licznik tur gracza
    const uint max_hand_size;   //zmienna ustala ile maksymalnie może być kart na ręce
    static bool is_anything_highlighted;    //ustala czy jakiś obiekt został kliknięty, sprawia że program rysuje ten obiekt na wierzchu innych

public:
    //konstruktory i destruktor:
    display_battle(unsigned int x = 1600, unsigned int y = 1200);  //konstruktor domyślno-parametryczny
    ~display_battle(); //destruktor

    //metody klasy:
    void new_frame() override;  //wyświetla nową klatkę na ekran
};

#endif