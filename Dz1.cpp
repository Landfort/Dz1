#include <iostream>
#include<cstring>
#include<string>
#include<iomanip>
using namespace std;
//05430D083B183F91BCD8193EDF4DE94F00080015BCA408C0163BFB4DAB173F80F5081BC16EA4371cc12d31271d42513d4f4a000000004b000000004c00000000

struct parameter
{
	int ID;			//DECOR
	bool flag;		//FUNC
	float info;		//FUNC-DECOR
	int weight;		//FUNC
	int casing;		//FUNC
	string name;	//DECOR
	string type;	//DECOR
	string measure;	//DECOR
	//strcut a()
};

void StructInit(parameter array[]);
void Structout(parameter array[]);
void deshifr(parameter d_structmas[], unsigned char d_pack[], int pack_cnt, int ai);


void filter(parameter f_structmas[], unsigned char f_pack[],int packlen) { //функция поиска существующих ID 
	int pack_cnt = 0;
	while (pack_cnt < packlen)// идем по байтам принятого пакета
	{
		for (int i = 0; i < 17; i++) // сверяем байт со списком наших ID
		{
			if (f_pack[pack_cnt] == f_structmas[i].ID && f_structmas[i].flag!=1) {//Если найдено соответствие и байт является ID
				f_structmas[i].flag = 1;
				deshifr(f_structmas, f_pack, pack_cnt,i);
				pack_cnt = pack_cnt + f_structmas[i].weight;//пропускаем байты идущие за ID, поскольку они являются данными
				
			}
		}
		pack_cnt++;
	}
}

void deshifr(parameter d_structmas[], unsigned char d_pack[], int pack_cnt, int ai)
{
	switch (d_structmas[ai].casing)
	{
		case 4: {
			int mas_cnt = 3;
			unsigned char mas[4] = { 0x00,0x00,0x00,0x00 };
			for (int j = pack_cnt + 1; j < pack_cnt + 5; ++j)
			{
				mas[mas_cnt] = d_pack[j];
				mas_cnt--;
			}
			float result;  // объявляем переменную
			memcpy(&result, mas, sizeof(float));
			d_structmas[ai].info = result;

			cout << fixed << left << setw(15) << d_structmas[ai].name << " "
				<< fixed << left << setw(3) << d_structmas[ai].ID << " "
				<< fixed << left << setw(8) << setprecision(4) << d_structmas[ai].info << " "
				<< fixed << left << setw(7) << d_structmas[ai].type << " "
				<< fixed << left << setw(7) << d_structmas[ai].measure << endl;

			break;
		}
		
		case 3: { 
			
			float fl_mas[4];
			int fl_cnt = 0;
			while (fl_cnt < 4) {
			
				int mas_cnt = 3;
				unsigned char mas[4] = { 0x00,0x00,0x00,0x00 };
				for (int j = pack_cnt + 1; j < pack_cnt + 5; ++j)
				{
					mas[mas_cnt] = d_pack[j];
					mas_cnt--;
				}
				float result;  // объявляем переменную
				memcpy(&result, mas, sizeof(float));
				fl_mas[fl_cnt] = result;
				pack_cnt = pack_cnt + 4;
				fl_cnt++;
			}

			cout << fixed << left << setw(15) << d_structmas[ai].name << " "
				<< fixed << left << setw(3) << d_structmas[ai].ID << " "
				<< fixed << left<< "[" << setprecision(4) << fl_mas[0] << ", " 
				<< setprecision(4) << fl_mas[1] << ", "
				<< setprecision(4) << fl_mas[2] << ", "
				<< setprecision(4) << fl_mas[3] << "] " << " "
				<< fixed << left << setw(7) << d_structmas[ai].type << " "
				<< fixed << left << setw(7) << d_structmas[ai].measure << endl;

			break; 
		}

		case 2: {
			if (d_pack[pack_cnt + 1] == 1) d_structmas[ai].info = 1;
			else d_structmas[ai].info = 0;

			if (d_structmas[ai].info == 1) {
				cout << fixed << left << setw(15) << d_structmas[ai].name << " "
					<< fixed << left << setw(3) << d_structmas[ai].ID << " "
					<< fixed << left << setw(8) << "true" << " "
					<< fixed << left << setw(7) << d_structmas[ai].type << " "
					<< fixed << left << setw(7) << d_structmas[ai].measure << endl;
			}
			else
			{
				cout << fixed << left << setw(15) << d_structmas[ai].name << " "
					<< fixed << left << setw(3) << d_structmas[ai].ID << " "
					<< fixed << left << setw(8) << "false" << " "
					<< fixed << left << setw(7) << d_structmas[ai].type << " "
					<< fixed << left << setw(7) << d_structmas[ai].measure << endl;
			}

			break;
		}

		case 1: {
			cout << fixed << left << setw(15) << d_structmas[ai].name << " "
				<< fixed << left << setw(3) << d_structmas[ai].ID << " "
				<< fixed << left << setw(8) << d_pack[pack_cnt] << " "
				<< fixed << left << setw(7) << d_structmas[ai].type << " "
				<< fixed << left << setw(7) << d_structmas[ai].measure << endl;
			break;
		}

	}
}

