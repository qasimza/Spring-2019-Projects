/*
 * Project Title:
 * - Solitaire
 * Description:
 * This program does attempts to recreate a text based version of solitaire
 *
 * Developers:
 * - Zaina Qasim - qasimza@mail.uc.edu
 * - Samantha Shaw - shaws8@mail.uc.edu
 *
 *
 * Developer comments: // Not optional
 * Developer 1: Zaina Qasim
 * Gained experience in pair coding
 * Developer 2:
 * Learned how to implement classes and member functions, the scope of variables
 */

 /*
 * Refer to milestone 1 for a detailed escription of the classes and member functions
 */

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

class Card {
	//private members
	char color;
	char suit;
	int num;
	bool displayed;
	bool accessible;
public:
	char get_color() {
		return color;
	}
	int get_num() {
		return num;
	}
	char get_suit() {
		return suit;
	}
	bool get_displayed() {
		return displayed;
	}
	bool get_accessible() {
		return accessible;
	}
	void set_color(char col) {
		color = col;
	}
	void set_num(int n) {
		num = n;
	}
	void set_suit(char s) {
		suit = s;
	}
	void set_displayed(bool d) {
		displayed = d;
	}
	void set_accessible(bool a) {
		accessible = a;
	}
	//public members
	Card() {
		set_color('e');
		set_num(-1);
		set_suit('e');
		set_displayed(false);
		set_accessible(false);
	}
	Card(char c, int n, char s, bool d, bool a) {
		set_color(c);
		set_num(n);
		set_suit(s);
		set_displayed(d);
		set_accessible(a);
	}
};

class Deck {
	char deck_type;
	int num_cards;
	vector <Card> deck;

public:
	char get_deck_type() {
		return deck_type;
	}
	void set_deck_type(char c) {
		deck_type = c;
	}
	int get_num_cards() {
		return num_cards;
	}
	void set_num_cards(int n) {
		num_cards = n;
	}
	vector<Card> get_deck() {
		return deck;
	}
	Card get_card(int x) {
		return deck.at(x);
	}
	void set_card(Card c, int x) {
		deck[x] = c;
	}
	void deck_pop() {
		deck.pop_back();
	}
	void deck_add(Card a) {
		deck.push_back(a);
	}
	void display_deck() {
		int i;
		if (deck.size() == 0)
			cout << 'X' << "        " << endl;
		else {
			for (i = 0; i < deck.size(); i++) {
				
				if (deck.at(i).get_displayed()) {
					if (deck.at(i).get_accessible()) {
						cout << "   ";
					}
					cout << deck[i].get_color() << deck[i].get_suit() << deck[i].get_num() << ' ';
				}
				else {
					cout << "---" << " ";
				}
				//cout << deck[i].get_color() << deck[i].get_suit() << deck[i].get_num() << ' ';
			}
			cout << endl;
		}
	}
};

class Player {
	string name;
	int wins;
	int losses;
	int total_games;
public:
	string get_name() {
		return name;
	}
	int get_losses() {
		return losses;
	}
	int get_wins() {
		return wins;
	}
	int get_total_games() {
		return total_games;
	}
	void set_name(string n) {
		name = n;
	}
	void set_losses(int l) {
		losses++;
	}
	void set_wins(int w) {
		wins++;
	}
	void set_total_games(int t) {
		total_games++;
	}
	void display_player_stats() {
		cout << "Player Stats : " << endl;
		cout << "Player name : " << get_name() << endl;
		cout << "Number of wins : " << get_wins() << endl;
		cout << "Number of losses : " << get_losses() << endl;
		cout << "Total games played : " << get_total_games() << endl;
	}
	Player() {
		set_name("null");
		set_losses(0);
		set_wins(0);
		set_total_games(0);
	}

	Player(string n, int l, int w, int t) {
		name = n;
		losses = l;
		wins = w;
		total_games = t;
	}
};

class Gameboard {

