#include <gtest/gtest.h>

#include <limits>
#include <new>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

#include "LibraryCatalog.h"

// ==================== Author ====================

TEST(AuthorTests, ConstructorAndAllGetters) {
    const Author author(1, "Михаил Булгаков");

    ASSERT_EQ(author.getId(), 1);
    ASSERT_EQ(author.getFullName(), "Михаил Булгаков");
    ASSERT_EQ(author.getInfo(), "1, Михаил Булгаков");
}

TEST(AuthorTests, EmptyName) {
    const Author author(1, "");

    ASSERT_EQ(author.getFullName(), "");
    ASSERT_EQ(author.getInfo(), "1, ");
}

TEST(AuthorTests, InvalidId) {
    ASSERT_THROW(Author(0, "Автор"), std::invalid_argument);
    ASSERT_THROW(Author(-1, "Автор"), std::invalid_argument);
}

TEST(AuthorTests, MaximumId) {
    const Author author(std::numeric_limits<int>::max(), "Автор");

    ASSERT_EQ(author.getId(), std::numeric_limits<int>::max());
}

// ==================== Publisher ====================

TEST(PublisherTests, ConstructorAndAllGetters) {
    const Publisher publisher(10, "Эксмо");

    ASSERT_EQ(publisher.getId(), 10);
    ASSERT_EQ(publisher.getName(), "Эксмо");
}

TEST(PublisherTests, EmptyName) {
    ASSERT_EQ(Publisher(10, "").getName(), "");
}

TEST(PublisherTests, InvalidId) {
    ASSERT_THROW(Publisher(0, "Название"), std::invalid_argument);
    ASSERT_THROW(Publisher(-1, "Название"), std::invalid_argument);
}

// ==================== Общие проверки наследников ====================

// Каждый TYPED_TEST выполняется для Textbook и FictionBook.
template<class T>
class BookImplementationTests : public ::testing::Test {};

using BookTypes = ::testing::Types<Textbook, FictionBook>;

struct BookTypeNames {
    template<class T>
    static std::string GetName(int) {
        return std::is_same<T, Textbook>::value
            ? "Textbook"
            : "FictionBook";
    }
};

TYPED_TEST_SUITE(
    BookImplementationTests,
    BookTypes,
    BookTypeNames
);

TYPED_TEST(BookImplementationTests, ConstructorAndBaseGetters) {
    const TypeParam concrete(
        101,
        "Название",
        {1, 2},
        10,
        "Тематика",
        "Полка 1",
        "Дополнение"
    );

    const Book& book = concrete;

    ASSERT_EQ(book.getId(), 101);
    ASSERT_EQ(book.getTitle(), "Название");
    ASSERT_EQ(book.getAuthorIds(), (std::vector<int>{1, 2}));
    ASSERT_EQ(book.getPublisherId(), 10);
    ASSERT_EQ(book.getTopic(), "Тематика");
    ASSERT_EQ(book.getLocation(), "Полка 1");
}

TYPED_TEST(BookImplementationTests, InvalidId) {
    ASSERT_THROW(
        TypeParam(0, "", {}, 10, "", "", ""),
        std::invalid_argument
    );

    ASSERT_THROW(
        TypeParam(-1, "", {}, 10, "", "", ""),
        std::invalid_argument
    );
}

TYPED_TEST(BookImplementationTests, ConstructorCopiesAuthorIds) {
    std::vector<int> ids{1, 2};

    const TypeParam book(101, "Название", ids, 10, "", "", "");

    ids.clear();

    ASSERT_EQ(book.getAuthorIds(), (std::vector<int>{1, 2}));
}

TYPED_TEST(BookImplementationTests, EmptyFields) {
    const TypeParam book(101, "", {}, 10, "", "", "");

    ASSERT_EQ(book.getTitle(), "");
    ASSERT_TRUE(book.getAuthorIds().empty());
    ASSERT_EQ(book.getTopic(), "");
    ASSERT_EQ(book.getLocation(), "");
}

TYPED_TEST(BookImplementationTests, BookCopyPreservesData) {
    const TypeParam original(
        101, "Название", {1}, 10, "Тема", "Полка", "Данные"
    );

    const TypeParam copy(original);

    ASSERT_EQ(copy.getInfo(), original.getInfo());
    ASSERT_EQ(copy.getAuthorIds(), original.getAuthorIds());
    ASSERT_EQ(copy.getPublisherId(), original.getPublisherId());
}

