#include <iostream>
using namespace std;
#include <cstdlib>

class Player {
protected:
  int maximumHealth;
  int health;
  int baseDamage;
  int additionalDamage;
  int maximumAdditionalDamage;
  int heal;
  int minimumHealValue;
  int maximumHealValue;

  void SetHeal() {
    srand(time(0));
    heal =
        rand() % (maximumHealValue - minimumHealValue + 1) + minimumHealValue;
  }

  void SetAdditionalDamage() {
    // srand(time(0));
    additionalDamage = rand() % maximumAdditionalDamage;
  }

public:
  int GetHealth() { return health; }
  int GetBaseDamage() { return baseDamage; }
  int GetAdditionalDamage() { return additionalDamage; }

  virtual void TakeDamage(int value) {
    if ((health - value) < 0) {
      value += (health - value);
    }

    health -= value;
  }
  virtual void Heal() {
    if ((heal + health) > maximumHealth) {
      heal = maximumHealth - health;
    }
    health += heal;
  }

  virtual void Attack(Player *currentPlayer) {
    SetAdditionalDamage();
    currentPlayer->TakeDamage(baseDamage + additionalDamage);
  }

  virtual void SpecialAbility() = 0;

  virtual ~Player() {}
};

class HugePlayer : public Player {
public:
  HugePlayer() {
    maximumHealth = 300;
    health = maximumHealth;
    baseDamage = 20;
    maximumAdditionalDamage = 5;
    minimumHealValue = 5;
    maximumHealValue = 15;

    cout << "Hey I am a HugePlayer,\nthanks for selecting me\n\n"
         << "Player health is " << health << endl
         << "BaseDamage is " << baseDamage << endl
         << "Additional Damage is "
         << "0 - " << maximumAdditionalDamage << endl
         << "Healing capacity is " << minimumHealValue << " - "
         << maximumHealValue << endl
         << "Special Ability is High Heal\n"
         << endl;
  }
  void TakeDamage(int value) override {
    Player::TakeDamage(value);
    cout << "HugePlayer is taking Damage";
  }

  void Heal() override {
    if (health < maximumHealth) {
      Player::SetHeal();

      srand(time(0));
      int hugeRandom = rand() % 100 + 1;

      if (hugeRandom % 5 == 0) {
        SpecialAbility();
      } else {
        cout << "HugePlayer is Getting Healed\n";
      }
      Player::Heal();
      cout << "HugePlayer Got healed by " << heal << endl;
      cout << "HugePlayer's health after getting Healed is " << health << endl;
    } else {
      cout << "You can not be healed anymore\nYou have wasted your turn\n";
    }
  }

  void SpecialAbility() override {
    heal += 15;
    cout << "HugePlayer Just used his special Ability of Healing\n";
  }

  ~HugePlayer() { cout << "HugePlayer just died\n"; }
};

class FastPlayer : public Player {
public:
  FastPlayer() {
    maximumHealth = 100;
    health = maximumHealth;
    baseDamage = 20;
    maximumAdditionalDamage = 10;
    minimumHealValue = 15;
    maximumHealValue = 25;

    cout << "Hey I am a FastPlayer,\nthanks for selecting me\n\n"
         << "Player health is " << health << endl
         << "BaseDamage is " << baseDamage << endl
         << "Additional Damage is "
         << "0 - " << maximumAdditionalDamage << endl
         << "Healing capacity is " << minimumHealValue << " - "
         << maximumHealValue << endl
         << "Special Ability is to Dodge the Attack\n"
         << endl;
  }

  void TakeDamage(int value) override {
    // srand(time(0));
    int fastRandom = rand() % 100 + 1;

    if (fastRandom % 5 == 0) {
      SpecialAbility();
    } else {
      Player::TakeDamage(value);
      cout << "FastPlayer is taking Damage";
    }
  }

  void Heal() override {
    if (health < maximumHealth) {
      Player::SetHeal();
      Player::Heal();
      cout << "FastPlayer is Getting Healed\n";
      cout << "FastPlayer Got healed by " << heal << endl;
      cout << "FastPlayer's health after getting Healed is " << health << endl;
    } else {
      cout << "You can not be healed anymore\nYou have wasted your turn\n";
    }
  }

  void SpecialAbility() override {
    cout << "Amaizing Dodge by Fast player, "
            "this is the benifit of being so"
            "fast that the opponent can't even touch you.\n";
  }

  ~FastPlayer() { cout << "FastPlayer just died\n"; }
};

class StrongPlayer : public Player {
public:
  StrongPlayer() {
    maximumHealth = 200;
    health = maximumHealth;
    baseDamage = 20;
    maximumAdditionalDamage = 15;
    minimumHealValue = 10;
    maximumHealValue = 20;

    cout << "Hey I am a StrongPlayer,\nthanks for selecting me\n\n"
         << "Player health is " << health << endl
         << "BaseDamage is " << baseDamage << endl
         << "Additional Damage is "
         << "0 - " << maximumAdditionalDamage << endl
         << "Healing capacity is " << minimumHealValue << " - "
         << maximumHealValue << endl
         << "Special Ability is Very High Additional Damage\n"
         << endl;
  }

  void TakeDamage(int value) override {
    Player::TakeDamage(value);
    cout << "StrongPlayer is taking Damage";
  }

