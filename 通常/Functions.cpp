# include "Functions.h"
# include "Object.h"
# include <random>

# define WIDTH 7//石の最大幅


// Zuku[y][x]
// First = trueのとき最初の石

int EvaFunc(AREA* pArea, STONE* pStone, int x, int y, int turn, bool First) {
	int Point = 0;
	bool hit = false;
	int n = 0;
	int Zuku_x = 0;
	int Zuku_y = 0;
	while (pStone->Zuku[n].x != ZUKUNULL) {
		switch (turn) {
		case 1:
			Zuku_x = pStone->Zuku[n].x + x + AREA_SENT;
			Zuku_y = pStone->Zuku[n].y + y + AREA_SENT;
			break;
		case 2:
			Zuku_x = (WIDTH - pStone->Zuku[n].y) + x + AREA_SENT;
			Zuku_y = pStone->Zuku[n].x + y + AREA_SENT;
			break;
		case 3:
			Zuku_x = (WIDTH - pStone->Zuku[n].x) + x + AREA_SENT;
			Zuku_y = (WIDTH - pStone->Zuku[n].y) + y + AREA_SENT;
			break;
		case 4:
			Zuku_x = pStone->Zuku[n].y + x + AREA_SENT;
			Zuku_y = (WIDTH - pStone->Zuku[n].x) + y + AREA_SENT;
			break;
		case 5:
			Zuku_x = (WIDTH - pStone->Zuku[n].x) + x + AREA_SENT;
			Zuku_y = pStone->Zuku[n].y + y + AREA_SENT;
			break;
		case 6:
			Zuku_x = (WIDTH - pStone->Zuku[n].y) + x + AREA_SENT;
			Zuku_y = (WIDTH - pStone->Zuku[n].x) + y + AREA_SENT;
			break;
		case 7:
			Zuku_x = pStone->Zuku[n].x + x + AREA_SENT;
			Zuku_y = (WIDTH - pStone->Zuku[n].y) + y + AREA_SENT;
			break;
		case 8:
			Zuku_x = pStone->Zuku[n].y + x + AREA_SENT;
			Zuku_y = pStone->Zuku[n].x + y + AREA_SENT;
			break;
		}
		if (pArea->Zuku[Zuku_y][Zuku_x] != 0) { return 0; }//設置不可
		else {
			//Point
			if (pArea->Zuku[Zuku_y - 1][Zuku_x] != 0)//bottom
				Point++;
			if (pArea->Zuku[Zuku_y + 1][Zuku_x] != 0)//top
				Point++;
			if (pArea->Zuku[Zuku_y][Zuku_x + 1] != 0)//left				
				Point++;
			if (pArea->Zuku[Zuku_y][Zuku_x - 1] != 0)//right
				Point++;
			//接しているか
			if (pArea->Zuku[Zuku_y - 1][Zuku_x] > 0)
				hit = true;
			if (pArea->Zuku[Zuku_y + 1][Zuku_x] > 0)
				hit = true;
			if (pArea->Zuku[Zuku_y][Zuku_x + 1] > 0)
				hit = true;
			if (pArea->Zuku[Zuku_y][Zuku_x - 1] > 0)
				hit = true;
		}
		n++;
	}
	if (First) {//最初の石
		return Point;
	}
	else if (hit) {
		return Point;
	}
	else {
		return 0;
	}
}

//石設置
void SetZuku(AREA* pArea, STONE* pStone, int num) {
	int Zuku_x = 0;
	int Zuku_y = 0;
	int n = 0;
	pArea->Point =pArea->Point - (pStone->Count * 1000 + 1);
	while (pStone->Zuku[n].x != ZUKUNULL) {
		switch (pStone->Max_Spot.turn) {
		case 1:
			Zuku_x = pStone->Zuku[n].x + pStone->Max_Spot.x + AREA_SENT;
			Zuku_y = pStone->Zuku[n].y + pStone->Max_Spot.y + AREA_SENT;
			break;
		case 2:
			Zuku_x = (WIDTH - pStone->Zuku[n].y) + pStone->Max_Spot.x + AREA_SENT;
			Zuku_y = pStone->Zuku[n].x + pStone->Max_Spot.y + AREA_SENT;
			break;
		case 3:
			Zuku_x = (WIDTH - pStone->Zuku[n].x) + pStone->Max_Spot.x + AREA_SENT;
			Zuku_y = (WIDTH - pStone->Zuku[n].y) + pStone->Max_Spot.y + AREA_SENT;
			break;
		case 4:
			Zuku_x = pStone->Zuku[n].y + pStone->Max_Spot.x + AREA_SENT;
			Zuku_y = (WIDTH - pStone->Zuku[n].x) + pStone->Max_Spot.y + AREA_SENT;
			break;
		case 5:
			Zuku_x = (WIDTH - pStone->Zuku[n].x) + pStone->Max_Spot.x + AREA_SENT;
			Zuku_y = pStone->Zuku[n].y + pStone->Max_Spot.y + AREA_SENT;
			break;
		case 6:
			Zuku_x = (WIDTH - pStone->Zuku[n].y) + pStone->Max_Spot.x + AREA_SENT;
			Zuku_y = (WIDTH - pStone->Zuku[n].x) + pStone->Max_Spot.y + AREA_SENT;
			break;
		case 7:
			Zuku_x = pStone->Zuku[n].x + pStone->Max_Spot.x + AREA_SENT;
			Zuku_y = (WIDTH - pStone->Zuku[n].y) + pStone->Max_Spot.y + AREA_SENT;
			break;
		case 8:
			Zuku_x = pStone->Zuku[n].y + pStone->Max_Spot.x + AREA_SENT;
			Zuku_y = pStone->Zuku[n].x + pStone->Max_Spot.y + AREA_SENT;
			break;
		}
		pArea->Zuku[Zuku_y][Zuku_x] = num;
		n++;
	}
}

