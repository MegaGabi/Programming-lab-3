#include <iostream>
#include <ctime>
#include <conio.h>
#include <ctype.h>
#include <fstream>

using namespace std;

const int max_chars_in_names = 12; //кол-во символов в имени, или отчестве, или фамилии 
const int student_description_size = 6; //кол-во свойств описывающих студента
int m_fn_size, f_fn_size, mn_size, ln_size; //кол-во строк в массивах с ФИО

enum gender {male, female};
enum array_names {Last_name, First_name, Mid_name, Year, Course, Gender};
//<прізвище> - 0, <ім’я> - 1, <по-батькові> - 2, <рік народження> - 3, <курс> - 4, <стать> - 5
//<массивы имен>

 char m_fnames[][max_chars_in_names] //имена(мужские)
	=	
		{ 
			{ "Дима" },
			{ "Вася" },
			{ "Артем" },
			{ "Коля" },
			{ "Влад" },
			{ "Илья" },
			{ "Олег" },
			{ "Руслан" },
			{ "Петя" }
		};

 char f_fnames[][max_chars_in_names] //имена(женские)
=
{
	{ "Настя" },
	{ "Даша" },
	{ "Таня" },
	{ "Оля" },
	{ "Саша" },
	{ "Вера" },
	{ "Катя" },
	{ "Наташа" },
	{ "Женя" }
};


 char mnames[][max_chars_in_names] //отчества(общее)
	=
		{
			{ "Дмитриев" },
			{ "Васильев" },
			{ "Артемов" },
			{ "Николаев" },
			{ "Ильи" },
			{ "Олегов" },
			{ "Русланов" },
			{ "Петров" }
		};

 char lnames[][max_chars_in_names] //фамилии(общее)
	=
		{
			{ "Петров" },
			{ "Левочкин" },
			{ "Грицай" },
			{ "Логвинов" },
			{ "Майтамал" },
			{ "Газанфаров" },
			{ "Солоха" },
			{ "Малышев" }
		};

//</массивы имен>

//<генерация имен>//

char* getMiddleName(char name[], int end, gender g)
{
	char *newName = new char[max_chars_in_names];
	strcpy_s(newName, max_chars_in_names, name);

	char *MEnd = (g == male ? "ич" : "на");//в зависимости от пола выбрать окончание отчества

	for (int i = end, IEnd = 0; i < max_chars_in_names - 1; i++)
	{
		if (IEnd == 2)//если кончилось окончание отчества закрыть текущий эл-т нультерминатором и закончить выполнение цикла
		{
			newName[i] = '\0';
			break;
		}

		if (name[i] == '\0')//если кончились значения во входном массиве, то начать заполнять окончанием отчества
		{
			newName[i] = MEnd[IEnd];
			IEnd++;
		}
	}
	newName[max_chars_in_names - 1] = '\0';//в любом случае закрыть массив символов нуль терминатора

	return newName;
}

char* getFemaleLastName(char name[], int end)
{
	char *newName = new char[max_chars_in_names];
	strcpy_s(newName, max_chars_in_names, name);

	const int size_vowels = 14;
	char vowels[size_vowels] = { "ауоыиэяюёеьъй" };
	end--;
	//проверяем является ли последний символ запрещенным
	bool isVowel = false;
	for (int v = 0; v < size_vowels - 1; v++)
	{
		if (vowels[v] == name[end])
		{
			isVowel = true;
			break;
		}
	}

	if (!isVowel && (end < max_chars_in_names - 2))
	{
		newName[end + 1] = 'a';
		newName[end + 2] = '\0';
	}
	
	return newName;
}

