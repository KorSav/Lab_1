#pragma warning(disable : 4996)
#include "funcs.h"

//обробка слів у рядку, згідно з першим завданням
void asterix_str(string& str) {
	char c = tolower(str[0]);
	for (int i = 1; str[i]; i++) {
		if (str[i] != '.' && str[i] != ' ') {
			if (c == '.' || c == ' ') c = tolower(str[i]);
			else if ((signed char)tolower(str[i]) == (signed char)c) str[i] = '*';
		}
		else c = str[i];
	}
	return;
}
void asterix_str(char* str) {
	char c = tolower(str[0]);
	for (int i = 1; str[i]; i++) {
		if (str[i] != '.' && str[i] != ' ') {
			if (c == '.' || c == ' ') c = tolower(str[i]);
			else if ((signed char)tolower(str[i]) == (signed char)c) str[i] = '*';
		}
		else c = str[i];
	}
	return;
}

//видалення найдовшого слова у рядку
void remove_longest_word(string& str) {
	int lmax = 0, //довжина найдовшого слова
	    lcur = 0, //довжина поточного слова
	    imax = 0, //індекс початку найдовшого слова
	    icur = 0; //індекс початку поточного слова
	for (int i = 0; str[i]; i++) {
		if (str[i] != '.' && str[i] != ' ')
			if (lcur++ == 0) icur = i;
		else {
			if (lcur > lmax) {
				lmax = lcur; imax = icur;
			}
			lcur = 0;
		}
	}
	if (lcur > lmax) {//якщо рядок не закінчується на крапку чи пробіл
		lmax = lcur; imax = icur;
	}
	str.erase(imax, lmax);
	return;
}
void remove_longest_word(char* str) {
	int lmax = 0, //довжина найдовшого слова
	    lcur = 0, //довжина поточного слова
	    imax = 0, //індекс початку найдовшого слова
	    icur = 0; //індекс початку поточного слова
	for (int i = 0; str[i]; i++) {
		if (str[i] != '.' && str[i] != ' ')
			if (lcur++ == 0) icur = i;
		else {
			if (lcur > lmax) {
				lmax = lcur; imax = icur;
			}
			lcur = 0;
		}
	}
	if (lcur > lmax) {//якщо рядок не закінчується на крапку чи пробіл
		lmax = lcur; imax = icur;
	}
	str[imax] = '\0';
	strcat(str, str + imax + lmax);
	return;
}

//генерація випадкового слова
void random_word(string& s, bool startsWithBig) {
	char c;
	int len = rand() % (WMAX - WMIN + 1) + WMIN;
	s.clear();
	s += (rand() % 26 + 'a');
	for (int i = 1; i < len; i++) {
		c = rand() % 26 + 'a';
		s += (c < ('z' - 'a') / 3 + 'a') ? s[0] : c;//підвищення шансу на повтор символу
	}
	if (startsWithBig) s[0] = toupper(s[0]);
	return;
}
void random_word(char* s, char startsWithBig) {
	char c;
	int len = rand() % (WMAX - WMIN + 1) + WMIN;
	s[0] = (rand() % 26 + 'a');
	for (int i = 1; i < len; i++) {
		c = rand() % 26 + 'a';
		s[i] = (c < ('z' - 'a') / 3 + 'a') ? s[0] : c;//підвищення шансу на повтор символу
	}
	if (startsWithBig) s[0] = toupper(s[0]);
	return;
}