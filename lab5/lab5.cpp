#include <iostream>
#include <windows.h>
#include <stdexcept>
#include <locale>
#include <cmath> 
#include <limits>
using namespace std;

class Integer
{
private:
	int value;
public:

	Integer() :value(0) {}

	Integer(int val)
	{
		if (val > 10000)
		{
			throw invalid_argument("Ошибка: Число не может быть больше 10000!");
		}
		if (val < -10000)
		{
			throw out_of_range("Ошибка: Число не может быть меньше -10000!");
		}
		value = val;
	}

	void print() const {
		cout << value << endl;
	}

	int get() const { return value;}
	// ++ как функция-член
	Integer& operator++()
	{
		if (value + 1 > 10000)
		{
			throw out_of_range("Исключение: Выход за верхнюю границу диапазона!");
		}
		value++;
		return *this;
	}

	// -- как дружественная функция
	friend Integer& operator--(Integer& val);
};

Integer& operator--(Integer& val)
{
	if (val.value - 1 < -10000)
	{
		throw out_of_range("Исключение: Выход за нижнюю границу диапазона!");
	}
	val.value--;
	return val;
}

class Point
{
private:
	int x, y;
public:
	Point() :x(0), y(0) {}

	Point(int x, int y)
	{
		if (x > 10000 || y > 10000)
		{
			throw invalid_argument("Ошибка: Значение X и Y не может быть больше 10000!");
		}
		if (x < -10000 || y < -10000)
		{
			throw out_of_range("Ошибка: Значение X и Y не может быть меньше -10000!");
		}
		this->x = x;
		this->y = y;
	}

	void print() const { cout <<"Координаты: " << "(" << x << ", " << y << ")" << endl; }

	Point operator+(Point& other) const
	{
		if (abs(x + other.x) > 10000 || abs(y + other.y) > 10000)
		{
			throw out_of_range("Исключение: Выход за  границу диапазона!");
		}
		return Point(x + other.x, y + other.y);
	}

	Point& operator=(const Point& other) {
		if (this != &other) {
			x = other.x;
			y = other.y;
		}
		return *this;
	}

	// Операторы сравнения (== и !=) как функции-члены
	bool operator==(const Point& other) const {
		return (x == other.x && y == other.y);
	}
	bool operator!=(const Point& other) const {
		return !(*this == other);
	}

	Point operator+(int num) const
	{
		if (abs(x + num) > 10000 || abs(y + num) > 10000)
		{
			throw out_of_range("Исключение: Выход за верхнюю границу диапазона!");
		}
		return Point(x + num, y + num);
	}
	friend Point operator-(const Point& p1, const Point& p2);
	friend Point operator-(const Point& p, int num);
};

// Реализация вычитания координат друг из друга
Point operator-(const Point& p1, const Point& p2) {
	if (abs(p1.x - p2.x) > 10000 || abs(p1.y - p2.y) > 10000)
	{
		throw out_of_range("Исключение: Выход за  границу диапазона!");
	}
	return Point(p1.x - p2.x, p1.y - p2.y);
}

// Реализация вычитания числа из координаты
Point operator-(const Point& p, int num) {
	if (abs(p.x - num) > 10000 || abs(p.y - num) > 10000)
	{
		throw out_of_range("Исключение: Выход за верхнюю границу диапазона!");
	}
	return Point(p.x - num, p.y - num);
}

// Функция для безопасного ввода одного числа
int getSafeInt() {
	int val;
	while (true) {
		cin >> val;
		if (!cin.fail()) {
			return val;
		}
		cout << "Ошибка: Введено не число! Попробуйте еще раз: ";
		cin.clear();
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
	}
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// Объекты по умолчанию для работы меню
	Integer num(5);
	Point p1(10, 20);
	Point p2(5, 5);

	int choice = 0;
	while (true)
	{
		cout << "\n================ ТЕКУЩИЕ ДАННЫЕ ================" << endl;
		cout << "Число (num): "; num.print();
		cout << "Точка 1 (p1): "; p1.print();
		cout << "Точка 2 (p2): "; p2.print();
		cout << "================================================" << endl;
		cout << "1. Инкремент числа (++num)" << endl;
		cout << "2. Декремент числа (--num)" << endl;
		cout << "3. Сложить Точку 1 и Точку 2 (p1 + p2)" << endl;
		cout << "4. Вычесть Точку 2 из Точки 1 (p1 - p2)" << endl;
		cout << "5. Сложить Точку 1 с Числом (p1 + num)" << endl;
		cout << "6. Вычесть Число из Точки 1 (p1 - num)" << endl;
		cout << "7. Сравнить Точку 1 и Точку 2 (==, !=)" << endl;
		cout << "8. Присвоить Точке 2 значения Точки 1 (p2 = p1)" << endl;
		cout << "9. Присвоить Точке 1 сумму точек (p1 + p2)" << endl;
		cout << "10. Присвоить Точке 1 разность точек (p1 - p2)" << endl;
		cout << "11. Ввести новые данные" << endl;
		cout << "0. Выход" << endl;
		cout << "Выберите действие: ";
		cin >> choice;

		if (choice == 0) break;

		cout << "\n--- РЕЗУЛЬТАТ ---" << endl;
		try
		{
			switch (choice)
			{
			case 1:
				++num;
				cout << "Число успешно увеличено!" << endl;
				break;
			case 2:
				--num;
				cout << "Число успешно уменьшено!" << endl;
				break;
			case 3: {
				Point res = p1 + p2;
				cout << "Результат p1 + p2 = "; res.print();
				break;
			}
			case 4: {
				Point res = p1 - p2;
				cout << "Результат p1 - p2 = "; res.print();
				break;
			}
			case 5: {
				Point res = p1 + num.get();
				cout << "Результат p1 + num = "; res.print();
				break;
			}
			case 6: {
				Point res = p1 - num.get();
				cout << "Результат p1 - num = "; res.print();
				break;
			}
			case 7:
				cout << "p1 == p2: " << (p1 == p2 ? "Равны" : "Не равны") << endl;
				cout << "p1 != p2: " << (p1 != p2 ? "Не равны" : "Равны") << endl;
				break;
			case 8:
				p2 = p1;
				cout << "Присваивание выполнено! Теперь p2 равна p1." << endl;
				break;
			case 9:
				p1 = p1 + p2;
				cout << "Присваивание выполнено! Теперь p1 равна p1 + p2." << endl;
				break;
			case 10:
				p1 = p1 - p2;
				cout << "Присваивание выполнено! Теперь p1 равна p1 - p2." << endl;
				break;
			case 11: {
				int n, x1, y1, x2, y2;
				cout << "Введите новое целое число: "; n = getSafeInt();
				num = Integer(n);
				cout << "Введите X для Точки 1: "; x1 = getSafeInt();
				cout << "Введите Y для Точки 1: "; y1 = getSafeInt();
				p1 = Point(x1, y1);
				cout << "Введите X для Точки 2: "; x2 = getSafeInt();
				cout << "Введите Y для Точки 2: "; y2 = getSafeInt();
				p2 = Point(x2, y2);
				cout << "Данные успешно обновлены!" << endl;
				break;
			}
			default:
				cout << "Неверный пункт меню! Попробуйте снова." << endl;
				break;
			}
		}
		catch (const exception& e)
		{
			cout << "Перехвачена ошибка: " << e.what() << endl;
		}
		cout << "-----------------" << endl;
	}

	return 0;
}
