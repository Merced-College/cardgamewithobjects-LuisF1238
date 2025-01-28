// Luis Flores
// Caydin Klups
// Hemant Kulkarni
// 01/28/2024
// Card Game With Objects




#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class Card {
public:
  // Constructor
  Card() : suit(""), rank(""), value(0) {}

  Card(string suit, string rank, int value) : suit(suit), rank(rank), value(value) {}

  // Getters
  string get_suit() const { return suit; }
  string get_rank() const { return rank; }
  int get_value() const { return value; }

  // Setters
  void set_suit(string suit) { this->suit = suit; }
  void set_rank(string rank) { this->rank = rank; }
  void set_value(int value) { this->value = value; }

  // Method to print card details
  void print_card() const {
    cout << rank << " of " << suit << " (Value: " << value << ")" << endl;
  }

private:
  string suit;
  string rank;
  int value;
};

const string SUITS[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
const string RANKS[] = {"2", "3",  "4",    "5",     "6",    "7",  "8",
                        "9", "10", "Jack", "Queen", "King", "Ace"};
const int VALUES[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

Card deck[52];
int currentCardIndex = 0;

void initializeDeck() {
  int deckIndex = 0;
  for (int suitIndex = 0; suitIndex < 4; suitIndex++) {
    for (int rankIndex = 0; rankIndex < 13; rankIndex++) {
      deck[deckIndex++] = Card(SUITS[suitIndex], RANKS[rankIndex], VALUES[rankIndex]);
    }
  }
}

void shuffleDeck() {
  srand((time(0)));
  for (int i = 0; i < 52; i++) {
    int index = rand() % 52;
    Card temp = deck[i];
    deck[i] = deck[index];
    deck[index] = temp;
  }
}

Card dealCard() {
  return deck[currentCardIndex++];
}

int dealInitialPlayerCards() {
  Card card1 = dealCard();
  Card card2 = dealCard();
  cout << "Your cards: ";
  card1.print_card();
  card2.print_card();
  return card1.get_value() + card2.get_value();
}

int playerTurn(int playerTotal) {
  while (true) {
    cout << "Your total is " << playerTotal << ". Do you want to hit or stand?" << endl;
    string action;
    getline(cin, action);
    if (action == "hit") {
      Card newCard = dealCard();
      playerTotal += newCard.get_value();
      cout << "You drew a ";
      newCard.print_card();
      if (playerTotal > 21) {
        break;
      }
    } else if (action == "stand") {
      break;
    } else {
      cout << "Invalid action. Please type 'hit' or 'stand'." << endl;
    }
  }
  return playerTotal;
}

int main() {
  initializeDeck();
  shuffleDeck();

  double playerMoney = 100.0; // Initial player money

  while (playerMoney > 0) {
    cout << "You have $" << playerMoney << ". How much would you like to bet?" << endl;
    double bet;
    cin >> bet;
    cin.ignore(); // Ignore the newline character left in the input buffer

    if (bet <= 0 || bet > playerMoney) {
      cout << "Invalid bet amount. Please try again." << endl;
      continue;
    }

    int playerTotal = dealInitialPlayerCards();
    cout << "Your total is " << playerTotal << endl;

    playerTotal = playerTurn(playerTotal);

    if (playerTotal > 21) {
      cout << "You busted! Dealer wins." << endl;
      playerMoney -= bet;
    } else {
      // Dealer's turn (simple logic: dealer hits until 17 or higher)
      int dealerTotal = 0;
      while (dealerTotal < 17) {
        Card dealerCard = dealCard();
        dealerTotal += dealerCard.get_value();
      }

      cout << "Dealer's total is " << dealerTotal << endl;

      if (dealerTotal > 21 || playerTotal > dealerTotal) {
        cout << "You win!" << endl;
        playerMoney += bet;
      } else if (playerTotal < dealerTotal) {
        cout << "Dealer wins." << endl;
        playerMoney -= bet;
      } else {
        cout << "It's a tie!" << endl;
      }
    }

    if (playerMoney <= 0) {
      cout << "You're out of money! Game over." << endl;
      break;
    }

    cout << "Do you want to play another round? (yes/no)" << endl;
    string response;
    getline(cin, response);
    if (response != "yes") {
      cout << "Thank you for playing! You leave with $" << playerMoney << "." << endl;
      break;
    }

    currentCardIndex = 0; // Reset the deck index
    shuffleDeck();       // Shuffle for a new round
  }

  return 0;
}