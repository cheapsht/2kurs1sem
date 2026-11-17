#include <memory>
#include <vector>

#include "Author.h"
#include "Publisher.h"
#include "Textbook.h"
#include "FictionBook.h"
#include "LibraryCatalog.h"

int main() {
    Author bulgakov(1, "Михаил Булгаков");
    Author arkady(2, "Аркадий Стругацкий");
    Author boris(3, "Борис Стругацкий");
    Author kolmogorov(4, "Андрей Колмогоров");

    Publisher eksmo("Эксмо");
    Publisher ast("АСТ");
    Publisher prosveshchenie("Просвещение");

    LibraryCatalog catalog;

    catalog.addBook(std::make_unique<FictionBook>(
        "Мастер и Маргарита",
        std::vector<Author>{bulgakov},
        eksmo,
        "Художественная литература",
        "Стеллаж 1, полка 2",
        "Роман"
    ));

    catalog.addBook(std::make_unique<FictionBook>(
        "Пикник на обочине",
        std::vector<Author>{arkady, boris},
        ast,
        "Художественная литература",
        "Стеллаж 1, полка 3",
        "Фантастика"
    ));

    // Состав авторов упрощён для демонстрации.
    catalog.addBook(std::make_unique<Textbook>(
        "Алгебра и начала анализа",
        std::vector<Author>{kolmogorov},
        prosveshchenie,
        "Математика",
        "Стеллаж 2, полка 1",
        "Алгебра"
    ));

    const auto allBooks = catalog.getBooks();

    const auto byTitle =
        catalog.findByTitle("Мастер и Маргарита");

    const auto byAuthor =
        catalog.findByAuthor(boris.getId());

    const auto byTopic =
        catalog.findByTopic("Математика");

    const auto byPublisher =
        catalog.findByPublisher("АСТ");

    return 0;
}