// ==================== Textbook ====================

TEST(TextbookTests, SubjectAndExactDescription) {
    const Textbook concrete(
        103, "Алгебра", {4}, 30, "Математика", "Полка 1", "Алгебра"
    );

    const Book& book = concrete;

    ASSERT_EQ(concrete.getSubject(), "Алгебра");

    ASSERT_EQ(
        book.getInfo(),
        "Учебник: Алгебра"
        "\nID: 103"
        "\nТематика: Математика"
        "\nРасположение: Полка 1"
        "\nПредмет: Алгебра"
    );
}

TEST(TextbookTests, EmptySubjectAndDescription) {
    const Textbook book(1, "", {}, 10, "", "", "");

    ASSERT_EQ(book.getSubject(), "");

    ASSERT_EQ(
        book.getInfo(),
        "Учебник: "
        "\nID: 1"
        "\nТематика: "
        "\nРасположение: "
        "\nПредмет: "
    );
}

// ==================== FictionBook ====================

TEST(FictionBookTests, GenreAndExactDescription) {
    const FictionBook concrete(
        101,
        "Мастер и Маргарита",
        {1},
        10,
        "Литература",
        "Полка 2",
        "Роман"
    );

    const Book& book = concrete;

    ASSERT_EQ(concrete.getGenre(), "Роман");

    ASSERT_EQ(
        book.getInfo(),
        "Художественная книга: Мастер и Маргарита"
        "\nID: 101"
        "\nТематика: Литература"
        "\nРасположение: Полка 2"
        "\nЖанр: Роман"
    );
}

TEST(FictionBookTests, EmptyGenreAndDescription) {
    const FictionBook book(1, "", {}, 10, "", "", "");

    ASSERT_EQ(book.getGenre(), "");

    ASSERT_EQ(
        book.getInfo(),
        "Художественная книга: "
        "\nID: 1"
        "\nТематика: "
        "\nРасположение: "
        "\nЖанр: "
    );
}

// ==================== Интерфейс Book ====================

TEST(BookInterfaceTests, IsAbstractAndHasVirtualDestructor) {
    ASSERT_TRUE(std::is_abstract<Book>::value);
    ASSERT_TRUE(std::has_virtual_destructor<Book>::value);
}

class DestructionProbe : public Textbook {
private:
    bool& destroyed;

public:
    explicit DestructionProbe(bool& flag)
        : Textbook(1, "", {}, 10, "", "", ""),
          destroyed(flag) {
    }

    ~DestructionProbe() override {
        destroyed = true;
    }
};

TEST(BookInterfaceTests, VirtualDestructorDestroysDerivedObject) {
    bool destroyed = false;

    alignas(DestructionProbe)
        unsigned char storage[sizeof(DestructionProbe)];

    // Создаём объект в готовом буфере, без выделения памяти.
    Book* base = new (storage) DestructionProbe(destroyed);

    const bool aliveBeforeDestruction = !destroyed;

    // Проверяем виртуальный вызов деструктора через Book.
    base->~Book();

    ASSERT_TRUE(aliveBeforeDestruction);
    ASSERT_TRUE(destroyed);
}

// ==================== Заполненный каталог ====================

class CatalogTests : public ::testing::Test {
protected:
    LibraryCatalog catalog;

    void SetUp() override {
        catalog.addAuthor(Author(1, "Михаил Булгаков"));
        catalog.addAuthor(Author(2, "Аркадий Стругацкий"));
        catalog.addAuthor(Author(3, "Борис Стругацкий"));
        catalog.addAuthor(Author(4, "Андрей Колмогоров"));

        catalog.addPublisher(Publisher(10, "Эксмо"));
        catalog.addPublisher(Publisher(20, "АСТ"));
        catalog.addPublisher(Publisher(30, "Просвещение"));

        catalog.addFictionBook(FictionBook(
            101, "Мастер и Маргарита", {1},
            10, "Литература", "Полка 1", "Роман"
        ));

        catalog.addFictionBook(FictionBook(
            102, "Пикник на обочине", {2, 3},
            20, "Литература", "Полка 2", "Фантастика"
        ));

        catalog.addTextbook(Textbook(
            103, "Алгебра", {4},
            30, "Математика", "Полка 3", "Алгебра"
        ));
    }
};

