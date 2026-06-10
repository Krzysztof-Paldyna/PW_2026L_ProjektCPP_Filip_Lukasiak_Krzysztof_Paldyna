#include "Battle.h"

Battle::Battle()
{
	player = new Player;
}
Battle::Battle(Player* pl, std::vector<Enemy*> be, sf::RenderWindow *bw, graphics_object_end_turn *end, graphics_object_energy_counter *e_counter, graphics_object_deck_info *d_info)
{
	player = pl;
	Battle_Enemies = be;
	player->SetHand();
	battle_window = bw;
	card_font.loadFromFile("resources/fonts/Andale_Mono.ttf");
	end_turn_button = end;
	energy_counter = e_counter;
	deck_amount_info = d_info;
	isBattleOver = false;
}
void Battle::EndPlayerTurn()
{
	player->Reset_Energy();
	player->RerollHand();
	end_turn_button->set_highlight_state(highlight::none);
	end_turn_button->set_is_Player_Turn(false);
	currentState = BattleState::Enemy_turn;
}
void Battle::EnemyAction()
{
	if(currentState == BattleState::Enemy_turn){
		//akcje przeciwników
		for(auto &v : Battle_Enemies)
		{
			v->Update_End_of_Turn_Effects();
			v->Add_Shield(-1 * v->Return_Shield());
		}
		Undertaker();
		for(auto &v : Battle_Enemies)
		{
			v->EnemyBehaviour(this);
			EndBattleCheck();
		}
		TurnCounter += 1;

		//akcje na początku tury gracza:
		currentState = BattleState::Player_turn;
		end_turn_button->set_is_Player_Turn(true);
		player->Return_Character().Update_End_of_Turn_Effects();
		player->Return_Character().Add_Shield(-1 * player->Return_Character().Return_Shield());
	}
}
void Battle::Render_Cards()
{
	//rysowanie kart:
    int cards_on_hand = player->Return_PlayerHand().size();
    for(int i = 0; i < cards_on_hand; ++i){
        auto card = player->Return_PlayerHand().at(i);
        card->set_position(int((battle_window->getSize().x / (cards_on_hand + 1) * (i + 1) - card->get_dim_x()/2)), int(battle_window->getSize().y - card->get_dim_y() - 10));
        card->draw(*battle_window, card_font);
    }
}
void Battle::Render_Player()
{
	//update wartości graficznych
	player->Return_Character().set_hp(player->Return_Character().Return_CurrentHP());
	player->Return_Character().set_shield(player->Return_Character().Return_Shield());
	//rysowanie postaci gracza
    player->Return_Character().set_position(int(battle_window->getSize().x / 6 - player->Return_Character().get_dim_x()/2), int (battle_window->getSize().y / 4));
    player->Return_Character().draw(*battle_window, card_font);
	
	if(player->Return_Character().Return_Damage_Val().size() > 0){
		for(auto &v : player->Return_Character().Return_Damage_Val()){
			v.draw(*battle_window, card_font);
		}
		for(int i = 0; i < player->Return_Character().Return_Damage_Val().size(); ++i){
			if(!player->Return_Character().Return_Damage_Val().at(i).get_state()){
				player->Return_Character().Return_Damage_Val().erase(player->Return_Character().Return_Damage_Val().begin() + i);
				//std::cout << "player damage icon deleted" << std::endl;
				--i;
			}
		}
	}
}
void Battle::Render_Enemies()
{
	float Enemy_Count = Battle_Enemies.size();
	for(int i = 0; i < Enemy_Count; ++i)
	{
		//update wartości graficznych
		Battle_Enemies.at(i)->set_hp(Battle_Enemies.at(i)->Return_CurrentHP());
		Battle_Enemies.at(i)->set_shield(Battle_Enemies.at(i)->Return_Shield());
		//rysowanie wrogów w odpowiednich pozycjach
        Battle_Enemies.at(i)->set_position(int(battle_window->getSize().x * (0.35 + 0.7*(i + 1)/(Enemy_Count + 1)) - Battle_Enemies.at(i)->get_dim_x()/1.25), int(battle_window->getSize().y / 4));
		Battle_Enemies.at(i)->draw(*battle_window, card_font);

		if(Battle_Enemies.at(i)->Return_Damage_Val().size() > 0){
			for(auto &v : Battle_Enemies.at(i)->Return_Damage_Val()){
				v.draw(*battle_window, card_font);
			}
			for(int j = 0; j < Battle_Enemies.at(i)->Return_Damage_Val().size(); ++j){
				if(!Battle_Enemies.at(i)->Return_Damage_Val().at(j).get_state()){
					Battle_Enemies.at(i)->Return_Damage_Val().erase(Battle_Enemies.at(i)->Return_Damage_Val().begin() + j);
					//std::cout << "enemy damage icon deleted" << std::endl;
					--j;
				}
			}
		}
    }
}

