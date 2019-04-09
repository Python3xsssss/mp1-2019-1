#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <Windows.h>
using namespace std;


short int compareRusString(string str1, string str2)
{
	size_t minlen = (str1.length() < str2.length()) ? str1.length() : str2.length();

	short int res = 0;
	for (size_t i = 0; (res == 0) && (i < minlen); i++)
	{
		short int shift1 = 0, shift2 = 0;
		if ((str1[i] >= 'А') && (str1[i] <= 'Я'))
			shift1 = 32;
		if ((str2[i] >= 'А') && (str2[i] <= 'Я'))
			shift2 = 32;
		if ((int)(str1[i]) + shift1 < (int)(str2[i]) + shift2)
			res = -1;
		else if ((int)(str1[i]) + shift1 >(int)(str2[i]) + shift2)
			res = 1;
	}
	if (res == 0)
	{
		if (str1.length() < str2.length())
			res = -1;
		else if (str1.length() > str2.length())
			res = 1;
	}
	return res;
}


class ContactInfo
{
private:
	string surname, name, patronymic;
	string phone;
	string day, month, year;
	bool favourite;
public:
	ContactInfo()
	{
		favourite = false;
	}

	ContactInfo(string srnm, string nm, string ptrn, string ph, string dy, string mnth, string yr, bool fav)
	{
		surname = srnm;
		name = nm;
		patronymic = ptrn;
		phone = ph;
		day = dy;
		month = mnth;
		year = yr;
		favourite = fav;
	}

	ContactInfo(const ContactInfo& contact)
	{
		name = contact.name;
		surname = contact.surname;
		patronymic = contact.patronymic;
		phone = contact.phone;
		day = contact.day;
		month = contact.month;
		year = contact.year;
		favourite = contact.favourite;
	}

	~ContactInfo() {}

	ContactInfo& operator= (const ContactInfo& tmp)
	{
		surname = tmp.surname;
		name = tmp.name;
		patronymic = tmp.patronymic;
		phone = tmp.phone;
		day = tmp.day;
		month = tmp.month;
		year = tmp.year;
		favourite = tmp.favourite;
		return *this;
	}

	void Show()
	{
		cout << surname << " " << name << " " << patronymic << endl << phone << endl << day << " " << month << " " << year << endl;
		if (favourite)
			cout << "В избранном" << endl;
	}

	void SetSurname(string srnm)
	{
		surname = srnm;
	}

	void SetName(string nm)
	{
		name = nm;
	}

	void SetPatronymic(string ptrn)
	{
		patronymic = ptrn;
	}

	void SetPhone(string ph)
	{
		phone = ph;
	}

	void SetDay(string dy)
	{
		day = dy;
	}

	void SetMonth(string mnth)
	{
		month = mnth;
	}

	void SetYear(string yr)
	{
		year = yr;
	}

	void SetFavourite(bool fav)
	{
		favourite = fav;
	}

	string GetSurname()
	{
		return surname;
	}

	string GetName()
	{
		return name;
	}

	string GetPatronymic()
	{
		return patronymic;
	}

	string GetPhone()
	{
		return phone;
	}

	string GetDay()
	{
		return day;
	}

	string GetMonth()
	{
		return month;
	}

	string GetYear()
	{
		return year;
	}

	bool GetFavourite()
	{
		return favourite;
	}
};

class Contacts
{
private:
	vector <ContactInfo> list;
public:
	Contacts() {}

	Contacts(size_t size)
	{
		list.resize(size);
	}

	Contacts(vector <ContactInfo> tmp)
	{
		list = tmp;
	}

	Contacts(const Contacts& tmp)
	{
		list = tmp.list;
	}

	~Contacts() {}

	void Show()
	{
		for (size_t i = 0; i < list.size(); i++)
		{
			list[i].Show();
			cout << endl;
		}
	}

	void Show(size_t index)
	{
		list[index].Show();
		cout << endl;
	}

