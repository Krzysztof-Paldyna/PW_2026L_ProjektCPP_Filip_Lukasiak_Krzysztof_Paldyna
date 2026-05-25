#ifndef CLASS_DISPLAY_VIRTUAL
#define CLASS_DISPLAY_VIRTUAL

#include<chrono>

/**
* Klasa wirtualna zarządzająca wyświetlaniem interfejsu graficznego, po której dziedziczą klasy wyświetlające konkretne elementy gry
*/
class display_virtual{
    
protected:
    unsigned int const dim_x;    //wymiar x ekranu
    unsigned int const dim_y;    //wymiar y ekranu - należy pamiętać że oś Y jest odwrócona!

public:
    //konstruktory i destruktor:
    display_virtual(unsigned int x = 1600, unsigned int y = 1200) : dim_x(x), dim_y(y) {}  //konstruktor domyślno-parametryczny
    ~display_virtual(); //destruktor

    //gettery:
    unsigned int get_dim_x() {return dim_x;}
    unsigned int get_dim_y() {return dim_y;}

    //metody klasy:
    virtual void new_frame() = 0;  //wyświetla nową klatkę na ekran
};

#endif