char** generateRandomFullName(gender g)
{
	char **FullName = new char*[3];
	for (int i = 0; i < 3; i++)
	{
		FullName[i] = new char[max_chars_in_names];
	}

	int li = rand() % (ln_size),	//индекс случайной фамилии
		mi = rand() % (mn_size);	//индекс случайного отчества

	if (g == male)
	{
		int fi = rand() % (m_fn_size);  //индекс случайного имени(тут т.к. у мальчиков и девочек разные массивы имен)

		strcpy_s(FullName[0], max_chars_in_names,  lnames[li]);
		strcpy_s(FullName[1], max_chars_in_names, m_fnames[fi]);
	}
	else
	{
		int fi = rand() % (f_fn_size);  //индекс случайного имени(тут т.к. у мальчиков и девочек разные массивы имен)

		strcpy_s(FullName[0], max_chars_in_names, getFemaleLastName(lnames[li], strlen(lnames[li])));
		strcpy_s(FullName[1], max_chars_in_names, f_fnames[fi]);
	}

	strcpy_s(FullName[2], max_chars_in_names, getMiddleName(mnames[mi], strlen(mnames[mi]), g));//getMiddleName - автоматически возвращает отчество по переданному полу

	return FullName;
}

//<\генерация имен>//

int CountOfDigits(int num)
{
	int count = 0;
	for (int i = 0; ; i++)
	{
		if (abs(num) < pow(10, i))
		{
			count = i;
			break;
		}
	}

	if (num < 0)
		count++;
	return count;
}

int getRandomNumberWithin(int f, int l)
{
	return f + rand() % (l - f + 1);
}

int GetCurYear()
{
	const time_t *curTime = new time_t(time(NULL));
	tm *tmData = new tm;
	localtime_s(tmData, curTime);

	return tmData->tm_year + 1900;
}

bool CheckIfCharArrayIsBigger(char* fname, char* lname) //если fname больше то вернет true
{
	int fsize = strlen(fname), lsize = strlen(lname);
	
	if (fsize >= 1 && lsize >= 1)
	{
		if (fname[0] > lname[0])
		{
			return true;
		}
		else if (fname[0] == lname[0])
		{
			return CheckIfCharArrayIsBigger(fname + 1, lname + 1);
		}
		else return false;
	}

	return false;
}

void WriteStudentToFile(ofstream &fout)
{
	gender g = gender(rand() % 2);

	int year = GetCurYear();

	char **FIO = generateRandomFullName(g);

	char* born = new char[5];
	_itoa_s(getRandomNumberWithin(1900, year), born, 5,  10);

	char* course = new char[2];
	_itoa_s(getRandomNumberWithin(1, 5), course, 2, 10);

	fout.write(FIO[0], strlen(FIO[0]));
	fout.write("|", 1);
	fout.write(FIO[1], strlen(FIO[1]));
	fout.write("|", 1);
	fout.write(FIO[2], strlen(FIO[2]));
	fout.write("|", 1);

	fout.write(born, 4);
	fout.write("|", 1);

	fout.write(course, 1);
	fout.write("|", 1);

	fout.write(g==male?"М":"Ж", 1);

	fout.write(";", 1);
	fout.write("\n", 1);
}

char** ReadStudentFromFile(ifstream &fin)
{
	char *String = new char[255];
	char **StudentInfo = new char*[student_description_size];
	for (int i = 0; i < student_description_size; i++)
	{
		StudentInfo[i] = new char[max_chars_in_names];
	}

	fin.getline(String, 255, ';');

	for (int i = 0, j = 0, s = 0; i < strlen(String) + 1; i++, s++)//strlen(String) + 1 записать нуль терминатор в последний эллемент
	{
		if (String[i] == '|')
		{
			StudentInfo[j][s] = '\0';
			s = -1;
			j++;
		}
		else if (String[i] == '\n')
		{
			s--;//пропустить символ в строке и начать запись в массив со следующего
		}
		else
		{
			StudentInfo[j][s] = String[i];
		}
	}

	return StudentInfo;
}

void CommonAge(ifstream &fin, int &index_common_age, int &common_age_count)
{
	const int ages_size = GetCurYear() - 1900;
	int* ages = new int[ages_size] {0};
	common_age_count = INT_MIN; index_common_age = 0;

	while (!fin.eof())
	{
		char** Info = ReadStudentFromFile(fin);

		if (fin.eof()) break;

		ages[atoi(Info[Year]) - 1900]++;
	}

	for (int i = 0; i < ages_size; i++)
	{
		if (common_age_count < ages[i])
		{
			common_age_count = ages[i];
			index_common_age = i;
		}
	}

	index_common_age += 1900;
}

