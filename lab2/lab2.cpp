#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <iomanip>

using namespace std;
// стек
struct Flight {
    string reis;
    string date;
    Flight* next = nullptr; 
};

// односвязный список
struct Pass {
    string FIO;
    Flight* flight = nullptr; 
    int vesh;
    double weight;
    Pass* next = nullptr;
};
//добавление в стек
void pushFlight(Pass* passenger, const string& reis, const string& date) {
    Flight* newFlight = new Flight;
    newFlight->reis = reis;
    newFlight->date = date;
    newFlight->next = passenger->flight;
    passenger->flight = newFlight;
}

void popFlight(Pass* passenger) {
    if (passenger->flight == nullptr) return;
    Flight* temp = passenger->flight;
    passenger->flight = passenger->flight->next;
    delete temp;
}
//проверка фио
bool prov(const string& fio)
{
    if (fio.empty() || fio.length() > 35 || fio.find_first_not_of(" \t") == std::string::npos) return false;
    for (char uc : fio) {
        unsigned char c = static_cast<unsigned char>(uc);
        bool ras = (c >= 192 && c <= 255) || c == 168 || c == 184
            || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == ' ' || c == '-');
        if (!ras) return false;
    }
    return true;

}
// проверка рейса
bool prov_flight(const string& reis)
{
    if (reis.empty() || reis.length() > 10 || reis.find_first_not_of(" \t") == std::string::npos) return false;
    for (char c : reis) {
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))) return false;
    }
    return true;
}
//проверка даты
bool prov_date(const string& date)
{
    if (date.length() != 10 || date[2] != '.' || date[5] != '.') return false;

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (date[i] < '0' || date[i] > '9') return false;
    }
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if (year < 2026 || year > 2100) return false;

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
    if (month == 2 && day > 29) return false;

    return true;
}
//добавление в массив + проверка корректности данных
void addPass(Pass*& head)
{
    Pass passag;
    char choice;
    int mass_mer;
    do {
        Pass* passag = new Pass;
        while (true) {
            cout << "Введите ФИО:";
            getline(cin, passag->FIO);
            if (prov(passag->FIO)) break;
            cout << "Некорректные данные ФИО! Повторите ввод." << endl;
        }
        string reis, date;
        while (true) {
            cout << "Введите номер рейса:";
            getline(cin, reis;
            if (prov_flight(reis)) break;
            cout << "Некорректный номер рейса! Повторите ввод." << endl;
        }
        while (true) {
            cout << "Введите дату вылета в формате(ДД.ММ.ГГГГ):";
            getline(cin, date);
            if (prov_date(date)) break;
            cout << "Некорректная дата! Повторите ввод." << endl;
        }

        while (true) {
            cout << "Введите количество вещей:";
            string str;
            getline(cin, str);
            bool fl = !str.empty();
            for (char c : str) {
                if (c < '0' || c > '9') {
                    fl = false;
                    break;
                }
            }
            if (fl) {
                passag->vesh = stoi(str);
                if (passag->vesh >= 0 && passag->vesh <= 10) {
                    break;
                }
            }
            cout << "Недопустимое количество вещей! Введите число от 0 до 10." << endl;
        }

        if (passag->vesh != 0) {
            while (true) {
                cout << "Укажите в чем измеряется масса ващих вещей [1] - фунт;[2] - кг:";
                string str;
                getline(cin, str);

                bool fl = !str.empty();
                for (char c : str) {
                    if (c < '0' || c > '9') {
                        fl = false;
                        break;
                    }
                }
                if (fl) {
                    mass_mer = stoi(str);
                    if (mass_mer == 1 || mass_mer == 2) {
                        break;
                    }
                }
                cout << "Некорректный выбор! Введите 1 или 2." << endl;
            }

            while (true) {
                cout << "Введите общую массу вещей: ";
                string str;
                getline(cin, str);
                bool fl = !str.empty();
                int dot_count = 0; // Счетчик точек,чтобы не было больше 1

                for (char c : str) {
                    if (c == '.') {
                        dot_count++;
                    }
                    else if (c < '0' || c > '9') {
                        fl = false;//чтобы не было пробелов, табуляций, букв
                        break;
                    }
                }
                if (dot_count > 1) fl = false;
                if (fl) {
                    passag->weight = stod(str);
                    if (passag->weight >= 0.0 && passag->weight <= 220.46 && mass_mer == 1) {
                        break;
                    }
                    else if (passag->weight >= 0.0 && passag->weight <= 100) break;
                }
                cout << "Некорректный вес! Повторите ввод." << endl;
            }

            if (mass_mer == 1)
            {
                passag->weight = passag->weight * 0.453592;
            }
        }
        else passag->weight = 0;

        passag->next = head;
        head = passag;
        
        cout << "Данные пассажира успешно добавлены в массив!" << endl;
        cout << "Хотите добавить еще одного пассажира? (y/n):";
        cin >> choice;
        cin.ignore(10000, '\n');

    } while (choice == 'y' || choice == 'Y' || choice == 'н' || choice == 'Н');
}
//пузырек для ФИО
void Sort_FIO(Pass* head)
{
    if (head == nullptr || head->next == nullptr) {
        cout << "Список пуст или содержит один элемент, сортировать нечего." << endl;
        return;
    }

    bool swapp;
    do {
        swapp = false;
        Pass* current = head;
        while (current->next != nullptr)
        {
            if (current->FIO > current->next->FIO)
            {
                swap(current->FIO, current->next->FIO);
                swap(current->flight, current->next->flight);
                swap(current->vesh, current->next->vesh);
                swap(current->weight, current->next->weight);
                swapp = true;
            }
            current = current->next;
        }
    } while (swapp);
    cout << "\nСписок отсортирован по ФИО\n";
}
//поиск пассажиров с 1 вещью весом >30 кг
void resh(Pass* head)
{
    double sr = 0;
    int fl = 0, count = 0;
    if (head == nullptr) { cout << "Список пуст!"; return; }
    cout << "\nПассажиры с одной вещью весом более 30 кг:" << endl;
    Pass* current = head;
    while (current != nullptr)
    {
        sr += current->weight;
        count++;
        if (current->vesh == 1 and current->weight > 30)
        {
            cout << current->FIO << endl;
            fl = 1;
        }
        current = current->next;
    }
    if (fl == 0) cout << "В списке нет пассажиров с одной вещью весом более 30 кг" << endl;
    cout << "\nСредняя масса багажа:" << sr / count<< "[кг]" << endl;
}
//вывод в таблицу
void CoutPassengers(Pass* head) {
    if (head == nullptr)
    {
        cout << "\nСписок пассажиров пуст" << endl;
        return;
    }
    cout << "\nСписок пассажиров:" << endl;
    Pass* current = head;
    int count = 0;
    while (current != nullptr) {
        count++;
        cout << left << "ФИО: " << setw(35) << current->FIO << " | Рейс: " << setw(10) << current->flight->reis << " | Дата вылета: "
            << setw(10) << current->flight->date << " | Количество вещей: " << setw(10) << current->vesh
            << " | Масса вещей[кг]: " << fixed << setprecision(2) << current->weight << endl;
        current = current->next;
    }
    cout << "Всего пассажиров:" << count << endl;
}

// Вспомогательная функция для генерации тестовой базы
void addMock(Pass*& head, string fio, string reis, string date, int vesh, double weight) {
    Pass* p = new Pass{ fio, nullptr, vesh, weight, head };
    pushFlight(p, reis, date);
    head = p;
}

    passengers.push_back({ "Иванов Иван Иванович", {"SU100", "12.10.2026"}, 1, 32.50 });
    passengers.push_back({ "John Doe", {"AA123", "15.10.2026"}, 1, 10.00 });
    passengers.push_back({ "Петров Петр Петрович", {"A4250", "28.02.2026"}, 3, 35.20 });
    passengers.push_back({ "Alice Smith", {"LH456", "20.05.2027"}, 0, 0.00 });
    passengers.push_back({ "Сидоров Сидор Сидорович", {"SU100", "01.01.2027"}, 2, 15.00 });
    passengers.push_back({ "Alex Brown", {"BA011", "11.11.2026"}, 1, 32.00 });
    passengers.push_back({ "Козлов Алексей Сергеевич", {"SU200", "19.04.2026"}, 1, 12.30 });
    passengers.push_back({ "Смирнова Анна Дмитриевна", {"DP444", "05.09.2026"}, 2, 22.10 });
    passengers.push_back({ "Michael Jordan", {"NY23", "17.02.2027"}, 4, 45.00 });
    passengers.push_back({ "Федоров Олег Игоревич", {"A4250", "30.06.2026"}, 1, 30.50 });

void loadValidMockData(Pass*& head) {
    addMock(head, "Иванов Иван Иванович", "SU100", "12.10.2026", 1, 32.50);
    addMock(head, "John Doe", "AA123", "15.10.2026", 1, 10.00);
    addMock(head, "Петров Петр Петрович", "A4250", "28.02.2026", 3, 35.20);
    addMock(head, "Alice Smith", "LH456", "20.05.2027", 0, 0.00);
    addMock(head, "Сидоров Сидор Сидорович", "SU100", "01.01.2027", 2, 15.00);
    addMock(head, "Alex Brown", "BA011", "11.11.2026", 1, 32.00);
    addMock(head, "Козлов Алексей Сергеевич", "SU200", "19.04.2026", 1, 12.30);
    addMock(head, "Смирнова Анна Дмитриевна", "DP444", "05.09.2026", 2, 22.10);
    addMock(head, "Michael Jordan", "NY23", "17.02.2027", 4, 45.00);
    addMock(head, "Федоров Олег Игоревич", "A4250", "30.06.2026", 1, 30.50);
    cout << "\n[Система]: Массив успешно заполнен 10 тестовыми записями!" << endl;
}

// Полная очистка всей динамической памяти (профилактика утечек)
void clearMemory(Pass*& head) {
    while (head != nullptr) {
        Pass* tempPass = head;
        head = head->next;
        // Очищаем стек рейсов этого пассажира
        while (tempPass->flight != nullptr) {
            popFlight(tempPass);
        }
        delete tempPass;
    }


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Pass* head = nullptr;
    int choice;

    do {
        cout << "\n--- МЕНЮ ---" << endl;
        cout << "1. Добавить пассажира" << endl;
        cout << "2. Сортировать пассажиров" << endl;
        cout << "3. Решить задачу" << endl;
        cout << "4. Вывести список" << endl;
        cout << "5. Авто-заполнение базы" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите пункт: ";


        if (!(cin >> choice)) {
            cout << "Ошибка! Введите цифру от 0 до 5." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore();

        switch (choice) {
        case 1:
            addPass(head);
            break;
        case 2:
            Sort_FIO(head);
            break;
        case 3:
            resh(head);
            break;
        case 4:
            CoutPassengers(head);
            break;
        case 5:
            loadValidMockData(head);//izm
            break;
        case 0:
            cout << "Выход из программы" << endl;
            break;
        default:
            cout << "Неверный пункт меню! Попробуйте снова." << endl;
        }

    } while (choice != 0);
    clearMemory(head);
    return 0;
}