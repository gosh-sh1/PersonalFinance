#include <iostream>
#include <string>
#include <iomanip>
#include <clocale>
#include <fstream>

using namespace std;

const int SIZE = 100;
const int ROWS = 5;
const int COLS = 4;

// Проверка ввода целого числа
int readInt(const string& message)
{
    int number;

    cout << message;
    cin >> number;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Ошибка! Введите целое число: ";
        cin >> number;
    }

    return number;
}

// Проверка ввода вещественного числа
double readDouble(const string& message)
{
    double number;

    cout << message;
    cin >> number;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Ошибка! Введите число: ";
        cin >> number;
    }

    return number;
}

// Вывод одной транзакции
void showRecord(
    int index,
    const string (&transactionType)[SIZE],
    const string (&transactionCategory)[SIZE],
    const string (&transactionDate)[SIZE],
    const string (&transactionDescription)[SIZE],
    const double (&transactionAmount)[SIZE])
{
    cout << "\nТранзакция №" << index + 1 << endl;
    cout << "Тип: " << transactionType[index] << endl;
    cout << "Категория: " << transactionCategory[index] << endl;
    cout << "Дата: " << transactionDate[index] << endl;
    cout << "Описание: " << transactionDescription[index] << endl;
    cout << "Сумма: " << fixed << setprecision(2)
         << transactionAmount[index] << endl;
}

// Добавление транзакции
void addRecord(
    const string& type,
    string (&transactionType)[SIZE],
    string (&transactionCategory)[SIZE],
    string (&transactionDate)[SIZE],
    string (&transactionDescription)[SIZE],
    double (&transactionAmount)[SIZE],
    long long& count)
{
    if (count >= SIZE)
    {
        cout << "Достигнуто максимальное количество транзакций!" << endl;
        return;
    }

    transactionType[count] = type;

    cin.ignore(10000, '\n');

    cout << "Введите категорию: ";
    getline(cin, transactionCategory[count]);

    cout << "Введите дату: ";
    getline(cin, transactionDate[count]);

    cout << "Введите описание: ";
    getline(cin, transactionDescription[count]);

    transactionAmount[count] = readDouble("Введите сумму: ");

    if (transactionAmount[count] < 0)
    {
        cout << "Сумма не может быть отрицательной!" << endl;
        return;
    }

    count++;

    cout << "Транзакция успешно добавлена!" << endl;
}

// Вывод всех транзакций с использованием арифметики указателей
void showAll(
    const string (&transactionType)[SIZE],
    const string (&transactionCategory)[SIZE],
    const string (&transactionDate)[SIZE],
    const string (&transactionDescription)[SIZE],
    const double (&transactionAmount)[SIZE],
    long long count)
{
    if (count == 0)
    {
        cout << "Список транзакций пуст!" << endl;
        return;
    }

    const string* typePtr = transactionType;
    const string* categoryPtr = transactionCategory;
    const string* datePtr = transactionDate;
    const string* descriptionPtr = transactionDescription;
    const double* amountPtr = transactionAmount;

    for (int i = 0; i < count; i++)
    {
        cout << "\nТранзакция №" << i + 1 << endl;
        cout << "Тип: " << *typePtr << endl;
        cout << "Категория: " << *categoryPtr << endl;
        cout << "Дата: " << *datePtr << endl;
        cout << "Описание: " << *descriptionPtr << endl;
        cout << "Сумма: " << fixed << setprecision(2)
             << *amountPtr << endl;

        typePtr++;
        categoryPtr++;
        datePtr++;
        descriptionPtr++;
        amountPtr++;
    }
}

