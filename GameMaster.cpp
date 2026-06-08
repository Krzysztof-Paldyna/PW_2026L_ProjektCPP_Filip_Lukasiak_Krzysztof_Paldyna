#include "GameMaster.h"

GameMaster::GameMaster(sf::RenderWindow *w): Start_Button("Start"), Quit_Button("Quit"), Skip_Button("Pomin"), Choose_Button("Wybierz"), Continue_Button("Dalej"), Character_1("Pimpek", 77), Character_2("Bombel", 70)
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
    Continue_Button.set_button_position(800, 750);
    Skip_Button.set_button_position(1500, 400);
    Choose_Button.set_button_position(1500, 200);
    Character_1.Set_Character_Description("Najbardziej normalna wanilla \nnijaka szara codzienna postac.");
    Character_2.Set_Character_Description("Druga postac na razie \ndla pokazu.");
    Character_2.Set_Character_File_Path("resources/textures/BasicEnemy.png");
    std::cout << "[DEBUG] Koniec konstruktora GameMaster" << std::endl;

    Game_Over_Texture.loadFromFile("resources/textures/GameOver.png", sf::IntRect({0,0}, {int(500), int(380)}));  
    Game_Over_Image.setTexture(Game_Over_Texture);
    Game_Over_Image.setPosition(650, 350);
    Game_Over_Text.setFont(menu_font);
    Game_Over_Text.setString("    KONIEC GRY \n  PRZEGRYWASZ :C");
    Game_Over_Text.setCharacterSize(40);
    Game_Over_Text.setFillColor(sf::Color::Black);
    Game_Over_Text.setPosition(675, 170);

    Victory_Texture.loadFromFile("resources/textures/VictoryPic.png", sf::IntRect({0,0}, {int(500), int(380)}));  
    Victory_Image.setTexture(Victory_Texture);
    Victory_Image.setPosition(650, 350);
    Victory_Text.setFont(menu_font);
    Victory_Text.setString("  WYGRYWASZ \n    WALKE ");
    Victory_Text.setCharacterSize(40);
    Victory_Text.setFillColor(sf::Color::Black);
    Victory_Text.setPosition(675, 170);

    Choose_Card_Text.setFont(menu_font);
    Choose_Card_Text.setString("Wybierz karte do dodania.");
    Choose_Card_Text.setCharacterSize(60);
    Choose_Card_Text.setFillColor(sf::Color::Black);
    Choose_Card_Text.setPosition(500, 250);
}