TEST_F(CatalogTests, AllCollectionGetters) {
    ASSERT_EQ(catalog.getAuthors().size(), 4u);
    ASSERT_EQ(catalog.getPublishers().size(), 3u);
    ASSERT_EQ(catalog.getTextbooks().size(), 1u);
    ASSERT_EQ(catalog.getFictionBooks().size(), 2u);

    ASSERT_EQ(catalog.getAuthors()[2].getId(), 3);
    ASSERT_EQ(catalog.getPublishers()[1].getName(), "АСТ");
    ASSERT_EQ(catalog.getTextbooks()[0].getSubject(), "Алгебра");
    ASSERT_EQ(catalog.getFictionBooks()[1].getGenre(), "Фантастика");
}

TEST_F(CatalogTests, AddAuthorCopiesObject) {
    {
        Author local(5, "Новый автор");
        catalog.addAuthor(local);
    }

    ASSERT_EQ(catalog.getAuthors().size(), 5u);
    ASSERT_EQ(catalog.findAuthorById(5).getFullName(), "Новый автор");
}

TEST_F(CatalogTests, RejectDuplicateAuthorId) {
    ASSERT_THROW(
        catalog.addAuthor(Author(1, "Другое имя")),
        std::invalid_argument
    );

    ASSERT_EQ(catalog.getAuthors().size(), 4u);
    ASSERT_EQ(
        catalog.findAuthorById(1).getFullName(),
        "Михаил Булгаков"
    );
}

TEST_F(CatalogTests, AddPublisherCopiesObject) {
    {
        Publisher local(40, "Новое издательство");
        catalog.addPublisher(local);
    }

    ASSERT_EQ(catalog.getPublishers().size(), 4u);
    ASSERT_EQ(
        catalog.findPublisherById(40).getName(),
        "Новое издательство"
    );
}

TEST_F(CatalogTests, RejectDuplicatePublisherId) {
    ASSERT_THROW(
        catalog.addPublisher(Publisher(10, "Другое")),
        std::invalid_argument
    );

    ASSERT_EQ(catalog.getPublishers().size(), 3u);
}

TEST_F(CatalogTests, FindAuthorById) {
    ASSERT_EQ(
        catalog.findAuthorById(1).getFullName(),
        "Михаил Булгаков"
    );

    ASSERT_EQ(
        catalog.findAuthorById(3).getInfo(),
        "3, Борис Стругацкий"
    );

    ASSERT_THROW(catalog.findAuthorById(999), std::out_of_range);
    ASSERT_THROW(catalog.findAuthorById(0), std::out_of_range);
}

TEST_F(CatalogTests, FindPublisherById) {
    ASSERT_EQ(catalog.findPublisherById(10).getName(), "Эксмо");
    ASSERT_EQ(catalog.findPublisherById(30).getName(), "Просвещение");

    ASSERT_THROW(catalog.findPublisherById(999), std::out_of_range);
}

TEST_F(CatalogTests, FindBothBookTypesById) {
    ASSERT_EQ(
        catalog.findBookById(101).getTitle(),
        "Мастер и Маргарита"
    );

    ASSERT_EQ(catalog.findBookById(103).getTitle(), "Алгебра");

    ASSERT_NE(
        dynamic_cast<const FictionBook*>(&catalog.findBookById(101)),
        nullptr
    );

    ASSERT_NE(
        dynamic_cast<const Textbook*>(&catalog.findBookById(103)),
        nullptr
    );

    ASSERT_THROW(catalog.findBookById(999), std::out_of_range);
}

TEST_F(CatalogTests, GetBookIds) {
    ASSERT_EQ(
        catalog.getBookIds(),
        (std::vector<int>{103, 101, 102})
    );
}

TEST_F(CatalogTests, FindByTitle) {
    ASSERT_EQ(
        catalog.findByTitle("Алгебра"),
        (std::vector<int>{103})
    );

    ASSERT_EQ(
        catalog.findByTitle("Мастер и Маргарита"),
        (std::vector<int>{101})
    );

    ASSERT_TRUE(catalog.findByTitle("Неизвестная").empty());
    ASSERT_TRUE(catalog.findByTitle("Мастер").empty());
    ASSERT_TRUE(catalog.findByTitle("алгебра").empty());
}