	vector <vector <Deck>> gameboard; // stores decks placed on the gameboard
public:
	void generate_gameboard() {

		// Generating full deck

		Deck full;
		int i, j, counter = 0;
		Card c, c2;
		for (i = 1; i < 14; i++) /* Spades */ {
			c.set_color('b');
			c.set_displayed(false);
			c.set_num(i);
			c.set_suit('s');
			c.set_accessible(false);
			full.deck_add(c);
		}

		for (i = 1; i < 14; i++)/* Hearts */ {
			c.set_color('r');
			c.set_displayed(false);
			c.set_num(i);
			c.set_suit('h');
			c.set_accessible(false);
			full.deck_add(c);
		}

		for (i = 1; i < 14; i++) /* Clubs */ {
			c.set_color('b');
			c.set_displayed(false);
			c.set_num(i);
			c.set_suit('c');
			c.set_accessible(false);
			full.deck_add(c);
		}

		for (i = 1; i < 14; i++) /* Diamonds */ {
			c.set_color('r');
			c.set_displayed(false);
			c.set_num(i);
			c.set_suit('d');
			c.set_accessible(false);
			full.deck_add(c);
		}

		//full.display_deck();

		// shuffle
		srand(time(0));
		int r;
		
		for (i = 0; i < 52; i++) {
			int r = i + rand() % (52 - i);
			c = full.get_card(i);
			c2 = full.get_card(r);
			full.set_card(c2, i);
			full.set_card(c, r);

		}

		//full.display_deck();


		vector <Deck> tableau;
		vector <Deck> waste;
		vector <Deck> foundation;

		for (i = 0; i < 4; i++) {
			Deck temp;
			temp.set_deck_type('f');
			foundation.push_back(temp);
			temp.set_num_cards(13);
		}

		gameboard.push_back(foundation);

		for (i = 0; i < 7; i++) {
			Deck temp;
			temp.set_deck_type('t');
			for (j = 0; j <= i; j++) {
				temp.deck_add(full.get_card(counter));
				counter++;
			}
			c = temp.get_card(j - 1);
			c.set_displayed(true);
			c.set_accessible(true);
			temp.set_card(c, j - 1);
			temp.set_num_cards(j + 13);
			tableau.push_back(temp);
		}

		gameboard.push_back(tableau);

		Deck temp;
		temp.set_deck_type('w');
		temp.set_num_cards(24);
		for (i = 0; i < 24; i++) {
			temp.deck_add(full.get_card(28 + i));
		}

		c = temp.get_card(23);
		c.set_displayed(true);
		c.set_accessible(true);
		temp.set_card(c, 23);
		waste.push_back(temp);
		gameboard.push_back(waste);
	}

	void display_gameboard() {
		int i, j;
		cout << "Foundations Piles: " << endl;
		for (i = 0; i < 4; i++) {
			cout << (i + 1) << ": ";
			gameboard.at(0).at(i).display_deck();
		}
		cout << "Tableau Piles: " << endl;
		for (i = 0; i < 7; i++) {
			cout << (i + 1) << ": ";
			gameboard.at(1).at(i).display_deck();
		}
		cout << "Waste Pile: " << endl;
		for (i = 0; i < 1; i++) {

			gameboard.at(2).at(i).display_deck();
		}

	}

	void reveal_card(char d_type, int n) {
		if (d_type == 'f') {
			cout << "All foundations card are already revealed." << endl;
		}
		else if (d_type == 't') {
			if (n > 7 || n < 1) {
				cout << "Error: Choose a pile between 1 and 7." << endl;
			}
			else {
				if (!(gameboard.at(1).at(n - 1).get_deck().empty())) {
					int last = gameboard.at(1).at(n - 1).get_deck().size() - 1;
					Card c = gameboard.at(1).at(n - 1).get_card(last);
					c.set_accessible(true);
					c.set_displayed(true);
					gameboard.at(1).at(n - 1).set_card(c, last);
				}
			}
		}
		else if (d_type == 'w') {

			int i;
			for (i = 0; i < gameboard.at(2).at(0).get_deck().size() - 1; i++) {
				if (gameboard.at(2).at(0).get_card(i).get_accessible()) {
					break;
				}
			}

			if (i == 0) {
				cout << "No cards left to reveal. Waste pile used up." << endl;
			}
			else {

				Card c = gameboard.at(2).at(0).get_card(i);
				c.set_accessible(false);
				gameboard.at(2).at(0).set_card(c, i);
				c = gameboard.at(2).at(0).get_card(i - 1);
				c.set_accessible(true);
				c.set_displayed(true);
				gameboard.at(2).at(0).set_card(c, i - 1);
			}
		}
		else {
			cout << "Why :(" << endl;
		}
	}

