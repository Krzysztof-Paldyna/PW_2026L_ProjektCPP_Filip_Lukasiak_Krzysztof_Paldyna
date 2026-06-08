#ifndef CLASS_GRAPHICS_OBJECT
#define CLASS_GRAPHICS_OBJECT

#include<vector>
#include<iostream>
#include<chrono>
#include<cmath>
#include<tuple>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

enum class highlight{   //definiuje, czy dany obiekt ma być wyróżniony graficznie (np. po kliknięciu kursorem) i w jaki sposób
    none,
    positive,
    negative,
    mouse_over
};

/**
* Klasa wirtualna po której dziedziczą klasy przechowujące informacje o wyświetlanych na ekranie elementach
*/
class graphics_object{

protected:
    std::string name;   //nazwa obiektu
    std::string file_path;  //przechowuje ścieżkę do pliku graficznego wyświetlanego przez obiekt
    const uint dim_x;   //wymiar x obiektu
    const uint dim_y;   //wymiar y obiektu
    uint x = 0; //pozycja x obiektu (górnego lewego rogu)
    uint y = 0; //pozycja y obiektu (górnego lewego rogu)
    highlight is_highlighted;   //określa czy obiekt ma być renderowany z podświetleniem

public:
    graphics_object(std::string name, std::string file_path, uint dim_x, uint dim_y, uint x, uint y) : name(name), file_path(file_path), dim_x(dim_x), dim_y(dim_y), x(x), y(y) {}  //konstruktor domyślno-parametryczny
    ~graphics_object() {}

    //gettery:
    const std::string get_name() {return name;} //zwraca nazwę obiektu
    const std::string get_file_path() {return file_path;}   //zwraca ścieżkę pliku ładowanego przez obiekt
    const uint get_dim_x() {return dim_x;}  //zwraca wymiar x obiektu
    const uint get_dim_y() {return dim_y;}  //zwraca wymiat y obiektu
    const uint get_x() {return x;}  //zwraca pozycję x obiektu
    const uint get_y() {return y;}  //zwraca pozycję u obiektu
    const highlight get_highlight_state() {return is_highlighted;}  //zwraca stan podświetlenia obiektu

    //settery:
    void set_name(std::string name) {this->name = name;}
    void set_file_path(std::string path) {file_path = path;}
    void set_x(uint x) {this->x = x;}   //zmienia pozycję x obiektu
    void set_y(uint y) {this->y = y;}   //zmienia pozycję y obiektu
    void set_highlight_state(highlight highlight) {is_highlighted = highlight;}   //zmienia stan podświetlenia obiektu

    graphics_object& operator=(const graphics_object& other) {name = other.name; file_path = other.file_path; x = other.x; y=other.y; is_highlighted = other.is_highlighted; return *this;}

    //metody klasy:
    void set_position(uint x, uint y) {this->x = x; this->y = y;}   //zmienia wartość zmiennych x i y obiektu
    virtual void draw(sf::RenderWindow &window, sf::Font &font) = 0; //przeciążana funkcja rysująca obiekt w podanych koordynatach na oknie SMFL
};

#endif