void GameMaster::Update_And_Render(int mx, int my, bool isClicked)
{
    Game_Window->clear(sf::Color::White);
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
        case GameState::LoseBattle:   
            GameOver(mx, my, isClicked);
            break;
        case GameState::WinBattle:
            BattleVictory(mx, my, isClicked);
            break;
        case GameState::CardChoice:
            Choose_Card_To_Add(mx, my, isClicked);
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
void GameMaster::GameOver(int mx, int my, bool isClicked)
{
    
    if (Game_Window != nullptr)
    {
        Quit_Button.draw(*Game_Window, menu_font); 
        Game_Window->draw(Game_Over_Image);
        Game_Window->draw(Game_Over_Text);
    }
    if (isClicked)
    {
        if (mx >= Quit_Button.get_x() && mx <= Quit_Button.get_x() + Quit_Button.get_dim_x() &&
            my >= Quit_Button.get_y() && my <= Quit_Button.get_y() + Quit_Button.get_dim_y())
        {
            if (Game_Window != nullptr) Game_Window->close();
        }
    }
}
void GameMaster::BattleVictory(int mx, int my, bool isClicked)
{
    
    if (Game_Window != nullptr)
    {
        Continue_Button.draw(*Game_Window, menu_font); 
        Game_Window->draw(Victory_Image);
        Game_Window->draw(Victory_Text);
    }
    if (isClicked)
    {
        if (mx >= Continue_Button.get_x() && mx <= Continue_Button.get_x() + Continue_Button.get_dim_x() &&
            my >= Continue_Button.get_y() && my <= Continue_Button.get_y() + Continue_Button.get_dim_y())
        {
            Genarate_Cards_To_Choose();
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
            Playing_Player.Add_Card(CardFactory::create(1)->clone());
            Playing_Player.Add_Card(CardFactory::create(1)->clone());
            Playing_Player.Add_Card(CardFactory::create(1)->clone());
            Playing_Player.Add_Card(CardFactory::create(1)->clone());
            Playing_Player.Add_Card(CardFactory::create(2)->clone());
            Playing_Player.Add_Card(CardFactory::create(2)->clone());
            Playing_Player.Add_Card(CardFactory::create(2)->clone());
            Playing_Player.Add_Card(CardFactory::create(2)->clone());
            Playing_Player.Add_Card(CardFactory::create(4)->clone());
            Start_New_Battle();
        }
         if (mx >= Character_2.get_x() && mx <= Character_2.get_x() + Character_2.get_dim_x() &&
                my >= Character_2.get_y() && my <= Character_2.get_y() + Character_2.get_dim_y())
        {
            Playing_Player.Set_Character(Character_2);
            Playing_Player.Add_Card(CardFactory::create(1)->clone());
            Playing_Player.Add_Card(CardFactory::create(1)->clone());
            Playing_Player.Add_Card(CardFactory::create(2)->clone());
            Playing_Player.Add_Card(CardFactory::create(2)->clone());
            Playing_Player.Add_Card(CardFactory::create(1)->clone());
            Playing_Player.Add_Card(CardFactory::create(1)->clone());
            Playing_Player.Add_Card(CardFactory::create(2)->clone());
            Playing_Player.Add_Card(CardFactory::create(2)->clone());
            Playing_Player.Add_Card(CardFactory::create(3)->clone());
            Playing_Player.Add_Card(CardFactory::create(3)->clone());
            Start_New_Battle();
        }
    }
}

void GameMaster::Start_New_Battle() 
{
    Quit_Button.set_button_position(800, 750);
    if (current_battle != nullptr) 
    {
        delete current_battle;
    }
    std::vector<Enemy*> Act_Enemies;
    int enemy_count = 1 + rand() % 3;
    for(int i; i < enemy_count; ++i){
        Act_Enemies.push_back(EnemyFactory::create_random());
    }
    Playing_Player.Return_Character().Clear_Effects();
    current_battle = new Battle(&Playing_Player, Act_Enemies, Game_Window, &end, &e_counter, &d_info);
    
    State_of_Game = GameState::Battle;
}

void GameMaster::Update_Battle_Frame(int mx, int my, bool isClicked) {
    if (current_battle == nullptr) 
    {
        return;
    }

    // Obsługa kliknięć
    if(isClicked){
        current_battle->Handle_Mouse_Click(mx, my);
        current_battle->Undertaker();
    }

    current_battle->EnemyAction();
    
    current_battle->Render_Cards();
    current_battle->Render_Player();
    current_battle->Render_Enemies();
    current_battle->Render_Energy_Counter();
    current_battle->Render_End_Turn_Button();
    current_battle->Render_Card_Info_Piles();
    if(current_battle->Return_Is_Battle_Over() == true)
    {
        if(current_battle->Return_Player_Lost() == true)
        {
            State_of_Game = GameState::LoseBattle;
        }
        else if (current_battle->Return_Enemy_Lost() == true)
        {
            State_of_Game = GameState::WinBattle;
        }
    }
}
void GameMaster::Genarate_Cards_To_Choose()
{
    if(Card_to_Choose.empty() == false)
    {
        for (Card* ptr : Card_to_Choose)
        {
            delete ptr; 
        }
        Card_to_Choose.clear();
    }
    Card_to_Choose.push_back(CardFactory::create_random());
    Card_to_Choose.push_back(CardFactory::create_random());
    Card_to_Choose.push_back(CardFactory::create_random());

    State_of_Game = GameState::CardChoice;
}
void GameMaster::Choose_Card_To_Add(int mx, int my, bool isClicked)
{
    bool kliknieto_karte = false;
    if (Game_Window != nullptr)
    {
        Game_Window->draw(Choose_Card_Text);
        Choose_Button.draw(*Game_Window, menu_font);
        Skip_Button.draw(*Game_Window, menu_font); 
    
        int cards_to_choose = Card_to_Choose.size();
        for(int i = 0; i < cards_to_choose; ++i)
        {
            auto card = Card_to_Choose.at(i);
            card->set_position(int((Game_Window->getSize().x / (cards_to_choose + 1) * (i + 1) - card->get_dim_x()/2)), int(Game_Window->getSize().y - card->get_dim_y() - 10) - 100);
            card->draw(*Game_Window, menu_font);
        }
    }
    if (isClicked)
    {
        if (mx >= Skip_Button.get_x() && mx <= Skip_Button.get_x() + Skip_Button.get_dim_x() &&
            my >= Skip_Button.get_y() && my <= Skip_Button.get_y() + Skip_Button.get_dim_y())
            {
                    Selected_Card = nullptr;
                    Start_New_Battle();
            }
        
        for(int i = 0; i <Card_to_Choose.size(); i++)
		{
			Card* sprawdzana_karta = Card_to_Choose.at(i);
			int x = sprawdzana_karta->get_x();
			int y = sprawdzana_karta->get_y();
			int dim_x = sprawdzana_karta->get_dim_x();
			int dim_y = sprawdzana_karta->get_dim_y();

			if(mx >= x && mx <= x + dim_x && my >= y && my <= y + dim_y)
			{
				if(Selected_Card != nullptr) 
                {
					Selected_Card->set_highlight_state(highlight::none);
				}

				sprawdzana_karta->set_highlight_state(highlight::positive);
				Selected_Card = sprawdzana_karta;
				Selected_Card_Index = i;
				
				kliknieto_karte = true;
				break;
			}
		}
        if (!kliknieto_karte)
        {
            if (mx >= Choose_Button.get_x() && mx <= Choose_Button.get_x() + Choose_Button.get_dim_x() &&
                my >= Choose_Button.get_y() && my <= Choose_Button.get_y() + Choose_Button.get_dim_y())
                {
                    if(Selected_Card != nullptr)
                    {
                        Selected_Card->set_highlight_state(highlight::none);
                        Playing_Player.Add_Card(Selected_Card->clone());
                        Selected_Card = nullptr;
                        Start_New_Battle();
                    }

                }
            
        }
    }
    
}
GameState GameMaster::Return_State_Of_Game()
{
    return State_of_Game;
}
GameMaster::~GameMaster()
{

}