#include <iostream>
#include <string>
#include <vector>

class Book {
protected:
    std::string title;
    std::string author;
    int year;
    bool rented;
    int rentalDuration;

public:
    Book(std::string t, std::string a, int y, bool r) : title(t), author(a), year(y), rented(r) {}

    virtual void displayInfo() const = 0;

    std::string getTitle() const {
        return title;
    }
    bool isRented() const {
        return rented;
    }

    void setRented(bool isRented) {
        rented = isRented;
    }
    int getRentalDuration() const {
        return rentalDuration;
    }

    void setRentalDuration(int duration) {
        rentalDuration = duration;
    }
};

class ForeignLiterature : public Book {
private:
    std::string country;

public:
    ForeignLiterature(std::string t, std::string a, int y, std::string c, bool r) : Book(t, a, y, r), country(c) {}

    void displayInfo() const override {
        std::cout << "Название книги: " << title << ", Автор: " << author << ", Год: " << year << ", Страна: " << country << ", Арендована: " << rented << std::endl;
    }
};

class RussianLiterature : public Book {
public:
    RussianLiterature(std::string t, std::string a, int y, bool r) : Book(t, a, y, r) {}

    void displayInfo() const override {
        std::cout << "Название книги: " << title << ", Автор: " << author << ", Год: " << year << ", Арендована: " << rented << std::endl;
    }
};

class Library {
private:
    std::vector<Book*> books;

public:
    void addBook(Book* book) {
        books.push_back(book);
    }

    void editBook(int index, Book* newBook) {
        if (index >= 0 && index < books.size()) {
            books[index] = newBook;
        }
    }

    void removeBook(Book* book) {
        auto it = std::find(books.begin(), books.end(), book);
        if (it != books.end()) {
            books.erase(it);
        }
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book->displayInfo();
        }
    }

    void rentBook(const std::string& title, int duration) {
        for (auto& book : books) {
            if (book->getTitle() == title) {
                if (!book->isRented()) {
                    book->setRented(true);
                    book->setRentalDuration(duration);
                    std::cout << "Книга '" << title << "' арендована на " << duration << " дней." << std::endl;
                }
                else {
                    std::cout << "Извините, книга '" << title << "' уже арендована." << std::endl;
                }
                return;
            }
        }
        std::cout << "Книга '" << title << "' не найдена в библиотеке." << std::endl;
    }

    void displayRentedBooks() const {
        bool foundRented = false;
        for (const auto& book : books) {
            if (book->isRented()) {
                book->displayInfo();
                foundRented = true;
            }
        }
        if (!foundRented) {
            std::cout << "Ни одной книги еще не арендовано." << std::endl;
        }
    }

    void returnBook(const std::string& title) {
        for (auto& book : books) {
            if (book->getTitle() == title && book->isRented()) {
                book->setRented(false);
                book->setRentalDuration(0);
                std::cout << "Книга '" << title << "' успешно возвращена." << std::endl;
                return;
            }
        }
        std::cout << "Книга '" << title << "' не найдена или не арендована." << std::endl;
    }
};

int main() {
    setlocale(LC_ALL, "Rus");
        Library library;

        ForeignLiterature book1("1984", "Джордж Оруэлл", 1949, "Британия", false);
        RussianLiterature book2("Война и мир", "Лев Толстой", 1869, false);

        library.addBook(&book1);
        library.addBook(&book2);
        int choice;
        std::string title;
        int duration;
    do {

        std::cout << "\nМеню библиотеки:\n";
        std::cout << "1. Показать все книги\n";
        std::cout << "2. Арендовать книгу\n";
        std::cout << "3. Вернуть книгу\n";
        std::cout << "4. Показать арендованные книги\n";
        std::cout << "5. выход\n";
        std::cout << "Введите опцию: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "\nВсе книги в библиотеке:\n";
            library.displayAllBooks();
            break;
        case 2:
            std::cout << "\nВведите название книги, которую вы хотите арендовать: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            std::cout << "Введите количество дней, на которое вы хотите арендовать книгу: ";
            std::cin >> duration;
            library.rentBook(title, duration);
            break;
        case 3:
            std::cout << "\nВведите название книги, которую вы хотите вернуть: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            library.returnBook(title);
            break;
        case 4:
            std::cout << "\nАрендованные книги:\n";
            library.displayRentedBooks();
            break;
        case 5:
            std::cout << "Выход из программы...\n";
            break;
        default:
            std::cout << "Неправильный выбор\n";
            break;
        }
    } while (choice != 5);

    return 0;
}