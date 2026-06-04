#include "GameMaster.h"

GameMaster::GameMaster(sf::RenderWindow *w): Start_Button("Start"), Quit_Button("Quit"), Character_1("Pimpek", 77), Character_2("Bombel", 70)
{
    std::cout << "[DEBUG] Start konstruktora GameMaster" << std::endl;
    if (!menu_font.loadFromFile("resources/fonts/Andale_Mono.ttf"))
    {
        std::cerr << "BLAD: Nie udalo sie wczytac czcionki! Sprawdz sciezke." << std::endl;
        std::exit(1); 
    }
    State_of_Game = GameState::MainMenu;
    Game_Window = w;  
    Start_Button.set_button_position(800, 300);
    Quit_Button.set_button_position(800, 500);
    Character_1.Set_Character_Description("Najbardziej normalna wanilla \nnijaka szara codzienna postac.");
    Character_2.Set_Character_Description("Druga postac na razie \ndla pokazu.");
    Character_2.Set_Character_File_Path("resources/textures/BasicEnemy.png");
    std::cout << "[DEBUG] Koniec konstruktora GameMaster" << std::endl;
}

void GameMaster::Update_And_Render(int mx, int my, bool isClicked)
{
    switch (State_of_Game)
    {
        case GameState::MainMenu:
            Main_Menu(mx, my, isClicked);
            break;

        case GameState::PlayerChoice:
            Choose_Character(mx, my, isClicked);
            break;
            
        case GameState::Battle:
            Update_Battle_Frame(mx, my, isClicked);
            break;
    }
}

void GameMaster::Main_Menu(int mx, int my, bool isClicked)
{
    if (Game_Window != nullptr)
    {
        Start_Button.draw(*Game_Window, menu_font);
        Quit_Button.draw(*Game_Window, menu_font); 
    }
    if (isClicked)
    {
        if (mx >= Start_Button.get_x() && mx <= Start_Button.get_x() + Start_Button.get_dim_x() &&
            my >= Start_Button.get_y() && my <= Start_Button.get_y() + Start_Button.get_dim_y())
        {
            State_of_Game = GameState::PlayerChoice; 
        }
        if (mx >= Quit_Button.get_x() && mx <= Quit_Button.get_x() + Quit_Button.get_dim_x() &&
            my >= Quit_Button.get_y() && my <= Quit_Button.get_y() + Quit_Button.get_dim_y())
        {
            if (Game_Window != nullptr) Game_Window->close();
        }
    }
}
void GameMaster::Choose_Character(int mx, int my, bool isClicked)
{
    graphics_object_choose_character Character_1_Sprite(Character_1), Character_2_Sprite(Character_2);
    Character_2_Sprite.set_character_sprite_position(600, 0);
    Character_2.set_position(600, 0);
    if (Game_Window != nullptr)
    {
        Character_1_Sprite.draw(*Game_Window, menu_font);
        Character_2_Sprite.draw(*Game_Window, menu_font);
    }
    if (isClicked)
    {
        if (mx >= Character_1.get_x() && mx <= Character_1.get_x() + Character_1.get_dim_x() &&
            my >= Character_1.get_y() && my <= Character_1.get_y() + Character_1.get_dim_y())
        {
            Playing_Player.Set_Character(Character_1);
            Playing_Player.Add_Card(CardFactory::create(1, "Basic Attack", 1));
            Playing_Player.Add_Card(CardFactory::create(1, "Basic Attack", 1));
            Playing_Player.Add_Card(CardFactory::create(2, "Basic Shield", 1));
            Playing_Player.Add_Card(CardFactory::create(2, "Basic Shield", 1));
            Playing_Player.Add_Card(CardFactory::create(4, "Draw", 0));
            Start_New_Battle();
        }
         if (mx >= Character_2.get_x() && mx <= Character_2.get_x() + Character_2.get_dim_x() &&
                my >= Character_2.get_y() && my <= Character_2.get_y() + Character_2.get_dim_y())
        {
            Playing_Player.Set_Character(Character_2);
            Playing_Player.Add_Card(CardFactory::create(1, "Basic Attack", 1));
            Playing_Player.Add_Card(CardFactory::create(1, "Basic Attack", 1));
            Playing_Player.Add_Card(CardFactory::create(2, "Basic Shield", 1));
            Playing_Player.Add_Card(CardFactory::create(2, "Basic Shield", 1));
            Playing_Player.Add_Card(CardFactory::create(3, "Basic Attack Shield", 1));
            Playing_Player.Add_Card(CardFactory::create(3, "Basic Attack Shield", 1));
            Start_New_Battle();
        }
    }
}

void GameMaster::Start_New_Battle() 
{
    if (current_battle != nullptr) 
    {
        delete current_battle;
    }
    std::vector<Enemy*> Act_Enemies;
    Act_Enemies.push_back(EnemyFactory::create(1, "BasicEnemy", 25));

    current_battle = new Battle(&Playing_Player, Act_Enemies, Game_Window, &end, &e_counter, &d_info);
    
    State_of_Game = GameState::Battle;
}

void GameMaster::Update_Battle_Frame(int mx, int my, bool isClicked) {
    if (current_battle == nullptr) 
    {
        return;
    }

    // Obsługa kliknięć
    if (isClicked) 
    {
        current_battle->Handle_Mouse_Click(mx, my);
    }

    // Rysowanie (wywołujemy metody, które już masz)
    current_battle->Render_Cards();
    current_battle->Render_Player();
    current_battle->Render_Enemies();
    current_battle->Render_Energy_Counter();
    current_battle->Render_End_Turn_Button();
    current_battle->Render_Card_Info_Piles();
    // Logika wrogów (pamiętaj, by nie wywoływać tego co klatkę, 
    // tylko gdy tura się zmienia - patrz poprzednie rady o State Machine!)
    // current_battle->Update_Battle_Logic(); 
}

GameState GameMaster::Return_State_Of_Game()
{
    return State_of_Game;
}
GameMaster::~GameMaster()
{

}