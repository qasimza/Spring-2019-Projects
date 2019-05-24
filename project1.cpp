/*
 * Project Title:
 * - Project 1: Minesweeper 2.0
 * Description: (should be a few sentences)
 * This program is a game based off of mine sweeper. Instead of dying instantly, you start with 100 health.
 * There are three different types of bombs that need to be flagged, small, medium, and big. Small mines do 20 damage,
 * medium mines do 50 damage, big mines do 100 damage. There is another additional item that will give the player 100
 * additional health points. One last twist is that the zone is not given and the player has to check each and every space.
 * This makes the game substantially harder for the player and is unforgiving.
 *
 * Developers:
 * - Zaina Qasim - qasimza@mail.uc.edu
 * - Adra Smtih - smit4ar@mail.uc.edu
 *
 * Help Received:
 * - None
 *
 * Special Instructions: // optional
 * - There are two display functions: one is commented out on line 375 and the other one is the display function on line 346. 
 *   Replace the one on line 346 with the one on 375 to display game board contents (useful for test runs)
 *
 * Developer comments: // Not optional
 * Developer 1: Zaina Qasim
 * I learned about visibility rules and the scope of private, protected, and public variables and functions. 
 * I also gained insight on the sequential flow of c++ and its differences from java. 
 * Working with loops and the rand() function also taught me about time complexity and how probability relates to it
 *
 * Developer 2: Adra Smith
 * I learned more about adding classes and structures into programs and how they are used to program games. I also learned that 
 * using classes and structures simplify main() by a vast amount. Learning more about how to program this game showed me different techniques
 * that I can use in future programming.
 */

/* In struct cell: 
 *
 * Parameters:
 * string status - stores the cell description (empty, blast mine, fragmentation mine, flame fougausse mine, healt item) 
 * char id - stores a character identifier for the type of cell, numbers 1 to 8 for number of mines in vicinity, 'h' for health item, 's' for small (blast) mine, 'm' for medium (fragmentation mine), 'b' for big (flame fougausse) mine
 * bool displayed - stores true if cell is displayed, false if cell is not displayed 
 * int damage - stores amount of damage dealt by the cell contents if player choses to reveal it
 * bool flagged = stores true if the cell is flagged, false if cell is not flagged
 *
 *
 * In class Gameboard
 * 
 * Parameters:
 * num_rows - stores the number of rows the gameboard should have in the current game
 * int num_columns - stores the number of columns the gameboard should have in the current game
 * int num_mines - stores the number of mines on the gameboard in the current game 
 * string difficulty - stores the difficulty level of the current game
 * vector <vector <cell>> gameboard - vector of cell vectors that stores the gameboard
 *
 * Functions:
 * int get_rows() - returns the value stored in num_rows
 * int get_columns() - returns the value stored in num_columns
 * int get_mines() - returns the value stored in num_mines
 * string get_difficulty() - returns the value stored in difficulty
 * void set_gameboard_properties() - Sets the values for num_rows, num_columns, num_mines, and difficulty
 * void gameboard_generate() - generates the gameboard
 * void generate_mines() - generates mines and places them randomly on the gameboard
 * void generate_item() - generates bonus healt item and places it on an empty cell on the gameboard
 * void generate player_position() - Lets player initially select a cell so that gameboard can be mapped around their position
 * void get_mines() - returns the value stored in num_mines
 * int check_vicinity(int r, int c) - returns the number of mines (0-8) around the gameboard cell at r,c
 * bool winning condition() - returns true if the player finds all the mines and has not unflagged any other mines,
 *							  false if the player has extra mines flagged or has not won the game yet
 * void display() - displays the gameboard
 *
 *
 * In class player
 *
 * Parameters:
 * string player name - stores the name of the current player
 * int player_hp - stores the player's hp.
 * int games_played - stores the number of games played
 * int wins - stores the number of games won
 * int losses - stores the number of games lost
 *
 * Functions:
 * void change_hp() - changes players hp, if new game is started or if the player relveals a mine
 * string get_playerName() - returns player's name
 * int get_playerHP() - returns player_hp
 * int get_gamesplayed() - returns the number of games played
 * int get_wins() returns he number of wins
 * int get_losses() - return the number of losses
 *
 *
 * Other functions:
 *
 * void display_game_instructions() - displays game instructions
 * void display_game_stats(player a, Gameboard g) - displays the games stats for player p and gameboard g
 * void play_one_game (player& p, Gameboard& g) - To play one game (gameboard) and update any values in referened player and Gameboard objects  
 */