	void move_cards_t_to_t(int n, int n2) {
		if (gameboard.at(1).at(n - 1).get_deck().empty()) {
			cout << endl << "No cards left to move" << endl;
		}

		else { // if deck from which the card is to moved is not empty is not empty
			int i, j;

			for (i = 0; i < gameboard.at(1).at(n - 1).get_deck().size() - 1; i++) { // finding the first displayed card in deck 1 
				if (gameboard.at(1).at(n - 1).get_card(i).get_displayed()) {
					break;
				}
			}

			Card c1 = gameboard.at(1).at(n - 1).get_card(i); // first displayed card
			int l = gameboard.at(1).at(n - 1).get_deck().size() - 1; // size of deck 1

			if (gameboard.at(1).at(n2 - 1).get_deck().empty() && c1.get_num() == 13) { //if deck 2 is empty and deck 1 is a king

				for (j = i; j <= l; j++) { //add cards from deck 1 (first displayed card to the last card) to deck 2
					gameboard.at(1).at(n2 - 1).deck_add(gameboard.at(1).at(n - 1).get_card(j));
				}

				for (j = i; j <= l; j++) { // remove cards i to l from deck 2
					gameboard.at(1).at(n - 1).deck_pop();
				}

				if (gameboard.at(1).at(n - 1).get_deck().empty() == false) { // if deck 1 is not empty after moving card reveal last card
					reveal_card('t', n);
				}

			}

			else { // if both deck 1 and deck 2 are non empty
				
				Card c2 = gameboard.at(1).at(n2 - 1).get_card(gameboard.at(1).at(n2 - 1).get_deck().size() - 1); // last card on deck 2

				if ((c2.get_num() == c1.get_num() + 1) && (c2.get_color() != c1.get_color())) { //if card can be moved from pile n to n2
					c2.set_accessible(false);
					gameboard.at(1).at(n2 - 1).set_card(c2, gameboard.at(1).at(n2 - 1).get_deck().size() - 1);
					for (j = i; j <= l; j++) {
						gameboard.at(1).at(n2 - 1).deck_add(gameboard.at(1).at(n - 1).get_card(j)); //adding cards to pile n2
					}

					for (j = i; j <= l; j++) {
						gameboard.at(1).at(n - 1).deck_pop(); //removing cards from pile n
					}

					if (gameboard.at(1).at(n - 1).get_deck().empty() == false) { //if deck 1 is not empty reveal top (last) card
						reveal_card('t', n);
					}
				}

				else {
					cout << endl << "Card cannot be moved" << endl;
				}
			}
		}
	}