  void Heal() override {
    if (health < maximumHealth) {
      Player::SetHeal();
      Player::Heal();
      cout << "StrongPlayer is Getting Healed\n";
      cout << "StrongPlayer Got healed by " << heal << endl;
      cout << "StrongPlayer's health after getting Healed is " << health
           << endl;
    } else {
      cout << "You can not be healed anymore\nYou have wasted your turn\n";
    }
  }

  void Attack(Player *currentPlayer) override {
    srand(time(0));
    int strongRandom = rand() % 100 + 1;

    if (strongRandom % 5 == 0) {
      SpecialAbility();
      currentPlayer->TakeDamage(baseDamage + additionalDamage);
    } else {
      Player::Attack(currentPlayer);
    }
  }

  void SpecialAbility() override {
    cout << "StrongPlayer Just used his SpecialAbility\n";
    this->additionalDamage = (rand() % (11)) + 10;
  }

  ~StrongPlayer() { cout << "StrongPlayer just died\n"; }
};

class ArenaManager {
  Player *player1 = nullptr, *player2 = nullptr;

public:
  ArenaManager() { Introduction(); }

  void Introduction() {
    cout << "Welcome to the 2 Player battele royal\n"
         << "where 2 player will fight with each other till deth\n"
         << "Whoever dies Loses, and other player Wins the Game\n"
         << "There are three types of player to chose from\n\n"
         << "1 - HugePlayer : \n"
         << "who has : High Health, Average Damage, Low Heal\n"
         << "and Special ability of gaining High Heal for turn \n(it only "
            "triggers if you try to heal)\n\n"
         << "2 - FastPlayer : \n"
         << "who has : Low Health, Avarage Attack, High Heal\n"
         << "and Special ability to Dodge any Attack\n\n"
         << "3 - StrongPlayer : \n"
         << "who has : Average Health, High Damage, Average Heal\n"
         << "and Special Ability of Very High Additional Damage\n\n";
  }

  void SpawnPlayer(int playerNumber) {
    cout << "Press 1 : for HugePlayer\n"
         << "Press 2 : for FastPlayer\n"
         << "Press 3 : for StrongPlayer\n";
    // Player *p;
    int input;
    cin >> input;

    switch (input) {
    case 1:
      if (playerNumber == 1) {
        player1 = new HugePlayer();
      } else if (playerNumber == 2) {
        player2 = new HugePlayer();
      }
      break;
    case 2:
      if (playerNumber == 1) {
        player1 = new FastPlayer();
      } else if (playerNumber == 2) {
        player2 = new FastPlayer();
      }
      break;
    case 3:
      if (playerNumber == 1) {
        player1 = new StrongPlayer();
      } else if (playerNumber == 2) {
        player2 = new StrongPlayer();
      }
      break;
    default:
      cout << "Enter Valid Input\n";
      SpawnPlayer(playerNumber);
    }
  }

  void ChosePlayerToFight() {
    cout << "Player1, Chose which player do you want to fight with\n";
    SpawnPlayer(1);

    cout << "Player2, Chose which player do you want to fight with\n";
    SpawnPlayer(2);
  }

  char TakeFightInput() {
    cout << "Enter a to Attack\nEnter h to heal\n";
    char input;
    char output;
    cin >> input;

    switch (input) {
    case 'a':
    case 'A':
      output = 'a';
      break;
    case 'h':
    case 'H':
      output = 'h';
      break;
    default:
      cout << "Provide valid input\n";
      output = TakeFightInput();
      break;
    }

    return output;
  }

  void StartFigting() {
    ChosePlayerToFight();
    do {
      cout << "Player 1's Turn\n";
      char input = TakeFightInput();

      if (input == 'h') {
        player1->Heal();
      } else if (input == 'a') {

        player1->Attack(player2);

        cout << "\t(Player2)\n";
        cout << "Additional Damage Given : " << player1->GetAdditionalDamage()
             << "\nTotal Damage done by Player1 is : "
             << player1->GetBaseDamage() + player1->GetAdditionalDamage()
             << "\nHealth of player2 After recieving Damage is : "
             << player2->GetHealth() << endl;
      }

      if (player2->GetHealth() <= 0) {
        delete player2;
        player2 = nullptr;
        cout << "\n\n\nAnd The Winner of the Match is Player1\n\n\n";
        break;
      }

      cout << "Player 2's Turn\n";
      input = TakeFightInput();

      if (input == 'h') {
        player2->Heal();
      } else if (input == 'a') {

        player2->Attack(player1);

        cout << "\t(Player1)\n";
        cout << "Additional Damage Given : " << player2->GetAdditionalDamage()
             << "\nTotal Damage done by Player1 is : "
             << player2->GetBaseDamage() + player2->GetAdditionalDamage()
             << "\nHealth of player1 After recieving Damage is : "
             << player1->GetHealth() << endl;

        if (player1->GetHealth() <= 0) {
          delete player1;
          player1 = nullptr;
          cout << "\n\n\nAnd The Winner of the Match is Player2\n\n\n";
          break;
        }
      }
    } while ((player1->GetHealth() > 0) || (player2->GetHealth() > 0));

    cout << endl;
  }

  ~ArenaManager() {
    if (player1 != nullptr) {
      cout << "Player1 Won!\n";
      delete player1;
    }
    if (player2 != nullptr) {
      cout << "Player2 Won!\n";
      delete player2;
    }
  }
};

int main() {
  srand(time(0));
  ArenaManager fightManager;
  fightManager.StartFigting();
}