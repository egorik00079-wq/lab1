#include <iostream>
#include <windows.h>
#include <stdexcept>
#include <locale>
#include <string>
#include <cctype>

using namespace std;

class Counter
{
	//hidden fields
private:
	int value;
	int min_range;
	int max_range;

	int prov(const string& rawInput, const string& fieldName)
	{
		// 1. Проверяем на пустую строку
		if (rawInput.empty())
		{
			throw invalid_argument("Ошибка: Поле '" + fieldName + "' не может быть пустым!");
		}

		size_t i = 0;
		if (rawInput[0] == '-')
		{
			if (rawInput.length() == 1) // Если введен только одиночный минус
			{
				throw invalid_argument("Ошибка: В поле '" + fieldName + "' введен только знак минуса!");
			}
			i = 1;
		}

		for (; i < rawInput.length(); i++)
		{
			// isdigit возвращает true только для символов от '0' до '9'
			if (!isdigit(rawInput[i]))
			{
				throw invalid_argument("Ошибка: В поле '" + fieldName + "' допустимы только цифры (без пробелов, табуляций и букв)!");
			}
		}

		// 3. Конвертация строки в int с проверкой на переполнение типа данных
		try
		{
			return stoi(rawInput);
		}
		catch (const out_of_range&)
		{
			throw out_of_range("Ошибка: Число в поле '" + fieldName + "' слишком велико или мало для формата int!");
		}
	}
public:
	//constuctor(without parameters)
	Counter() :value(0), min_range(0), max_range(10) {}

	//constuctor(with parameters)
	Counter(string strVal, string strMin, string strMax)
	{
		int minVal = prov(strMin, "Минимальная граница");
		int maxVal = prov(strMax, "Максимальная граница");
		int val = prov(strVal, "Начальное значение");
		if (minVal > maxVal)
		{
			throw invalid_argument("Ошибка: Минимальная граница не может быть больше максимальной!");
		}
		if (val < minVal || val > maxVal)
		{
			throw out_of_range("Ошибка: Начальное значение выходит за пределы диапазона!");
		}
		if (minVal < -10000 || maxVal > 10000)
		{
			throw out_of_range("Введеный диапазон недопустим, допустымый диапазон [-10000;10000]");
		}
		
		//все исключительные ситуации нужно предусмотреть(пробелы,буквы,вне границы,табуляции),ограничение на границы до 10.000, добавить в менб вывод ограничений(допустимых значений). Сжато написать ограничения в отчете.диаграмма класов
		min_range = minVal;
		max_range = maxVal;
		value = val;
	}
	virtual ~Counter() = default;

	//getter
	int getValue() const { return value; }
	int getMin() const { return min_range; }
	int getMax() const { return max_range; }

	int check(const string& str, const string& context)
	{
		return prov(str, context);
	}
	//setter
	void setValue(int newVal)
	{
		if (newVal < min_range || newVal > max_range)
		{
			throw out_of_range("Исключение: Попытка установить значение вне диапазона!");
		}
		value = newVal;
	}
	//methods
	void increase()
	{
		if (value + 1 > max_range)
		{
			throw out_of_range("Исключение: Выход за верхнюю границу диапазона!");
		}
		value++;
	}
	void decrease()
	{
		if (value - 1 < min_range)
		{
			throw out_of_range("Исключение: Выход за нижнюю границу диапазона!");
		}
		value--;
	}
};

class Counter1 : public Counter
{
public:
	Counter1() : Counter() {}
	Counter1(string strVal, string strMin, string strMax) : Counter(strVal, strMin, strMax) {}
	void increaseOn(string strStep)
	{
		int step = check(strStep, "Шаг увеличения");
		if (step < 0)
		{
			throw invalid_argument("Ошибка: Шаг не может быть отрицательным!");
		}
		if (getValue() + step > getMax())
		{
			throw out_of_range("Исключение: Выход за верхнюю границу диапазона!");
		}
		setValue(getValue() + step);
	}

	void decreaseOn(string strStep)
	{
		int step = check(strStep, "Шаг уменьшения");
		if (step < 0)
		{
			throw invalid_argument("Ошибка: Шаг не может быть отрицательным!");
		}
		if (getValue() - step < getMin())
		{
			throw out_of_range("Исключение: Выход за нижнюю границу диапазона!");
		}
		setValue(getValue() - step);
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int choise = 0;
	string minVal, maxVal, startVal;
	Counter1 count;
	cout << "Создание счетчика" << endl;

	while (true) {
		try
		{
			cout << "Введите минимальную границу (до -10000): ";
			getline(cin,minVal);
			cout << "Введите максимальную границу (до 10000): ";
			getline(cin,maxVal);
			cout << "Введите начальное значение: ";
			getline(cin,startVal);
		
			count = Counter1(startVal, minVal, maxVal);
			cout << "\nСчетчик создан!" << endl;
			break;
		}
		catch (const exception& e) {
			cout << "\n" << e.what() << endl;
			cout << "Повторите ввод.\n" << endl;
		}
	}

	while (true) {
		cout << "\n================ ТЕКУЩЕЕ СОСТОЯНИЕ ================" << endl;
		cout << " Диапазон: [" << count.getMin() << "; " << count.getMax() << "]" << endl;
		cout << " Значение: " << count.getValue() << endl;
		cout << "===================================================" << endl;
		cout << "1. Увеличить на 1" << endl;
		cout << "2. Уменьшить на 1" << endl;
		cout << "3. Увеличить на заданное число " << endl;
		cout << "4. Уменьшить на заданное число" << endl;
		cout << "5. Выйти из программы" << endl;
		cout << "Выберите действие (1-5): ";
		cin >> choise;

		if (choise == 5) {
			cout << "Программа завершена. До свидания!" << endl;
			break;
		}
		try {
			string steps;
			switch (choise) {
			case 1:
				count.increase();
				cout << "Значение увеличено на 1." << endl;
				break;
			case 2:
				count.decrease();
				cout << "Значение уменьшено на 1." << endl;
				break;
			case 3:
				cout << "Введите число для увеличения: ";
				getline(cin,steps);
				count.increaseOn(steps);
				cout << "Значение увеличено на " << steps << "." << endl;
				break;
			case 4:
				cout << "Введите число для уменьшения: ";
				getline(cin, steps);
				count.decreaseOn(steps);
				cout << "Значение уменьшено на " << steps << "." << endl;
				break;
			default:
				cout << "[Внимание] Неверный пункт меню. Попробуйте еще раз." << endl;
				break;
			}
		}
		catch (const out_of_range& e) {
			cout << "\n Выход за границы: " << e.what() << endl;
		}
		catch (const invalid_argument& e) {
			cout << "\n Ошибка аргумента: " << e.what() << endl;
		}
	}
}