#pragma once
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif // !DBG_NEW
#endif

#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <Windows.h>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <cmath>

using namespace std;

class Bingo
{
private:
	Bingo();
protected:
	const int length;
	int** map = nullptr;
	bool** isMapped = nullptr;

	//int* sels = nullptr;

	string filename;
public:
	Bingo(const int& lenght);		// 생성자
	Bingo(int** &map, bool** &isMapped, const int& n);
	~Bingo();

	// Bingo의 멤버 변수 설정 및 초기화
	void makeMap(int** map);			// 안씀
	void setIsMapped(bool** ismap);		// 안씀2

	void reset(Bingo& bingo);


	int** getMap();
	int** getMap() const;
	bool** getIsMapped() const;
	int getLength() const;

};

