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
// 1. Добавление в начало списка
void addToFront(Pass*& head, Pass* newPass, const string& reis, const string& date) {
    if (newPass == nullptr) return;

    pushFlight(newPass, reis, date);
    newPass->next = head;
    head = newPass;
}

// 2. Добавление в конец списка
void addToEnd(Pass*& head, Pass* newPass, const string& reis, const string& date) {
    if (newPass == nullptr) return;
    pushFlight(newPass, reis, date);
    newPass->next = nullptr;
    if (head == nullptr) {
        head = newPass;
        return;
    } 
    Pass* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newPass;
}

// 3. Добавление в середину (после указанного узла)
void insertAfter(Pass* prevPass, Pass* newPass, const string& reis, const string& date) {
    if (prevPass == nullptr || newPass == nullptr) return;

    pushFlight(newPass, reis, date); 
    newPass->next = prevPass->next;
    prevPass->next = newPass;
}

//добавление в массив + проверка корректности данных
void addPass(Pass*& head)
{
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
            getline(cin, reis);
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


        int insertChoice;
        while (true) {
            cout << "\nКуда добавить пассажира?\n";
            cout << "1 - В начало списка\n";
            cout << "2 - В конец списка\n";
            cout << "3 - В середину (на заданную позицию)\n";
            cout << "Ваш выбор: ";
            if (cin >> insertChoice) {
                if (insertChoice >= 1 && insertChoice <= 3) break;
            }
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Неверный ввод! Введите цифру от 1 до 3.\n";
        }
        cin.ignore(10000, '\n'); // Очистка буфера после ввода цифры

        if (insertChoice == 1) {
            addToFront(head, passag, reis, date);
            cout << "Пассажир добавлен в начало списка!" << endl;
        }
        else if (insertChoice == 2) {
            addToEnd(head, passag, reis, date);
            cout << "Пассажир добавлен в конец списка!" << endl;
        }
        else if (insertChoice == 3) {
            if (head == nullptr) {
                cout << "Список был пуст, пассажир автоматически стал первым (в начале)!" << endl;
                addToFront(head, passag, reis, date);
            }
            else {
                int pos;
                cout << "Введите номер позиции, НА которую хотите поставить пассажира (начиная с 1): ";
                while (!(cin >> pos) || pos < 1) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Некорректная позиция! Введите число больше 0: ";
                }
                cin.ignore(10000, '\n');

                if (pos == 1) {
                    addToFront(head, passag, reis, date);
                }
                else {
                    Pass* current = head;
                    for (int i = 1; i < pos - 1 && current->next != nullptr; i++) {
                        current = current->next;
                    }
                    insertAfter(current, passag, reis, date);
                }
                cout << "Пассажир успешно добавлен на позицию " << pos << "!" << endl;
            }
        }
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
    cout << "\nСредняя масса багажа:" << sr / count << "[кг]" << endl;
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
        cout << left << "№"<< setw(3) << count<< "| ФИО: " << setw(35) << current->FIO << " | Рейс: " << setw(10) << current->flight->reis << " | Дата вылета: "
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
}
void deleteFront(Pass*& head)
{
    if (head == nullptr) return;
    Pass* temp = head;
    head = head->next;
    if (temp->flight != nullptr) {
        popFlight(temp);
    }
    delete temp;

}

void deleteEnd(Pass*& head)
{
    if (head == nullptr) return;

    if (head->next == nullptr) {
        if (head->flight != nullptr) popFlight(head);
        delete head;
        head = nullptr;
        return;
    }
    Pass* current = head;
    while (current->next->next != nullptr)
    {
        current = current->next;
    }
    Pass* temp = current->next;
    current->next = nullptr;
    if (temp->flight != nullptr) {
        popFlight(temp);
    }
    
    delete temp;
}

void deleteCurr(Pass*& head, int pos)
{
    if (head == nullptr) return;
    if (pos == 1) {
        Pass* temp = head;
        head = head->next;
        while (temp->flight != nullptr) popFlight(temp);
        delete temp;
        return;
    }

    Pass* current = head;
    for (int i = 1; i < pos - 1 && current->next != nullptr; i++) {
        current = current->next;
    }

    if (current == nullptr || current->next == nullptr) {
        cout << "Позиция не найдена!" << endl;
        return;
    }
    Pass* temp = current->next;
    current->next = temp->next;
    if (temp->flight != nullptr) {
        popFlight(temp);
    }
    delete temp;
}

void vib(Pass*& head)
{
    int insertChoice;
        while (true) {
            cout << "Откуда удалить элемент?\n";
            cout << "1 - Из начала списка\n";
            cout << "2 - Из конца списка\n";
            cout << "3 - Из середины (на заданной позиции)\n";
            cout << "Ваш выбор: ";
            if (cin >> insertChoice) {
                if (insertChoice >= 1 && insertChoice <= 3) break;
            }
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Неверный ввод! Введите цифру от 1 до 3.\n";
        }
        cin.ignore(10000, '\n');
        switch (insertChoice)
        {
        case 1:
            deleteFront(head);
            cout << "Первый пассажир успешно удален!";
            break;
        
        case 2:
            deleteEnd(head);
            cout << "Последний пассажир успешно удален!";
            break;
        case 3:
            int pos;
            cout << "Введите позицию для удаления: ";
            cin >> pos;
            deleteCurr(head, pos);
            cout << "Пассажир под номером "<< pos <<" успешно удален!";
            break;
        }
        
}

