#include <iostream>
#include <windows.h>
#include <stdexcept>
#include <locale>


using namespace std;

class Counter
{
//hidden fields
protected:
		int value;
		int min_range;
		int max_range;
public:
//constuctor(without parameters)
	Counter() :value(0), min_range(0), max_range(10) {}

//constuctor(with parameters)
	Counter(int val, int minVal, int maxVal)
	{
		if (minVal > maxVal)
		{
			throw invalid_argument("Ошибка: Минимальная граница не может быть больше максимальной!");
		}
		if (val < minVal || val > maxVal)
		{
			throw out_of_range("Ошибка: Начальное значение выходит за пределы диапазона!");
		}
		min_range = minVal;
		max_range = maxVal;
		value = val;
	}
	virtual ~Counter() = default;

//characteristisc
	int getValue() const { return value; }

	int getMin() const { return min_range; }
	int getMax() const { return max_range; }

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
	Counter1(): Counter() {}
	Counter1(int val, int minVal, int maxVal) : Counter(val, minVal, maxVal) {}

	void increaseOn(int step)
	{
		if (step < 0)
		{
			throw invalid_argument("Ошибка: Шаг не может быть отрицательным!");
		}
		if (value + step > max_range)
		{
			throw out_of_range("Исключение: Выход за верхнюю границу диапазона!");
		}
		value += step;
	}

	void decreaseOn(int step)
	{
		if (step < 0)
		{
			throw invalid_argument("Ошибка: Шаг не может быть отрицательным!");
		}
		if (value - step < min_range)
		{
			throw out_of_range("Исключение: Выход за нижнюю границу диапазона!");
		}
		value -= step;
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int choise = 0;
	int minVal, maxVal, startVal;
	cout << "Создание счетчика" << endl;
	cout << "Введите минимальную границу: ";
	cin >> minVal;
	cout << "Введите максимальную границу: ";
	cin >> maxVal;
	cout << "Введите начальное значение: ";
	cin >> startVal;
	Counter1 count;
	try
	{
		count = Counter1(startVal, minVal, maxVal);
		cout << "\nСчетчик создан!" << endl;
	}
	catch (const exception& e) {
		cout << "\n" << e.what() << endl;
		cout << "Выход из программы." << endl;
		return 0;
	}
	while (true) {
		cout << "\n================ ТЕКУЩЕЕ СОСТОЯНИЕ ================" <<endl;
		cout << " Диапазон: [" << count.getMin() << "; " << count.getMax() << "]" << endl;
		cout << " Значение: " << count.getValue() <<endl;
		cout << "===================================================" << endl;
		cout << "1. Увеличить на 1" << endl;
		cout << "2. Уменьшить на 1" << endl;
		cout << "3. Увеличить на число " << endl;
		cout << "4. Уменьшить на число" << endl;
		cout << "5. Выйти из программы" << endl;
		cout << "Выберите действие (1-5): ";
		cin >> choise;

		if (choise == 5) {
			cout << "Программа завершена. До свидания!" << endl;
			break;
		}
		try {
			int steps = 0;
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
				cin >> steps;
				count.increaseOn(steps);
				cout << "Значение увеличено на " << steps << "." << endl;
				break;
			case 4:
				cout << "Введите число для уменьшения: ";
				cin >> steps;
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
