#pragma warning(disable : 4996)
#include "funcs.h"

using namespace std;

//створення файлу
void file_create(string fileName) {
	ofstream newFile(fileName+".txt");
	newFile.close();
	return;
}
void file_create(char  *fileName) {
	int ierase = strlen(fileName);
	strcat(fileName, ".txt");
	FILE* file; 
	file = fopen(fileName, "w");
	fclose(file);
	fileName[ierase] = '\0';
	return;
}

//випадкове заповнення файлу
void file_fill(string fileName, string rword_buf) {
	bool bigletter = true;
	int seed = time(NULL);
	fstream file(fileName+".txt", ios::out|ios::trunc);
	for (int i = 0; i < RNUM; i++) {
		for (int j = 0; j < WNUM; j++) {
			srand((seed+=j+1) * time(NULL));
			random_word(rword_buf, bigletter);
			file << rword_buf;
			if (rand() % 2) {
				file << ". ";
				bigletter = true;
			}
			else {
				file << " ";
				bigletter = false;
			}
		}
		file << endl;
	}
	file.close();
	return;
}
void file_fill(char* fileName, char* rword_buf) {
	int ierase = strlen(fileName);
	char bigletter = 1;
	strcat(fileName, ".txt");
	FILE* file = fopen(fileName, "w");
	for (int i = 0; i < RNUM; i++) {
		for (int j = 0; j < WNUM; j++) {
			srand((i + 13) * (j + 7)+time(NULL));
			random_word(rword_buf, bigletter);
			fprintf(file, rword_buf);
			if (rand() % 2) {
				fprintf(file, ". ");
				bigletter = 1;
			}
			else {
				fprintf(file, " ");
				bigletter = 0;
			}
		}
		fprintf(file, "\n");
	}
	fclose(file);
	fileName[ierase] = '\0';
	return;
}

//допис у файл
void file_append(string fileName) {
	//для закінчення допису вводиться \0
	char ch;
	bool slash = false;
	ofstream file(fileName+".txt", ios_base::app);
	while (cin.get() != '\n');
	while ((ch = cin.get()) != '0' || !slash) {
		if (ch == '\\') slash = true;
		else if (ch == -1) file << "Я"; //код літери я співпадає з кодом EOF(-1)
		else file << ch;
	}
	file << endl;
	file.close();
	return;
}
void file_append(char* fileName) {
	//для закінчення допису вводиться \0
	char slash=0, c;
	int ierase = strlen(fileName);
	strcat(fileName, ".txt");
	FILE* file = fopen(fileName, "a");
	while (fgetc(stdin) != '\n');
	while ((c = fgetc(stdin)) != '0' || !slash) {
		if (c == '\\') slash = 1;
		else if (c == -1) fputc('Я', file); //код літери я співпадає з кодом EOF(-1)
		else fputc(c, file);
	}
	fputc('\n', file);
	fclose(file);
	fileName[ierase] = '\0';
	return;
}

//виведення вмісту файлу
void file_print(string fileName) {
	char c;
	ifstream file(fileName + ".txt");
	if ((c = file.get()) == EOF)
		cout << "Файл порожній!";
	else {
		do cout << c;
		while ((c = file.get()) != EOF);
	}
	file.close();
	return;
}
void file_print(char* fileName) {
	char c;
	int ierase = strlen(fileName);
	strcat(fileName, ".txt");
	FILE* file = fopen(fileName, "r");
	if ((c = fgetc(file)) == EOF)
		printf("Файл порожній!");
	else {
		do printf("%c", c);
		while ((c = fgetc(file)) != EOF);
	}
	fclose(file);
	fileName[ierase] = '\0';
	return;
}

//перевірка існування файлу
bool file_exists(string fileName) {
	ifstream file(fileName + ".txt");
	if (!file)
		return false;
	file.close();
	return true;
}
char file_exists(char* fileName) {
	int ierase = strlen(fileName);
	strcat(fileName, ".txt");
	FILE* file = fopen(fileName, "r");
	if (!file) {
		fileName[ierase] = '\0';
		return 0;
	}
	fclose(file);
	fileName[ierase] = '\0';
	return 1;
}

//створення нового файлу, згідно з першим завданням
void file_asterix(string fileName, string newFileName, string& row) {
	int lnum=0;
	ofstream newFile(newFileName + ".txt");
	ifstream oldFile(fileName + ".txt");
	while (getline(oldFile, row))
		if (++lnum % 2) {
			asterix_str(row); newFile << row << endl;
		}
	newFile.close();
	oldFile.close();
	return;
}
void file_asterix(char* fileName, char* newFileName, char* row) {
	int lnum = 0;
	int ierase1 = strlen(fileName);
	int ierase2 = strlen(newFileName);
	FILE *newFile, *oldFile;
	strcat(newFileName, ".txt");
	strcat(fileName, ".txt");
	newFile = fopen(newFileName, "w");
	oldFile = fopen(fileName, "r");
	while (fscanf(oldFile, "%[^\n]s", row)&&fgetc(oldFile)!=EOF)
		if (++lnum % 2) {
			asterix_str(row); 
			fprintf(newFile, "%s\n", row);
		}
	fclose(newFile);
	fclose(oldFile);
	fileName[ierase1] = '\0';
	newFileName[ierase2] = '\0';
	return;
}

//внесення змін у файл, згідно з другим завданням
void file_change(string fileName, string& row) {
	int lnum=1;
	ofstream newFile("temporary_file.tmp");
	ifstream curFile(fileName + ".txt");
	while (getline(curFile, row)) {
		if (++lnum % 2)
			remove_longest_word(row);
		newFile << row << endl;
	}
	newFile.close();
	curFile.close();
	remove(string(fileName+".txt").c_str());
	rename("temporary_file.tmp", string(fileName + ".txt").c_str());
	return;
}
void file_change(char* fileName, char* row) {
	int ierase = strlen(fileName);
	int lnum = 1;
	FILE* newFile, * curFile;
	newFile = fopen("temporary_file.tmp", "w");
	strcat(fileName, ".txt");
	curFile = fopen(fileName, "r");
	while (fscanf(curFile, "%[^\n]s", row) && fgetc(curFile) != EOF) {
		if (++lnum % 2)
			remove_longest_word(row);
		fprintf(newFile, "%s\n", row);
	}
	fclose(newFile);
	fclose(curFile);
	remove(fileName);
	rename("temporary_file.tmp", fileName);
	fileName[ierase] = '\0';
	return;
}