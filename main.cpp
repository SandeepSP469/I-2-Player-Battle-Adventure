#include<iostream>
class Ranger
{
public:
    int health;
    int maxHealth;
    int basePower;
    int baseHeal;
    int maxheal;
    int basedamage;
    int maxdamage;
    Ranger(int h, int bp, int bh, int mh, int bd, int md)
    {
        maxHealth = h;
        health = h;
        basePower = bp;
        baseHeal = bh;
        maxheal = mh;
        basedamage = bd;
        maxdamage = md;
    }

    bool IsAlive()
{ 
  return health > 0; 
  }
    float Attack() 
    { 
        return basePower + GetAdditionalDamage();
    }
    float virtual GetAdditionalDamage() 
{ 
  return 0; 
  }
    void TakeDamage(int damage) 
{ 
  health -= damage; 
  }
    void Heal()
    {
        if (OverHeal())
        {
            std::cout << "\nMaximum health Chance Wasted!!!";
            return;
        }
        float effectiveHealing = GetEffectiveHealing();
        std::cout << "\nHealed " << effectiveHealing;
        health += effectiveHealing;
        if (OverHeal())
            health = maxHealth;
    }
    bool OverHeal()
    { 
     return health >= maxHealth;
    }
    float GetEffectiveHealing() 
    { 
      return (rand() % 30) + (baseHeal + (rand() % maxheal)); 
    }

    void Stats()
    {
        std::cout << "\nHealth : " << health;
        std::cout << "\nAttack Power : " << basePower;
        std::cout << "\nHealing range: " << baseHeal <<"-" << maxheal;
        std::cout << "\nMaximum damage range:"<< basedamage <<"-"<< maxdamage;
    }
};

class Green : public Ranger {
public:
    Green() : Ranger(500, 10, 10, 20, 20, 30) 
    {
        std::cout << "I will fight for you with the help of the dragon zord";
    }

    float GetAdditionalDamage()
    {
        int additionalDamage = (rand() % 50) + (basedamage + (rand() % maxdamage));
        std::cout << "Addition Damage " << additionalDamage<< " is Dealt";
        return additionalDamage;
    }

};

class White : public Ranger {
public:
    White() : Ranger(300, 30, 30, 40, 15, 25) 
    {
        std::cout << "\nI will fight for you with the help of the falcon zord";
    }

    float GetAdditionalDamage()
    {
        int additionalDamage = (rand() % 30) + (basedamage + (rand() % maxdamage));
        std::cout << "Addition Damage " << additionalDamage << " is Dealt";
        return additionalDamage;
    }
};

class Red : public Ranger {
public:
    Red() : Ranger(100, 50, 30, 35, 18, 28)
    {
        std::cout << "\nI will fight for you with the help of the zeo crystal";
    }

    float GetAdditionalDamage()
    {
        int additionalDamage = (rand() % 10) + (basedamage + (rand() % maxdamage));
        std::cout << "Addition Damage " << additionalDamage << " is Dealt";
        return additionalDamage;
    }

};

class Game{

    Ranger* players[3];

    void ShowInstructions()
    {
        std::cout<<" ############################# \n";
        std::cout<<std::endl;
        std::cout<<"           WELCOME  \n";
        std::cout<<"             TO \n";
        std::cout<<"        Power Rangers \n";
        std::cout<<"     A 2-Player battle adventure \n";
        std::cout<<std::endl;
        std::cout<<" ############################# \n";
        std::cout<<std::endl;
        std::cout << "Instructions :\n";
        std::cout << "1) Each Player is given a turn \n";
        std::cout << "2) The player can either damage the other player or they can heal themselves \n";
        std::cout << "3) Press A to attack and H to heal \n";
        std::cout << "4) The player whose health goes below 0 first, will loose the game \n";
 
    }
    void ShowPlayerTypeInstuction()
    {
        std::cout << "\n\nPlease select a ranger:\n";
        std::cout << "Enter 1 to morph into Green MMPR Ranger \n";
        std::cout << "Enter 2 to morph into White MMPR Ranger \n";
        std::cout << "Enter 3 to morph into Zeo Ranger V \n";
    }
    void ShowStats()
    {
        std::cout<<"\n\nPlayer 1 Stats";
        players[1]->Stats();

        std::cout << "\nPlayer 2 Stats";
        players[2]->Stats();
    }
    bool Restart()
    {
        char choice;
        std::cout << "\n\nPress 'R' To Restart. Choice : " << std::endl;
        std::cin >> choice;

        return (choice == 'R' || choice == 'r') ? true : false;
    }
    

    void DeletePlayers()
    {
        delete players[1];
				delete players[2];
    }
    
    void PlayerSelection()
    {
        for (int playerTurn = 1; playerTurn <= 2; playerTurn++)
        {
            ShowPlayerTypeInstuction();
            int typeChoice;
            do
            {
                std::cout << "\nPlayer " << playerTurn << " : Select player type\n";
                std::cout << "Player Type : ";
                std::cin >> typeChoice;
                switch (typeChoice)
                {
                    case 1:
                    case 2:
                    case 3:
                        CreatePlayer(playerTurn, typeChoice);
                        break;
                    default:
                        std::cout << "\nWRONG choice.. Try again!!\n";
                }
            } while (typeChoice < 1 || typeChoice > 3);
        }
    }
    void CreatePlayer(int playerTurn, int type)
    {
        std::cout << "\nPlayer " << playerTurn << " Selected " << type;
        players[playerTurn] = GetCharacterOfType(type);
        players[playerTurn]->Stats();
    }  
    Ranger* GetCharacterOfType(int type)
    {
        switch (type)
        {
        case 1:
            return new Green();
        case 2:
            return new White();
        case 3:
            return new Red();
        }
    }

    bool IsPlayersAlive() { return players[1]->IsAlive() && players[2]->IsAlive(); }
    void Battle()
    {

        bool isPlayer2Turn = false;
        while(IsPlayersAlive())
        {
            ShowStats();
            std::cout << "\n\nPlayer " << isPlayer2Turn + 1 << ", Choose your Action \nPress 'H' to heal and 'A' to attack.\nAction : ";
            bool isActionValid;
            do
            {
                isActionValid = true;
                char choice;
                std::cin >> choice;
                switch (choice)
                {
                case 'a':
                case 'A':
                    players[(!isPlayer2Turn) + 1]->TakeDamage(players[isPlayer2Turn + 1]->Attack());
                    break;
                case 'h':
                case 'H':
                    players[isPlayer2Turn + 1]->Heal();
                    break;
                default:
                    std::cout << "\nInvalid Action. Try again!!";
                    isActionValid = false;
                    break;
                }
            } while (!isActionValid);
            isPlayer2Turn = !isPlayer2Turn;
        }  

        GameOver((!isPlayer2Turn)+1);
    }

    void GameOver(int playerIndex)
    {
        std::cout << "\nPlayer " << playerIndex << " Wins";
    }

public:
    void startgame()
    {
        bool play = true;
        while (play)
        {
            ShowInstructions();
            PlayerSelection();
            Battle();
            DeletePlayers();
            play = Restart();
        }
    }
};

int main()
{
  Game play;
  play.startgame();
}