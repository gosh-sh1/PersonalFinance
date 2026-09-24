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

    if (income >= 0 && expense >= 0)
    {
        balance = income - expense;

        cout << endl;
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
    }
    else
    {
        cout << "Ошибка: доход и расход не могут быть отрицательными." << endl;
    }

    return 0;
}
