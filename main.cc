#include <iostream>

#include <random>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sstream>

// implement money

using namespace std;

int generate_random(int num, string hold);

int money = 500;

// these variables define if the player or dealer 
// have As (can represent either an 1 or 11).
//
// char consumes less memory than built-in integers.
char player_as = '0';	
char dealer_as = '0';

int main() {
  int player_count = 0;
  int dealer_count = 0;
  string input;


  cout << "Welcome to blackjack." << endl << endl;

RESET:
  while (true) {
    REPLAY:
    int bet = 0;
    cout << "You have " << money << " dollars. Bet how much?" << endl;
    cin >> input;

    // try to transform input to an integer,
    // and if something goes wrong, ask to reinput.
    istringstream iss(input);
    iss >> bet;

    if (bet <= 0 || bet > money) {
      cout << "Invalid bet." << endl << endl;
      goto RESET;
    }

    player_count = 0;
    dealer_count = 0;

    player_count += generate_random(10, "player");
    player_count += generate_random(10, "player");

    dealer_count += generate_random(10, "dealer");

    cout << endl << "You have " << player_count << " points." << endl;
    cout << "The dealer has " << dealer_count << " points." << endl << endl;

    while (player_count <= 21) {
      cout << "Hit or stay? h = hit, s = stay. ";
      cin >> input;

      if (input == "h" || input == "hit") {
        player_count += generate_random(10, "player");


        cout << "You have " << player_count << " points." << endl << endl;
      }

      else if (input == "s" || input == "stay") {
        while (dealer_count < player_count) {
          dealer_count += generate_random(10, "dealer");
          cout << "The dealer has " << dealer_count << " points." << endl;
        }

        if (dealer_count > player_count && (dealer_count <= 21 || (dealer_count == 11 && dealer_as == '1'))) {
          cout << endl << "You lost." << endl;
          money -= bet;
          goto REPLAY;
        }

        else {
          cout << endl << "You won!" << endl;
          money += bet;
          goto REPLAY;
        }
      }

      if ((player_count == 21) || (player_count == 11 && player_as == '1')) {
        cout << endl << "You won!" << endl;
        money += bet;
        goto REPLAY;
      }
    }
    cout << "You lost!" << endl;
    money -= bet;
    goto REPLAY;
  }
  return 0;
}

int generate_random(int num, string hold) {
  if (num == 10) {
    num = 13;
  }

  struct timeval t;
  gettimeofday(&t, NULL);
  pid_t pid = getpid();
  srand(t.tv_usec * t.tv_sec * pid);
  int i = rand() % num;

  while (i == 0) {
    i = rand() % num;
  }

  if (i > 10) {
    i = 10;
  }

  if (hold == "player") {
    player_as = '1';
  }

  if (hold == "dealer") {
    dealer_as = '1';
  }

  return i;
}