#include <vector>
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;

struct cell {
	string status;
	char id;
	bool displayed;
	int damage;
	bool flagged = false;
	cell(){
		status = "Empty";
		id = '-';
		displayed = false;
		damage = 0;
	
	}
	char get_id() { return id; }
};

class Gameboard {
	int num_rows;
	int num_columns;
	int num_mines;
	string difficulty;

public:
	
	int get_rows() { return num_rows; }
	int get_columns() { return num_columns; }
	int get_mines() { return num_mines; }
	string get_difficulty() { return difficulty; }
	vector <vector <cell>> gameboard;
		
	//To set the gameboard size and other properties
	void set_gameboard_properties() { //constructor sets game board properties
		int flag = 0;
		int choice = 0;
		do {
			cout << endl << "Select diffculty (1,2,3,4): " << endl
				<< "1 - Beginner" << endl
				<< "2 - Intermediate" << endl
				<< "3 - Expert" << endl
				<< "4 - Custom" << endl;
			cin >> choice;
			if (choice > 0 && choice < 5)
				flag = 1;
			else
				cout << "Error: Incorrect Selection" << endl;
		} while (flag == 0);
		switch (choice) {
		case 1:
			num_rows = 9;
			num_columns = 9;
			num_mines = 10;
			difficulty = "Beginner";
			break;
		case 2:
			num_rows = 16;
			num_columns = 16;
			num_mines = 40;
			difficulty = "Intermediate";
			break;
		case 3:
			num_rows = 16;
			num_columns = 30;
			num_mines = 99;
			difficulty = "Expert";
			break;
		case 4:

			do {
				cout << "Enter number of rows (must be greater than 2): ";
				cin >> num_rows;
				if (num_rows < 3) {
					cout << "ERROR: Size of minfield must be greater than 2." << endl;
				}
			} while (num_rows < 3);

			do {
				cout << "Enter number of columns (must be greater than 2): ";
				cin >> num_columns;
				if (num_columns < 3) {
					cout << "ERROR: Number of columns must be greater than 2." << endl;
				}
			} while (num_columns < 3);

			do {
				cout << "Enter number of mines: ";
				cin >> num_mines;
				if ((num_mines >= num_rows * num_columns-1) || num_mines <1) {
					cout << "ERROR: Number of mines is out of range. Setting number of mines to a random number..." << endl;

					num_mines = rand()%(num_rows * num_columns)/5+1;
				}
			} while (num_mines < 0);
			difficulty = "Custom";
			break;
		default:
			cout << "WHY IS THE CONTROL HERE?" << endl;
			break;
		}
	}

	//To generate the gameboard
	void gameboard_generate() {
		vector <cell> a(num_columns);
		gameboard.resize(num_rows);
		for (int i = 0; i < num_rows; i++) {
			gameboard.at(i).resize(num_columns);
			gameboard.at(i) = a;
		}
	}

	// To add mines to the gameboard 
    void generate_mines() {
		int i, choice, row, column;
		for (i = 0; i < num_mines; i++) {
			choice = (rand() % 3)+1; 
			do {
				row = rand() % num_rows;
				column = rand() % num_columns;
				
			} while (gameboard[row][column].get_id()!='-');

			switch (choice) { //putting different types of mines on the gameboard
			case 1:
				gameboard[row][column].id = 's';
				gameboard[row][column].status = "Blast Mine";
				gameboard[row][column].damage = 20;
				break;
			case 2:
				gameboard[row][column].id = 'm';
				gameboard[row][column].status = "Fragmentation Mine";
				gameboard[row][column].damage = 50;
				break;
			case 3:
				gameboard[row][column].id = 'b';
				gameboard[row][column].status = "Flame Fougasse Mine";
				gameboard[row][column].damage = 100;
				break;
			default:
				cout << "CHECK THE CODE" << endl;
			}
		}
		
	}