TEST_F(CatalogTests, SameTitleAcrossBookTypes) {
    catalog.addTextbook(Textbook(
        104, "Мастер и Маргарита", {4}, 30,
        "Литература", "Полка 4", "Литература"
    ));

    ASSERT_EQ(
        catalog.findByTitle("Мастер и Маргарита"),
        (std::vector<int>{104, 101})
    );
}

TEST_F(CatalogTests, FindByAuthorAndCoauthors) {
    ASSERT_EQ(catalog.findByAuthor(1), (std::vector<int>{101}));
    ASSERT_EQ(catalog.findByAuthor(2), (std::vector<int>{102}));
    ASSERT_EQ(catalog.findByAuthor(3), (std::vector<int>{102}));
    ASSERT_EQ(catalog.findByAuthor(4), (std::vector<int>{103}));

    ASSERT_TRUE(catalog.findByAuthor(999).empty());
}

TEST_F(CatalogTests, FindAllBooksOfAuthor) {
    catalog.addTextbook(Textbook(
        104, "Новая", {1}, 10, "Тема", "Полка", "Предмет"
    ));

    ASSERT_EQ(
        catalog.findByAuthor(1),
        (std::vector<int>{104, 101})
    );
}

TEST_F(CatalogTests, FindByTopic) {
    ASSERT_EQ(
        catalog.findByTopic("Литература"),
        (std::vector<int>{101, 102})
    );

    ASSERT_EQ(
        catalog.findByTopic("Математика"),
        (std::vector<int>{103})
    );

    ASSERT_TRUE(catalog.findByTopic("Нет").empty());
    ASSERT_TRUE(catalog.findByTopic("литература").empty());
}

TEST_F(CatalogTests, FindByPublisher) {
    ASSERT_EQ(
        catalog.findByPublisher("Эксмо"),
        (std::vector<int>{101})
    );

    ASSERT_EQ(
        catalog.findByPublisher("АСТ"),
        (std::vector<int>{102})
    );

    ASSERT_EQ(
        catalog.findByPublisher("Просвещение"),
        (std::vector<int>{103})
    );

    ASSERT_TRUE(catalog.findByPublisher("Нет").empty());
    ASSERT_TRUE(catalog.findByPublisher("аст").empty());
}

TEST_F(CatalogTests, FindAllBooksOfPublisher) {
    catalog.addTextbook(Textbook(
        104, "Новая", {1}, 10, "Тема", "Полка", "Предмет"
    ));

    ASSERT_EQ(
        catalog.findByPublisher("Эксмо"),
        (std::vector<int>{104, 101})
    );
}

TEST_F(CatalogTests, SamePublisherNameWithDifferentIds) {
    catalog.addPublisher(Publisher(40, "Эксмо"));

    catalog.addTextbook(Textbook(
        104, "Новая", {1}, 40, "Тема", "Полка", "Предмет"
    ));

    ASSERT_EQ(
        catalog.findByPublisher("Эксмо"),
        (std::vector<int>{104, 101})
    );
}

TEST_F(CatalogTests, LocationForBothBookTypes) {
    ASSERT_EQ(catalog.getLocation(101), "Полка 1");
    ASSERT_EQ(catalog.getLocation(103), "Полка 3");

    ASSERT_THROW(catalog.getLocation(999), std::out_of_range);
}

TEST_F(CatalogTests, FullInfoForSingleAuthor) {
    ASSERT_EQ(
        catalog.getBookInfo(101),
        "Художественная книга: Мастер и Маргарита"
        "\nID: 101"
        "\nТематика: Литература"
        "\nРасположение: Полка 1"
        "\nЖанр: Роман"
        "\nАвторы: 1, Михаил Булгаков"
        "\nИздательство: Эксмо"
    );
}

TEST_F(CatalogTests, FullInfoForCoauthors) {
    ASSERT_EQ(
        catalog.getBookInfo(102),
        "Художественная книга: Пикник на обочине"
        "\nID: 102"
        "\nТематика: Литература"
        "\nРасположение: Полка 2"
        "\nЖанр: Фантастика"
        "\nАвторы: 2, Аркадий Стругацкий; 3, Борис Стругацкий"
        "\nИздательство: АСТ"
    );
}

