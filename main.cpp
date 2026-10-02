#include <iostream>
#include <string>

using namespace std;

int main()
{
    string incomeCategory;
    string incomeDate;
    string incomeSource;

    string expenseCategory;
    string expenseDate;
    string expenseDescription;

    double income = 0;
    double expense = 0;
    double balance = 0;

    int choice = 0;

    cout << "===== СИСТЕМА УПРАВЛЕНИЯ ПЕРСОНАЛЬНЫМИ ФИНАНСАМИ =====" << endl;

    cout << endl;
    cout << "1 - Добавить доход" << endl;
    cout << "2 - Добавить расход" << endl;
    cout << "3 - Показать текущий баланс" << endl;
    cout << "0 - Выход" << endl;
    cout << "Выберите действие: ";
    cin >> choice;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Некорректный ввод. Введите номер пункта: ";
        cin >> choice;
    }

    switch (choice)
    {
        case 1:
        {
            cout << "Введите категорию дохода: ";
            cin >> incomeCategory;

            while (incomeCategory.empty())
            {
                cout << "Ошибка: поле не может быть пустым. Введите категорию дохода: ";
                cin >> incomeCategory;
            }

            cout << "Введите сумму дохода: ";
            cin >> income;

            while (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');

                cout << "Некорректный ввод. Введите число: ";
                cin >> income;
            }

            while (income < 0)
            {
                cout << "Ошибка: сумма дохода не может быть отрицательной. Введите число: ";
                cin >> income;

                while (cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    cout << "Некорректный ввод. Введите число: ";
                    cin >> income;
                }
            }

            cout << "Введите дату дохода: ";
            cin >> incomeDate;

            while (incomeDate.empty())
            {
                cout << "Ошибка: поле не может быть пустым. Введите дату дохода: ";
                cin >> incomeDate;
            }

            cout << "Введите источник дохода: ";
            cin >> incomeSource;

            while (incomeSource.empty())
            {
                cout << "Ошибка: поле не может быть пустым. Введите источник дохода: ";
                cin >> incomeSource;
            }

            cout << "Доход успешно добавлен." << endl;

            break;
        }

        case 2:
        {
            cout << "Введите категорию расхода: ";
            cin >> expenseCategory;

            while (expenseCategory.empty())
            {
                cout << "Ошибка: поле не может быть пустым. Введите категорию расхода: ";
                cin >> expenseCategory;
            }

            cout << "Введите сумму расхода: ";
            cin >> expense;

            while (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');

                cout << "Некорректный ввод. Введите число: ";
                cin >> expense;
            }

            while (expense < 0)
            {
                cout << "Ошибка: сумма расхода не может быть отрицательной. Введите число: ";
                cin >> expense;

                while (cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    cout << "Некорректный ввод. Введите число: ";
                    cin >> expense;
                }
            }

            cout << "Введите дату расхода: ";
            cin >> expenseDate;

            while (expenseDate.empty())
            {
                cout << "Ошибка: поле не может быть пустым. Введите дату расхода: ";
                cin >> expenseDate;
            }

            cout << "Введите описание расхода: ";
            cin >> expenseDescription;

            while (expenseDescription.empty())
            {
                cout << "Ошибка: поле не может быть пустым. Введите описание расхода: ";
                cin >> expenseDescription;
            }

            cout << "Расход успешно добавлен." << endl;

            break;
        }

        case 3:
        {
            balance = income - expense;

            cout << "Доход: " << income << endl;
            cout << "Расход: " << expense << endl;
            cout << "Текущий баланс: " << balance << endl;

            if (balance > 0)
            {
                cout << "Финансовый результат: доход превышает расходы." << endl;
            }
            else if (balance < 0)
            {
                cout << "Финансовый результат: расходы превышают доход." << endl;
            }
            else
            {
                cout << "Финансовый результат: доходы равны расходам." << endl;
            }

            break;
        }

        case 0:
        {
            cout << "Выход из программы." << endl;

            break;
        }

        default:
        {
            cout << "Ошибка: такого пункта меню не существует." << endl;

            break;
        }
    }

    return 0;
}
