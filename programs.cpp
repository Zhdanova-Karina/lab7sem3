#pragma warning(disable : 4996)
#define CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale.h>
#include <windows.h>
#include <vector> // для работы с динамическим массивом (вектор)
#include <algorithm> // для сортировки
#include <string>
#include <utility> // Для std::pair

using namespace std;

// Базовый класс
class Dog {
protected:
    string name;

public:
    Dog(const string& name) : name(name) {}
    virtual ~Dog() {}

    string getName() const { return name; }
    virtual void display() const = 0; // Чисто виртуальная функция
};

// Производный класс - Далматинец
class Dalmatian : public Dog {
public:
    Dalmatian(const string& name) : Dog(name) {}

    void display() const override {
        cout << "Далматинец: " << name << endl;
    }
};

// Класс для мест
class Place {
private:
    string name;
    bool hasDalmatian; // Переменная для хранения информации о наличии далматинца

public:
    Place(const string& name, bool hasDalmatian = false) : name(name), hasDalmatian(hasDalmatian) {}

    string getName() const { return name; }
    bool existsDalmatian() const { return hasDalmatian; }

    void setHasDalmatian(bool value) { hasDalmatian = value; }

    void display() const {
        cout << "Место: " << name << endl;
    }
};

// Функция для поиска далматинца по имени и возврат места, где он был найден
pair<Dog*, Place*> findDalmatianByName(const vector<Dog*>& dogs, const string& name, const vector<Place*>& places) {
    for (size_t i = 0; i < dogs.size(); ++i) {
        if (dogs[i]->getName() == name) {
            return make_pair(dogs[i], const_cast<Place*>(places[i])); // Возвращаем далматинца и его место
        }
    }
    return make_pair(nullptr, nullptr); // Не найдено
}

void displayMenu() {
    cout << "\nВыберите действие:\n";
    cout << "1. Показать всех далматинцев\n";
    cout << "2. Поиск далматинца по имени\n";
    cout << "3. Сортировать далматинцев по имени\n";
    cout << "4. Показать все места\n";
    cout << "5. Сортировать места по имени\n";
    cout << "6. Выйти\n";
}

int main() {
    vector<Dog*> dogs;
    vector<Place*> places;
    setlocale(LC_ALL, "RU");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    // Добавление далматинцев и мест в одинаковом количестве
    dogs.push_back(new Dalmatian("Понго"));
    places.push_back(new Place("Стадион", true)); // Место для Понго

    dogs.push_back(new Dalmatian("Патч"));
    places.push_back(new Place("Парк", true)); // Место для Патча

    dogs.push_back(new Dalmatian("Ролли"));
    places.push_back(new Place("Сад", true)); // Место для Ролли

    dogs.push_back(new Dalmatian("Пэдди"));
    places.push_back(new Place("Двор", true)); // Место для Пэдди

    int choice;
    string searchName;

    while (true) {
        displayMenu();
        cout << "Введите номер действия: ";

        // Проверка ввода целого числа
        if (!(cin >> choice)) {
            cout << "Некорректный ввод! Пожалуйста, введите число." << endl;
            cin.clear(); // Сброс статуса потока
            cin.ignore(32767, '\n'); // Игнорировать до следующей строки
            continue; // Перезапустить цикл
        }

        switch (choice) {
        case 1:
            cout << "\nИсходный список далматинцев:" << endl;
            for (const auto& dog : dogs) {
                dog->display();
            }
            break;

        case 2: {
            cout << "\nВведите имя далматинца для поиска: ";
            cin >> searchName;

            pair<Dog*, Place*> result = findDalmatianByName(dogs, searchName, places);
            Dog* foundDog = result.first;
            Place* location = result.second;

            if (foundDog) {
                cout << "Найденный далматинец:" << endl;
                foundDog->display();
                if (location) {
                    cout << "Он был найден в месте: " << location->getName() << endl;
                }
            }
            else {
                cout << "Далматинец с именем " << searchName << " не найден." << endl;
            }
            break;
        }

        case 3:
            sort(dogs.begin(), dogs.end(), [](Dog* a, Dog* b) { return a->getName() < b->getName(); });
            cout << "\nСписок далматинцев отсортирован." << endl;
            break;

        case 4:
            cout << "\nИсходный список мест:" << endl;
            for (const auto& place : places) {
                place->display();
            }
            break;

        case 5:
            sort(places.begin(), places.end(), [](Place* a, Place* b) { return a->getName() < b->getName(); });
            cout << "\nСписок мест отсортирован." << endl;
            break;

        case 6:
            // Освобождение памяти
            for (auto dog : dogs) {
                delete dog;
            }
            for (auto place : places) {
                delete place;
            }
            cout << "Выход из программы." << endl;
            return 0;

        default:
            cout << "Некорректный выбор! Попробуйте снова." << endl;
            break;
        }
    }

    return 0;
}