	void Show(size_t first, size_t last)
	{
		for (size_t i = first; i <= last; i++)
		{
			list[i].Show();
			cout << endl;
		}
	}

	void ShowFavourites()
	{
		cout << "Избранное:" << endl;
		for (size_t i = 0; i < list.size(); i++)
			if (list[i].GetFavourite())
			{
				list[i].Show();
				cout << endl;
			}
	}

	void AddContact(ContactInfo tmp)
	{
		string sur = tmp.GetSurname();
		string nam = tmp.GetName();
		string pat = tmp.GetPatronymic();

		bool flag = true;
		for (size_t i = 0; (flag) && (i < list.size()); i++)
		{
			short int res1 = compareRusString(sur, list[i].GetSurname());
			if (res1 == -1)
			{
				list.insert(list.begin() + i, tmp);
				flag = false;
			}
			else if (res1 == 0)
			{
				short int res2 = compareRusString(nam, list[i].GetName());
				if (res2 == -1)
				{
					list.insert(list.begin() + i, tmp);
					flag = false;
				}
				else if (res2 == 0)
				{
					short int res3 = compareRusString(pat, list[i].GetPatronymic());
					if (res3 == -1)
					{
						list.insert(list.begin() + i, tmp);
						flag = false;
					}
				}
			}
		}
		if (flag)
			list.push_back(tmp);
	}

	void AddChanges(size_t numMethod, int numContact, char *newStr)
	{
		void(ContactInfo::*method[7])(string str) = { &ContactInfo::SetSurname, &ContactInfo::SetName, &ContactInfo::SetPatronymic, &ContactInfo::SetPhone, &ContactInfo::SetDay, &ContactInfo::SetMonth, &ContactInfo::SetYear };

		(list[numContact].*method[numMethod])(newStr);
	}

	vector<int> Find(string surname, string name, string patronymic)
	{
		size_t i;
		vector <int> found;
		for (i = 0; i < list.size(); i++)
			if ((surname == list[i].GetSurname()) && (name == list[i].GetName()) && (patronymic == list[i].GetPatronymic()))
				found.push_back(i);
		return found;
	}

	vector<int> Find(string phone)
	{
		size_t i;
		vector <int> found;
		for (i = 0; i < list.size(); i++)
			if (phone == list[i].GetPhone())
				found.push_back(i);
		return found;
	}

	vector <int> Find(char firstletter)
	{
		char sizedLetter;
		if ((firstletter >= 'А') && (firstletter <= 'Я'))
			sizedLetter = (char)((int)(firstletter)+32);
		else
			sizedLetter = (char)((int)(firstletter)-32);

		size_t i = 0;
		while ((i < list.size()) && (list[i].GetSurname()[0] != firstletter) && (list[i].GetSurname()[0] != sizedLetter))
			i++;
		size_t first = i;

		while ((i < list.size()) && ((list[i].GetSurname()[0] == firstletter) || (list[i].GetSurname()[0] == sizedLetter)))
			i++;
		size_t last = i;

		vector <int> mas;
		if (last - first == 0)
			cout << "Ни одного контакта на букву '" << firstletter << "' не найдено" << endl;
		else
			for (i = first; i < last; i++)
			{
				mas.push_back(i);
			}
		return mas;
	}

	vector <int> FindFavourites()
	{
		vector <int> mas;
		for (size_t i = 0; i < list.size(); i++)
			if (list[i].GetFavourite())
				mas.push_back(i);
		return mas;
	}

	size_t GetAmount()
	{
		return list.size();
	}

	bool GetFavouriteStatus(size_t index)
	{
		return list[index].GetFavourite();
	}

	void SetFavouriteStatus(size_t index, bool status)
	{
		list[index].SetFavourite(status);
	}

	void DeleteContact(size_t index)
	{
		list.erase(list.begin() + index);
	}

