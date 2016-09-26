#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <array>
#include <vector>
#include <stdlib.h>

// cout << "checkpoint 1" << endl;

using namespace std;

int nplayer;
int size;
int winSeq;
int currentPlayer;
int** board;

char players[27] = {' ', 'X', 'O' ,'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 
					'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'Y', 'Z'}; 

/*
 * check: 1. player number, 2. board size, 3. win sequence
 * 4. win is possible?
 * return int array w/ size of 3, int[0]: # of player, 
 * int[1]: board size, int[2]: win sequence.
 */
vector<int> checksforNewGame() {
	vector<int> data;
	string temp;

	// let user input nplayer, size and winseq, until everything valid.
	do {
		cout << "How many players are playing? (1-26)" << endl;
		cin >> temp;

		if (!isdigit(temp[0])) {
			cout << "Invalid number of player, Please try again!" << endl;
			continue;
		}

		nplayer = stoi(temp);
		
		if (nplayer <= 26 && nplayer >= 1) {
			data.push_back(nplayer);
			break;
		}
		else {
			cout << "Invalid number of player, Please try again!" << endl;
		}
	} while(1);

	do {
		cout << "What's an ideal board size for your game? (3-999)" << endl;
		cin >> temp;

		if (!isdigit(temp[0])) {
			cout << "Invalid number of player, Please try again!" << endl;
			continue;
		}

		size = stoi(temp);

		if (size >= 3 && size <= 999) {
			data.push_back(size);
			break;
		}
		else {
			cout << "Invalid board size, Please try again!" << endl;
		}
	} while (1);

	do {
		cout << "How long will the winning sequence be? (eg. 3)" << endl;
		cin >> temp;

		if (!isdigit(temp[0])) {
			cout << "Invalid number of player, Please try again!" << endl;
			continue;
		}
	
		winSeq = stoi(temp);
		data.push_back(winSeq);
		break;
	} while (1);

	return data;
}

// set every element in the 2d array to 0 to avoid out of bound error
void initializeBoard(int size) {
	for (int i = 0; i < size; i++) {
		board[i] = new int[size];
		for (int j = 0; j < size; j++) {
			board[i][j] = 0;
		}
	}
}

// return true if load game successful, false if load game failed
void loadSavedGame(string gameName) {
	ifstream inputfile;
	inputfile.open(gameName);

	inputfile >> nplayer;
	inputfile >> size;
	inputfile >> winSeq;
	inputfile >> currentPlayer;

	board = new int* [size];
	initializeBoard(size);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			inputfile >> board[i][j];
		}
	}
	
	inputfile.close();
}

/* Legend: 
 * L - Left
 * R - Right
 * U - Up
 * D - Down
 * Q - LeftTop
 * Z - LeftBottom
 * P - RightTop
 * M - RightBottom
 */
bool checkwin(int x, int y) {
	char direction = 'L';
	int count = 0;
	x = x - 1;
	y = y - 1;
	
	for (int i = 0; i < winSeq; i++) {
		if (direction == 'L') {
			if (x - i < 0) {
				direction = 'R';
				i = 0;
				continue;
			}
			if (board[x - i][y] == board[x][y]) {
				count++;
			}
			else {
				direction = 'R';
				i = 0;
				continue;
			}
			//cout << winSeq << endl;
			if (count == winSeq)
				return true;
		}
		else if (direction == 'R'){
			if (x + i >= size) {
				direction = 'U';
				i = -1;
				count = 0;
				continue;
			}
			if (board[x + i][y] == board[x][y]) {
				count++;
			}
			else {
				direction = 'U';
				i = -1;
				count = 0;
				continue;
			}

			if (count == winSeq)
				return true;
		}
		else if (direction == 'U') {
			if (y - i < 0) {
				direction = 'D';
				i = 0;
				continue;
			}
			if (board[x][y - i] == board[x][y]) {
				count++;
			}
			else {
				direction = 'D';
				i = 0;
				continue;
			}

			if (count == winSeq)
				return true;
		}

		else if (direction == 'D') {
			if (y + i >= size) {
				direction = 'Q';
				i = -1;
				count = 0;
				continue;
			}
			if (board[x][y + i] == board[x][y]) {
				count++;
			}
			else {
				direction = 'Q';
				i = -1;
				count = 0;
				continue;
			}

			if (count == winSeq)
				return true;
		}

		else if (direction == 'Q') {
			if (y - i < 0 || x - i < 0) {
				direction = 'M';
				i = 0;
				continue;
			}
			if (board[x - i][y - i] == board[x][y]) {
				count++;
			}
			else {
				direction = 'M';
				i = 0;
				continue;
			}

			if (count == winSeq)
				return true;
		}

		else if (direction == 'M') {
			if (y + i >= size || x + i >= size) {
				direction = 'Z';
				i = -1;
				count = 0;
				continue;
			}
			if (board[x + i][y + i] == board[x][y]) {
				count++;
			}
			else {
				direction = 'Z';
				i = -1;
				count = 0;
				continue;
			}

			if (count == winSeq)
				return true;
		}

		else if (direction == 'Z') {
			if (y + i >= size || x - i < 0) {
				direction = 'P';
				i = 0;
				continue;
			}
			if (board[x - i][y + i] == board[x][y]) {
				count++;
			}
			else {
				direction = 'P';
				i = 0;
				continue;
			}

			if (count == winSeq)
				return true;
		}

		else if (direction == 'P') {
			if (y - i < 0 || x + i >= size) {
				break;
			}
			if (board[x + i][y + i] == board[x][y]) {
				count++;
			}
			else {
				break;
			}

			if (count == winSeq)
				return true;
		}
	}

	return false;
}