int maslen(unsigned char m_pack[]) { // функция подсчета веса массива
	int len;
	int flag = 0xFF;
	int i = 0;
	while (m_pack[i] != flag)++i;
	len = i;
	return len;
}

int main()
{
	//unsigned char pack[] = {0x05,0x3F,0x80,0x00,0x00,0x09,0x01,0x1C,0x40,0x00,0x00,0x00,0xFF};
	//unsigned char pack[] = { 0x4C,0x41,0xA4,0x00,0x00,0x4B,0x3F,0x91,0xBC,0xD8,0xFF };
	//unsigned char pack[] = { 0x07,0x41,0xA4,0x00,0x00,0x05,0x3F,0x91,0xBC,0xD8,0x19,0x41,0x35,0x47,0xAE,0xFF };
	unsigned char pack[] = {0x05,0x43,0x0D,0x08,0x3B,0x18,0x3F,0x91,0xBC,0xD8,0x19,0x3E,0xDF,0x4D,0xE9,0x4D,
	0x42,0x28,0x69,0xE2,0x41,0xF8,0xF5,0xC3,0x41,0xDE,0xC2,0x8F,0x3C,0x59,0x4D,0x0E,0xFF};
	/*unsigned char pack[] = { 0x05,0x43,0x0D,0x08,0x3B,0x18,0x3F,0x91,0xBC,0xD8,0x19,0x3E,0xDF,0x4D,0xE9,
		0x4F,0x00,0x08,0x00,0x15,0xBC,0xA4,0x08,0xC0,0x16,0x3B,0xFB,0x4D,0xAB,0x17,
		0x3F,0x80,0xF5,0x08,0x1B,0xC1,0x6E,0xA4,0x37,0x1C,0xC1,0x2D,0x31,0x27,0x1D,
		0x42,0x51,0x3D,0x4F,0x4A,0x00,0x00,0x00,0x00,0x4B,0x00,0x00,0x00,0x00,0x4C,0x00,0x00,0x00,0x00,0xFF };*/

	setlocale(LC_ALL, "Rus");

	parameter structmas[17];
	StructInit(structmas);
	cout << endl;
	int length = maslen(pack);
	filter(structmas,pack,length);
	return 0;
}

void StructInit(parameter arrayS[])
{
	parameter P5 {5, 0, 0, 4, 4 ,"kHeading",       "float",    "град."};
	parameter P24{24,0, 0, 4, 4 ,"kPitch",         "float",    "град." };  
	parameter P25{25,0, 0, 4, 4 ,"kRoll",          "float",    "град." };
	parameter P79{79,0, 0, 1, 1 ,"kHeadingStatus", "char",     "" };
	parameter P77{77,0, 0, 16, 3,"kQuaternion",    "float[4]", "" };
	parameter P7 {7, 0, 0, 4, 4 ,"kTemperature",   "float",    "град.С" };
	parameter P8 {8, 0, 0, 1, 2 ,"kDistortion",    "bool",     "True/false" };
	parameter P9 {9, 0, 0, 1, 2 ,"kCalStatus",     "bool",     "True/false" };
	parameter P21{21,0, 0, 4, 4 ,"kAccelX",        "float",    "g" };
	parameter P22{22,0, 0, 4, 4 ,"kAccelY",        "float",    "g" };
	parameter P23{23,0, 0, 4, 4 ,"kAccelZ",        "float",    "g" };
	parameter P27{27,0, 0, 4, 4 ,"kMagX",          "float",    "mT" };
	parameter P28{28,0, 0, 4, 4 ,"kMagY",          "float",    "mT" };
	parameter P29{29,0, 0, 4, 4 ,"kMagZ",		   "float",    "mT" };
	parameter P74{74,0, 0, 4, 4 ,"kGyroX",         "float",    "рад/сек" };
	parameter P75{75,0, 0, 4, 4 ,"kGyroY",         "float",    "рад/сек" };
	parameter P76{76,0, 0, 4, 4 ,"kGyroZ",         "float",    "рад/сек" };

	arrayS[0]  = P5;
	arrayS[1]  = P24;
	arrayS[2]  = P25;
	arrayS[3]  = P79;
	arrayS[4]  = P77;
	arrayS[5]  = P7;
	arrayS[6]  = P8;
	arrayS[7]  = P9;
	arrayS[8]  = P21;
	arrayS[9]  = P22;
	arrayS[10] = P23;
	arrayS[11] = P27;
	arrayS[12] = P28;
	arrayS[13] = P29;      
	arrayS[14] = P74;
	arrayS[15] = P75;
	arrayS[16] = P76;
}


void Structout(parameter array[])
{
	for (int i = 0; i < 17; i++)
	{
		
			cout << fixed << left << setw(15) << array[i].name << ' '
				<< fixed << internal << setw(3) << array[i].ID << ' '
				<< fixed << internal << setw(2) << array[i].info << ' '
				<< fixed << left << setw(7) << array[i].type << ' '
				<< fixed << left << setw(7) << array[i].measure << endl;
		
	}
}

