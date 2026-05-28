#include "Battle.h"

Battle::Battle()
{
	player = new Player;
}
Battle::Battle(Player* pl, std::vector<Enemy> be, sf::RenderWindow *bw)
{
	player = pl;
	Battle_Enemies = be;
	player->SetHand();
	battle_window = bw;
	card_font.loadFromFile("resources/fonts/Andale_Mono.ttf");
}
void Battle::PlayerTurn()
{
	bool g = false;
	int tt;
	while (g == true)
	{
		std::cout << "Aktualna Energia: " << player->Return_Current_Energy() << "/" << player->Return_Max_Energy() << std::endl;
		std::cout << "Aktualna Tarcza: " << player->Return_Character().Return_Shield() << std::endl;
		std::cout << std::endl;
		std::cout << "Tura nr:." << TurnCounter << std::endl;
		std::cout << std::endl;
		std::cout << player->Return_Character().Return_Name() << " " << player->Return_Character().Return_CurrentHP()<<"/"<< player->Return_Character().Return_MaxHP() << " ";
		std::cout << Battle_Enemies.at(0).Return_Name() << " " << Battle_Enemies.at(0).Return_CurrentHP() << "/" << Battle_Enemies.at(0).Return_MaxHP();
		for (int i = 1; i < Battle_Enemies.size(); i++)
		{
			std::cout << " & " << Battle_Enemies.at(i).Return_Name() << " " << Battle_Enemies.at(i).Return_CurrentHP() << "/" << Battle_Enemies.at(i).Return_MaxHP();
		}
		std::cout << std::endl;
		std::cout << "Co chcesz zrobic? " << std::endl;
		std::cout << " 0 --- jakie mam karty w stosie" << std::endl;
		std::cout << " 1 --- jakie mam karty w rece" << std::endl;
		std::cout << " 2 --- jakie mam discarded karty " << std::endl;
		std::cout << " 3 --- zagraj karte " << std::endl;
		std::cout << " 4 --- skoncz ture " << std::endl;
		std::cout << " 5 --- wyjdz" << std::endl;
		std::cin >> tt;
		switch (tt)
		{
		case 0:
		{
			std::cout << "\033[2J\033[1;1H";
			player->All_Cards();
			break;
		}
		case 1:
		{
			std::cout << "\033[2J\033[1;1H";
			player->All_Hand_Cards();
			break;
		}
		case 2:
		{
			std::cout << "\033[2J\033[1;1H";
			player->All_Discard_Cards();
			break;
		}
		case 3:
		{
			std::cout << "\033[2J\033[1;1H";
			CanPlayCardCheck();
			break;
		}
		case 4:
		{
			std::cout << "\033[2J\033[1;1H";
			EndPlayerTurn();
			break;
		}
		case 5:
		{
			g = false;
			break;
		}
		default:
		{
			std::cout << "\033[2J\033[1;1H";
			std::cout << "Zla opcja" << std::endl;
			continue;
		}
		}
	}
}
void Battle::EndPlayerTurn()
{
	player->Reset_Energy();
	player->RerollHand();
	EnemyAction();
}
void Battle::Render_Cards()
{
	//rysowanie kart:
    int cards_on_hand = player->Return_PlayerHand().size();
    for(int i = 0; i < cards_on_hand; ++i){
        auto card = player->Return_PlayerHand().at(i);
        card->set_position(int((battle_window->getSize().x / (cards_on_hand + 1) * (i + 1) - card->get_dim_x()/2)), int(battle_window->getSize().y - card->get_dim_y() - 10));
        card->draw(*battle_window, card_font);
		card->update_texture();
    }
}
void Battle::Render_Player()
{
	//rysowanie postaci gracza
    player->Return_Character().set_position(int(battle_window->getSize().x / 6 - player->Return_Character().get_dim_x()/2), int (battle_window->getSize().y / 4));
    player->Return_Character().draw(*battle_window, card_font);
	player->Return_Character().update_texture();
}
void Battle::Render_Enemies()
{
	for(int i = 0; i < Battle_Enemies.size(); ++i)
	{
        Battle_Enemies.at(i).set_position(int(battle_window->getSize().x / 2 * (1 + 1/((Battle_Enemies.size() + 1) * (i + 1))) + Battle_Enemies.at(i).get_dim_x()), int(battle_window->getSize().y / 4));
        Battle_Enemies.at(i).draw(*battle_window, card_font);
		Battle_Enemies.at(i).update_texture();
    }
}
void Battle::Select_Card(int mx, int my)
{
	for(int i = 0; i < player->Return_PlayerHand().size(); i++)
	{
        int x = player->Return_PlayerHand().at(i)->get_x();
        int y = player->Return_PlayerHand().at(i)->get_y();
        int dim_x = player->Return_PlayerHand().at(i)->get_dim_x();
        int dim_y = player->Return_PlayerHand().at(i)->get_dim_y();
		
        if(mx >= x && mx <= x + dim_x && my >= y && my <= y + dim_y)
		{
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
                player->Return_PlayerHand().at(i)->set_highlight_state(highlight::positive);
				Selected_Card = player->Return_PlayerHand().at(i);
				Selected_Card_Index = i;
            }
        }
        else
		{
			
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				player->Return_PlayerHand().at(i)->set_highlight_state(highlight::none);
				Selected_Card = nullptr;

			}
							
        }
    }
}
void Battle::Handle_Mouse_Click(int mx, int my)
{
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) return;

    bool kliknieto_karte = false;
    bool kliknieto_wroga = false;


    for(int i = 0; i < player->Return_PlayerHand().size(); i++)
    {
        Card* sprawdzana_karta = player->Return_PlayerHand().at(i);
        int x = sprawdzana_karta->get_x();
        int y = sprawdzana_karta->get_y();
        int dim_x = sprawdzana_karta->get_dim_x();
        int dim_y = sprawdzana_karta->get_dim_y();

        if(mx >= x && mx <= x + dim_x && my >= y && my <= y + dim_y)
        {

            if(Selected_Card != nullptr) {
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
        for(int i = 0; i < Battle_Enemies.size(); i++)
        {
            int x = Battle_Enemies.at(i).get_x();
            int y = Battle_Enemies.at(i).get_y();
            int dim_x = Battle_Enemies.at(i).get_dim_x();
            int dim_y = Battle_Enemies.at(i).get_dim_y();

            if(mx >= x && mx <= x + dim_x && my >= y && my <= y + dim_y)
            {
                Selected_Enemy = &Battle_Enemies.at(i);
                Selected_Enemy->set_highlight_state(highlight::positive);
                kliknieto_wroga = true;


                if(Selected_Card != nullptr)
                {
                    CanPlayCardCheck2(Selected_Card, Selected_Enemy, Selected_Card_Index);
                    Selected_Card->set_highlight_state(highlight::none);
                    Selected_Card = nullptr;
                    Selected_Enemy->set_highlight_state(highlight::none);
                    Selected_Enemy = nullptr;
                }
                break; 
            }
        }
    }
    if (!kliknieto_karte && !kliknieto_wroga)
    {
        
        if (Selected_Card != nullptr)
        {
            Selected_Card->set_highlight_state(highlight::none);
            Selected_Card = nullptr;
        }
        
        
        if (Selected_Enemy != nullptr)
        {
            Selected_Enemy->set_highlight_state(highlight::none);
            Selected_Enemy = nullptr;
        }
        
    }
}
void Battle::Select_Enemy(int mx, int my)
{
	for(int i = 0; i < Battle_Enemies.size(); i++)
	{
        int x = Battle_Enemies.at(i).get_x();
        int y = Battle_Enemies.at(i).get_y();
        int dim_x = Battle_Enemies.at(i).get_dim_x();
        int dim_y = Battle_Enemies.at(i).get_dim_y();
        if(mx >= x && mx <= x + dim_x && my >= y && my <= y + dim_y)
		{
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
                Battle_Enemies.at(i).set_highlight_state(highlight::positive);
				Selected_Enemy = &Battle_Enemies.at(i);
				if(Selected_Card != nullptr)
				{
					CanPlayCardCheck2(Selected_Card, Selected_Enemy, Selected_Card_Index);
					Selected_Card = nullptr;
				}
            }
        }
        else
		{
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
                Battle_Enemies.at(i).set_highlight_state(highlight::none);
				Selected_Enemy = nullptr;

            }
        }
    }
}
void Battle::EnemyAction()
{
	for (int i = 0; i < Battle_Enemies.size(); i++)
	{
		Battle_Enemies.at(i).EnemyBehaviour();
	}
	TurnCounter += 1;
	PlayerTurn();
}
void Battle::EndBattleCheck()
{
	bool End = true;
	for(int i = 0; i < Battle_Enemies.size(); i++)
	{
		if(Battle_Enemies.at(i).Return_isDead() == false)
		{
			End = false;
		}
	}
	if(End == true)
	{
		std::cout<<" KONIEC "<<std::endl;
	}
}
std::vector<Enemy>& Battle::Return_Enemies()
{
	return Battle_Enemies;
}
void Battle::CanPlayCardCheck()
{
	int g;
	std::cout << "Jaka karte chcesz zagrac? " << std::endl;
	player->All_Hand_Cards();
	std::cin >> g;
	if (player->Return_Current_Energy() >= player->Return_PlayerHand().at(g)->Return_Card_Cost())
	{
		player->PlayCard(g)->Card_Effect(this);
	}
	else
	{
		std::cout << "Nie masz energii by zagrac te karte :( " << std::endl;
	}
}
void Battle::CanPlayCardCheck2(Card *c, Enemy *e, int i)
{
	if (player->Return_Current_Energy() >= c->Return_Card_Cost())
	{
		player->PlayCard(i)->Card_Effect(this);
	}
	else
	{
		std::cout << "Nie masz energii by zagrac te karte :( " << std::endl;
	}
}
Player* Battle::Return_Player()
{
	return player;
}
Enemy* &Battle::Return_Selected_Enemy()
{
	return Selected_Enemy;
}
Battle::~Battle()
{

}