	void SaveToFile(const char* filename)
	{
		ofstream fout;
		fout.open(filename);
		for (size_t i = 0; i < list.size(); i++)
		{
			fout << list[i].GetSurname() << endl << list[i].GetName() << endl << list[i].GetPatronymic() << endl << list[i].GetPhone() << endl;
			fout << list[i].GetDay() << endl << list[i].GetMonth() << endl << list[i].GetYear() << endl << list[i].GetFavourite() << endl << endl;
		}
		fout.close();
	}

	void LoadFromFile(const char* filename)
	{
		void(ContactInfo::*method[7])(string str) = { &ContactInfo::SetSurname, &ContactInfo::SetName, &ContactInfo::SetPatronymic, &ContactInfo::SetPhone, &ContactInfo::SetDay, &ContactInfo::SetMonth, &ContactInfo::SetYear };

		ifstream fin(filename);
		if (!fin.is_open())
		{
			char error[256];
			strcpy_s(error, filename);
			throw error;
		}
		int numMethod = 0;
		char buf[256];
		ContactInfo tmp;
		while (fin >> buf)
		{
			if (numMethod < 7)
			{
				(tmp.*method[numMethod])(buf);
				numMethod++;
			}
			else
			{
				int fav, container = 0;
				fav = _strtoi64(buf, NULL, container);
				tmp.SetFavourite(fav);
				AddContact(tmp);
				numMethod = 0;
			}
		}
	}
};


int options()
{
	cout << "Опции:" << endl;
	cout << "1 - Создать новый контакт" << endl;
	cout << "2 - Изменить контакт" << endl;
	cout << "3 - Удалить контакт" << endl;
	cout << "4 - Найти контакт" << endl;
	cout << "5 - Показать избранное" << endl;
	cout << "6 - Сохранить контакты в текстовый файл" << endl;
	cout << "7 - Загрузить контакты из текстового файла" << endl;
	cout << "0 - Выйти" << endl;
	cout << endl << "Выберите, что хотите сделать, из списка выше: ";
	int action;
	cin >> action;
	cout << endl;
	return action;
}


void backToMenu()
{
	cout << endl << "Нажмите любую клавишу, чтобы вернуться к списку контактов" << endl << endl;
	_getch();
}

void createNewContact(Contacts& listing)
{
	string buf;
	int fav;
	ContactInfo tmp;

	cout << "Создание нового контакта:" << endl;

	cout << "Фамилия: " << endl;
	cin >> buf;
	tmp.SetSurname(buf);

	cout << "Имя: " << endl;
	cin >> buf;
	tmp.SetName(buf);

	cout << "Отчество: " << endl;
	cin >> buf;
	tmp.SetPatronymic(buf);

	cout << "Номер телефона: " << endl;
	cin >> buf;
	tmp.SetPhone(buf);

	cout << "Дата рождения:" << endl;

	cout << "День: " << endl;
	cin >> buf;
	tmp.SetDay(buf);

	cout << "Месяц: " << endl;
	cin >> buf;
	tmp.SetMonth(buf);

	cout << "Год: " << endl;
	cin >> buf;
	tmp.SetYear(buf);

	cout << "Добавить этот контакт в избранное? (1 - Да; 0 - Нет): ";
	cin >> fav;
	tmp.SetFavourite(fav);

	listing.AddContact(tmp);
	cout << "Контакт успешно создан!" << endl;
	backToMenu();
}

vector <int> searchByName(Contacts& listing)
{
	string tmpSurname, tmpName, tmpPatr;
	int again;
	vector <int> indexes;
	do
	{
		cout << "Введите фамилию: " << endl;
		cin >> tmpSurname;
		cout << "Введите имя: " << endl;
		cin >> tmpName;
		cout << "Введите отчество: " << endl;
		cin >> tmpPatr;
		indexes = listing.Find(tmpSurname, tmpName, tmpPatr);
		if (indexes.size() == 0)
		{
			cout << "Контактов с таким ФИО не найдено!" << endl;
			cout << "Попробовать снова? (1 - Да; 0 - Вернуться к списку контактов): ";
			cin >> again;
		}
		else
			again = 0;
	} while ((indexes.size() == 0) && (again == 1));
	if (indexes.size() > 0)
	{
		cout << endl << "Найденные контакты:" << endl << endl;
		for (size_t i = 0; i < indexes.size(); i++)
		{
			cout << i + 1 << "." << endl;
			listing.Show(indexes[i]);
		}
	}
	return indexes;
}


