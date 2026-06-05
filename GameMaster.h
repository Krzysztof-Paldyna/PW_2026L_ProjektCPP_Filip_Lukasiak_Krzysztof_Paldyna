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
    Battle
};

class GameMaster
{
protected:
	GameState State_of_Game = GameState::MainMenu;
    graphics_object_menu_button Start_Button;
    graphics_object_menu_button Quit_Button;
    PlayerCharacter Character_1, Character_2;
    sf::RenderWindow *Game_Window = nullptr;
    sf::Font menu_font;
    Player Playing_Player;

    graphics_object_end_turn end;
    graphics_object_energy_counter e_counter;
    graphics_object_deck_info d_info;
    Battle* current_battle = nullptr;
    
public:
	GameMaster(sf::RenderWindow *w);

    GameState Return_State_Of_Game();
    void Update_And_Render(int mx, int my, bool isClicked);
    void Main_Menu(int mx, int my, bool isClicked);
    void Choose_Character(int mx, int my, bool isClicked);

    void Start_New_Battle();
    void Update_Battle_Frame(int mx, int my, bool isClicked); 
    void Handle_Mouse_Click();
    ~GameMaster();
};
#endif