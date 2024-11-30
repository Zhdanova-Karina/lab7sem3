import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;

abstract class Dog {
    protected String name;

    public Dog(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public abstract void display();
}

class Dalmatian extends Dog {
    public Dalmatian(String name) {
        super(name);
    }

    @Override
    public void display() {
        System.out.println("Далматинец: " + name);
    }
}

class Place {
    private String name;
    private boolean hasDalmatian; // Переменная для хранения информации о наличии далматинца

    public Place(String name, boolean hasDalmatian) {
        this.name = name;
        this.hasDalmatian = hasDalmatian;
    }

    public String getName() {
        return name;
    }

    public boolean existsDalmatian() {
        return hasDalmatian;
    }

    public void setHasDalmatian(boolean value) {
        hasDalmatian = value;
    }

    public void display() {
        System.out.println("Место: " + name);
    }
}

class Main {
    public static void main(String[] args) {
        List<Dog> dogs = new ArrayList<>();
        List<Place> places = new ArrayList<>();
        Scanner scanner = new Scanner(System.in);

        dogs.add(new Dalmatian("Понго"));
        places.add(new Place("Стадион", true));

        dogs.add(new Dalmatian("Патч"));
        places.add(new Place("Парк", true));

        dogs.add(new Dalmatian("Ролли"));
        places.add(new Place("Сад", true));

        dogs.add(new Dalmatian("Пэдди"));
        places.add(new Place("Двор", true));

        while (true) {
            displayMenu();
            System.out.print("Введите номер действия: ");

            int choice;
            if (scanner.hasNextInt()) {
                choice = scanner.nextInt();
            } else {
                System.out.println("Некорректный ввод! Пожалуйста, введите число.");
                scanner.nextLine(); // Чистим поток ввода
                continue;
            }

            switch (choice) {
                case 1:
                    System.out.println("\nИсходный список далматинцев:");
                    for (Dog dog : dogs) {
                        dog.display();
                    }
                    break;

                case 2:
                    System.out.print("\nВведите имя далматинца для поиска: ");
                    String searchName = scanner.next();
                    findDalmatianByName(dogs, searchName, places);
                    break;

                case 3:
                    dogs.sort(Comparator.comparing(Dog::getName));
                    System.out.println("\nСписок далматинцев отсортирован.");
                    break;

                case 4:
                    System.out.println("\nИсходный список мест:");
                    for (Place place : places) {
                        place.display();
                    }
                    break;

                case 5:
                    places.sort(Comparator.comparing(Place::getName));
                    System.out.println("\nСписок мест отсортирован.");
                    break;

                case 6:
                    System.out.println("Выход из программы.");
                    scanner.close();
                    return;

                default:
                    System.out.println("Некорректный выбор! Попробуйте снова.");
                    break;
            }
        }
    }

    private static void displayMenu() {
        System.out.println("\nВыберите действие:");
        System.out.println("1. Показать всех далматинцев");
        System.out.println("2. Поиск далматинца по имени");
        System.out.println("3. Сортировать далматинцев по имени");
        System.out.println("4. Показать все места");
        System.out.println("5. Сортировать места по имени");
        System.out.println("6. Выйти");
    }

    private static void findDalmatianByName(List<Dog> dogs, String name, List<Place> places) {
        for (int i = 0; i < dogs.size(); i++) {
            if (dogs.get(i).getName().equals(name)) {
                System.out.println("Найденный далматинец:");
                dogs.get(i).display();
                System.out.println("Он был найден в месте: " + places.get(i).getName());
                return;
            }
        }
        System.out.println("Далматинец с именем " + name + " не найден.");
    }
}
