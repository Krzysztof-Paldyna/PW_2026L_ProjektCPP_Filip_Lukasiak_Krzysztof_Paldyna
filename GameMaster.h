#ifndef GAMEMASTER
#define GAMEMASTER
#include"graphics_object_menu_button.h"
#include"graphics_object_choose_character.h"
#include "Player.h"
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

enum class GameState
{
    MainMenu,
    PlayerChoice,
    Battle,
    WinBattle,
    LoseBattle,
    CardChoice
};

class GameMaster
{
protected:
	GameState State_of_Game = GameState::MainMenu;

    graphics_object_menu_button Start_Button;
    graphics_object_menu_button Quit_Button;
    graphics_object_menu_button Continue_Button;
    graphics_object_menu_button Skip_Button;
    graphics_object_menu_button Choose_Button;

    PlayerCharacter Character_1, Character_2, Character_3;
    sf::RenderWindow *Game_Window = nullptr;
    sf::Font menu_font;
    Player Playing_Player;

    std::vector<Card*> Card_to_Choose;
    Card* Selected_Card = nullptr;
    int Selected_Card_Index = 0;

    graphics_object_end_turn end;
    graphics_object_energy_counter e_counter;
    graphics_object_deck_info d_info;
    Battle* current_battle = nullptr;

    sf::Texture Game_Over_Texture;
    sf::Texture Victory_Texture;   
    sf::Sprite Game_Over_Image;
    sf::Sprite Victory_Image;
    sf::Text Game_Over_Text;
    sf::Text Victory_Text;
    sf::Text Choose_Card_Text;
    
public:
	GameMaster(sf::RenderWindow *w);

    GameState Return_State_Of_Game();
    void Update_And_Render(int mx, int my, bool isClicked);
    void Main_Menu(int mx, int my, bool isClicked);
    void Choose_Character(int mx, int my, bool isClicked);
    void GameOver(int mx, int my, bool isClicked);
    void BattleVictory(int mx, int my, bool isClicked);
    void Choose_Card_To_Add(int mx, int my, bool isClicked);

    void Start_New_Battle();
    void Genarate_Cards_To_Choose();
    void Update_Battle_Frame(int mx, int my, bool isClicked); 
    ~GameMaster();
};
#endif