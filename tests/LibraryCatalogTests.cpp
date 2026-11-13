#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include "Author.h"
#include "Publisher.h"
#include "Textbook.h"
#include "FictionBook.h"
#include "LibraryCatalog.h"

/**
 * @brief Создаёт заполненный каталог перед каждым тестом TEST_F.
 */
class LibraryCatalogTests : public ::testing::Test {
protected:
    LibraryCatalog catalog;

    void SetUp() override {
        catalog.addBook(std::make_unique<FictionBook>(
            "Мастер и Маргарита",
            std::vector<Author>{
                Author(1, "Михаил Булгаков")
            },
            Publisher("Эксмо"),
            "Художественная литература",
            "Стеллаж 1, полка 2",
            "Роман"
        ));

        catalog.addBook(std::make_unique<FictionBook>(
            "Пикник на обочине",
            std::vector<Author>{
                Author(2, "Аркадий Стругацкий"),
                Author(3, "Борис Стругацкий")
            },
            Publisher("АСТ"),
            "Художественная литература",
            "Стеллаж 1, полка 3",
            "Фантастика"
        ));

        catalog.addBook(std::make_unique<Textbook>(
            "Алгебра и начала анализа",
            std::vector<Author>{
                Author(4, "Андрей Колмогоров")
            },
            Publisher("Просвещение"),
            "Математика",
            "Стеллаж 2, полка 1",
            "Алгебра"
        ));
    }
};

// ---------- addBook ----------

TEST_F(LibraryCatalogTests, AddBookIncreasesSize) {
    catalog.addBook(std::make_unique<FictionBook>(
        "Новая книга",
        std::vector<Author>{Author(5, "Новый автор")},
        Publisher("Эксмо"),
        "Литература",
        "Полка 4",
        "Рассказ"
    ));

    const auto books = catalog.getBooks();

    ASSERT_EQ(books.size(), 4u);
    ASSERT_EQ(books.back()->getTitle(), "Новая книга");
}

TEST_F(LibraryCatalogTests, AddBookTransfersOwnership) {
    std::unique_ptr<Book> book = std::make_unique<Textbook>(
        "Физика",
        std::vector<Author>{Author(5, "Автор учебника")},
        Publisher("Просвещение"),
        "Физика",
        "Полка 5",
        "Физика"
    );

    const Book* original = book.get();

    catalog.addBook(std::move(book));

    ASSERT_EQ(book.get(), nullptr);

    const auto found = catalog.findByTitle("Физика");

    ASSERT_EQ(found.size(), 1u);
    ASSERT_EQ(found[0], original);
}

TEST_F(LibraryCatalogTests, AddNullBookThrows) {
    const auto sizeBefore = catalog.getBooks().size();

    ASSERT_THROW(
        catalog.addBook(std::unique_ptr<Book>{}),
        std::invalid_argument
    );

    ASSERT_EQ(catalog.getBooks().size(), sizeBefore);
}

// ---------- getBooks ----------

TEST_F(LibraryCatalogTests, GetBooksReturnsAllBooks) {
    const auto books = catalog.getBooks();

    ASSERT_EQ(books.size(), 3u);
    ASSERT_NE(books[0], nullptr);
    ASSERT_NE(books[1], nullptr);
    ASSERT_NE(books[2], nullptr);

    ASSERT_EQ(books[0]->getTitle(), "Мастер и Маргарита");
    ASSERT_EQ(books[1]->getTitle(), "Пикник на обочине");
    ASSERT_EQ(books[2]->getTitle(), "Алгебра и начала анализа");
}

TEST_F(LibraryCatalogTests, ChangingResultDoesNotChangeCatalog) {
    auto books = catalog.getBooks();
    books.clear();

    ASSERT_TRUE(books.empty());
    ASSERT_EQ(catalog.getBooks().size(), 3u);
}

// ---------- findByTitle ----------

