#include"graphics_object_card.hpp"

graphics_object_card::graphics_object_card(std::string name, std::string cost, std::string text, std::string file_path, uint x, uint y, uint red, uint green, uint blue, uint alpha) : graphics_object(name, file_path, 200, 300, x, y){//konstruktor domyślno-parametryczny
    card_border.setSize({float(dim_x), float(dim_y)});
    card_border.setFillColor(sf::Color(red, green, blue, alpha));
    card_border.setOutlineColor(sf::Color(0, 0, 0));
    card_border.setOutlineThickness(2);
    this->cost = cost;
    this->text = text;
    if(file_path != "None"){
        card_texture.loadFromFile(file_path, sf::IntRect({0, 0}, {int(dim_x - 12), 120}));  //ładujemy teksturę (pierwsza para argumentów pokazuje start tekstury, druga wycinany rozmiar)
        card_image.setTexture(card_texture);
    }
    is_highlighted = highlight::none;
}

graphics_object_card::~graphics_object_card(){//destruktor

}

void graphics_object_card::draw(sf::RenderWindow &window, sf::Font &font){//przeciążana funkcja rysująca kartę w podanym oknie SMFL, z użyciem podanej czcionki
    //jeśli obiekt jest highlightowany zmienia kolor i grubość ramki karty
    switch(is_highlighted){
        case highlight::positive:{
            card_border.setOutlineColor(sf::Color(0, 255, 0, 128));
            card_border.setOutlineThickness(4);
            break;
        }
        case highlight::negative:{
            card_border.setOutlineColor(sf::Color(255, 0, 0, 128));
            card_border.setOutlineThickness(4);
            break;
        }
        default:{
            card_border.setOutlineColor(sf::Color(0, 0, 0));
            card_border.setOutlineThickness(2);
            break;
        }
    }
    
    //rysuje prostokątną bazę pod kartą
    card_border.setPosition(x, y);
    window.draw(card_border);

    //rysuje na górze karty rysunek
    if(file_path != "None"){
        card_image.setPosition(x + 6, y + 40);
        window.draw(card_image);
    }

    //rysowanie tytułu karty:
    sf::Text card_title;    
    card_title.setFont(font);
    card_title.setString(name);
    card_title.setCharacterSize(20);
    card_title.setFillColor(sf::Color::Black);
    card_title.setPosition(x + 6, y + 4);
    window.draw(card_title);

    //rysowanie treści karty:
    sf::Text card_text;    
    card_text.setFont(font);
    card_text.setString(text);
    card_text.setCharacterSize(12);
    card_text.setFillColor(sf::Color::Black);
    card_text.setPosition(x + 6, y + 164);
    window.draw(card_text);

    //rysowanie kosztu karty:
    sf::CircleShape cost_bubble(20);
    int off_card_offset = 8;
    cost_bubble.setPosition(x + dim_x - 2 * cost_bubble.getRadius() + off_card_offset, y - off_card_offset);
    cost_bubble.setFillColor(sf::Color(255, 255, 255));
    cost_bubble.setOutlineColor(sf::Color(0, 0, 0));
    cost_bubble.setOutlineThickness(2);
    window.draw(cost_bubble);

    sf::Text cost_value;
    cost_value.setFont(font);
    cost_value.setString(cost);
    cost_value.setCharacterSize(28);
    cost_value.setFillColor(sf::Color::Black);
    cost_value.setStyle(sf::Text::Bold);
    cost_value.setPosition(x + dim_x - cost_bubble.getRadius(), y - 5);
    window.draw(cost_value);
}