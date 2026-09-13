#include <iostream>
#include <string>
#include <windows.h>
#include <vector>

using namespace std;
struct Flight
{
    string reis;
    string date;
};

struct Pass {
    string FIO;
    Flight flight;
    int vesh;
    double weight;
};

//фио
bool prov(const string& fio)
{
    if (fio.empty() || fio.length() > 100 || fio.find_first_not_of(" \t") == std::string::npos) return false;
    for (char uc : fio) {
        unsigned char c = static_cast<unsigned char>(uc);
        bool ras = (c >= 192 && c <= 255) || c == 168 || c == 184
            || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == ' ' || c == '-');
        if (!ras) return false;
    }
    return true;

}
// рейс
bool prov_flight(const string& reis)
{
    if (reis.empty() || reis.length() > 100 || reis.find_first_not_of(" \t") == std::string::npos) return false;
    for (char c : reis) {
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))) return false;
    }
    return true;
}

void addPass(vector<Pass>& pass)
{
    Pass passag;

}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Pass passag;
    vector<Pass> passengers;

    char choice;
    do {
        Pass passag;
        while (true) {
            cout << "Введите ФИО:";
            getline(cin, passag.FIO);
            if (prov(passag.FIO)) break;
            cout << "Некорректные данные ФИО! Повторите ввод." << endl;
        }

        while (true) {
            cout << "Введите номер рейса:";
            getline(cin, passag.flight.reis);
            if (prov_flight(passag.flight.reis)) break;
            cout << "Некорректный номер рейса! Повторите ввод." << endl;
        }

        passengers.push_back(passag);
        cout << "Данные пассажира успешно добавлены в массив!" << endl;
        cout << "Хотите добавить еще одного пассажира? (y/n):";
        cin >> choice;
        cin.ignore();

    } while (choice == 'y' || choice == 'Y');

    cout << "\nВсего пассажиров:\nСписок:" << passengers.size() << endl;
    for (int i = 0; i < passengers.size(); i++)
    {
        cout << "ФИО: " << passengers[i].FIO << " | Рейс: " << passengers[i].flight.reis << endl;
    }
}