//設置場所の探索
MAX_SPOT SpotFunc(AREA* pArea, STONE* pStone, bool First) {
	int Point = 0;
	int Max_Point = 0;
	MAX_SPOT* Max_Spots = new MAX_SPOT[16928];
	unsigned Spot_Count = 0;
	//y座標
	for (int y = -7; y < 32; y++) {
		//x座標
		for (int x = -7; x < 32; x++) {
			//turn
			for (int turn = 1; turn <= 8; turn++) {
				////////////////////////////////////////////
				//評価関数
				Point = EvaFunc(pArea, pStone, x, y, turn, First);
				if (Point > Max_Point) {
					Max_Point = Point;
					Max_Spots[0].x = x;
					Max_Spots[0].y = y;
					Max_Spots[0].turn = turn;
					Spot_Count = 1;
				}
				else if (Point == Max_Point && Point != 0) {
					Max_Spots[Spot_Count].x = x;
					Max_Spots[Spot_Count].y = y;
					Max_Spots[Spot_Count].turn = turn;
					Spot_Count++;
				}
				////////////////////////////////////////////
			}
		}
	}

	if (Spot_Count == 0) {
		MAX_SPOT MS = { 0 };
		delete[] Max_Spots;
		return MS;
	}
	else {
		static std::random_device rnd;
		static std::mt19937 rand(rnd());
		std::uniform_int_distribution<> from_to(0, Spot_Count - 1);
		int n = from_to(rand);
		MAX_SPOT MS = Max_Spots[n];
		delete[] Max_Spots;
		return MS;
	}
}

//点数の取得
//int GetPoint(AREA* Area) {
//	int Point = 0;
//	for (int x = 0; x < 46; x++) {
//		for (int y = 0; y < 46; y++) {
//			if (Area->Zuku[y][x] == 0)
//				Point++;
//		}
//	}
//	return Point;
//}

//スレッドで使う関数
void ThreadFunc(AREA* Area, STONE* pStones, int Size, int* MaxPoint) {
	AREA* copy_Area = new AREA;
	*copy_Area = (*Area);
	STONE* m_pStones = new STONE[Size];

	STONE* copy_pStones = new STONE[Size];
	for (int n = 0; n < Size; n++) {
		copy_pStones[n] = pStones[n];
	}

	*MaxPoint = 10000000;
	//モンテカルロ法
	for (unsigned int i = 0; i < TIMES; i++) {
		MAX_SPOT Max_Spot = { 0 };
		bool First = true;
		*copy_Area = *Area;
		for (int n = 0; n < Size; n++) {
			copy_pStones[n] = pStones[n];
		}

		for (int n = 1; n <= Size; n++) {
			//評価
			Max_Spot = SpotFunc(copy_Area, &copy_pStones[n - 1], First);
			//石設置
			if (Max_Spot.turn != 0) {
				First = false;
				copy_pStones[n - 1].Max_Spot = Max_Spot;
				SetZuku(copy_Area, &copy_pStones[n - 1], n);
			}
		}
		unsigned int Point = copy_Area->Point;
		if (Point < *MaxPoint) {
			*MaxPoint = Point;
			for (int n = 0; n < Size; n++) {
				m_pStones[n] = copy_pStones[n];
			}
		}
	}
	//石の確定
	for (int n = 0; n < Size; n++) {
		pStones[n] = m_pStones[n];
	}
	//メモリの解放
	delete copy_Area;
	delete[] m_pStones;
	delete[] copy_pStones;
}