// Поиск транзакции с возвратом указателя на найденную сумму
double* findRecord(
    string (&transactionType)[SIZE],
    string (&transactionCategory)[SIZE],
    string (&transactionDate)[SIZE],
    string (&transactionDescription)[SIZE],
    double (&transactionAmount)[SIZE],
    long long count)
{
    if (count == 0)
    {
        cout << "Список транзакций пуст!" << endl;
        return nullptr;
    }

    string searchText;

    cin.ignore(10000, '\n');

    cout << "Введите текст для поиска: ";
    getline(cin, searchText);

    string* typePtr = transactionType;
    string* categoryPtr = transactionCategory;
    string* datePtr = transactionDate;
    string* descriptionPtr = transactionDescription;
    double* amountPtr = transactionAmount;

    for (int i = 0; i < count; i++)
    {
        if (typePtr->find(searchText) != string::npos ||
            categoryPtr->find(searchText) != string::npos ||
            datePtr->find(searchText) != string::npos ||
            descriptionPtr->find(searchText) != string::npos)
        {
            cout << "\nНайдена транзакция!" << endl;
            cout << "Тип: " << *typePtr << endl;
            cout << "Категория: " << *categoryPtr << endl;
            cout << "Дата: " << *datePtr << endl;
            cout << "Описание: " << *descriptionPtr << endl;
            cout << "Сумма: " << fixed << setprecision(2)
                 << *amountPtr << endl;

            return amountPtr;
        }

        typePtr++;
        categoryPtr++;
        datePtr++;
        descriptionPtr++;
        amountPtr++;
    }

    cout << "Транзакция не найдена!" << endl;

    return nullptr;
}

// Сохранение транзакций в файл
void saveToFile(
    const string (&transactionType)[SIZE],
    const string (&transactionCategory)[SIZE],
    const string (&transactionDate)[SIZE],
    const string (&transactionDescription)[SIZE],
    const double (&transactionAmount)[SIZE],
    long long count)
{
    ofstream file("transactions.txt");

    if (!file.is_open())
    {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }

    file << count << endl;

    for (int i = 0; i < count; i++)
    {
        file << transactionType[i] << endl;
        file << transactionCategory[i] << endl;
        file << transactionDate[i] << endl;
        file << transactionDescription[i] << endl;
        file << transactionAmount[i] << endl;
    }

    file.close();

    cout << "Данные успешно сохранены!" << endl;
}

// Загрузка транзакций из файла
void loadFromFile(
    string (&transactionType)[SIZE],
    string (&transactionCategory)[SIZE],
    string (&transactionDate)[SIZE],
    string (&transactionDescription)[SIZE],
    double (&transactionAmount)[SIZE],
    long long& count)
{
    ifstream file("transactions.txt");

    if (!file.is_open())
    {
        cout << "Файл не найден!" << endl;
        return;
    }

    long long loadedCount;

    file >> loadedCount;
    file.ignore(10000, '\n');

    if (file.fail() || loadedCount < 0 || loadedCount > SIZE)
    {
        cout << "Ошибка чтения файла!" << endl;
        return;
    }

    count = 0;

    for (int i = 0; i < loadedCount; i++)
    {
        getline(file, transactionType[i]);
        getline(file, transactionCategory[i]);
        getline(file, transactionDate[i]);
        getline(file, transactionDescription[i]);

        file >> transactionAmount[i];
        file.ignore(10000, '\n');

        if (file.fail())
        {
            cout << "Ошибка чтения данных!" << endl;
            break;
        }

        count++;
    }

    file.close();

    cout << "Загружено транзакций: " << count << endl;
}

// Вывод баланса
void showBalance(
    const string (&transactionType)[SIZE],
    const double (&transactionAmount)[SIZE],
    long long count)
{
    double income = 0;
    double expense = 0;

    for (int i = 0; i < count; i++)
    {
        if (transactionType[i] == "Доход")
        {
            income += transactionAmount[i];
        }
        else if (transactionType[i] == "Расход")
        {
            expense += transactionAmount[i];
        }
    }

    cout << "\nОбщая сумма доходов: "
         << fixed << setprecision(2) << income << endl;

    cout << "Общая сумма расходов: " << expense << endl;

    cout << "Текущий баланс: " << income - expense << endl;
}