void Battle::Render_End_Turn_Button()
{
	end_turn_button->draw(*battle_window, card_font);
}

void Battle::Render_Energy_Counter(){
	energy_counter->update_current_energy(player->Return_Current_Energy());
	energy_counter->update_max_energy(player->Return_Max_Energy());
	energy_counter->draw(*battle_window, card_font);
}

void Battle::Render_Card_Info_Piles()
{
	deck_amount_info->update_discard_info(player->Return_DiscardDeck().size());
	deck_amount_info->update_draw_info(player->Return_PlayerDeck().size());
	deck_amount_info->draw(*battle_window, card_font);
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
    bool kliknieto_karte = false;
    bool kliknieto_wroga = false;
	bool kliknieto_end = false;

	if(mx >= end_turn_button->get_x() && mx <= end_turn_button->get_x() + end_turn_button->get_dim_x() && my >= end_turn_button->get_y() && my <= end_turn_button->get_y() + end_turn_button->get_dim_y()){
		kliknieto_end = true;
		EndPlayerTurn();
		return;
	}

    if(!kliknieto_end){
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
	}

    if (!kliknieto_karte)
    {
        for(int i = 0; i < Battle_Enemies.size(); i++)
        {
            int x = Battle_Enemies.at(i)->get_x();
            int y = Battle_Enemies.at(i)->get_y();
            int dim_x = Battle_Enemies.at(i)->get_dim_x();
            int dim_y = Battle_Enemies.at(i)->get_dim_y();

            if(mx >= x && mx <= x + dim_x && my >= y && my <= y + dim_y)
            {
                Selected_Enemy = Battle_Enemies.at(i);
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
        int x = Battle_Enemies.at(i)->get_x();
        int y = Battle_Enemies.at(i)->get_y();
        int dim_x = Battle_Enemies.at(i)->get_dim_x();
        int dim_y = Battle_Enemies.at(i)->get_dim_y();
        if(mx >= x && mx <= x + dim_x && my >= y && my <= y + dim_y)
		{
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
                Battle_Enemies.at(i)->set_highlight_state(highlight::positive);
				Selected_Enemy = Battle_Enemies.at(i);
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
                Battle_Enemies.at(i)->set_highlight_state(highlight::none);
				Selected_Enemy = nullptr;

            }
        }
    }
}

void Battle::Undertaker(){
	if(Battle_Enemies.size() > 0){
		for(int i = 0; i < Battle_Enemies.size(); ++i){
			if(Battle_Enemies.at(i)->Return_isDead()){
				Battle_Enemies.erase(Battle_Enemies.begin() + i);
				--i;
			}
		}
	}
	EndBattleCheck();
}

void Battle::EndBattleCheck()
{
	if(player->Return_Character().Return_isDead() == true)
	{
		isBattleOver = true;
		PlayerLost = true;
	}
	if(Battle_Enemies.size() == 0)
	{
		player->Reset_Energy();
		player->Return_Discarded_Cards_to_Deck();
		player->Return_Hand_Cards_to_Deck();
		player->Return_Character().Add_Shield(-1 * player->Return_Character().Return_Shield());
		std::cout<<" KONIEC "<<std::endl;
		isBattleOver = true;
		EnemyLost = true;
	}
}

std::vector<Enemy*>& Battle::Return_Enemies()
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
bool Battle::Return_Is_Battle_Over()
{
	return isBattleOver;
}

bool Battle::Return_Player_Lost()
{
	return PlayerLost;
}
bool Battle::Return_Enemy_Lost()
{
	return EnemyLost;
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
