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

    cout << "Система управления персональными финансами" << endl;

    cout << "Введите категорию дохода: ";
    cin >> incomeCategory;

    cout << "Введите сумму дохода: ";
    cin >> income;

    cout << "Введите дату дохода: ";
    cin >> incomeDate;

    cout << "Введите источник дохода: ";
    cin >> incomeSource;

    cout << "Введите категорию расхода: ";
    cin >> expenseCategory;

    cout << "Введите сумму расхода: ";
    cin >> expense;

    cout << "Введите дату расхода: ";
    cin >> expenseDate;

    cout << "Введите описание расхода: ";
    cin >> expenseDescription;

    balance = income - expense;

    cout << endl;
    cout << "Доход: " << income << endl;
    cout << "Расход: " << expense << endl;
    cout << "Текущий баланс: " << balance << endl;

    return 0;
}