// Таблица стоимости
void showPriceTable()
{
    string products[] = {
        "Продукты",
        "Транспорт",
        "Жилье",
        "Развлечения",
        "Прочее"
    };

    double prices[] = {
        5000,
        2000,
        15000,
        3000,
        1000
    };

    cout << "\nТаблица примерных расходов" << endl;
    cout << "-----------------------------------" << endl;
    cout << left << setw(20) << "Категория"
         << "Сумма" << endl;

    for (int i = 0; i < 5; i++)
    {
        cout << left << setw(20) << products[i]
             << fixed << setprecision(2) << prices[i] << endl;
    }
}

// Ввод матрицы расходов
void inputMatrix(
    double (&monthlyExpenses)[ROWS][COLS],
    const string (&categories)[ROWS],
    const string (&months)[12])
{
    cout << "\nВведите расходы по категориям за 4 месяца." << endl;

    for (int i = 0; i < ROWS; i++)
    {
        cout << "\nКатегория: " << categories[i] << endl;

        for (int j = 0; j < COLS; j++)
        {
            monthlyExpenses[i][j] = readDouble(
                "Введите расходы за " + months[j] + ": "
            );
        }
    }

    cout << "Матрица расходов заполнена!" << endl;
}

// Вывод матрицы
void showMatrix(
    const double (&monthlyExpenses)[ROWS][COLS],
    const string (&categories)[ROWS],
    const string (&months)[12])
{
    cout << "\nМатрица расходов" << endl;

    cout << left << setw(20) << "Категория";

    for (int j = 0; j < COLS; j++)
    {
        cout << setw(15) << months[j];
    }

    cout << endl;

    for (int i = 0; i < ROWS; i++)
    {
        cout << left << setw(20) << categories[i];

        for (int j = 0; j < COLS; j++)
        {
            cout << setw(15) << fixed << setprecision(2)
                 << monthlyExpenses[i][j];
        }

        cout << endl;
    }
}

// Поиск минимального и максимального элементов матрицы
void findMatrixMinMax(
    const double (&monthlyExpenses)[ROWS][COLS],
    const string (&categories)[ROWS],
    const string (&months)[12])
{
    double minValue = monthlyExpenses[0][0];
    double maxValue = monthlyExpenses[0][0];

    int minRow = 0;
    int minCol = 0;
    int maxRow = 0;
    int maxCol = 0;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (monthlyExpenses[i][j] < minValue)
            {
                minValue = monthlyExpenses[i][j];
                minRow = i;
                minCol = j;
            }

            if (monthlyExpenses[i][j] > maxValue)
            {
                maxValue = monthlyExpenses[i][j];
                maxRow = i;
                maxCol = j;
            }
        }
    }

    cout << "\nМинимальный расход: " << minValue << endl;
    cout << "Категория: " << categories[minRow] << endl;
    cout << "Месяц: " << months[minCol] << endl;

    cout << "\nМаксимальный расход: " << maxValue << endl;
    cout << "Категория: " << categories[maxRow] << endl;
    cout << "Месяц: " << months[maxCol] << endl;
}

// Суммы расходов по строкам и столбцам
void showMatrixSums(
    const double (&monthlyExpenses)[ROWS][COLS],
    const string (&categories)[ROWS],
    const string (&months)[12])
{
    cout << "\nСуммы расходов по категориям:" << endl;

    for (int i = 0; i < ROWS; i++)
    {
        double sum = 0;

        for (int j = 0; j < COLS; j++)
        {
            sum += monthlyExpenses[i][j];
        }

        cout << categories[i] << ": " << sum << endl;
    }

    cout << "\nСуммы расходов по месяцам:" << endl;

    for (int j = 0; j < COLS; j++)
    {
        double sum = 0;

        for (int i = 0; i < ROWS; i++)
        {
            sum += monthlyExpenses[i][j];
        }

        cout << months[j] << ": " << sum << endl;
    }
}

// Редактирование элемента матрицы
void editMatrixElement(double (&monthlyExpenses)[ROWS][COLS])
{
    int row = readInt("Введите номер строки (1-5): ");
    int col = readInt("Введите номер столбца (1-4): ");

    if (row < 1 || row > ROWS || col < 1 || col > COLS)
    {
        cout << "Неверные координаты!" << endl;
        return;
    }

    monthlyExpenses[row - 1][col - 1] =
        readDouble("Введите новое значение: ");

    cout << "Элемент успешно изменен!" << endl;
}