	void move_cards_w_to_t(int n) {

		if (gameboard.at(2).at(0).get_deck().empty()) {
			cout << endl << "No cards left to move." << endl;
		}

		else { //if there are cards in the waste pile

			int i, j;
			int l1 = gameboard.at(2).at(0).get_deck().size() - 1; // number of cards in waste pile
			int l2 = gameboard.at(1).at(n - 1).get_deck().size() - 1; // number of cards in tableau deck

			for (i = 0; i <= l1; i++) { // finding the first displayed card in waste pile
				if (gameboard.at(2).at(0).get_card(i).get_displayed()) {
					break;
				}
			}

			Card c1 = gameboard.at(2).at(0).get_card(i); //waste pile card to be moved

			if (l2 == -1 && c1.get_num() == 13) { //if a king is to be moved from waste pile to empty tableau deck
				gameboard.at(1).at(n - 1).deck_add(c1);
				// removing card at i from the waste pile
				
				for (j = i; j < l1; j++) { //shifting cards in waste pile
					c1 = gameboard.at(2).at(0).get_card(j + 1);
					gameboard.at(2).at(0).set_card(c1, j);
				}

				gameboard.at(2).at(0).deck_pop(); // removing last card

				//revealing next waste pile card
				
				//last card
				if (i == gameboard.at(2).at(0).get_deck().size() && i > 0) { // if 
					c1 = gameboard.at(2).at(0).get_card(i - 1);
					c1.set_accessible(true);
					c1.set_displayed(true);
					gameboard.at(2).at(0).set_card(c1, i - 1);
				}

				//middle card
				else if (gameboard.at(2).at(0).get_deck().size() > 0 && i >= 0) {
					c1 = gameboard.at(2).at(0).get_card(i); // ith card
					c1.set_accessible(true);
					c1.set_displayed(true);
					gameboard.at(2).at(0).set_card(c1, i);
				}
			}

			else {
				Card c2 = gameboard.at(1).at(n - 1).get_card(l2); //card on tableau pile
				if (c1.get_num() == c2.get_num() - 1 && c1.get_color() != c2.get_color()) {//to move card from waste pile to a non-empty tableau pile
					c2.set_accessible(false);
					gameboard.at(1).at(n - 1).set_card(c2, l2);
					gameboard.at(1).at(n - 1).deck_add(c1);
					// removing card at i from the waste pile
					for (j = i; j < l1; j++) {
						c1 = gameboard.at(2).at(0).get_card(j + 1);
						gameboard.at(2).at(0).set_card(c1, j);
					}
					gameboard.at(2).at(0).deck_pop();
					//revealing waste pile card

					//last card
					if (i == gameboard.at(2).at(0).get_deck().size() && i > 0) {
						c1 = gameboard.at(2).at(0).get_card(i - 1);
						c1.set_accessible(true);
						c1.set_displayed(true);
						gameboard.at(2).at(0).set_card(c1, i - 1);
					}

					else if (gameboard.at(2).at(0).get_deck().size()> 0 && i >= 0) {
						c1 = gameboard.at(2).at(0).get_card(i);
						c1.set_accessible(true);
						c1.set_displayed(true);
						gameboard.at(2).at(0).set_card(c1, i);
					}
				}

				else {
					cout << endl << "Invalid Operation: Card cannot be moved." << endl;
				}
			}
		}
	}

	void move_cards_w_to_f(int n) {

		if (gameboard.at(2).at(0).get_deck().empty()) {
			cout << endl << "No cards left to move." << endl;
		}
		else { //if waste pile is not empty

			int i, j;
			int l1 = gameboard.at(2).at(0).get_deck().size() - 1; // number of cards in waste pile

			for (i = 0; i <= l1; i++) { // finding the first accessible card in waste pile
				if (gameboard.at(2).at(0).get_card(i).get_accessible()) {
					break;
				}
			}

			Card c = gameboard.at(2).at(0).get_card(i); // waste pile card to be moved

			if (gameboard.at(0).at(n - 1).get_deck().empty() && c.get_num() == 1) {//ace to foundation pile
				gameboard.at(0).at(n - 1).deck_add(c);
				// removing card at i from the waste pile
				for (j = i; j < l1; j++) {
					c = gameboard.at(2).at(0).get_card(j + 1);
					gameboard.at(2).at(0).set_card(c, j);
				}
				gameboard.at(2).at(0).deck_pop();

				//revealing next waste pile card
				if (i == gameboard.at(2).at(0).get_deck().size()) {
					c = gameboard.at(2).at(0).get_card(i);
					c.set_accessible(true);
					c.set_displayed(true);
					gameboard.at(2).at(0).set_card(c, i);
				}
				else if (gameboard.at(2).at(0).get_deck().size() > 0 && i >= 0) {
					c = gameboard.at(2).at(0).get_card(i);
					c.set_accessible(true);
					c.set_displayed(true);
					gameboard.at(2).at(0).set_card(c, i);
				}

			}

			else if (!gameboard.at(0).at(n - 1).get_deck().empty())
			{
				int l2 = gameboard.at(0).at(n - 1).get_deck().size() - 1;

				Card c2 = gameboard.at(0).at(n - 1).get_card(l2); //fondation card on selected pile

				if (c.get_color() == c2.get_color() && c.get_num() == c2.get_num() + 1) {
					gameboard.at(0).at(n - 1).deck_add(c);

					// removing card at i from the waste pile
					for (j = i; j < l1; j++) {
						c = gameboard.at(2).at(0).get_card(j + 1);
						gameboard.at(2).at(0).set_card(c, j);
					}
					gameboard.at(2).at(0).deck_pop();

					//revealing next waste pile card
					if (i == gameboard.at(2).at(0).get_deck().size()) {
						c = gameboard.at(2).at(0).get_card(i);
						c.set_accessible(true);
						c.set_displayed(true);
						gameboard.at(2).at(0).set_card(c, i);
					}
					else if (gameboard.at(2).at(0).get_deck().size() > 0 && i >= 0) {
						c = gameboard.at(2).at(0).get_card(i);
						c.set_accessible(true);
						c.set_displayed(true);
						gameboard.at(2).at(0).set_card(c, i);
					}
				}
			}

			else {
				cout << "Invalid Operation: Card Cannot be moved." << endl;
			}
		}

	}

