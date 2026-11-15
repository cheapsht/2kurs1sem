#include "LibraryCatalog.h"

int main() {
    LibraryCatalog catalog;

    catalog.addAuthor(Author(1, "Михаил Булгаков"));
    catalog.addAuthor(Author(2, "Аркадий Стругацкий"));
    catalog.addAuthor(Author(3, "Борис Стругацкий"));
    catalog.addAuthor(Author(4, "Андрей Колмогоров"));

    catalog.addPublisher(Publisher(10, "Эксмо"));
    catalog.addPublisher(Publisher(20, "АСТ"));
    catalog.addPublisher(Publisher(30, "Просвещение"));

    catalog.addFictionBook(FictionBook(
        101,
        "Мастер и Маргарита",
        {1},
        10,
        "Художественная литература",
        "Стеллаж 1, полка 2",
        "Роман"
    ));

    catalog.addFictionBook(FictionBook(
        102,
        "Пикник на обочине",
        {2, 3},
        20,
        "Художественная литература",
        "Стеллаж 1, полка 3",
        "Фантастика"
    ));

    // Состав авторов учебника упрощён для демонстрации.
    catalog.addTextbook(Textbook(
        103,
        "Алгебра и начала анализа",
        {4},
        30,
        "Математика",
        "Стеллаж 2, полка 1",
        "Алгебра"
    ));

    const Book& book = catalog.findBookById(102);
    const Author& author = catalog.findAuthorById(3);

    const auto byTitle =
        catalog.findByTitle("Мастер и Маргарита");

    const auto byAuthor = catalog.findByAuthor(3);
    const auto byTopic = catalog.findByTopic("Математика");
    const auto byPublisher = catalog.findByPublisher("АСТ");

    const auto location = catalog.getLocation(102);
    const auto info = catalog.getBookInfo(102);

    // Переменные можно просмотреть в отладчике.
    (void)book;
    (void)author;
    (void)byTitle;
    (void)byAuthor;
    (void)byTopic;
    (void)byPublisher;
    (void)location;
    (void)info;

    return 0;
}