// Меню работы с матрицей
void matrixMenu(
    double (&monthlyExpenses)[ROWS][COLS],
    const string (&categories)[ROWS],
    const string (&months)[12],
    bool& matrixFilled)
{
    int choice;

    do
    {
        cout << "\n===== МЕНЮ МАТРИЦЫ =====" << endl;
        cout << "1. Заполнить матрицу" << endl;
        cout << "2. Вывести матрицу" << endl;
        cout << "3. Найти минимум и максимум" << endl;
        cout << "4. Суммы по строкам и столбцам" << endl;
        cout << "5. Изменить элемент" << endl;
        cout << "0. Назад" << endl;

        choice = readInt("Выберите действие: ");

        switch (choice)
        {
        case 1:
            inputMatrix(monthlyExpenses, categories, months);
            matrixFilled = true;
            break;

        case 2:
            if (matrixFilled)
            {
                showMatrix(monthlyExpenses, categories, months);
            }
            else
            {
                cout << "Сначала заполните матрицу!" << endl;
            }
            break;

        case 3:
            if (matrixFilled)
            {
                findMatrixMinMax(monthlyExpenses, categories, months);
            }
            else
            {
                cout << "Сначала заполните матрицу!" << endl;
            }
            break;

        case 4:
            if (matrixFilled)
            {
                showMatrixSums(monthlyExpenses, categories, months);
            }
            else
            {
                cout << "Сначала заполните матрицу!" << endl;
            }
            break;

        case 5:
            if (matrixFilled)
            {
                editMatrixElement(monthlyExpenses);
            }
            else
            {
                cout << "Сначала заполните матрицу!" << endl;
            }
            break;

        case 0:
            cout << "Возврат в главное меню." << endl;
            break;

        default:
            cout << "Неверный пункт меню!" << endl;
        }

    } while (choice != 0);
}

// Обмен двух транзакций
void swap(
    int first,
    int second,
    string (&transactionType)[SIZE],
    string (&transactionCategory)[SIZE],
    string (&transactionDate)[SIZE],
    string (&transactionDescription)[SIZE],
    double (&transactionAmount)[SIZE])
{
    string tempString;
    double tempAmount;

    tempString = transactionType[first];
    transactionType[first] = transactionType[second];
    transactionType[second] = tempString;

    tempString = transactionCategory[first];
    transactionCategory[first] = transactionCategory[second];
    transactionCategory[second] = tempString;

    tempString = transactionDate[first];
    transactionDate[first] = transactionDate[second];
    transactionDate[second] = tempString;

    tempString = transactionDescription[first];
    transactionDescription[first] = transactionDescription[second];
    transactionDescription[second] = tempString;

    tempAmount = transactionAmount[first];
    transactionAmount[first] = transactionAmount[second];
    transactionAmount[second] = tempAmount;
}

// Сортировка транзакций по сумме
void sortRecords(
    string (&transactionType)[SIZE],
    string (&transactionCategory)[SIZE],
    string (&transactionDate)[SIZE],
    string (&transactionDescription)[SIZE],
    double (&transactionAmount)[SIZE],
    long long count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (transactionAmount[j] > transactionAmount[j + 1])
            {
                swap(
                    j,
                    j + 1,
                    transactionType,
                    transactionCategory,
                    transactionDate,
                    transactionDescription,
                    transactionAmount
                );
            }
        }
    }

    cout << "Транзакции отсортированы по сумме!" << endl;
}

// Главное меню
void showMenu()
{
    cout << "\n========== PERSONAL FINANCE ==========" << endl;
    cout << "1. Добавить доход" << endl;
    cout << "2. Добавить расход" << endl;
    cout << "3. Показать баланс" << endl;
    cout << "4. Таблица стоимости" << endl;
    cout << "5. Показать все транзакции" << endl;
    cout << "6. Найти транзакцию" << endl;
    cout << "7. Работа с матрицей расходов" << endl;
    cout << "8. Сохранить данные в файл" << endl;
    cout << "9. Загрузить данные из файла" << endl;
    cout << "10. Сортировать транзакции" << endl;
    cout << "0. Выход" << endl;
    cout << "======================================" << endl;
}

