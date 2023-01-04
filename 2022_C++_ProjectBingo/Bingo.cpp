///////////////////////
////   Bingo.cpp   ////

#include "Bingo.h"

Bingo::Bingo()
	:length(0)
{
}

Bingo::Bingo(const int & length)
	: length(length)//, filename("dataBack.txt")
{
	// 2차원 동적 배열 생성 By Default Dynamic Memory
	this->map = new int*[length];
	this->isMapped = new bool*[length];
	
	for (size_t i = 0; i < length; i++) {
		this->map[i] = new int[length];
		this->isMapped[i] = new bool[length];
	}

	// 생성 후 초기화
	for (size_t j = 0; j < length; j++) {
		for (size_t k = 0; k < length; k++) {

			this->isMapped[j][k] = false;
		re:;
			this->map[j][k] = rand() % (length*length) + 1;
			// 중복제거
			for (size_t j1 = 0; j1 < j; j1++) {
				for (size_t k1 = 0; k1 < length; k1++) {
					if (map[j][k] == map[j1][k1])
						goto re;
				}
			}
			size_t j2 = j;
			for(size_t k2=0;k2<k;k2++)
				if (map[j][k] == map[j2][k2])
					goto re;
		}
	}

	//makeMap(this->map);
	//setIsMapped(this->isMapped);
	
}

Bingo::Bingo(int ** &map, bool** &isMapped, const int & n)
	:length(n)
{
	// 2차원 동적 배열 생성 By Default Dynamic Memory
	this->map = new int*[length];
	this->isMapped = new bool*[length];

	for (size_t i = 0; i < length; i++) {
		this->map[i] = new int[length];
		this->isMapped[i] = new bool[length];
	}

	// Data 입력
	for (size_t i = 0; i < length; i++) {
		for (size_t j = 0; j < length; j++) {
			this->map[i][j] = map[i][j];
			this->isMapped[i][j] = isMapped[i][j];
		}
	}
}

/*
Bingo::Bingo(const Bingo & bingo)
{
	bool isOk = false;
	this->length = bingo.length;

re:;
	makeMap(this->map);

	for (int i = 0; i < this->length; i++) {
		for (int j = 0; j < this->length; j++) {
			if (this->map[i][j] != bingo.map[i][j]) {
				isOk = true;
			}
		}
	}
	if (!isOk)
		goto re;
}
*/

// Delete Memory
Bingo::~Bingo()
{
	if (this->map != nullptr) {
		for (int i = 0; i < length; i++) {
			delete[] this->map[i];
		}
		delete[] this->map;
		this->map = nullptr;
	}

	if (this->isMapped != nullptr) {
		for (int j = 0; j < length; j++) {
			delete[] this->isMapped[j];
		}
		delete[] this->isMapped;
		this->isMapped = nullptr;
	}
}

void Bingo::makeMap(int ** map)
{
	// 2차원 Dynamic Array 에 1~lengnth^2 값 중복 제거 할당
	for (size_t j = 0; j < length; j++) {
		for (size_t k = 0; k < length; k++) {
		re:;
			map[j][k] = rand() % (length*length) + 1;

			// 중복제거
			for (int jj = 0; jj <= j; jj++) {
				for (int kk = 0; kk <= k; kk++) {
					if (map[jj][kk] == map[j][k] && !(j == jj && k == kk))
						goto re;
				}
			}
		}
	}
}

void Bingo::setIsMapped(bool ** ismap)
{
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++)
			ismap = false;
	}
}

void Bingo::reset(Bingo& bingo)
{
	auto temp = bingo.map[0][0];
	bingo.map[0][0] = bingo.map[1][1];
	bingo.map[1][1] = temp;
}

int ** Bingo::getMap()
{
	if (map != nullptr)
		return this->map;
}

int ** Bingo::getMap() const
{
	if (map != nullptr)
		return this->map;
}

bool ** Bingo::getIsMapped() const
{
	if (isMapped != nullptr)
		return this->isMapped;
}

int Bingo::getLength() const
{
	return this->length;
}
