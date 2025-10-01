#include <iostream>
#include<cstring>
#include<string>
#include<iomanip>
using namespace std;
//05430D083B183F91BCD8193EDF4DE94F00080015BCA408C0163BFB4DAB173F80F5081BC16EA4371cc12d31271d42513d4f4a000000004b000000004c00000000

struct parameter
{
	int ID;
	int info;
	int weight;
	string name;
	string type;
	string measure;

	/*parameter(const parameter& obj)
	{
		this->ID = obj.ID;
		this->info = obj.info;
		this->name = obj.name;
		this->type = obj.type;
		this->measure = obj.measure;
	}*/
};

void StructInit(parameter array[]);
void Structout(parameter array[]);

float chars_to_float(const unsigned char bytes[]) {
	float result;  // объявляем переменную
	memcpy(&result, bytes, sizeof(float));
	return result;
}

void filter(parameter f_structmas[], unsigned char f_pack[],int packlen) { //функция поиска существующих ID 
	int pack_cnt = 0;
	int checked_id = 0;// не факт что надо
	while (pack_cnt < packlen)// идем по байтам принятого пакета
	{
		for (int i = 0+checked_id; i < 17; i++) // сверяем байт со списком наших ID
		{
			if (f_pack[pack_cnt] == f_structmas[i].ID) {//Если найдено соответствие и байт является ID 
				pack_cnt = pack_cnt + f_structmas[i].weight;//пропускаем байты идущие за ID, поскольку они являются данными
				//checked_id++;//попытка исключить ID из сверки не факт что надо
				f_structmas[i].info = f_structmas[i].ID; // пока что флажок на то что мы прочитали чела
			}
		}
		pack_cnt++;
	}
}

int maslen(unsigned char m_pack[]) { // функция подсчета веса массива
	int len = sizeof(m_pack);
	return len;
}

void filter_type(unsigned char m_pack[], parameter f_structmas[]);

int main()
{
	//unsigned char pack[] = {0x05,0x3F,0x80,0x00,0x00,0x09,0x01,0x1C,0x40,0x00,0x00,0x00};
	//unsigned char pack[] = { 0x4C,0x41,0xA4,0x00,0x00,0x4B,0x3F,0x91,0xBC,0xD8 };
	unsigned char pack[] = { 0x07,0x41,0xA4,0x00,0x00,0x05,0x3F,0x91,0xBC,0xD8, 0x19, 0x41, 0x35, 0x47, 0xAE };
	setlocale(LC_ALL, "Rus");

	//unsigned char checkpack[] = { 0x3F,0x80,0x00,0x00 };
	//unsigned char checkpack[] = { 0x00,0x00,0x80,0x3F };
	//float answ = chars_to_float(checkpack);
	//cout << answ << endl;

	parameter structmas[17];
	StructInit(structmas);
	Structout(structmas);
	cout << endl;
	int length = maslen(pack);
	filter(structmas,pack,length);
	Structout(structmas);
	return 0;
}

void StructInit(parameter arrayS[])
{
	parameter P5 {5,  0, 4, "kHeading",       "float",    "град."};
	parameter P24{24, 0, 4, "kPitch",         "float",    "град." };  
	parameter P25{25, 0, 4, "kRoll",          "float",    "град." };
	parameter P79{79, 0, 1, "kHeadingStatus", "char",     "" };
	parameter P77{77, 0, 16, "kQuaternion",    "float[4]", "" };
	parameter P7 {7,  0, 4, "kTemperature",   "float",    "град.С" };
	parameter P8 {8,  0, 1, "kDistortion",    "bool",     "True/false" };
	parameter P9 {9,  0, 1, "kCalStatus",     "bool",     "True/false" };
	parameter P21{21, 0, 4, "kAccelX",        "float",    "g" };
	parameter P22{22, 0, 4, "kAccelY",        "float",    "g" };
	parameter P23{23, 0, 4, "kAccelZ",        "float",    "g" };
	parameter P27{27, 0, 4, "kMagX",          "float",    "mT" };
	parameter P28{28, 0, 4, "kMagY",          "float",    "mT" };
	parameter P29{29, 0, 4, "kMagZ",		  "float",    "mT" };
	parameter P74{74, 0, 4, "kGyroX",         "float",    "рад/сек" };
	parameter P75{75, 0, 4, "kGyroY",         "float",    "рад/сек" };
	parameter P76{76, 0, 4, "kGyroZ",         "float",    "рад/сек" };

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
		cout << fixed << left << setw(15)<< array[i].name<< ' ' 
			 << fixed << internal << setw(3) << array[i].ID <<' ' 
			 << fixed << internal << setw(2) << array[i].info<< ' ' 
			 << fixed << left << setw(7)<< array[i].type << ' ' 
			 << fixed << left << setw(7) << array[i].measure << endl;
	}
}

//,void sort(parameter array[])