	void move_cards_t_to_f(int n1, int n2) {

		if (gameboard.at(1).at(n1 - 1).get_deck().empty()) {
			cout << endl << "No cards left to move." << endl;
		}
		else { // if there are cards in the pile

			int i, j;
			int l1 = gameboard.at(1).at(n1 - 1).get_deck().size() - 1; // number of cards in tableau pile
			Card c1 = gameboard.at(1).at(n1 - 1).get_card(l1); // tableau card to be moved (last card)

			if (gameboard.at(0).at(n2 - 1).get_deck().empty() && c1.get_num() == 1) {//tableau ace to foundation pile
				cout << "HI" << endl;
				cout << "HI" << endl;
				gameboard.at(0).at(n2 - 1).deck_add(c1);

				// removing last card of selected tableau pile
				gameboard.at(1).at(n1 - 1).deck_pop();

				l1 = gameboard.at(1).at(n1 - 1).get_deck().size();
				
				//revealing next tableau pile card
				if (!gameboard.at(1).at(n1 - 1).get_deck().empty() && l1 > 0) {
					c1 = gameboard.at(1).at(n1 - 1).get_card(l1 - 1);
					c1.set_accessible(true);
					c1.set_displayed(true);
					gameboard.at(1).at(n1 - 1).set_card(c1, l1 - 1);
				}

			}

			else if (!gameboard.at(0).at(n2 - 1).get_deck().empty())
			{
				int l2 = gameboard.at(0).at(n2 - 1).get_deck().size() - 1;
				Card c2 = gameboard.at(0).at(n2 - 1).get_card(l2); //foundation card on selected pile

				if (c1.get_color() == c2.get_color() && c1.get_num() == c2.get_num() + 1) {
					gameboard.at(0).at(n2 - 1).deck_add(c1);

					// removing card at i from the tableau pile
					gameboard.at(1).at(n1 - 1).deck_pop();

					//revealing next tableau pile card
					if (!gameboard.at(1).at(n1 - 1).get_deck().empty() && l1 > 0) {
						c1 = gameboard.at(1).at(n1 - 1).get_card(l1 - 1);
						c1.set_accessible(true);
						c1.set_displayed(true);
						gameboard.at(1).at(n1 - 1).set_card(c1, l1 - 1);
					}

				}
			}
			else {
				cout << "Invalid Operation: Card Cannot be moved." << endl;
			}
		}

	}

	bool check_win_condition() {
		bool a = true;
		int i, size;
		for (i = 0; i < 4; i++) {
			size = gameboard.at(0).at(i).get_deck().size() - 1;
			if (size != 13)
				return false;
		}

		cout << endl << "Congratuations! you won! " << endl;
		return true;
	}

