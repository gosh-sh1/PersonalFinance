
#include <iostream>
#include <string>
#include <iomanip>
#include <clocale>
#include <fstream>

using namespace std;

const int SIZE = 100;
const int ROWS = 5;
const int COLS = 4;

string transactionType[SIZE];
string transactionCategory[SIZE];
string transactionDate[SIZE];
string transactionDescription[SIZE];
double transactionAmount[SIZE];

int count = 0;

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

// Проверка ввода целого числа
int readInt(string message)
{
    int value;

    cout << message;
    cin >> value;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Некорректный ввод. Повторите: ";
        cin >> value;
    }

    cin.ignore(10000, '\n');

    return value;
}

// Проверка ввода суммы
double readDouble(string message)
{
    double value;

    cout << message;
    cin >> value;

    while (cin.fail() || value < 0)
    {
        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Введите корректную сумму: ";
        cin >> value;
    }

    cin.ignore(10000, '\n');

    return value;
}

// Вывод одной транзакции
void showRecord(int index)
{
    cout << endl;
    cout << "Транзакция №" << index + 1 << endl;
    cout << "Тип: " << transactionType[index] << endl;
    cout << "Категория: " << transactionCategory[index] << endl;
    cout << "Дата: " << transactionDate[index] << endl;
    cout << "Описание: " << transactionDescription[index] << endl;
    cout << "Сумма: " << fixed << setprecision(2)
         << transactionAmount[index] << endl;
}

// Добавление дохода или расхода
void addRecord(string type)
{
    if (count >= SIZE)
    {
        cout << "Массив транзакций заполнен!" << endl;
        return;
    }

    string category;
    string date;
    string description;
    double amount;

    cout << "Введите категорию: ";
    getline(cin, category);

    cout << "Введите дату: ";
    getline(cin, date);

    if (type == "Доход")
    {
        cout << "Введите источник дохода: ";
    }
    else
    {
        cout << "Введите описание расхода: ";
    }

    getline(cin, description);

    amount = readDouble("Введите сумму: ");

    transactionType[count] = type;
    transactionCategory[count] = category;
    transactionDate[count] = date;

    transactionDescription[count] =
        description + " (категория: " + category +
        ", дата: " + date + ")";

    transactionAmount[count] = amount;

    count++;

    cout << type << " успешно добавлен." << endl;
}

// Вывод всех транзакций
void showAll()
{
    if (count == 0)
    {
        cout << "Транзакций пока нет." << endl;
        return;
    }

    cout << endl;
    cout << "===== ВСЕ ТРАНЗАКЦИИ =====" << endl;

    for (int i = 0; i < count; i++)
    {
        showRecord(i);
    }
}

// Поиск транзакций
void findRecord()
{
    if (count == 0)
    {
        cout << "Транзакций для поиска нет." << endl;
        return;
    }

    string searchText;
    bool found = false;

    cout << "Введите часть названия, категории или описания: ";
    getline(cin, searchText);

    for (int i = 0; i < count; i++)
    {
        if (transactionType[i].find(searchText) != string::npos ||
            transactionCategory[i].find(searchText) != string::npos ||
            transactionDescription[i].find(searchText) != string::npos)
        {
            showRecord(i);
            found = true;
        }
    }

    if (!found)
    {
        cout << "Транзакции с таким запросом не найдены." << endl;
    }
}

