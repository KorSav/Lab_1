#pragma warning(disable : 4996)
#include "funcs.h"

int main(int argc, char *argv[]) {
	//встановлення номеру сторінки кодування для роботи з кирилицею
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//обробка параметрів командного рядка
	if (argc != 3 || strcmp(argv[1], "-mode"))
		cout << "Для роботи програми необхідно передати" << endl
		     << "параметри командного рядка: -mode FilePointer (FileStream)" << endl;
	else if (!strcmp(argv[2], "FileStream")) {
		//Робота з файлами та даними за допомогою потоків та класу string
		string file,     //назва початкового файлу
		       new_file, //назва нового файлу (автоматично задається програмою)
		       buffer;	 //буфер для обробки рядків згідно з завданням
		char   answer;	 //код символу, який вводить користувач, відповідаючи на питання
		do {//головний цикл (для циклічності програми)
			cout << "Назва файлу, без розширення: ";
			cin >> file;
			new_file = (file + "_new");
			if (file_exists(file)) { 
				//якщо обраний файл існує, то виводиться вміст файлу
				//і користувач вирішує чи працювати з ним далі, чи доповнити його (вимога №5)
				cout << "Вміст файлу:" << endl << endl;
				file_print(file);
				cout << endl;
				cout << "Якщо бажаєте працювати з цим файлом, натисніть ENTER" << endl;
				if (_getch() != 13) { answer = 13; continue; }
				cout << "Якщо бажаєте доповнити файл, натисніть ENTER" << endl;
				if (_getch() == 13) {
					cout << "Щоб закінчити, в кінці рядка введіть символи \\0 і натисніть ENTER" << endl;
					file_append(file);
				}
			}
			else {
				//якщо файлу немає, то він створюється
				//користувач або заповнює його, або програма сама генерує текст (параметри в заголовочному файлі)
				file_create(file);
				cout << "Для автоматичного заповнення файлу натисність ENTER" << endl
				     << "Для заповнення вручну - будь-яку іншу клавішу" << endl;
				if (_getch() == 13)
					file_fill(file, buffer);
				else {
					cout << "Щоб закінчити, в кінці рядка введіть символи \\0 і натисніть ENTER" << endl;
					file_append(file);
				}
				cout << "Вміст файлу:" << endl << endl;
				file_print(file); cout << endl;
			}
			//обробка файлу згідно з завданням
			file_asterix(file, new_file, buffer);
			cout << "1. Створено новий файл \"" << new_file << "\", його вміст:\n" << endl;
			file_print(new_file);
			file_change(file, buffer);
			cout << endl;
			cout << "2. Файл \"" << file << "\" змінено, його вміст:" << endl << endl;
			file_print(file);
			cout << endl;
			//циклічність програми
			cout << "Якщо бажаєте продовжити працювати з програмою натисніть ENTER" << endl;
			answer = _getch();
		} while (answer == 13);
	}
	else if (!strcmp(argv[2], "FilePointer")) {
		//Робота з файлами та даними за допомогою покажчика на файл та динамічного масиву символів
		char *file,	//назва початкового файлу
		     *new_file, //назва нового файлу (автоматично задається програмою)
		     *buffer,	//буфер, в якому міститься вся інформація для роботи програми
		      answer;	//код символу, який вводить користувач, відповідаючи на питання
		//виділення пам'яті та налаштування покажчиків
		buffer = (char*)calloc(2*FNAME_SIZE+5 + BUFER_SIZE, 1);
		if (!buffer) {
			printf("Не вдалося виділити пам'ять для роботи програми!");
			return 1;
		}
		file = buffer + BUFER_SIZE;
		new_file = file + FNAME_SIZE;
		do {//головний цикл (для циклічності програми)
			new_file[0] = '\0';
			printf("Назва файлу, без розширення: ");
			scanf("%s", file); strcpy(new_file, file);
			strcat(new_file, "_new");
			if (file_exists(file)) {
				//якщо обраний файл існує, то виводиться вміст файлу
				//і користувач вирішує чи працювати з ним далі, чи доповнити його (вимога №5)
				printf("Вміст файлу:\n\n");
				file_print(file);
				printf("\nЯкщо бажаєте працювати з цим файлом, натисніть ENTER\n");
				if (_getch() != 13) { answer = 13; continue; }
				printf("\nЯкщо бажаєте доповнити файл, натисніть ENTER\n");
				if (_getch() == 13) {
					printf("Щоб закінчити, в кінці рядка введіть символи \\0 і натисніть ENTER\n");
					file_append(file);
				}
			}
			else {
				//якщо файлу немає, то він створюється
				//користувач або заповнює його, або програма сама генерує текст (параметри в заголовочному файлі)
				file_create(file);
				printf("Для автоматичного заповнення файлу натисність ENTER\n"
				       "Для заповнення вручну - будь-яку іншу клавішу\n");
				if (_getch() == 13)
					file_fill(file, buffer);
				else {
					printf("Щоб закінчити, в кінці рядка введіть символи \\0 і натисніть ENTER\n");
					file_append(file);
				}
				printf("Вміст файлу:\n\n");
				file_print(file); printf("\n\n");
			}
			//обробка файлу згідно з завданням
			file_asterix(file, new_file, buffer);
			printf("1. Створено новий файл \"%s\", його вміст:\n\n", new_file);
			file_print(new_file);
			file_change(file, buffer);
			printf("\n2. Файл \"%s\" змінено, його вміст:\n\n", file);
			file_print(file);
			//циклічність програми
			printf("\nЯкщо бажаєте продовжити працювати з програмою натисніть ENTER\n");
			answer = _getch();
		} while (answer == 13);
		free(buffer);
	}
	else
		cout << "Невідомий режим: " << argv[2] << endl
		     << "Допустимі режими: FilePointer, FileStream." << endl;
	return 0;
}
