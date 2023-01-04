#include "JhleeGame.h"



JhleeGame::JhleeGame()
	:Bingo(5)
{
}


JhleeGame::~JhleeGame()
{
}

void JhleeGame::setting()
{	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	srand((unsigned)time(NULL));

	setCursorView(false);
}

void JhleeGame::play()
{
	// �޸� ���� üũ, ����� ��� ���, ���� ����, Ŀ�� �����
	setting();

	int sel;

	while (true) {

		system("cls");
		printName();

		sel = showMenu(); // okay

		switch (sel)
		{
		case 1:
			newGame();
			break;
		case 2:
			reGame();
			break;
		case 3:
			quitGame();
			return;
		default:
			break;
		}
	}
}

// 1. �����ϱ�
void JhleeGame::newGame()
{
	int n; // 3 <= n <= 9

	while (1) {
		
		system("cls");
		printName();

		cout << "\n >> �������� ���̸� �Է����ּ��� : ";
		cin >> n;
		cin.ignore();
		if (!(n >= 3 && n <= 9)) {
			cout << "\n > �ٽ� �Է����ּ���. ( 3 <= n <= 9 )";
			Sleep(1000);
		}
		else
			break;
	}

	ofstream fout("num.txt");
	fout << n;

	Bingo user = Bingo(n);
	Bingo comp = Bingo(n);

	// �� ������ �ߺ� ����
	do {
		if (checkMap(user, comp))
			break;
		else 
			reset(comp);
	} while (1);

	playGame(user, comp);
}

// 2. �̾��ϱ�
void JhleeGame::reGame()
{
	system("cls");
	printName();

	int n; // 3 <= n <= 9

	// data �Է�
	ifstream fin("num.txt");
	ifstream fin1("dataUser.txt");
	ifstream fin2("dataComp.txt");
	
	if (!(fin1.is_open() && fin2.is_open())) {
		cerr << " [Error] ���� �б� ����. \n";
		cout << "\n >> ���� ������ �����Ϸ��� �ƹ� Ű�� ��������.\n\n";
		_getch();
		return;
	}

	fin >> n;
	fin1 >> n;

	//Bingo user = Bingo(n);
	//Bingo comp = Bingo(n);

	int** userMap; bool** userIsMapped;
	int** compMap; bool** compIsMapped;

	// 2���� ���� �迭 ���� By Default Dynamic Memory
	userMap = new int*[n];
	compMap = new int*[n];

	userIsMapped = new bool*[n];
	compIsMapped = new bool*[n];

	for (size_t i = 0; i < n; i++) {
		userMap[i] = new int[n];
		userIsMapped[i] = new bool[n];
		compMap[i] = new int[n];
		compIsMapped[i] = new bool[n];
	}

	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			fin1 >> userMap[i][j] >> userIsMapped[i][j];
			fin2 >> compMap[i][j] >> compIsMapped[i][j];
		}
	}

	Bingo user(userMap, userIsMapped, n);
	Bingo comp(compMap, compIsMapped, n);


	for (int i = 0; i < n; i++) {
		delete[] userMap[i]; // �׼��� ����
		delete[] compMap[i];
		delete[] userIsMapped[i];
		delete[] compIsMapped[i];
	}
	delete[] userMap;
	delete[] compMap;
	delete[] userIsMapped;
	delete[] compIsMapped;

	playGame(user, comp);
}

// 3. ���� ������
void JhleeGame::quitGame()
{
	system("cls");
	printName();
	gotoxy(3, 5); cout << "- ������ �����մϴ�...\n\n\n";
}

