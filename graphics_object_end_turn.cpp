#include"graphics_object_end_turn.hpp"

graphics_object_end_turn::graphics_object_end_turn(std::string name, std::string path, uint dim_x, uint dim_y, uint x, uint y) : graphics_object(name, file_path, dim_x, dim_y, x, y){//konstruktor domyślny (POZYCJA PRZYCISKU USTAWIONA NA STAŁE)
    end_turn_button.setPosition(x, y);
    end_turn_button.setSize({float(dim_x), float(dim_y)});
    end_turn_button.setFillColor(sf::Color(128, 100, 0));
    end_turn_button.setOutlineColor(sf::Color::Black);
    is_Player_turn = true;
    is_highlighted = highlight::none;
}

graphics_object_end_turn::~graphics_object_end_turn(){//destruktor

}

void graphics_object_end_turn::draw(sf::RenderWindow &window, sf::Font &font){//przeciążana funkcja rysująca kartę w podanym oknie SMFL, z użyciem podanej czcionki
    //jeśli obiekt jest highlightowany zmienia kolor
    if(is_Player_turn){
        end_turn_button.setFillColor(sf::Color(230, 180, 0));
        switch(is_highlighted){
            case highlight::positive:{
                end_turn_button.setOutlineColor(sf::Color(0, 255, 0, 128));
                end_turn_button.setOutlineThickness(4);
                break;
            }
            default:{
                end_turn_button.setOutlineColor(sf::Color(0, 0, 0));
                end_turn_button.setOutlineThickness(2);
                break;
            }
        }
    }
    else{
        end_turn_button.setFillColor(sf::Color(128, 128, 128));
    }
    window.draw(end_turn_button);
    

    //rysowanie tekstu na przycisku:
    sf::Text text;
    text.setFont(font);
    text.setString(name);
    text.Bold;
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setOutlineColor(sf::Color::White);
    text.setOutlineThickness(2);
    text.setPosition(x + 12, y + 6);
    window.draw(text);
}