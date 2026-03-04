#include "../Lab1Code/Polynom.h"

void print_menu() // Функция для вывода меню в консоль.
{
	std::cout << "+-------------------------MENU-------------------------+\n" << "1 - Creating/Replacing the first polynomial\n" << "2 - Creating/Replacing the second polynomial\n";
	std::cout << "3 - Outputting the first polynomial to the console\n" << "4 - Outputting the second polynomial to the console\n" << "5 - Add polynomials\n";
	std::cout << "6 - Subtract polynomials\n" << "7 - Multiply a polynomial by a constant\n" << "8 - Multiply polynomials\n" << "9 - Outputting the program menu to the console\n" << "0 - Shutting down the program\n";
	std::cout << "+------------------------------------------------------+\n";
}

Polynomial input_polynom() // Функция для ввода полинома пользователем с консоли.
{
	std::cout << "The coefficients of monomials are real numbers.\nThe degree of a monomial is a three-digit number, where the hundreds digit is the degree of variable X, the tens digit is the degree of variable Y, and the units digit is the degree of variable Z.\n";

	bool flag_input = true; // Флаг для ввода пользователем всех нужных ему мономов.

	std::vector<std::pair<double, size_t>> source; // Вектор для хранения данных первого полинома, который будет передан в конструктор класса Polynomial для создания первого полинома.

	std::string user_input = ""; // Буфер ввода пользователем.

	while (flag_input)
	{
		// Вводим коэффициент монома:
		std::cout << "Enter the coefficient of the monomial:\n";

		double temp_coeff = 0.0; // Коэффициент монома.
		std::getline(std::cin, user_input); // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной user_input.
		try
		{
			temp_coeff = std::stod(user_input); // std::stod() преобразует строку user_input в число с плавающей запятой (double). Если строка не может быть преобразована в число, будет выброшено исключение std::invalid_argument. Если число слишком велико для типа double, будет выброшено исключение std::out_of_range.

			if (std::fabs(temp_coeff) < EPSILON) // Проверка на равенство коэффциеинта 0.
			{
				std::cout << "INVALID INPUT. The coefficient of the monomial must be different from 0.\n";
				continue;
			}
		}
		catch (std::exception)
		{
			std::cout << "INVALID INPUT. Please enter a real number as the coefficient of the monomial.\n";
			continue;
		}


		// Вводим степень монома:
		std::cout << "Enter the degree of the monomial:\n";

		size_t temp_deg = -1; // Степень монома.
		std::getline(std::cin, user_input); // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной user_input.
		try
		{
			temp_deg = std::stoull(user_input); // std::stoull() преобразует строку user_input в беззнаковое целое число (unsigned long long). Если строка не может быть преобразована в число, будет выброшено исключение std::invalid_argument. Если число слишком велико для типа unsigned long long, будет выброшено исключение std::out_of_range.

			if (temp_deg > 999 || temp_deg < 0) // Проверка на выход значения степени монома за установленные пределы.
			{
				std::cout << "INVALID INPUT. Please enter an integer between 0 and 999 as the degree of the monomial.\n";
				continue;
			}
		}
		catch (std::exception)
		{
			std::cout << "INVALID INPUT. Please enter an integer between 0 and 999 as the degree of the monomial.\n";
			continue;
		}

		source.push_back({ temp_coeff, temp_deg }); // Добавляем моном в вектор source для последующей записи в полином.

		// Даём пользователю выбор: продолжить ввод полинома(1) или завершить(0).
		std::cout << "1 - Continue entering the polynomial, 0 - Finish entering the polynomial.\nEnter:\n";
		bool flag_temp = true; // Флаг для выбора пользователем нужного варианта ответа.
		while (flag_temp)
		{
			int temp = -1; // Результат выбора пользователем.
			std::getline(std::cin, user_input); // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной user_input.
			try
			{
				temp = std::stoi(user_input); // std::stoi() преобразует строку user_input в целое число (int). Если строка не может быть преобразована в число, будет выброшено исключение std::invalid_argument. Если число слишком велико для типа int, будет выброшено исключение std::out_of_range.

				if (temp == 0)
				{
					flag_input = false;
					flag_temp = false;
				}
				else if (temp == 1)
				{
					flag_temp = false;
				}
				else
				{
					std::cout << "INVALID INPUT.\n1 - Continue entering the polynomial, 0 - Finish entering the polynomial.\nEnter:\n";
					continue;
				}
			}
			catch (std::exception)
			{
				std::cout << "INVALID INPUT.\n1 - Continue entering the polynomial, 0 - Finish entering the polynomial.\nEnter:\n";
				continue;
			}
		}
	}

	Polynomial temp_p1(source); // Создаём полином с данными, которые ввёл пользователь (source).
	return temp_p1; // Возврат из функции полученного полинома.
}