	//generate bonus item
	void generate_item() {
		int row, column;
		do {
			row = rand() % num_rows;
			column = rand() % num_columns;
		} while (gameboard[row][column].status=="Empty");
		gameboard[row][column].id = 'h';
		gameboard[row][column].status = "Health";
	}

	//gets player position
	void generate_player_position() {
		int prow, pcolumn;
		cout << endl <<  "Start game by randomly selecting a cell. " << endl;
		do {
			cout << "Enter your row coordinate: ";
			cin >> prow;
			if (prow<0 || prow>num_rows-1) {
				cout << "Enter a coordinate inside the grid" << endl;
			}
		} while (prow<0 || prow>num_rows-1);
		do {
			cout << "Enter your column coordinate: ";
			cin >> pcolumn;
			if (pcolumn<0 || pcolumn>num_columns-1) {
				cout << "Enter a coordinate inside the grid" << endl;
			}
		}while(pcolumn<0 || pcolumn>num_columns-1);
		gameboard[prow][pcolumn].id = 'p';
		gameboard[prow][pcolumn].displayed=true;
    }

	//stores numbers in the cells
	int check_vicinity(int r, int c) {
		int ri, rf, ci, cf;
		ri = r - 1 >= 0 ? r - 1 :0;
		rf = r + 1 <= num_rows-1 ? r + 1 :r;
		ci = c - 1 >= 0 ? c - 1 : 0;
		cf = c + 1 <= num_columns - 1 ? c + 1 : c;
		int i, j, counter=0;
			for (i = ri; i <= rf; i++) {
				for (j = ci; j <= cf; j++) {
					if (gameboard[i][j].id == 's' || gameboard[i][j].id == 'm' || gameboard[i][j].id == 'b')
						counter++;
				}
			}
	return counter;
	}

	//Maps numbers onto the gameboard
	void map_numbers() {
		int i, j, n;
		for (i = 0; i < num_rows; i++) {
			for (j = 0; j < num_columns; j++) {
				if (gameboard[i][j].get_id() == '-'|| gameboard[i][j].get_id() == 'p') {
					n = check_vicinity(i, j);
					gameboard[i][j].id=to_string(n).at(0);
				}
			}
		}
	}
	
	//check winning condition
	bool winning_condition() {
		int i, j, counter=0, unnecessary=0, num_revealed=0;
		for (i = 0; i < num_rows; i++) {
			for (j = 0; j < num_columns; j++) {
				if (gameboard[i][j].get_id() == 's' || gameboard[i][j].get_id() == 'm' || gameboard[i][j].get_id() == 'b') {
					if (gameboard[i][j].flagged == true || gameboard[i][j].displayed == true) {
						counter++;
					}
				}
				else if (gameboard[i][j].flagged == true)
					unnecessary++;

				else if (gameboard[i][j].displayed == true)
					num_revealed ++;
			}
		}

		if (counter == num_mines && unnecessary == 0)
			return true;

		else if (num_revealed == (num_columns*num_rows - num_mines) && unnecessary == 0) {
			cout << endl << "---You found all the empty cells--- " << endl;
			return true;
		}
		else if (counter == num_mines && unnecessary > 0) {
			cout << endl << "ERROR: Too many cells flagged! Flag only the mine cells to win." << endl;
			return false;
		} 
		else
			return false;
	}