TEST_F(CatalogTests, FullInfoForTextbook) {
    ASSERT_EQ(
        catalog.getBookInfo(103),
        "Учебник: Алгебра"
        "\nID: 103"
        "\nТематика: Математика"
        "\nРасположение: Полка 3"
        "\nПредмет: Алгебра"
        "\nАвторы: 4, Андрей Колмогоров"
        "\nИздательство: Просвещение"
    );

    ASSERT_THROW(catalog.getBookInfo(999), std::out_of_range);
}

TEST_F(CatalogTests, SearchDoesNotChangeCatalog) {
    const auto before = catalog.getBookIds();

    catalog.findByTitle("Алгебра");
    catalog.findByAuthor(3);
    catalog.findByTopic("Нет");
    catalog.findByPublisher("АСТ");
    catalog.getBookInfo(102);
    catalog.getLocation(101);

    ASSERT_EQ(catalog.getBookIds(), before);
    ASSERT_EQ(catalog.getAuthors().size(), 4u);
    ASSERT_EQ(catalog.getPublishers().size(), 3u);
}

// ==================== Проверка добавления обоих видов книг ====================

// Закрытый validateBook проверяется через публичные методы добавления.
template<class T>
class CatalogValidationTests : public ::testing::Test {
protected:
    LibraryCatalog catalog;

    void SetUp() override {
        catalog.addAuthor(Author(1, "Автор"));
        catalog.addPublisher(Publisher(10, "Издательство"));
    }

    void add(const Textbook& book) {
        catalog.addTextbook(book);
    }

    void add(const FictionBook& book) {
        catalog.addFictionBook(book);
    }
};

TYPED_TEST_SUITE(
    CatalogValidationTests,
    BookTypes,
    BookTypeNames
);

TYPED_TEST(CatalogValidationTests, AddsAndCopiesBook) {
    {
        const TypeParam local(
            1, "Название", {1}, 10, "Тема", "Полка", "Данные"
        );

        this->add(local);
    }

    ASSERT_EQ(this->catalog.getBookIds(), (std::vector<int>{1}));

    ASSERT_EQ(
        this->catalog.findBookById(1).getTitle(),
        "Название"
    );

    ASSERT_EQ(
        this->catalog.findBookById(1).getAuthorIds(),
        (std::vector<int>{1})
    );
}

TYPED_TEST(CatalogValidationTests, RejectsDuplicateIdInSameType) {
    const TypeParam book(1, "Название", {1}, 10, "", "", "");

    this->add(book);

    ASSERT_THROW(this->add(book), std::invalid_argument);
    ASSERT_EQ(this->catalog.getBookIds(), (std::vector<int>{1}));
}

TYPED_TEST(CatalogValidationTests, RejectsIdAlreadyUsedByTextbook) {
    this->catalog.addTextbook(
        Textbook(1, "Исходная", {1}, 10, "", "", "")
    );

    ASSERT_THROW(
        this->add(TypeParam(1, "Другая", {1}, 10, "", "", "")),
        std::invalid_argument
    );

    ASSERT_EQ(this->catalog.getBookIds().size(), 1u);

    ASSERT_EQ(
        this->catalog.findBookById(1).getTitle(),
        "Исходная"
    );
}

TYPED_TEST(CatalogValidationTests, RejectsIdAlreadyUsedByFictionBook) {
    this->catalog.addFictionBook(
        FictionBook(1, "Исходная", {1}, 10, "", "", "")
    );

    ASSERT_THROW(
        this->add(TypeParam(1, "Другая", {1}, 10, "", "", "")),
        std::invalid_argument
    );

    ASSERT_EQ(this->catalog.getBookIds().size(), 1u);
}

TYPED_TEST(CatalogValidationTests, RejectsUnknownPublisher) {
    ASSERT_THROW(
        this->add(TypeParam(1, "", {1}, 999, "", "", "")),
        std::out_of_range
    );

    ASSERT_THROW(
        this->add(TypeParam(1, "", {1}, 0, "", "", "")),
        std::out_of_range
    );

    ASSERT_TRUE(this->catalog.getBookIds().empty());
}

TYPED_TEST(CatalogValidationTests, RejectsUnknownAuthor) {
    ASSERT_THROW(
        this->add(TypeParam(1, "", {999}, 10, "", "", "")),
        std::out_of_range
    );

    ASSERT_THROW(
        this->add(TypeParam(1, "", {1, 999}, 10, "", "", "")),
        std::out_of_range
    );

    ASSERT_THROW(
        this->add(TypeParam(1, "", {0}, 10, "", "", "")),
        std::out_of_range
    );

    ASSERT_TRUE(this->catalog.getBookIds().empty());
}