	bool check_no_moves() {
		int i, j, s1, s2;
		Card c1, c2;

		// checking inter tableau piles
		for (i = 0; i < 7; i++) {
			for (j = 0; j < 7; j++) {
				if (!gameboard.at(1).at(i).get_deck().empty() && !gameboard.at(1).at(j).get_deck().empty()) {
					s1 = gameboard.at(1).at(i).get_deck().size() - 1;
					s2 = gameboard.at(1).at(j).get_deck().size() - 1;
					c1 = gameboard.at(1).at(i).get_card(s1);
					c2 = gameboard.at(1).at(j).get_card(s2);
					if (c1.get_color() != c2.get_color() && c1.get_num() == c2.get_num() - 1) {
						return false;
					}
				}
				else if (!gameboard.at(1).at(i).get_deck().empty() && gameboard.at(1).at(j).get_deck().empty()) {
					s1 = gameboard.at(1).at(i).get_deck().size() - 1;
					c1 = gameboard.at(1).at(i).get_card(s1);
					if (c1.get_num() == 13)
						return false;
				}

			}
		}

		// checking tableau to foundation
		for (i = 0; i < 7; i++) {
			for (j = 0; j < 4; j++) {
				if (!gameboard.at(1).at(i).get_deck().empty() && !gameboard.at(0).at(j).get_deck().empty()) {
					s1 = gameboard.at(1).at(i).get_deck().size() - 1;
					s2 = gameboard.at(0).at(j).get_deck().size() - 1;
					c1 = gameboard.at(1).at(i).get_card(s1);
					c2 = gameboard.at(0).at(j).get_card(s2);
					if (c1.get_color() == c2.get_color() && c1.get_num() == c2.get_num() + 1) {
						return false;
					}
				}
				else if (!gameboard.at(1).at(i).get_deck().empty() && gameboard.at(0).at(j).get_deck().empty()) {
					s1 = gameboard.at(1).at(i).get_deck().size() - 1;
					c1 = gameboard.at(1).at(i).get_card(s1);
					if (c1.get_num() == 1) {
						return false;
					}
				}

			}
		}

		// checking waste pile

		// waste card 
		s1 = gameboard.at(2).at(0).get_deck().size() - 1; //size of waste pile
		
		for (i = 0; i < s1; i++) { // finding the first accessible card in waste pile
			if (!gameboard.at(2).at(0).get_card(i).get_displayed()) {
				return false;
			}
		}

		
		for (i = 0; i <= s1; i++) { // finding the first accessible card in waste pile
			if (gameboard.at(2).at(0).get_card(i).get_accessible()) {
				break;
			}
		}

		if (i >= 0 && i>=s1) { //if there is a waste pile card
			c1 = gameboard.at(2).at(0).get_card(i); // accessible card in waste pile

			//to tableau
			for (j = 0; j < 7; j++) {

				if (gameboard.at(1).at(j).get_deck().empty() and c1.get_num() == 13) { //king to tableau
					return false;
				}
				else { // other card to tableau
					s2 = gameboard.at(1).at(j).get_deck().size() - 1;
					c2 = gameboard.at(1).at(j).get_card(s2);
					if (c2.get_num() == c1.get_num() - 1 && c1.get_color() != c2.get_color()) {
						return false;
					}

				}
			}

			//to foundations
			for (j = 0; j < 4; j++) {
				if (gameboard.at(0).at(j).get_deck().empty() && c1.get_num() == 1) { //ace to foundations
					break;
				}
				else if (!gameboard.at(0).at(j).get_deck().empty()) {
					s2 = gameboard.at(0).at(j).get_deck().size() - 1; // size of foundations pile
					c2 = gameboard.at(0).at(j).get_card(s2); // card on foundations pile 
					if (c2.get_num() == c1.get_num() - 1 && c1.get_color() != c2.get_color()) {
						return false;
					}
				}
			}
		}
		
		return true;
	}

};

void instructions() {
	cout << "\n Instructions: \n" << endl;
	cout << "Description: " << endl;
	cout << "Card color : b for black, r for red" << endl;
	cout << "Card suit : c for clubs, h for hearts, d for diamonds, s for spades" << endl;
	cout << "Card numbers : 1 for ace, 11 for jack, 12 for queen, 13 for king " << endl;
	cout << endl;
	cout << "Constraints: " << endl;
	cout << "Only cards at the end of each deck in the tableau is accessible." << endl;
	cout << "If a pile of ordered cards are placed at the end of each deck in the tableau, they can be moved as a whole." << endl;
	cout << endl;
	cout << "How to play : " << endl;
	cout << "Order the cards in each deck in the tableau in alternating color and in a decreasing order, king being the highest and ace being the smallest." << endl;
	cout << "“Fill up the foundations pile by adding cards from the smallest to the highest cards.All cards of the same suit should be in one pile." << endl;
}

