#pragma once
#include <string>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <random>
#include <time.h>
#include <cstdio>

//параметри генерації 
#define RNUM 6  //кількість рядків
#define WNUM 5  //кількість слів в рядку
#define WMAX 10	//максимальна довжина слова
#define WMIN 3	//мінімальна довжина слова

//параметри при роботі з масивом символів
#define FNAME_SIZE 100 //розмір буферу для назви файлу
#define BUFER_SIZE 200 //розмір буферу для обробки рядків згідно з завданням

using namespace std;
//функції для роботи з файлами
void file_create(string);
void file_create(char*);

void file_fill(string, string);
void file_fill(char* , char* );

void file_append(string);
void file_append(char*);

void file_print(string);
void file_print(char*);

bool file_exists(string);
char file_exists(char*);

void file_asterix(string, string, string&);
void file_asterix(char*, char*, char*);

void file_change(string, string&);
void file_change(char*, char*);

//функції для обробки рядків
void random_word(string&, bool);
void random_word(char*  , char);

void asterix_str(string&);
void asterix_str(char*);

void remove_longest_word(string&);
void remove_longest_word(char*);