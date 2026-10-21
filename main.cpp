#include <iostream>
#include <string>
#include <iomanip>
#include <clocale>

using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");
    string incomeCategory;
    string incomeDate;
    string incomeSource;

    string expenseCategory;
    string expenseDate;
    string expenseDescription;

    const int SIZE = 100;

    string transactionType[SIZE];
    string transactionCategory[SIZE];
    string transactionDate[SIZE];
    string transactionDescription[SIZE];
    double transactionAmount[SIZE];

    int count = 0;

    double income = 0;
    double expense = 0;
    double balance = 0;

    int choice;

    while (true)
    {
        cout << endl;
        cout << "===== МЕНЮ =====" << endl;
        cout << "1 - Добавить доход" << endl;
        cout << "2 - Добавить расход" << endl;
        cout << "3 - Показать текущий баланс" << endl;
        cout << "4 - Таблица стоимости" << endl;
        cout << "5 - Показать все транзакции" << endl;
        cout << "6 - Поиск транзакций по категории" << endl;
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

                cout << "Введите дату дохода: ";
                cin >> incomeDate;

                cout << "Введите источник дохода: ";
                cin >> incomeSource;

                cout << "Введите сумму дохода: ";
                cin >> income;

                while (cin.fail() || income < 0)
                {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    cout << "Введите корректную сумму дохода: ";
                    cin >> income;
                }

                if (count < SIZE)
                {
                    transactionType[count] = "Доход";
                    transactionCategory[count] = incomeCategory;
                    transactionDate[count] = incomeDate;
                    transactionDescription[count] = incomeSource;
                    transactionAmount[count] = income;

                    count++;

                    cout << "Доход успешно добавлен." << endl;
                }
                else
                {
                    cout << "Массив транзакций заполнен!" << endl;
                }

                break;
            }

            case 2:
            {
                cout << "Введите категорию расхода: ";
                cin >> expenseCategory;

                cout << "Введите дату расхода: ";
                cin >> expenseDate;

                cout << "Введите описание расхода: ";
                cin >> expenseDescription;

                cout << "Введите сумму расхода: ";
                cin >> expense;

                while (cin.fail() || expense < 0)
                {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    cout << "Введите корректную сумму расхода: ";
                    cin >> expense;
                }

                if (count < SIZE)
                {
                    transactionType[count] = "Расход";
                    transactionCategory[count] = expenseCategory;
                    transactionDate[count] = expenseDate;
                    transactionDescription[count] = expenseDescription;
                    transactionAmount[count] = expense;

                    count++;

                    cout << "Расход успешно добавлен." << endl;
                }
                else
                {
                    cout << "Массив транзакций заполнен!" << endl;
                }

                break;
            }

            case 3:
            {
                balance = income - expense;
                cout << endl;
                cout << "===== ФИНАНСОВАЯ СТАТИСТИКА =====" << endl;
                cout << "Доходы: " << income << endl;
                cout << "Расходы: " << expense << endl;
                cout << "Текущий баланс: " << balance << endl;

                if (balance > 0)
                {
                    cout << "Доходы превышают расходы." << endl;
                }
                else if (balance < 0)
                {
                    cout << "Расходы превышают доходы." << endl;
                }
                else
                {
                    cout << "Доходы равны расходам." << endl;
                }

                break;
            }

            case 4:
            {
                double price;
                int maxQuantity;

                cout << "Введите стоимость одной единицы: ";
                cin >> price;

                while (cin.fail() || price < 0)
                {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    cout << "Введите корректную стоимость: ";
                    cin >> price;
                }

                cout << "Введите максимальное количество: ";
                cin >> maxQuantity;

                while (cin.fail() || maxQuantity < 1)
                {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    cout << "Введите положительное количество: ";
                    cin >> maxQuantity;
                }

                cout << endl;
                cout << "===== ТАБЛИЦА СТОИМОСТИ =====" << endl;
                cout << setw(15) << "Количество"
                     << setw(15) << "Стоимость" << endl;

                for (int i = 1; i <= maxQuantity; i++)
                {
                    cout << setw(15) << i
                         << setw(15) << fixed << setprecision(2)
                         << price * i << endl;
                }

                break;
            }

            case 5:
            {
                if (count == 0)
                {
                    cout << "Транзакций пока нет." << endl;
                }
                else
                {
                    cout << endl;
                    cout << "===== ВСЕ ТРАНЗАКЦИИ =====" << endl;

                    for (int i = 0; i < count; i++)
                    {
                        cout << endl;
                        cout << "Транзакция №" << i + 1 << endl;
                        cout << "Тип: " << transactionType[i] << endl;
                        cout << "Категория: "
                             << transactionCategory[i] << endl;
                        cout << "Дата: " << transactionDate[i] << endl;
                        cout << "Описание: "
                             << transactionDescription[i] << endl;
                        cout << "Сумма: " << fixed << setprecision(2)
                             << transactionAmount[i] << endl;
                    }
                }

                break;
            }

            case 6:
            {
                if (count == 0)
                {
                    cout << "Транзакций для поиска нет." << endl;
                    break;
                }

                string searchCategory;
                bool found = false;

                cout << "Введите категорию для поиска: ";
                cin >> searchCategory;

                for (int i = 0; i < count; i++)
                {
                    if (transactionCategory[i] == searchCategory)
                    {
                        cout << endl;
                        cout << "Транзакция №" << i + 1 << endl;
                        cout << "Тип: " << transactionType[i] << endl;
                        cout << "Категория: " << transactionCategory[i] << endl;
                        cout << "Дата: " << transactionDate[i] << endl;
                        cout << "Описание: "
                             << transactionDescription[i] << endl;
                        cout << "Сумма: " << fixed << setprecision(2)
                             << transactionAmount[i] << endl;

                        found = true;
                    }
                }

                if (!found)
                {
                    cout << "Транзакции с такой категорией не найдены."
                         << endl;
                }

                break;
            }

            case 0:
            {
                cout << "Выход из программы." << endl;
                return 0;
            }

            default:
            {
                cout << "Ошибка: такого пункта меню не существует."
                     << endl;
                break;
            }
        }
    }

    return 0;
}