int main()
{
	Polynomial p1, p2, res_p; // p1, p2 - полиномы для ввода пользователем; res_p - результирующий полином.
	bool flag = true; // Флаг работы программы.

	print_menu(); // Выводим меню для пользователя.

	while (flag)
	{
		std::cout << "+--------------------+ENTER_CHOICE+--------------------+\n";

		std::string choice = ""; // Буфер для выбора команды пользователем.
		int num_choice = 0; // Число для switch-case.
		std::getline(std::cin, choice);  // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной choice.

		// Отлавливаем исключение, если пользователь вводит не число.
		try
		{
			num_choice = std::stoi(choice); // std::stoi() преобразует строку user_input в целое число (int). Если строка не может быть преобразована в число, будет выброшено исключение std::invalid_argument. Если число слишком велико для типа int, будет выброшено исключение std::out_of_range.
		}
		catch (std::exception)
		{
			std::cout << "INVALID INPUT. Please enter a number from 0 to 9\n";
			continue; // Переход к началу цикла, чтобы пользователь мог ввести правильное значение команды.
		}

		switch (num_choice)
		{
		case 1:
			p1 = input_polynom(); // Применяем перегруженный оператор присваивания.
			break;
		case 2:
			p2 = input_polynom(); // Применяем перегруженный оператор присваивания.
			break;
		case 3:
			p1.print_polynom();
			break;
		case 4:
			p2.print_polynom();
			break;
		case 5:
		{
			if (!p1.is_empty() && !p2.is_empty()) // Если полиномы не пусты, то выполняем команду.
			{
				res_p = p1 + p2; // Используем перегруженные операторы сложения и присваивания.
				res_p.print_polynom();
			}
			else
			{
				if (p1.is_empty())
				{
					std::cout << "The first polynomial is empty.\n";
				}
				if (p2.is_empty())
				{
					std::cout << "The second polynomial is empty.\n";
				}
			}

			break;
		}
		case 6:
		{
			if (!p1.is_empty() && !p2.is_empty()) // Если полиномы не пусты, то выполняем команду.
			{
				std::cout << "0 - subtract the second from the first polynomial (p1 - p2), 1 - subtract the first from the second polynomial (p2 - p1).\nEnter:\n";
				std::string user_input = ""; // Буфер ввода пользователем.

				bool flag_temp = true; // Флаг для выполнения команды до тех пор, пока не будет введено верное значение выбора.
				int temp = -1; // Результат выбора пользователем.
				while (flag_temp)
				{
					std::getline(std::cin, user_input); // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной user_input.
					try
					{
						temp = std::stoi(user_input); // std::stoi() преобразует строку user_input в целое число (int). Если строка не может быть преобразована в число, будет выброшено исключение std::invalid_argument. Если число слишком велико для типа int, будет выброшено исключение std::out_of_range.

						if (temp == 0)
						{
							res_p = p1 - p2; // Используем перегруженные операторы вычитания и присваивания.
							res_p.print_polynom();
							flag_temp = false;
						}
						else if (temp == 1)
						{
							res_p = p2 - p1; // Используем перегруженные операторы вычитания и присваивания.
							res_p.print_polynom();
							flag_temp = false;
						}
						else
						{
							std::cout << "INVALID INPUT.\n0 - subtract the second from the first polynomial (p1 - p2), 1 - subtract the first from the second polynomial (p2 - p1).\nEnter:\n";
							continue;
						}
					}
					catch (std::exception)
					{
						std::cout << "INVALID INPUT.\n0 - subtract the second from the first polynomial (p1 - p2), 1 - subtract the first from the second polynomial (p2 - p1).\nEnter:\n";
						continue;
					}
				}
			}
			else
			{
				if (p1.is_empty())
				{
					std::cout << "The first polynomial is empty.\n";
				}
				if (p2.is_empty())
				{
					std::cout << "The second polynomial is empty.\n";
				}
			}

			break;
		}
		case 7:
		{
			std::cout << "0 - multiply the first(p1) polynomial by a constant, 1 - multiply the second(p2) polynomial by a constant.\nEnter:\n";
			std::string user_input = ""; // Буфер ввода пользователем.

			bool flag_temp = true; // Флаг для выполнения команды до тех пор, пока не будет введено верное значение выбора.
			int temp = -1; // Результат выбора пользователем.
			double temp_const = -1; // Значение константы, введенное пользователем.
			while (flag_temp)
			{
				std::getline(std::cin, user_input); // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной user_input.
				try
				{
					temp = std::stoi(user_input); // std::stoi() преобразует строку user_input в целое число (int). Если строка не может быть преобразована в число, будет выброшено исключение std::invalid_argument. Если число слишком велико для типа int, будет выброшено исключение std::out_of_range.

					if (temp == 0 && !p1.is_empty() || temp == 1 && !p2.is_empty())
					{
						// Ввод константы пользователем.
						std::cout << "Enter a constant (real number):\n";

						bool flag_const = true; // Флаг для выполнения команды до тех пор, пока не будет введено верное значение выбора.
						while (flag_const)
						{
							std::getline(std::cin, user_input); // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной user_input.
							try
							{
								temp_const = std::stod(user_input); // std::stod() преобразует строку user_input в число с плавающей запятой (double). Если строка не может быть преобразована в число, будет выброшено исключение std::invalid_argument. Если число слишком велико для типа double, будет выброшено исключение std::out_of_range.
								flag_const = false;
							}
							catch (std::exception)
							{
								std::cout << "INVALID INPUT.\nEnter a constant (real number):";
								continue;
							}
						}

						// Выбор полинома пользователем.
						if (temp == 0)
						{
							res_p = p1 * temp_const;
							res_p.print_polynom();
							flag_temp = false;
						}
						else if (temp == 1)
						{
							res_p = p2 * temp_const;
							res_p.print_polynom();
							flag_temp = false;
						}
					}
					else if (temp == 0 && p1.is_empty())
					{
						std::cout << "The first polynomial is empty.\n";
						flag_temp = false;
					}
					else if (temp == 1 && p2.is_empty())
					{
						std::cout << "The second polynomial is empty.\n";
						flag_temp = false;
					}
					else
					{
						std::cout << "INVALID INPUT.\n0 - multiply the first(p1) polynomial by a constant, 1 - multiply the second(p2) polynomial by a constant.\nEnter:\n";
						continue;
					}
				}
				catch (std::exception)
				{
					std::cout << "INVALID INPUT.\n0 - multiply the first(p1) polynomial by a constant, 1 - multiply the second(p2) polynomial by a constant.\nEnter:\n";
					continue;
				}
			}
		}

		break;
		case 8:
			if (!p1.is_empty() && !p2.is_empty()) // Если полиномы не пусты, то выполняем команду.
			{
				try
				{
					res_p = p1 * p2; // Используем перегруженные операторы умножения и присваивания.
					res_p.print_polynom();
				}
				catch (std::range_error)
				{
					std::cout << "The degrees of the obtained variables are greater than 9. The maximum degree of a polynomial is 999.\n";
				}
			}
			else
			{
				if (p1.is_empty())
				{
					std::cout << "The first polynomial is empty.\n";
				}
				if (p2.is_empty())
				{
					std::cout << "The second polynomial is empty.\n";
				}
			}
			break;
		case 9:
			print_menu();
			break;
		case 0:
			std::cout << "Shutdown program.\n";
			flag = false;
			break;
		default:
			std::cout << "INVALID INPUT. Please enter a number from 0 to 9\n";
			break;
		}
	}
	return 0;
}