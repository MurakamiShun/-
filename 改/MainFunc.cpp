/*////////////////////////////////////////
turn:
0:PASS
1:head & 0
2:head & 90
3:head & 180
4:head & 270
5:tail & 0
6:tail & 90
7:tail & 180
8:tail & 270

////////////////////////////////////////*/

/*//////////////////////////////////////
Area:
0:Nothing
-1:Obstacle

Stone:
Pos: x, y
Num: First = 1
//////////////////////////////////////*/

# include <fstream>
# include <thread>
# include "Functions.h"
# include "Object.h"
# include "Class.h"

using namespace std;

extern GUIout Gout;
extern DayDuty DD;

void MainFunc(char* FilePass){
	AREA Area;
	Area.Point = 0;
	for (int i = 0; i < AREA_SENT; i++){
		for (int j = 0; j < 46; j++){
			Area.Zuku[i][j] = Area.Zuku[39 + i][j] = Area.Zuku[j][i] = Area.Zuku[j][39 + i] = -1;
		}
	}
	STONE* pStones = NULL;
	int Size = 0;
	//�ǂݍ���
	{
		ifstream ifs(FilePass);
		if (!ifs){ goto ERROR; }

		char buff[64];
		//�~�n
		for (int Line = 0; Line < 32; Line++){
			ifs.getline(buff, 64);
			for (int i = 0; i < 32; i++){
				Area.Zuku[Line + AREA_SENT][i + AREA_SENT] = (buff[i] == '1') ? -1 : 0;
				Area.Point += ((buff[i] == '1') ? 0 : 1000);
			}
		}
		ifs.getline(buff, 64);//���s
		//��
		ifs.getline(buff, 64);
		Size = atoi(buff);
		int Zuku_num = 0;
		//���������蓖��
		pStones = new STONE[Size];
		for (int n = 0; n < Size; n++){
			Zuku_num = 0;
			for (int y = 0; y < 8; y++){
				ifs.getline(buff, 64);
				for (int x = 0; x < 8; x++){
					if (buff[x] == '1'){
						pStones[n].Zuku[Zuku_num].x = x;
						pStones[n].Zuku[Zuku_num].y = y;
						Zuku_num++;
					}
				}
			}
			pStones[n].Zuku[Zuku_num].x = pStones[n].Zuku[Zuku_num].y = ZUKUNULL;
			pStones[n].Max_Spot.x = pStones[n].Max_Spot.y = pStones[n].Max_Spot.turn = 0;
			pStones[n].Count = Zuku_num;
			ifs.getline(buff, 64);//���s
		}
		ifs.close();
	}
	Gout << L"�ϊ�����\n";
	Gout << L"���s��...";
	//�X���b�h�Ȃǂ̗p�ӁE���s
	const int Thread_Count = thread::hardware_concurrency();
	int* MaxPoints = new int[Thread_Count];
	thread* threads = new thread[Thread_Count];
	STONE** c_Stones = new STONE*[Thread_Count];
	//���s
	for (int i = 0; i < Thread_Count; i++){
		c_Stones[i] = new STONE[Size];
		for (int n = 0; n < Size; n++){
			c_Stones[i][n] = pStones[n];
		}
		threads[i] = thread::thread(ThreadFunc, &Area, &c_Stones[i][0], Size, &MaxPoints[i]);
	}
	//�X���b�h�̑ҋ@
	for (int i = 0; i < Thread_Count; i++){
		threads[i].join();
	}
	//�ő哾�_�̎擾
	int Max_num = 0;
	int Max_Point = MaxPoints[0];
	for (int i = 1; i < Thread_Count; i++){
		if (MaxPoints[i] < Max_Point){
			Max_num = i;
			Max_Point = MaxPoints[i];
		}
	}
	Gout << L"�I��\n";
	Gout << L"���_:" + Format(int(Max_Point/1000)) + L"�_\n";
	Gout << L"�g�����΂̐�" + Format(Max_Point % 1000) + L"��\n";
	for (int n = 0; n < Size; n++){
		pStones[n] = c_Stones[Max_num][n];
	}
	for (int i = 0; i < Thread_Count; i++){
		delete[] c_Stones[i];
	}
	delete[] threads;
	delete[] MaxPoints;
	delete[] c_Stones;
	//�t�@�C���ɏo��
	if (DD.SetPoint(Max_Point)) {
		Gout << L"�t�@�C���ɏo��...";
		ofstream ofs("files/result.txt");
		if (!ofs) {
			Gout << L"�t�@�C�����J���܂���\n";
			goto ERROR;
		}
		for (int i = 0; i < Size; i++) {
			if (pStones[i].Max_Spot.turn == 0) {
				ofs << endl;
			}
			else {
				ofs << pStones[i].Max_Spot.x << " " << pStones[i].Max_Spot.y << " " << (((pStones[i].Max_Spot.turn / 5) == 0) ? 'H' : 'T') << " " << ((pStones[i].Max_Spot.turn - 1) % 4) * 90 << endl;

			}
		}
		ofs.close();
		Gout << L"����\n";
	}
	//���������
	delete[] pStones;

	return;

ERROR:
	Gout << L"�G���[����\n";
	return;
}