	//display gameboard
	void display() {

		cout << endl << "MINEFIELD: " << endl; 
		int i, j, temp = num_rows;
		cout << endl;
		cout << setw(10) << "";
		for (i = 0; i < num_columns; i++) {
			cout << setw(10) << i;
		}
		cout << endl << endl;

		for (i = 0; i < num_rows; i++) {
			cout << setw(10) << i;
			for (j = 0; j < num_columns; j++) {
				if (gameboard[i][j].flagged == true) {
					cout << setw(10) << 'f';
				}
				else if (gameboard[i][j].displayed == false) {
					cout << setw(10) << '-';
				}
				else {
					cout << setw(10) << gameboard[i][j].get_id();
				}
			}
			cout << endl;
		}
	}

	//Test gameboard values. Uncomment this function and comment out display gameboard on line 282 to view gameboard cells.
	/*void display() {

		cout << endl << "MINEFIELD: " << endl;
		int i, j, temp = num_rows;
		cout << endl;
		cout << setw(10) << "";
		for (i = 0; i < num_columns; i++) {
			cout << setw(10) << i;
		}
		cout << endl << endl;

		for (i = 0; i < num_rows; i++) {
			cout << setw(10) << i;
			for (j = 0; j < num_columns; j++) {
				if (gameboard[i][j].flagged == true) {
					cout << setw(10) << 'f';
				}
				else
					cout << setw(10) << gameboard[i][j].get_id();
				}
			cout << endl;
			}

		}*/

};

class player {
	string player_name;
	int player_hp;
	int games_played;
	int wins;
	int losses;
public:
	void change_hp(char a);
	player() {
		cout << "Enter your name: ";
		cin >> player_name;
		player_hp = 100;
		games_played = 0;
		wins = 0;
		losses = 0;
	}
	string get_playerName() { return player_name; }
	int get_playerHP() { return player_hp; }
	int get_gamesplayed() { return games_played; }
	int get_wins() { return wins; }
	int get_losses() { return losses; }

	void set_gamesplayed() { games_played++; }
	void set_wins() { wins++; }
	void set_losses() { losses++; }

};

void player::change_hp(char a) {
	if (a == 's') {
		cout << "You stepped on a Blast Mine. You took 20 Damage." <<endl;
		player_hp = player_hp - 20;
	}
	else if (a == 'm') {
		cout << "You stepped on a Fragmentation Mine. You took 50 Damage." << endl;
		player_hp = player_hp - 50;
	}
	else if (a == 'b') {
		cout << "You stepped on a Flame Fougausse Mine. You took 100 Damage." << endl;
		player_hp = player_hp - 100;
	}
	else if (a == 'h') {
		cout << "You found a Bonus Item. You gained 100 Health Points" << endl;
		player_hp = player_hp + 100;
	}
	else if (a == 'n') {
		player_hp = 100;
	}
	else {
		player_hp = player_hp + 0;
	}
}

//To display game instructions
void display_game_instructions(){
	cout << "OBJECTIVE:" << endl << "Find and flag all of the mines before you run out of health! \n" << endl;
	cout << "GAME INSTRUCTIONS: " << endl
		<< "There are three different kinds of mines in the field:" << endl
		<< "Blast Mines - Deals 20 HP Damage" << endl
		<< "Fragmentation Mines - Deals 50 HP Damage" << endl
		<< "Flame Fougasse Mines - Deals 100 HP Damage" << endl;
	/*cout << "There is a hidden item in the field that will boost your HP" << endl
		<< "Find it to gain 100 HP points! \n"<<endl;*/
	cout << "CONTROLS:" << endl;
	cout << "Column coordinates are displayed along the upper edge of game board" << endl;
	cout << "Row coordinates are displayed along the left edge of game board" << endl;
	cout << "Type the field coordinates (row, column) that you would like to inspect." << endl
		<< "Use 'f' to flag spaces and 'r' to reveal the cell \n" << endl;
}