// Главная функция
int main()
{
    setlocale(LC_ALL, "Russian");

    string transactionType[SIZE];
    string transactionCategory[SIZE];
    string transactionDate[SIZE];
    string transactionDescription[SIZE];
    double transactionAmount[SIZE];

    long long count = 0;

    string categories[ROWS] = {
        "Продукты",
        "Транспорт",
        "Жилье",
        "Развлечения",
        "Прочее"
    };

    string months[12] = {
        "Январь",
        "Февраль",
        "Март",
        "Апрель",
        "Май",
        "Июнь",
        "Июль",
        "Август",
        "Сентябрь",
        "Октябрь",
        "Ноябрь",
        "Декабрь"
    };

    double monthlyExpenses[ROWS][COLS] = {};
    bool matrixFilled = false;

    // Указатели на основные массивы и переменные
    string (*typePtr)[SIZE] = &transactionType;
    string (*categoryPtr)[SIZE] = &transactionCategory;
    string (*datePtr)[SIZE] = &transactionDate;
    string (*descriptionPtr)[SIZE] = &transactionDescription;
    double (*amountPtr)[SIZE] = &transactionAmount;

    long long* countPtr = &count;

    double (*matrixPtr)[ROWS][COLS] = &monthlyExpenses;
    bool* matrixFilledPtr = &matrixFilled;

    int choice;

    do
    {
        showMenu();

        choice = readInt("Выберите пункт меню: ");

        switch (choice)
        {
        case 1:
            addRecord(
                "Доход",
                *typePtr,
                *categoryPtr,
                *datePtr,
                *descriptionPtr,
                *amountPtr,
                *countPtr
            );
            break;

        case 2:
            addRecord(
                "Расход",
                *typePtr,
                *categoryPtr,
                *datePtr,
                *descriptionPtr,
                *amountPtr,
                *countPtr
            );
            break;

        case 3:
            showBalance(*typePtr, *amountPtr, *countPtr);
            break;

        case 4:
            showPriceTable();
            break;

        case 5:
            showAll(
                *typePtr,
                *categoryPtr,
                *datePtr,
                *descriptionPtr,
                *amountPtr,
                *countPtr
            );
            break;

        case 6:
        {
            double* foundAmount = findRecord(
                *typePtr,
                *categoryPtr,
                *datePtr,
                *descriptionPtr,
                *amountPtr,
                *countPtr
            );

            if (foundAmount != nullptr)
            {
                // Разыменование указателя
                cout << "\nНайденная сумма через указатель: "
                     << *foundAmount << endl;

                // Получение индекса через разность указателей
                int index = foundAmount - *amountPtr;

                cout << "Номер элемента массива: " << index + 1 << endl;

                showRecord(
                    index,
                    *typePtr,
                    *categoryPtr,
                    *datePtr,
                    *descriptionPtr,
                    *amountPtr
                );
            }

            break;
        }

        case 7:
            matrixMenu(
                *matrixPtr,
                categories,
                months,
                *matrixFilledPtr
            );
            break;

        case 8:
            saveToFile(
                *typePtr,
                *categoryPtr,
                *datePtr,
                *descriptionPtr,
                *amountPtr,
                *countPtr
            );
            break;

        case 9:
            loadFromFile(
                *typePtr,
                *categoryPtr,
                *datePtr,
                *descriptionPtr,
                *amountPtr,
                *countPtr
            );
            break;

        case 10:
            sortRecords(
                *typePtr,
                *categoryPtr,
                *datePtr,
                *descriptionPtr,
                *amountPtr,
                *countPtr
            );
            break;

        case 0:
            cout << "Программа завершена." << endl;
            break;

        default:
            cout << "Неверный пункт меню! Попробуйте снова." << endl;
        }

    } while (choice != 0);

    return 0;
}