vector<int> searchByPhone(Contacts& listing)
{
	string tmpPhone;
	int again;
	vector <int> indexes;
	do
	{
		cout << "Введите номер телефона: " << endl;
		cin >> tmpPhone;

		indexes = listing.Find(tmpPhone);
		if (indexes.size() == 0)
		{
			cout << "Контактов с таким ФИО не найдено!" << endl;
			cout << "Попробовать снова? (1 - Да; 0 - Вернуться к списку контактов): ";
			cin >> again;
		}
		else
			again = 0;
	} while ((indexes.size() == 0) && (again == 1));
	if (indexes.size() > 0)
	{
		cout << endl << "Найденные контакты:" << endl << endl;
		for (size_t i = 0; i < indexes.size(); i++)
		{
			cout << i + 1 << "." << endl;
			listing.Show(indexes[i]);
		}
	}
	return indexes;
}

vector <int> searchByLetter(Contacts& listing)
{
	int again;
	char letter;
	vector <int> indexes;
	do
	{
		cout << "Введите букву: ";
		cin >> letter;
		indexes = listing.Find(letter);
		if (indexes.size() == 0)
		{
			cout << "Контактов с таким ФИО не найдено!" << endl;
			cout << "Попробовать снова? (1 - Да; 0 - Вернуться к списку контактов): ";
			cin >> again;
		}
		else
			again = 0;
	} while ((indexes.size() == 0) && (again == 1));
	if (indexes.size() > 0)
	{
		cout << endl << "Найденные контакты:" << endl << endl;
		for (size_t i = 0; i < indexes.size(); i++)
		{
			cout << i + 1 << "." << endl;
			listing.Show(indexes[i]);
		}
	}
	return indexes;

}


vector <int> search(Contacts& listing)
{
	int tmp;
	cout << "1 - Искать по ФИО" << endl;
	cout << "2 - Искать по номеру телефона" << endl;
	cout << "3 - Выдать все контакты на определенную букву" << endl;
	cout << "Выберите из списка выше, как искать: ";
	cin >> tmp;

	vector <int> indexes;
	switch (tmp)
	{
	case 1:
		indexes = searchByName(listing);
		break;
	case 2:
		indexes = searchByPhone(listing);
		break;
	case 3:
		indexes = searchByLetter(listing);
		break;
	default:
		break;
	}
	return indexes;
}

int chooseTheContact(vector <int> indexes)
{
	int index, tmpindex;
	if (indexes.size() == 0)
		index = -1;
	else if (indexes.size() == 1)
		index = indexes[0];
	else
	{
		cout << "Введите порядковый номер нужного контакта из списка выше: ";
		cin >> tmpindex;
		tmpindex -= 1;
		index = indexes[tmpindex];
	}
	return index;
}


void changeFavourite(Contacts& listing, size_t index)
{
	if (listing.GetFavouriteStatus(index))
	{
		cout << "Этот контакт находится в избранном. Удалить контакт из избранного? (1 - Да; 0 - Нет): ";
		int sure;
		cin >> sure;
		if (sure == 1)
		{
			listing.SetFavouriteStatus(index, false);
			cout << "Контакт удален из избранного!" << endl;
		}
	}
	else
	{
		cout << "Этого контакта нет в избранном. Добавить контакт в избранное? (1 - Да; 0 - Нет): ";
		int sure;
		cin >> sure;
		if (sure == 1)
		{
			listing.SetFavouriteStatus(index, true);
			cout << "Контакт добавлен в избранное!" << endl;
		}
	}
}