TYPED_TEST(CatalogValidationTests, RejectsDuplicateAuthorIds) {
    ASSERT_THROW(
        this->add(TypeParam(1, "", {1, 1}, 10, "", "", "")),
        std::invalid_argument
    );

    ASSERT_TRUE(this->catalog.getBookIds().empty());
}

TYPED_TEST(CatalogValidationTests, AcceptsEmptyFieldsAndNoAuthors) {
    this->add(TypeParam(1, "", {}, 10, "", "", ""));

    ASSERT_EQ(
        this->catalog.findByTitle(""),
        (std::vector<int>{1})
    );

    ASSERT_EQ(
        this->catalog.findByTopic(""),
        (std::vector<int>{1})
    );

    ASSERT_TRUE(this->catalog.findByAuthor(1).empty());
    ASSERT_EQ(this->catalog.getLocation(1), "");

    ASSERT_NE(
        this->catalog.getBookInfo(1).find(
            "\nАвторы: \nИздательство: Издательство"
        ),
        std::string::npos
    );
}

TYPED_TEST(CatalogValidationTests, CanRetryAfterRejectedAddition) {
    ASSERT_THROW(
        this->add(TypeParam(1, "", {2}, 10, "", "", "")),
        std::out_of_range
    );

    this->catalog.addAuthor(Author(2, "Второй"));

    ASSERT_NO_THROW(
        this->add(TypeParam(1, "", {2}, 10, "", "", ""))
    );

    ASSERT_EQ(
        this->catalog.findByAuthor(2),
        (std::vector<int>{1})
    );
}

// ==================== Пустой каталог и особые случаи ====================

TEST(EmptyCatalogTests, AllMethodsOnEmptyCatalog) {
    const LibraryCatalog catalog;

    ASSERT_TRUE(catalog.getAuthors().empty());
    ASSERT_TRUE(catalog.getPublishers().empty());
    ASSERT_TRUE(catalog.getTextbooks().empty());
    ASSERT_TRUE(catalog.getFictionBooks().empty());
    ASSERT_TRUE(catalog.getBookIds().empty());

    ASSERT_TRUE(catalog.findByTitle("Название").empty());
    ASSERT_TRUE(catalog.findByAuthor(1).empty());
    ASSERT_TRUE(catalog.findByTopic("Тема").empty());
    ASSERT_TRUE(catalog.findByPublisher("Издательство").empty());

    ASSERT_THROW(catalog.findBookById(1), std::out_of_range);
    ASSERT_THROW(catalog.findAuthorById(1), std::out_of_range);
    ASSERT_THROW(catalog.findPublisherById(1), std::out_of_range);
    ASSERT_THROW(catalog.getLocation(1), std::out_of_range);
    ASSERT_THROW(catalog.getBookInfo(1), std::out_of_range);
}

TEST(EmptyCatalogTests, UnusedAuthorsAndPublishersHaveNoBooks) {
    LibraryCatalog catalog;

    catalog.addAuthor(Author(1, "Автор"));
    catalog.addPublisher(Publisher(10, "Издательство"));

    ASSERT_TRUE(catalog.findByAuthor(1).empty());
    ASSERT_TRUE(catalog.findByPublisher("Издательство").empty());
}

TEST(EmptyCatalogTests, EmptyPublisherNameCanBeSearched) {
    LibraryCatalog catalog;

    catalog.addPublisher(Publisher(10, ""));
    catalog.addTextbook(Textbook(1, "", {}, 10, "", "", ""));

    ASSERT_EQ(
        catalog.findByPublisher(""),
        (std::vector<int>{1})
    );
}

TEST(EmptyCatalogTests, SeparateEntitiesMayShareAnId) {
    LibraryCatalog catalog;

    catalog.addAuthor(Author(1, "Автор"));
    catalog.addPublisher(Publisher(1, "Издательство"));

    catalog.addTextbook(
        Textbook(1, "Учебник", {1}, 1, "", "", "")
    );

    ASSERT_EQ(catalog.findAuthorById(1).getFullName(), "Автор");

    ASSERT_EQ(
        catalog.findPublisherById(1).getName(),
        "Издательство"
    );

    ASSERT_EQ(catalog.findBookById(1).getTitle(), "Учебник");
}