void SwitchStudents(char ***&StudentsToShow, int indexA, int indexB)
{
	for (int i = 0; i < student_description_size; i++)
	{
		char *buf = new char[max_chars_in_names];
		strcpy_s(buf, max_chars_in_names, StudentsToShow[indexB][i]);
		strcpy_s(StudentsToShow[indexB][i], max_chars_in_names, StudentsToShow[indexA][i]);
		strcpy_s(StudentsToShow[indexA][i], max_chars_in_names, buf);
	}
}

void SortStudentsByAlphabet(char ***&StudentsToShow, int common_age_count)
{
	for (int i = 0; i < common_age_count; i++)
	{
		int smallest_name = i;
		for (int j = i + 1; j < common_age_count; j++)
		{
			if (!CheckIfCharArrayIsBigger(StudentsToShow[j][Last_name], StudentsToShow[smallest_name][Last_name]))
			{
				smallest_name = j;
			}
		}

		SwitchStudents(StudentsToShow, smallest_name, i);
	}
}

void StudentsFormatedOutput(ostream &out, char ***StudentsToShow, int count_to_show, int year)
{
	int buf_size = CountOfDigits(year) + 1;
	char *buf = new char[buf_size];
	_itoa_s(year, buf, buf_size, 10);

	out.write("Студенты которые родились в ", strlen("Студенты которые родились в ")); 
	out.write(buf, strlen(buf));
	out.write(" г. находятся в большинстве\n", strlen(" г. находятся в большинстве\n"));
	for (int i = 0; i < count_to_show; i++)
	{
		out.write(StudentsToShow[i][Last_name], strlen(StudentsToShow[i][Last_name]));
		out.write(" ", 1);
		out.write(StudentsToShow[i][First_name], 1);
		out.write(".", 1);
		out.write(StudentsToShow[i][Mid_name], 1);
		out.write(".\n", 2);
	}
}

char*** GetStudentsByYear(ifstream &fin, int common_age, int common_age_count)
{
	char ***StudentsToShow = new char**[common_age_count];
	for (int i = 0; i < common_age_count; i++)
	{
		StudentsToShow[i] = new char*[student_description_size];
		for (int j = 0; j < student_description_size; j++)
		{
			StudentsToShow[i][j] = new char[max_chars_in_names];
		}
	}

	int curStudent = 0;
	while (!fin.eof())
	{
		char** Info = ReadStudentFromFile(fin);

		if (fin.eof()) break;

		if (atoi(Info[Year]) == common_age)
		{
			for (int i = 0; i < student_description_size; i++)
			{
				strcpy_s(StudentsToShow[curStudent][i], max_chars_in_names, Info[i]);
			}
			curStudent++;
		}
	}

	SortStudentsByAlphabet(StudentsToShow, common_age_count);

	return StudentsToShow;
}

void main()
{
	m_fn_size = sizeof(m_fnames) / sizeof(m_fnames[0]);
	f_fn_size = sizeof(f_fnames) / sizeof(f_fnames[0]);
	mn_size = sizeof(mnames) / sizeof(mnames[0]);
	ln_size = sizeof(lnames) / sizeof(lnames[0]);

	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	ofstream fout("input.txt", ios::trunc | ios::out);

	for (int i = 0; i < 1000; i++)
	{
		WriteStudentToFile(fout);
	}

	fout.close();

	ifstream fin("input.txt", ios::in);
	fout.open("output.txt", ios::out);

	int common_age, common_age_count;

	CommonAge(fin, common_age, common_age_count);
	fin.clear();
	fin.seekg(0, ios::beg);

	char*** StudentsToShow = GetStudentsByYear(fin, common_age, common_age_count);
	StudentsFormatedOutput(cout, StudentsToShow, common_age_count, common_age);
	StudentsFormatedOutput(fout, StudentsToShow, common_age_count, common_age);

	fout.close();

	_getch();
}