// print saved board
void printBoard(int** board) {
	int flag = 1;
	for (int i = 0; i <= size; i++) {
		for (int j = 0; j <= size; j++) {
			// print horizontal title line
			if (i == 0) {
				if (j == 0) {
					cout << "   ";
					continue;
				}

				//cout << " " << j << "  ";
				if (j / 10 == 0)
					cout << " " << j << "  ";
				else if (j / 10 < 10)
					cout << "" << j << "  ";
				else {
					cout << j << " ";
				}
				continue;
			}

			// print vertical title line
			if (j == 0 && flag == 1) {
				if (i / 10 == 0)
					cout << " " << i << " ";
				else if (i / 10 < 10)
					cout << " " << i;
				else {
					cout << i;
				}
				continue;
			}

			// print first column
			if (j == 0 && flag == 2) {
				if (i == size) 
					continue;

				cout << "   ---";
				continue;
			}

			// | between each column
			if (flag == 1) {
				if (j == size) {
					cout << " " << players[board[i - 1][j - 1]];
					j = -1;
					flag = 2;
					cout << endl;
					continue;
				}
				cout << " " << players[board[i - 1][j - 1]] << " |";
				continue;
			}
			
			// ---+--- between each row
			if (flag == 2) {
				if (j == size) {
					flag = 1;
					continue;
				}

				if (i == size) 
					continue;

				cout << "+---";
			}
		}
		// Move to new row
		cout << endl;
	}
}

void updateBoard(int x, int y, int player, int** board) {
	board[x - 1][y - 1] = player;
}

void saveGame(string filename, int** board) {
	filename = filename + ".txt";
	ofstream outputfile;
	outputfile.open(filename);

	outputfile << nplayer << endl;
	outputfile << size << endl;
	outputfile << winSeq << endl;
	outputfile << currentPlayer << endl;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			outputfile << board[i][j] << " ";
		}
		outputfile << " ";
	}

	outputfile.close();
}

void gameStart(int** board) {
	bool win;
	// Terminates until win appear or user hit quit.
	while (1) {
		// nplayers will move during each round.
		for (int i = currentPlayer + 1; i <= nplayer; i++) {
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			string x, y;
			int xPos, yPos;
			cout << "Where do you wanna put your symbol?" << endl;
			cout << "(row column OR enter Q to quit)" << endl;
			cin >> x;
			
			if (x == "Q") {
				string saveornot;
				cout << "Do you want to save the game? (Y/n)" << endl;
				cin >> saveornot;

				if (saveornot != "n" && saveornot != "Y") {
					cout << "Invalid input! Game exit without saving." << endl;
					return;
				}

				if (saveornot == "n")
					return;
				else if (saveornot == "Y") {
					string gamefilename;
					cout << "Please name the file: (w/o extension)" << endl;
					cin >> gamefilename;
					saveGame(gamefilename, board);
					return;
				}
			}
			else if (!isdigit(x[0])) {
				cout << "Invalid input, please try again!" << endl;
				continue;
			}

			else {
				cin >> y;
			}

			xPos = stoi(x);
			yPos = stoi(y);

			if (xPos > size || yPos > size) {
				cout << size << endl;
				cout << "Invalid input, please try again!" << endl;
				continue;
			}

			if (board[xPos - 1][yPos - 1] != 0) {
				cout << "Player " << board[xPos - 1][yPos - 1] << " already put his/her symbol there!";
				cout << " Please try again!" << endl;
				continue;
			}

			currentPlayer = i;
			updateBoard(xPos, yPos, i, board);
			win = checkwin(xPos, yPos);
			printBoard(board);
			if (win == true) {
				cout << "Player " << currentPlayer << " win!!" << endl;
				return;
			}
		}
		currentPlayer = 0;
	}
}

int main() {
	string saved;

	do {
		cout << "Would you like to resume a saved game? (Y/n)" << endl;
		cin >> saved;

		if (saved == "Y") {
			break;
		}
		else if (saved == "n") {
			break;
		}
		else {
			cout << "Invalid command, please try again." << endl;
		}
	} while (1);

	//for new games
	if (saved == "n") {
		vector<int> specs = checksforNewGame();
		if ((specs[2]-1) * specs[0] > specs[1]*specs[1]) {
			cout << "It's impossible to win with that board size and win sequence!" << endl;
			return 0;
		}
		//printBoard();
		currentPlayer = 0;
		board = new int* [specs[1]];
		initializeBoard(specs[1]);
		printBoard(board);
	}
	else {
		// check has the specific file or not
		string gameName;
		cout << "Please enter the game file name you wanna recover: (w/o extension)" << endl;
		cin >> gameName;

		gameName = gameName + ".txt";
		ifstream savedGame;
		savedGame.open(gameName);

		// if load game failed
		if (!savedGame.is_open()) {
			vector<int> specs = checksforNewGame();
			if ((specs[2]-1) * specs[0] > specs[1]*specs[1] || specs[2] > specs[1]) {
				cout << "It's impossible to win with that board size and win sequence!" << endl;
				return 0;
			}
			//printBoard();
			currentPlayer = 0;
			board = new int* [specs[1]];
			initializeBoard(specs[1]);
			printBoard(board);
		}
		else {
			savedGame.close();
			// load saved data and print board.
			loadSavedGame(gameName);
			printBoard(board);
		}
	}

	gameStart(board);

	delete board;

	return 0;
}