char menu() {

	string s;
	char num;

	cout << endl << "Operations: " << endl;
	cout << "Enter 1 if you want to reveal a waste card." << endl;
	cout << "Enter 2 if you want to move tableau card(s) from one deck to another." << endl;
	cout << "Enter 3 if you want to move card(s) from the waste pile to a tableau pile." << endl;
	cout << "Enter 4 if you want to move card(s) from the waste pile to a foundations pile" << endl;
	cout << "Enter 5 if you want to move a card(s) from the tableau to a foundations pile." << endl;
	cout << "Enter 6 if you want to quit the game." << endl;
	cin >> s;

	num = s.at(0);
	if (s.length() == 1 && (num == '1' || num == '2' || num == '3' || num == '4' || num == '5' || num == '6')) {
		
		return num;
	}


	else {
		cout << endl << "ERROR: Menu option does not exist" << endl;
		return menu();
	}

}

int main() {

	cout << "Enter player name: ";
	string player_name;
	cin >> player_name;
	Player p(player_name, 0, 0, 0);
	char choice = ' ';

	do {
		instructions();
		Gameboard g;
		g.generate_gameboard();
		char option = 0;
		do {
			cout << endl;
			p.display_player_stats();
			cout << endl << "Gameboard: " << endl;
			g.display_gameboard();
			cout << endl;
			option = menu();
			switch (option) {
			case '1': // To reveal waste pile cards
				g.reveal_card('w', -1);
				break;
			case '2': //To move cards from one tableau pile to another tableau pile
				int num, num2;
				cout << endl << "Enter the pile number from which the card(s) is to be moved: ";
				cin >> num;
				cout << endl << "Enter the pile number to which the card(s) is to be moved: ";
				cin >> num2;
				if (num > 0 && num < 8 && num2 > 0 && num2 < 8 && num != num2) {
					g.move_cards_t_to_t(num, num2);
				}
				else {
					cout << endl << "Error: Invalid pile selection." << endl;
				}
				break;
			case '3': //To move cards from the waste pile to the tableau pile
				cout << endl << "Enter the pile number to which the card(s) is to be moved: ";
				cin >> num2;
				if (num2 > 0 && num2 < 8) {
					g.move_cards_w_to_t(num2);
				}
				else {
					cout << endl << "Error: Invalid pile selection." << endl;
				}
				break;
			case '4': //Waste pile to foundations
				cout << endl << "Enter the pile number to which the card(s) is to be moved: ";
				cin >> num2;
				if (num2 > 0 && num2 < 5) {
					g.move_cards_w_to_f(num2);
				}
				else {
					cout << endl << "Error: Invalid pile selection." << endl;
				}
				break;
			case '5': //Tableau to foundations
				cout << endl << "Enter the tableau pile number from which the card(s) is to be moved: ";
				cin >> num;
				cout << endl << "Enter the foundation pile number to which the card(s) is to be moved: ";
				cin >> num2;
				if (num > 0 && num < 8 && num2 > 0 && num2 < 5) {
					g.move_cards_t_to_f(num, num2);
				}
				else {
					cout << endl << "Error: Invalid pile selection." << endl;
				}
				break;
			case '6': //Quit
				cout << endl << "Quitting game... " << endl;
				break;
			default:
				cout << endl << "ERROR: God does not exist. I've lost faith in humanity. " << endl;
			}

		} while (!(option == '6' || g.check_win_condition() || g.check_no_moves()));

		if (g.check_win_condition()) {
			p.set_wins(1);
		}
		else if (g.check_no_moves()) {
			cout << endl << "You lose! No moves possible." << endl;
			p.set_losses(1);
		}
		else {
			cout << "You lose! You quit." << endl;
			p.set_losses(1);
		}

		p.set_total_games(1);
		p.display_player_stats();

		//ask user for another game
		cout << endl << "Play another game? Press y to play another game. Any other key to quit. " << endl;
		cin >> choice;

	} while (choice == 'y');

	p.display_player_stats();
	return 0;
}