TEST_F(LibraryCatalogTests, FindByTitleReturnsMatchingBook) {
    const auto found =
        catalog.findByTitle("Мастер и Маргарита");

    ASSERT_EQ(found.size(), 1u);
    ASSERT_EQ(found[0]->getTitle(), "Мастер и Маргарита");
    ASSERT_EQ(found[0]->getLocation(), "Стеллаж 1, полка 2");
}

TEST_F(LibraryCatalogTests, FindByTitleReturnsAllMatches) {
    catalog.addBook(std::make_unique<FictionBook>(
        "Мастер и Маргарита",
        std::vector<Author>{Author(1, "Михаил Булгаков")},
        Publisher("АСТ"),
        "Художественная литература",
        "Полка 10",
        "Роман"
    ));

    const auto found =
        catalog.findByTitle("Мастер и Маргарита");

    ASSERT_EQ(found.size(), 2u);
    ASSERT_EQ(found[0]->getPublisher().getName(), "Эксмо");
    ASSERT_EQ(found[1]->getPublisher().getName(), "АСТ");
}

TEST_F(LibraryCatalogTests, FindByTitleReturnsEmptyForUnknownTitle) {
    ASSERT_TRUE(catalog.findByTitle("Неизвестная книга").empty());
}

TEST_F(LibraryCatalogTests, FindByTitleRequiresExactMatch) {
    ASSERT_TRUE(catalog.findByTitle("Мастер").empty());
    ASSERT_TRUE(catalog.findByTitle("мастер и маргарита").empty());
}

// ---------- findByAuthor ----------

TEST_F(LibraryCatalogTests, FindByAuthorFindsSingleAuthorBook) {
    const auto found = catalog.findByAuthor(1);

    ASSERT_EQ(found.size(), 1u);
    ASSERT_EQ(found[0]->getTitle(), "Мастер и Маргарита");
}

TEST_F(LibraryCatalogTests, FindByAuthorFindsBothCoauthors) {
    const auto firstAuthorBooks = catalog.findByAuthor(2);
    const auto secondAuthorBooks = catalog.findByAuthor(3);

    ASSERT_EQ(firstAuthorBooks.size(), 1u);
    ASSERT_EQ(secondAuthorBooks.size(), 1u);

    ASSERT_EQ(firstAuthorBooks[0]->getTitle(), "Пикник на обочине");
    ASSERT_EQ(firstAuthorBooks[0], secondAuthorBooks[0]);
}

TEST_F(LibraryCatalogTests, FindByAuthorReturnsAllTheirBooks) {
    catalog.addBook(std::make_unique<FictionBook>(
        "Собачье сердце",
        std::vector<Author>{Author(1, "Михаил Булгаков")},
        Publisher("Эксмо"),
        "Художественная литература",
        "Полка 4",
        "Повесть"
    ));

    const auto found = catalog.findByAuthor(1);

    ASSERT_EQ(found.size(), 2u);
    ASSERT_EQ(found[0]->getTitle(), "Мастер и Маргарита");
    ASSERT_EQ(found[1]->getTitle(), "Собачье сердце");
}

TEST_F(LibraryCatalogTests, FindByAuthorDoesNotDuplicateBook) {
    catalog.addBook(std::make_unique<FictionBook>(
        "Книга с повтором автора",
        std::vector<Author>{
            Author(5, "Автор"),
            Author(5, "Автор")
        },
        Publisher("Эксмо"),
        "Литература",
        "Полка 5",
        "Рассказ"
    ));

    const auto found = catalog.findByAuthor(5);

    ASSERT_EQ(found.size(), 1u);
}

TEST_F(LibraryCatalogTests, FindByAuthorReturnsEmptyForUnknownId) {
    ASSERT_TRUE(catalog.findByAuthor(999).empty());
}

TEST_F(LibraryCatalogTests, FindByAuthorSkipsBooksWithoutAuthors) {
    catalog.addBook(std::make_unique<FictionBook>(
        "Без автора",
        std::vector<Author>{},
        Publisher("Эксмо"),
        "Литература",
        "Полка 6",
        "Рассказ"
    ));

    ASSERT_TRUE(catalog.findByAuthor(999).empty());

    const auto found = catalog.findByAuthor(1);

    ASSERT_EQ(found.size(), 1u);
}