void JhleeGame::playGame(Bingo & user, Bingo & comp)
{
	int** userMap = user.getMap(); bool** userIsMapped = user.getIsMapped();
	int** compMap = comp.getMap(); bool** compIsMapped = comp.getIsMapped();

	int userSel, compSel;
	list<int> sels;

	int n = user.getLength();
	
	int result = -2; // -1 : comp win
					 //  0 : DRAW
					 // +1 : user win  

	int turn = 0;

	int hint[2] = { 0,0 }; // 0 <= *hint <= n - 1

	while (result == -2) {

		userMap = user.getMap(); userIsMapped = user.getIsMapped();
		compMap = comp.getMap(); compIsMapped = comp.getIsMapped();

		showMap(user, comp);

		////// User ��
		if (!(turn % 2)) {
			
			setCursorView(true);

			cout << "  �� ( Save & Quit == -1 )\n\n";
			cout << " >> Enter number : ";

			cin >> userSel;
			sels.push_back(userSel);
			cin.ignore();

			// Save and Quit , ������ ���� �� ����
			if (userSel == -1) {
				saveData(user, comp);
				break;
			}

			if (!(userSel >= 1 && userSel <= n * n)) {
				cout << "\n > �ٽ� �Է����ּ���. \n ( 1 <= sel <= " << n * n << " )\n";
				Sleep(1000);
				continue;
			}

			// # Process 1) userSel :: Find and Check Function
			for (size_t i = 0; i < n; i++) {
				for (size_t j = 0; j < n; j++) {
					if (userMap[i][j] == userSel)
						userIsMapped[i][j] = true;
					if (compMap[i][j] == userSel) {
						compIsMapped[i][j] = true;
						hint[0] = i;
						hint[1] = j;
					}
				}
			}
			turn++;
		}

		////// Computer ��
		else {
			
			setCursorView(false);

			cout << "\n\n >> Computer �Է� �� ";
			Sleep(600); cout << ". ";
			Sleep(600); cout << ". ";
			Sleep(600); cout << ". \n";

			// # Process 2) compSel :: ��ǻ�� �¸� Algorithm �����ؼ� �߰�

			// userSel :: In-circle of Array => ���� �迭 ����, �¸� Ȯ�� UP
			if (hint[0] > 0 && hint[0] < n - 1 && hint[1] > 0 && hint[1] < n - 1) {
				int row = rand() % 3, col = rand() % 3;
				row -= 1; col -= 1;
				compSel = compMap[hint[0] + row][hint[1] + col];
			}
			// userSel :: Boundary of Array => ���� �� ����
			else {
			resel:;
				compSel = rand() % (n*n) + 1;
				if (compSel == userSel)
					goto resel;
			}

			sels.push_back(userSel);
			
			cout << "\n  * Computer SEL => [ " << compSel << " ]\n\n";
			cout << "     (Press any key to play)";
			_getch();

			for (size_t i = 0; i < n; i++) {
				for (size_t j = 0; j < n; j++) {
					if (userMap[i][j] == compSel)
						userIsMapped[i][j] = true;
					if (compMap[i][j] == compSel)
						compIsMapped[i][j] = true;
				}
			}
			turn++;
		}

		// ++ ) ���а��� �� ������ ���
		if (!(turn % 2)) {
			result = isBingoIMI(userIsMapped, compIsMapped, n);
			switch (result)
			{
			case -1: // comp win
				system("cls");
				showMap(user, comp);
				cout << "\n\n";
				cout << "================================\n";
				cout << "==      Y O U    L O S E      ==\n";
				cout << "================================\n";
				break;
			case 0: // draw
				system("cls");
				showMap(user, comp);
				cout << "\n\n";
				cout << "================================\n";
				cout << "==           D R A W          ==\n";
				cout << "================================\n";
				break;
			case 1: // user win
				system("cls");
				showMap(user, comp);
				cout << "\n\n";
				cout << "================================\n";
				cout << "==      Y O U   W I N !!      ==\n";
				cout << "================================\n";
				break;
			default:
				break;
			}
		}
	}

	// ���� ���� ���� ���÷���
	if (!(result == -2)) {
		cout << "\n\n >> Press Any Key To Watch Replay <<";
		_getch();
		replay(user, comp, sels);
	}
	else {
		cout << "\n\n >> Press Any Key To Restart <<";
		_getch();
	}

}

void JhleeGame::printName()
{
	cout << " [201812767 ������]\n\n";
}

int JhleeGame::showMenu()
{
	int sel = -1;

	cout << "===============================================\n";
	cout << "*                   M E N U                   *\n";
	cout << "===============================================\n";
	cout << "*                                             *\n";
	cout << "*     >> 1) �� ����                           *\n";
	cout << "*                                             *\n";
	cout << "*     >> 2) �̾��ϱ�                          *\n";
	cout << "*                                             *\n";
	cout << "*     >> 3) ����                              *\n";
	cout << "*                                             *\n";
	cout << "===============================================\n";
	cout << "\n >> Select menu : ";

	do {
		sel = _getch();
		sel -= 48;

		if (sel == 1 || sel == 2 || sel == 3)
			return sel;
		else
			continue;
	} while (true);
}

void JhleeGame::showMap(const Bingo & user, const Bingo & comp)
{
	system("cls");
	printName();

	// PRINT USER INTERFACE
	int** userMap = user.getMap();
	bool** userIsMapped = user.getIsMapped();
	
	gotoxy(3 * user.getLength() - 2, 6); cout << "<user>";
	for (int i = 0; i < user.getLength(); i++) {
		gotoxy(user.getLength(), i + 7);
		for (int j = 0; j < user.getLength(); j++) {
			if (userIsMapped[i][j])
				cout << setw(3) << "��";
			else
				cout << setw(3) << userMap[i][j];
		}
	}
		
	// PRINT COMPUTER INTERFACE
	int** compMap = comp.getMap();
	bool** compIsMapped = comp.getIsMapped();

	gotoxy(7 * user.getLength(), 6); cout << "<comp>";
	for (int i = 0; i < comp.getLength(); i++) {
		gotoxy(9 + 4 * user.getLength(), i + 7);
		for (int j = 0; j < comp.getLength(); j++) {
			if (compIsMapped[i][j])
				cout << setw(3) << "��";
			else
				cout << setw(3) << compMap[i][j];
		}
	}

	cout << "\n\n";
}