// Сохранение транзакций в файл
void saveToFile()
{
    ofstream file("transactions.txt");

    if (!file.is_open())
    {
        cout << "Не удалось открыть файл для сохранения." << endl;
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

    cout << "Транзакции успешно сохранены в файл." << endl;
}

// Загрузка транзакций из файла
void loadFromFile()
{
    ifstream file("transactions.txt");

    if (!file.is_open())
    {
        cout << "Файл transactions.txt не найден." << endl;
        return;
    }

    int loadedCount;

    file >> loadedCount;
    file.ignore(10000, '\n');

    if (file.fail() || loadedCount < 0 || loadedCount > SIZE)
    {
        cout << "Некорректные данные в файле." << endl;
        file.close();
        return;
    }

    string newType[SIZE];
    string newCategory[SIZE];
    string newDate[SIZE];
    string newDescription[SIZE];
    double newAmount[SIZE];

    for (int i = 0; i < loadedCount; i++)
    {
        getline(file, newType[i]);
        getline(file, newCategory[i]);
        getline(file, newDate[i]);
        getline(file, newDescription[i]);

        file >> newAmount[i];
        file.ignore(10000, '\n');

        if (file.fail())
        {
            cout << "Ошибка чтения данных из файла." << endl;
            file.close();
            return;
        }
    }

    for (int i = 0; i < loadedCount; i++)
    {
        transactionType[i] = newType[i];
        transactionCategory[i] = newCategory[i];
        transactionDate[i] = newDate[i];
        transactionDescription[i] = newDescription[i];
        transactionAmount[i] = newAmount[i];
    }

    count = loadedCount;

    file.close();

    cout << "Транзакции успешно загружены из файла." << endl;
}

// Расчёт и вывод баланса
void showBalance()
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

    double balance = income - expense;

    cout << endl;
    cout << "===== ФИНАНСОВАЯ СТАТИСТИКА =====" << endl;
    cout << "Доходы: " << fixed << setprecision(2) << income << endl;
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
}

// Таблица стоимости
void showPriceTable()
{
    double price = readDouble("Введите стоимость одной единицы: ");
    int maxQuantity = readInt("Введите максимальное количество: ");

    while (maxQuantity < 1)
    {
        maxQuantity = readInt("Введите положительное количество: ");
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
}

// Ввод матрицы расходов
void inputMatrix()
{
    for (int i = 0; i < ROWS; i++)
    {
        cout << endl;
        cout << "Категория: " << categories[i] << endl;

        for (int j = 0; j < COLS; j++)
        {
            monthlyExpenses[i][j] =
                readDouble("Расходы за месяц " + months[j] + ": ");
        }
    }

    matrixFilled = true;

    cout << "Матрица успешно заполнена." << endl;
}

// Вывод матрицы расходов
void showMatrix()
{
    cout << endl;
    cout << setw(18) << "Категория";

    for (int j = 0; j < COLS; j++)
    {
        cout << setw(12) << months[j];
    }

    cout << endl;

    for (int i = 0; i < ROWS; i++)
    {
        cout << setw(18) << categories[i];

        for (int j = 0; j < COLS; j++)
        {
            cout << setw(12) << fixed << setprecision(2)
                 << monthlyExpenses[i][j];
        }

        cout << endl;
    }
}

// Поиск максимального и минимального расходов
void findMatrixMinMax()
{
    double maximum = monthlyExpenses[0][0];
    double minimum = monthlyExpenses[0][0];

    int maxRow = 0;
    int maxCol = 0;
    int minRow = 0;
    int minCol = 0;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (monthlyExpenses[i][j] > maximum)
            {
                maximum = monthlyExpenses[i][j];
                maxRow = i;
                maxCol = j;
            }

            if (monthlyExpenses[i][j] < minimum)
            {
                minimum = monthlyExpenses[i][j];
                minRow = i;
                minCol = j;
            }
        }
    }

    cout << "Максимальный расход: " << maximum << endl;
    cout << "Категория: " << categories[maxRow] << endl;
    cout << "Месяц: " << months[maxCol] << endl;

    cout << endl;
    cout << "Минимальный расход: " << minimum << endl;
    cout << "Категория: " << categories[minRow] << endl;
    cout << "Месяц: " << months[minCol] << endl;
}

// Суммы по категориям и месяцам
void showMatrixSums()
{
    cout << endl;
    cout << "===== СУММЫ ПО КАТЕГОРИЯМ =====" << endl;

    for (int i = 0; i < ROWS; i++)
    {
        double rowSum = 0;

        for (int j = 0; j < COLS; j++)
        {
            rowSum += monthlyExpenses[i][j];
        }

        cout << categories[i] << ": "
             << fixed << setprecision(2) << rowSum << endl;
    }

    cout << endl;
    cout << "===== СУММЫ ПО МЕСЯЦАМ =====" << endl;

    for (int j = 0; j < COLS; j++)
    {
        double colSum = 0;

        for (int i = 0; i < ROWS; i++)
        {
            colSum += monthlyExpenses[i][j];
        }

        cout << months[j] << ": "
             << fixed << setprecision(2) << colSum << endl;
    }
}