//To display game statistics
void display_game_stats(player a, Gameboard g) {
	cout << "\nGAME STATS: \n" << endl;
	cout << "Player Name: " << a.get_playerName() << endl
		<< "Games played: " << a.get_gamesplayed() << endl
		<< "Wins: " << a.get_wins() << endl
		<< "Losses: " << a.get_losses() << endl
		<< "Player HP: " << a.get_playerHP() << endl;
	cout << "Difficulty Level: " << g.get_difficulty() << " (" <<g.get_rows()<<" x " << g.get_columns() << ", " << g.get_mines() <<" mines)" << endl;
 
}

//For one iteration of the game
void play_one_game(player& p, Gameboard& g) {
	int prow, pcolumn;
	char yn;
	g.set_gameboard_properties();
	g.gameboard_generate();
	g.generate_player_position();
	g.generate_mines();
	g.map_numbers();
	g.generate_item();
	p.change_hp('n');
	display_game_stats(p, g);
	g.display();
	while (p.get_playerHP() > 0 && g.winning_condition() == false) {
		do {
			cout << endl << "Enter your row coordinate: ";
			cin >> prow;
			if (prow<0 || prow>g.get_rows() - 1) {
				cout << "Enter a coordinate inside the grid" << endl;
			}
		} while (prow<0 || prow>g.get_rows() - 1);
		do {
			cout << "Enter your column coordinate: ";
			cin >> pcolumn;
			if (pcolumn<0 || pcolumn>g.get_columns() - 1) {
				cout << "Enter a coordinate inside the grid" << endl;
			}
		} while (pcolumn<0 || pcolumn>g.get_columns() - 1);
		cout << "To reveal the contents of the cell, press r" << endl
			<< "To flag the cell, press f" << endl
			<< "To unflag the cell, press u" << endl
			<< "Press any other key to cancel: ";

		cin >> yn;
		switch (yn) {
		case 'r': //If player wishes to reveal cell
			if (g.gameboard[prow][pcolumn].displayed == true) {
				cout << "ERROR: Cannot reveal already displayed cell." << endl;
			}
			else if (g.gameboard[prow][pcolumn].flagged == true)
				cout << "ERROR: Cannot reveal unflagged cell. Select cell again and unflag by hitting u." << endl;
			else{
				g.gameboard[prow][pcolumn].displayed = true;
				p.change_hp(g.gameboard[prow][pcolumn].get_id());
			}

			break;

		case 'f': //If player wishes to flag cell
			if (g.gameboard[prow][pcolumn].displayed == true) {
				cout << "ERROR: Cannot flag a revealed cell" << endl;
			}
			else {
				g.gameboard[prow][pcolumn].flagged = true;
			}
			break;

		case 'u': //If player wishes to unflag cell
			g.gameboard[prow][pcolumn].flagged = false;
			break;
		default:
			cout << "Cancelled...Displaying Game Stats and Minefield." << endl;
		}

		if (p.get_playerHP() <= 0) {  //Losing condition
		cout << endl << "--- Your HP is 0. You Lose! " << p.get_playerName() << "---" << endl;
		p.set_losses();
		p.set_gamesplayed();
		display_game_stats(p, g);
		}

		else if (g.winning_condition()) { //Winning condition
			cout << endl << "--- Congratulations, "<< p.get_playerName() << "! You've found all the mines! You win! ---" << endl;
			p.set_wins();
			p.set_gamesplayed();
			display_game_stats(p, g);
		}

		else {
			display_game_stats(p, g);
			g.display();
		}

	}
}

int main() {
	
	srand(time(0));
	cout << "Welcome to Minesweeper 2.0! \n" << endl;
	char ans;
	display_game_instructions();
	player p_ob;
	Gameboard g_ob;

	//Play multiple games
	do {
		play_one_game(p_ob, g_ob);
		cout << "New game? (Press y). Press any other key to quit..." << endl;
		cin >> ans;
	} while (ans == 'y');

	cout << endl << "---GAME OVER---" << endl
		<<"Displaying Final Player Stats..." << endl;
	
	display_game_stats(p_ob,g_ob);
	
	return 0;
}