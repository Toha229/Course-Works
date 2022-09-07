#include "Matrix.h"
//#include <MMSystem.h>
//#pragma comment(lib, "winmm.lib")

int main()
{
	srand(time(0));
	////PlaySound(TEXT("menu.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	//cout << "16237689";
	//while (true) {
	//	cout << 1;
	//}
	Matrix m;
	while (1) {
		if (!m.Draw()) {
			return 0;
		}
		
	}
	HANDLE Con = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Con, 15);

}