bool JhleeGame::checkMap(const Bingo & user, const Bingo & comp)
{
	// �� ���� �ٸ��� true ��ȯ
	int** a = user.getMap();
	int** b = comp.getMap();

	for (int i = 0; i < user.getLength(); i++) {
		for (int j = 0; i < user.getLength(); j++) {
			if (a[i][j] != b[i][j]) {
				return true;
			}
		}
	}

	return false;
}

int JhleeGame::isBingoIMI(bool ** user, bool ** comp, const int & n)
{
	bool userIsBingo = false;
	bool compIsBingo = false;

	int i, j;
	int result = -2; // -1 : comp win
						//  0 : DRAW
						// +1 : user win  

	// user ���� ���� üũ
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (!user[i][j])
				break;
			if (j == n - 1 && user[i][j])
				userIsBingo = true;
		}
	}

	// user ���� ���� üũ
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (!user[j][i])
				break;
			if (j == n - 1 && user[j][i])
				userIsBingo = true;
		}
	}

	// user �밢�� ���� üũ
	for (i = 0; i < n; i++) {
		if (!user[i][i])
			break;
		if (i == n - 1 && user[i][i])
			userIsBingo = true;
	}
	for (i = 0; i < n; i++) {
		if (!user[i][n - 1 - i])
			break;
		if (i == n - 1 && user[i][n - 1 - i])
			userIsBingo = true;
	}

	// comp ���� ���� üũ
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (!comp[i][j])
				break;
			if (j == n - 1 && comp[i][j])
				compIsBingo = true;
		}
	}

	// comp ���� ���� üũ
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (!comp[j][i])
				break;
			if (j == n - 1 && comp[j][i])
				compIsBingo = true;
		}
	}

	// comp �밢�� ���� üũ
	for (i = 0; i < n; i++) {
		if (!comp[i][i])
			break;
		if (i == n - 1 && comp[i][i])
			compIsBingo = true;
	}
	for (i = 0; i < n; i++) {
		if (!comp[i][n - 1 - i])
			break;
		if (i == n - 1 && comp[i][n - 1 - i])
			compIsBingo = true;
	}

	if (userIsBingo && compIsBingo)
		result = 0;
	else if (userIsBingo && !compIsBingo)
		result = 1;
	else if (!userIsBingo && compIsBingo)
		result = -1;
	else
		result = -2;

	return result;
}

void JhleeGame::replay(const Bingo & user, const Bingo & comp, list<int> sel)
{
	setCursorView(false);

	int select = 0;
	int n = user.getLength();
	
	auto userMap = user.getMap(); auto userIsMapped = user.getIsMapped();
	auto compMap = comp.getMap(); auto compIsMapped = comp.getIsMapped();

	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++)
			userIsMapped[i][j] = compIsMapped[i][j] = false;
	}

	system("cls");
	showMap(user, comp);
	cout << "\n\n >> Press any key to next replay.";
	_getch();

	while (!sel.empty()) {

		// user turn
		select = sel.front();
		sel.pop_front();
		for (size_t i = 0; i < n; i++) {
			for (size_t j = 0; j < n; j++) {
				if (userMap[i][j] == select)
					userIsMapped[i][j] = true;
				if (compMap[i][j] == select)
					compIsMapped[i][j] = true;
			}
		}
		system("cls");
		showMap(user, comp);
		cout << "\n\n >> Press any key to next replay.";
		_getch();


		// computer turn
		select = sel.front();
		sel.pop_front();
		for (size_t i = 0; i < n; i++) {
			for (size_t j = 0; j < n; j++) {
				if (userMap[i][j] == select)
					userIsMapped[i][j] = true;
				if (compMap[i][j] == select)
					compIsMapped[i][j] = true;
			}
		}
		system("cls");
		showMap(user, comp);
		cout << "\n\n >> Press any key to next replay.";
		_getch();
	}

	system("cls");
	showMap(user, comp);
	cout << " # Replay Completed !!";
	cout << "\n\n >> Press any key to restart game !!";
	_getch();
}

void JhleeGame::saveData(const Bingo & user, const Bingo & comp)
{
	int n = user.getLength();

	auto userMap = user.getMap();
	auto compMap = user.getMap();

	auto userIsMapped = user.getIsMapped();
	auto compIsMapped = comp.getIsMapped();

	string userData("dataUser.txt");
	string compData("dataComp.txt");

	ofstream fout1(userData);
	ofstream fout2(compData);

	if (!(fout1.is_open() && fout2.is_open())) {
		cerr << "���� ���� ����\n";
		exit(0);
	}

	// userData ����  (length ����)
	fout1 << n << '\n';
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			fout1 << userMap[i][j] << " " << (userIsMapped[i][j] ? 1 : 0) << '\n';
		}
	}

	// compData ����  (length ������)
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			fout2 << compMap[i][j] << " " << (compIsMapped[i][j] ? 1 : 0) << '\n';
		}
	}
}