// Изменение элемента матрицы
void editMatrixElement()
{
    cout << "Категории:" << endl;

    for (int i = 0; i < ROWS; i++)
    {
        cout << i + 1 << " - " << categories[i] << endl;
    }

    int row = readInt("Введите номер категории: ");

    while (row < 1 || row > ROWS)
    {
        row = readInt("Введите номер от 1 до 5: ");
    }

    cout << "Месяцы:" << endl;

    for (int j = 0; j < COLS; j++)
    {
        cout << j + 1 << " - " << months[j] << endl;
    }

    int col = readInt("Введите номер месяца: ");

    while (col < 1 || col > COLS)
    {
        col = readInt("Введите номер от 1 до 4: ");
    }

    double newValue = readDouble("Введите новое значение расходов: ");

    monthlyExpenses[row - 1][col - 1] = newValue;

    cout << "Элемент матрицы изменён." << endl;
}

// Меню матрицы расходов
void matrixMenu()
{
    int matrixChoice;

    while (true)
    {
        cout << endl;
        cout << "===== МАТРИЦА РАСХОДОВ =====" << endl;
        cout << "1 - Ввести данные матрицы" << endl;
        cout << "2 - Вывести матрицу" << endl;
        cout << "3 - Найти максимум и минимум" << endl;
        cout << "4 - Суммы по категориям и месяцам" << endl;
        cout << "5 - Изменить элемент матрицы" << endl;
        cout << "0 - Вернуться в главное меню" << endl;

        matrixChoice = readInt("Выберите действие: ");

        if (matrixChoice == 0)
        {
            break;
        }

        if (!matrixFilled && matrixChoice >= 2 && matrixChoice <= 5)
        {
            cout << "Сначала необходимо заполнить матрицу." << endl;
            continue;
        }

        switch (matrixChoice)
        {
            case 1:
                inputMatrix();
                break;

            case 2:
                showMatrix();
                break;

            case 3:
                findMatrixMinMax();
                break;

            case 4:
                showMatrixSums();
                break;

            case 5:
                editMatrixElement();
                break;

            default:
                cout << "Ошибка: такого пункта меню не существует." << endl;
                break;
        }
    }
}

// Вывод главного меню
void showMenu()
{
    cout << endl;
    cout << "===== МЕНЮ =====" << endl;
    cout << "1 - Добавить доход" << endl;
    cout << "2 - Добавить расход" << endl;
    cout << "3 - Показать текущий баланс" << endl;
    cout << "4 - Таблица стоимости" << endl;
    cout << "5 - Показать все транзакции" << endl;
    cout << "6 - Поиск транзакций по категории" << endl;
    cout << "7 - Работа с матрицей расходов" << endl;
    cout << "8 - Сохранить транзакции в файл" << endl;
    cout << "9 - Загрузить транзакции из файла" << endl;
    cout << "0 - Выход" << endl;
}

// Главная функция
int main()
{
    setlocale(LC_ALL, "Russian");

    int choice;

    while (true)
    {
        showMenu();

        choice = readInt("Выберите действие: ");

        switch (choice)
        {
            case 1:
                addRecord("Доход");
                break;

            case 2:
                addRecord("Расход");
                break;

            case 3:
                showBalance();
                break;

            case 4:
                showPriceTable();
                break;

            case 5:
                showAll();
                break;

            case 6:
                findRecord();
                break;

            case 7:
                matrixMenu();
                break;

            case 8:
                saveToFile();
                break;

            case 9:
                loadFromFile();
                break;

            case 0:
                cout << "Выход из программы." << endl;
                return 0;

            default:
                cout << "Ошибка: такого пункта меню не существует." << endl;
                break;
        }
    }

    return 0;
}
