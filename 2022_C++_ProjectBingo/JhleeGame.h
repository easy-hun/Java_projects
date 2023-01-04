#include "Bingo.h"


class JhleeGame :
	public Bingo
{
private:
	// queue<int> sel;
protected:

public:

	JhleeGame();
	~JhleeGame();
	
	// 0.
	void setting();

	// 1. Basic function
	void play();

	void newGame();
	void reGame();
	void quitGame();

	void playGame(Bingo& user, Bingo& comp);


	// 2. Tool functions
	void printName();
	int showMenu();
	void showMap(const Bingo& user, const Bingo& comp);
	bool checkMap(const Bingo& user, const Bingo& comp);
	int isBingoIMI(bool** user, bool** comp, const int& n);
	void replay(const Bingo& user, const Bingo& comp, list<int> sel);
	void saveData(const Bingo& user, const Bingo& comp);
	// Windows API function
	void setCursorView(bool visible) {
		CONSOLE_CURSOR_INFO cursor = { 1, visible };
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
	}
	void gotoxy(int x, int y) {
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
};