// ---------- findByTopic ----------

TEST_F(LibraryCatalogTests, FindByTopicReturnsMatchingBooks) {
    const auto found =
        catalog.findByTopic("Художественная литература");

    ASSERT_EQ(found.size(), 2u);
    ASSERT_EQ(found[0]->getTitle(), "Мастер и Маргарита");
    ASSERT_EQ(found[1]->getTitle(), "Пикник на обочине");
}

TEST_F(LibraryCatalogTests, FindByTopicFindsTextbook) {
    const auto found = catalog.findByTopic("Математика");

    ASSERT_EQ(found.size(), 1u);
    ASSERT_EQ(found[0]->getTitle(), "Алгебра и начала анализа");
}

TEST_F(LibraryCatalogTests, FindByTopicReturnsEmptyForUnknownTopic) {
    ASSERT_TRUE(catalog.findByTopic("Биология").empty());
}

TEST_F(LibraryCatalogTests, FindByTopicRequiresExactMatch) {
    ASSERT_TRUE(catalog.findByTopic("математика").empty());
    ASSERT_TRUE(catalog.findByTopic("Матем").empty());
}

// ---------- findByPublisher ----------

TEST_F(LibraryCatalogTests, FindByPublisherReturnsMatchingBook) {
    const auto found = catalog.findByPublisher("АСТ");

    ASSERT_EQ(found.size(), 1u);
    ASSERT_EQ(found[0]->getTitle(), "Пикник на обочине");
}

TEST_F(LibraryCatalogTests, FindByPublisherReturnsAllMatches) {
    catalog.addBook(std::make_unique<FictionBook>(
        "Новая книга",
        std::vector<Author>{Author(5, "Автор")},
        Publisher("Эксмо"),
        "Литература",
        "Полка 7",
        "Рассказ"
    ));

    const auto found = catalog.findByPublisher("Эксмо");

    ASSERT_EQ(found.size(), 2u);
    ASSERT_EQ(found[0]->getTitle(), "Мастер и Маргарита");
    ASSERT_EQ(found[1]->getTitle(), "Новая книга");
}

TEST_F(LibraryCatalogTests, FindByPublisherReturnsEmptyForUnknownName) {
    ASSERT_TRUE(
        catalog.findByPublisher("Неизвестное издательство").empty()
    );
}

TEST_F(LibraryCatalogTests, FindByPublisherRequiresExactMatch) {
    ASSERT_TRUE(catalog.findByPublisher("аст").empty());
    ASSERT_TRUE(catalog.findByPublisher("АС").empty());
}

// ---------- Пустой каталог ----------

TEST(EmptyLibraryCatalogTests, AllMethodsReturnEmptyResults) {
    LibraryCatalog catalog;

    ASSERT_TRUE(catalog.getBooks().empty());
    ASSERT_TRUE(catalog.findByTitle("Книга").empty());
    ASSERT_TRUE(catalog.findByAuthor(1).empty());
    ASSERT_TRUE(catalog.findByTopic("Математика").empty());
    ASSERT_TRUE(catalog.findByPublisher("АСТ").empty());
}

// ---------- Пустые строки ----------

TEST(EmptyLibraryCatalogTests, FindsBooksWithEmptyFields) {
    LibraryCatalog catalog;

    catalog.addBook(std::make_unique<Textbook>(
        "",
        std::vector<Author>{},
        Publisher(""),
        "",
        "",
        ""
    ));

    const auto byTitle = catalog.findByTitle("");
    const auto byTopic = catalog.findByTopic("");
    const auto byPublisher = catalog.findByPublisher("");

    ASSERT_EQ(byTitle.size(), 1u);
    ASSERT_EQ(byTopic.size(), 1u);
    ASSERT_EQ(byPublisher.size(), 1u);

    ASSERT_EQ(byTitle[0], byTopic[0]);
    ASSERT_EQ(byTitle[0], byPublisher[0]);
}
