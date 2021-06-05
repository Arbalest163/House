#include <iostream>
#include<time.h>

class Man {
	char* fio;
public:
	Man() :Man("Default") {}
	explicit Man(const char* _fio);
	explicit Man(Man& man);
	~Man();
	char* getFIO() const;
	Man& setFIO(const char* _fio);
	friend std::ostream& operator<< (std::ostream& out, const Man& man);
	Man& operator=(Man& man);
};
Man::Man(const char* _fio) {
	if (_fio!=nullptr) {
		int size = strlen(_fio);
		fio = nullptr;
		fio = new char[size + 1];
		strcpy_s(fio, size + 1, _fio);
	}
	else { 
		fio = new char[8];
		strcpy_s(fio, 8, "Default");
	}
}
Man::Man(Man& man) {
	if (man.fio != nullptr) {
		int size = strlen(man.fio);
		fio = nullptr;
		fio = new char[size + 1];
		strcpy_s(fio, size + 1, man.fio);
	}
	else {
		fio = new char[8];
		strcpy_s(fio, 8, "Default");
	}
}
Man& Man::operator=(Man& man) {
	if (&man == this) return *this;
	int size = strlen(man.fio);
	delete[]fio;
	fio = nullptr;
	fio = new char[size + 1];
	strcpy_s(fio, size + 1, man.fio);
	return *this;
}
Man::~Man() { delete[] fio; }
char* Man::getFIO() const { return fio; }
Man& Man::setFIO(const char* _fio) {
	if (_fio != nullptr) {
		int size = strlen(_fio);
		fio = nullptr;
		fio = new char[size + 1];
		strcpy_s(fio, size + 1, _fio);
	}
	else {
		fio = new char[8];
		strcpy_s(fio, 8, "Default");
	}
	return *this;
}
std::ostream& operator<< (std::ostream& out, const Man& man) {
	out << "FIO: " << man.fio << std::endl;
	return out;
}
//=========================================================================

class Flat {
	int numberFlat;
	int countMan;
	Man* mans;
public:
	Flat();
	Flat(Flat& flat);
	~Flat();
	Flat& setNumberFlat(int num);
	int getNumberFlat() const { return numberFlat; }
	friend std::ostream& operator<<(std::ostream& out, Flat& flat);
	Man& getMan(int index);
	Flat& operator=(Flat& flat);
};
Flat::Flat()
:numberFlat{ 0 } 
{
	countMan = 2 + rand() % 4;
	mans = new Man[countMan];
}
Flat::Flat(Flat& flat)
	:numberFlat(flat.numberFlat), countMan(flat.countMan)
{
	mans = new Man[countMan];
	for (int i{ 0 }; i < countMan; i++)
		mans[i] = flat.mans[i];
}
Flat::~Flat() { delete[]mans; }

Flat& Flat::setNumberFlat(int num) {
	numberFlat = num;
	return* this;
}
std::ostream& operator<<(std::ostream& out, Flat& flat) {
	for (int i{ 0 }; i < flat.countMan; i++) {
		out << flat.mans[i];
	}
	return out;
}
Man& Flat::getMan(int index) {
	try {
		if (index <= 0 || index > countMan)
			throw "Index <= 0 or index > count mans Flat";
		else
			return mans[index - 1];
	}
	catch (const char* str) {
		std::cout << str;
	}
}
Flat& Flat::operator=(Flat& flat) {
	numberFlat = flat.numberFlat;
	countMan = flat.countMan;
	delete[]mans;
	mans = new Man[countMan];
	for (int i{ 0 }; i < countMan; i++)
		mans[i] = flat.mans[i];
	return *this;
}

//==================================================================

template<int size>
class House {
	int countFlat;
	Flat flats[size];
public:
	House()
		:countFlat(size)
	{
		for (int i{ 0 }; i < size; i++)
			flats[i].setNumberFlat(i + 1);
	}
	~House(){}
	Flat& operator[](int index) { 
		try {
			if (index <=0 || index > size)
				throw "Index <= 0 or index > size House";
			else
				return flats[index - 1];
		}
		catch (const char* str) { std::cout << str;
		}
	}
	int getCountFlat() { return countFlat; }
};
//=================================================================

int main()
{
	setlocale(0, "");
	srand(static_cast<unsigned int>(time(0)));
	Man graf("Drakula Vladislav");
	Man graf2{ graf };
	std::cout << "Конструктор копирования людей: \n";
	std::cout << "graf " << graf << "\n";
	std::cout << "graf2 " << graf2 << "\n";
	std::cout << "Изменение фио первого человека и заселеине в квартиру двух человек. \n";
	graf.setFIO("Kim Chin");
	Flat oneflat;
	oneflat.getMan(1) = graf2;
	oneflat.getMan(2) = graf;
	oneflat.setNumberFlat(1);
	House<5> house;
	std::cout << "Помещение квартиры в дом и вывод всех жильцов дома: \n";
	house[1] = oneflat;
	house[2].getMan(1).setFIO("Bulkin Oleg");
	house[3].getMan(2).setFIO("Minin Vladilen");
	house[5].getMan(2).setFIO("Orlov Dmitriy");
	
	for (int i{ 1 }; i <= house.getCountFlat(); i++)
		std::cout << "Квартира № " << house[i].getNumberFlat() << ":\n" << house[i];
	
}