void change(Contacts& listing)
{
	char buf[256];
	cout << "Необходимо найти контакт, который вы хотите изменить." << endl;
	vector <int> indexes = search(listing);
	int index = chooseTheContact(indexes);
	if (index == -1)
		return;
	cout << endl << "Вы собираетесь изменить следующий контакт:" << endl;
	int method;
	do
	{
		listing.Show(index);
		cout << "1 - Изменить фамилию" << endl;
		cout << "2 - Изменить имя" << endl;
		cout << "3 - Изменить отчество" << endl;
		cout << "4 - Изменить номер телефона" << endl;
		cout << "5 - Изменить дату рождения" << endl;
		cout << "6 - Добавить контакт в избранное/удалить контакт из избранного" << endl;
		cout << "0 - Вернуться к списку контактов" << endl;
		cout << endl << "Выберите, что хотите сделать из списка выше: ";
		cin >> method;
		switch (method)
		{
		case 1:
			cout << "Введите новую фамилию: " << endl;
			cin >> buf;
			listing.AddChanges(0, index, buf);
			break;
		case 2:
			cout << "Введите новое имя: " << endl;
			cin >> buf;
			listing.AddChanges(1, index, buf);
			break;
		case 3:
			cout << "Введите новое отчество: " << endl;
			cin >> buf;
			listing.AddChanges(2, index, buf);
			break;
		case 4:
			cout << "Введите новый номер телефона: " << endl;
			cin >> buf;
			listing.AddChanges(3, index, buf);
			break;
		case 5:
			cout << "Введите новую дату рождения: " << endl;
			cout << "День:" << endl;
			cin >> buf;
			listing.AddChanges(4, index, buf);

			cout << "Месяц: " << endl;
			cin >> buf;
			listing.AddChanges(5, index, buf);

			cout << "Год: " << endl;
			cin >> buf;
			listing.AddChanges(6, index, buf);
			break;
		case 6:
			changeFavourite(listing, index);
			break;
		default:
			break;
		}
		if (method != 0)
			cout << endl << "Изменения успешно сохранены!" << endl << endl;
	} while (method != 0);
	backToMenu();
}

void deleteContact(Contacts& listing)
{
	cout << "Необходимо найти контакт, который вы хотите удалить." << endl;
	vector <int> indexes = search(listing);
	int index = chooseTheContact(indexes);
	if (index == -1)
		return;
	cout << endl << "Вы собираетесь удалить следующий контакт:" << endl;
	listing.Show(index);
	cout << "Вы уверены, что хотите удалить этот контакт?(1 - Да; 0 - Нет): ";
	int sure;
	cin >> sure;
	if (sure == 1)
	{
		listing.DeleteContact(index);
		cout << "Контакт успешно удален!" << endl;
	}
	backToMenu();
}

void saveContact(Contacts& listing)
{
	char buf[256];
	cout << "Введите путь к файлу" << endl;
	cin >> buf;
	listing.SaveToFile(buf);
}

void loadContact(Contacts& listing)
{
	char buf[256];
	cout << "Введите путь к файлу" << endl;
	cin >> buf;
	try
	{
		listing.LoadFromFile(buf);
	}
	catch (char* error)
	{
		cout << "Ошибка - файл " << error << " не может быть открыт!" << endl;
	}
}

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Contacts mine;
	try
	{
		mine.LoadFromFile("contacts.txt");
	}
	catch (char* error)
	{
		cout << "Ошибка - файл " << error << " не может быть открыт!" << endl;
	}
	bool go = true;
	do
	{
		cout << "Мои контакты:" << endl;
		mine.Show();
		cout << "Количество: " << mine.GetAmount() << endl << endl;
		int action = options();
		switch (action)
		{
		case 1:
			createNewContact(mine);
			break;
		case 2:
			change(mine);
			break;
		case 3:
			deleteContact(mine);
			break;
		case 4:
			search(mine);
			backToMenu();
			break;
		case 5:
			mine.ShowFavourites();
			backToMenu();
			break;
		case 6:
			saveContact(mine);
			break;
		case 7:
			loadContact(mine);
			break;
		case 0:
			go = false;
			break;
		default:
			break;
		}
	} while (go);
}