void izm(Pass * &head) {

    if (head == nullptr) {
        cout << "Список пуст!" << endl;
        return;
    }

    int pos;
    while (true) {
        cout << "Укажите номер записи, которую вы хотите изменить: ";
        if (cin >> pos && pos > 0) {
            break;
        }
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Неверный ввод! Введите число больше 0.\n";
    }
    cin.ignore(10000, '\n');

    // поиск по позиции и поиск элемента перед искомым 
    Pass* current = head;
    for (int i = 1; i < pos && current != nullptr; i++) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Позиция не найдена!" << endl;
        return;
    }

    int choice;
    cout << "\nЧто именно вы хотите изменить?" << endl;
    cout << "1 - ФИО" << endl;
    cout << "2 - Номер рейса" << endl;
    cout << "3 - Дата вылета" << endl;
    cout << "4 - Количество вещей и вес" << endl;
    cout << "Ваш выбор: ";

    while (!(cin >> choice) || choice < 1 || choice > 4) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Неверный ввод! Выберите пункт от 1 до 4: ";
    }
    cin.ignore(10000, '\n');


    switch (choice) {
    case 1: {
        while (true) {
            cout << "Введите новое ФИО: ";
            getline(cin, current->FIO);
            if (prov(current->FIO)) break;
            cout << "Некорректные данные ФИО! Повторите ввод." << endl;
        }
        break;
    }
    case 2: {
        string new_reis, current_date = "";
        if (current->flight != nullptr) {
            current_date = current->flight->date;
            popFlight(current);
        }
        while (true) {
            cout << "Введите новый номер рейса: ";
            getline(cin, new_reis);
            if (prov_flight(new_reis)) break;
            cout << "Некорректный номер рейса! Повторите ввод." << endl;
        }
        pushFlight(current, new_reis, current_date);
        break;
    }
    case 3: {
        string current_reis = "", new_date;
        if (current->flight != nullptr)
        {
            current_reis = current->flight->reis;
            popFlight(current);
        }

        while (true) {
            cout << "Введите новую дату вылета (ДД.ММ.ГГГГ): ";
            getline(cin, new_date);
            if (prov_date(new_date)) break;
            cout << "Некорректная дата! Повторите ввод." << endl;
        }
        pushFlight(current, current_reis, new_date);
        break;
    }
    case 4: {
        // Ввод количества вещей
        while (true) {
            cout << "Введите новое количество вещей: ";
            string str;
            getline(cin, str);
            bool fl = !str.empty();
            for (char c : str) {
                if (c < '0' || c > '9') { fl = false; break; }
            }
            if (fl) {
                current->vesh = stoi(str);
                if (current->vesh >= 0 && current->vesh <= 10) break;
            }
            cout << "Недопустимое количество вещей! Введите число от 0 до 10." << endl;
        }

        // Ввод веса, если вещи есть
        if (current->vesh != 0) {
            int mass_mer;
            while (true) {
                cout << "Укажите в чем измеряется масса вещей [1] фунт; [2] кг: ";
                string str;
                getline(cin, str);
                if (str == "1" || str == "2") {
                    mass_mer = stoi(str);
                    break;
                }
                cout << "Некорректный выбор! Введите 1 или 2." << endl;
            }

            while (true) {
                cout << "Введите общую массу вещей: ";
                string str;
                getline(cin, str);
                bool fl = !str.empty();
                int dot_count = 0;
                for (char c : str) {
                    if (c == '.') dot_count++;
                    else if (c < '0' || c > '9') { fl = false; break; }
                }
                if (dot_count > 1) fl = false;
                if (fl) {
                    current->weight = stod(str);
                    if (mass_mer == 1 && current->weight >= 0.0 && current->weight <= 220.46) break;
                    else if (mass_mer == 2 && current->weight >= 0.0 && current->weight <= 100.0) break;
                }
                cout << "Некорректный вес! Повторите ввод." << endl;
            }
            if (mass_mer == 1) {
                current->weight *= 0.453592;
            }
        }
        else {
            current->weight = 0;
        }
        break;
    }
    }

    cout << "\nЗапись под номером " << pos << " успешно обновлена!" << endl;
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
        cout << "6. Удалить элемент" << endl;
        cout << "7. Изменить запись" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите пункт: ";


        if (!(cin >> choice)) {
            cout << "Ошибка! Введите цифру от 0 до 7." << endl;
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
            loadValidMockData(head);
            break;
        case 6:
            vib(head);
            break;
        case 7:
            izm(head);
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
