#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "dual_list.h"


TEST(List, Constructors) {
    auto list1 = DualList<int>{};
    EXPECT_EQ(list1.size(), 0);

    auto list2 = DualList<std::string>{};
    EXPECT_EQ(list2.size(), 0);

    auto list3 = DualList<std::pair<std::string, std::vector<std::string>>>{};
    EXPECT_EQ(list3.size(), 0);
}

TEST(List, Insert) {
    auto list = DualList<std::string>{};

    list.insert(0, "0");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0], "0");

    list.insert(0, "-1");
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], "-1");
    EXPECT_EQ(list[1], "0");

    list.insert(list.size(), "1");
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list[0], "-1");
    EXPECT_EQ(list[1], "0");
    EXPECT_EQ(list[2], "1");

    list.insert(1, "-0.5");
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list[0], "-1");
    EXPECT_EQ(list[1], "-0.5");
    EXPECT_EQ(list[2], "0");
    EXPECT_EQ(list[3], "1");
}

TEST(List, Remove) {
    auto list = DualList<std::string>{};

    list.push_back("1");
    list.push_back("2");
    list.push_back("3");
    list.push_back("4");
    list.push_back("5");

    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list[0] + list[1] + list[2] + list[3] + list[4], "12345");

    list.remove(0);
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list[0] + list[1] + list[2] + list[3], "2345");

    list.remove(2);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list[0] + list[1] + list[2], "235");

    list.remove(list.size() - 1);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0] + list[1], "23");

    list.remove(list.size() - 1);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0], "2");

    list.remove(0);
    EXPECT_EQ(list.size(), 0);
}

TEST(List, Swap) {
    auto list = DualList<std::string>{};

    list.push_back("1");
    list.push_back("2");
    list.push_back("3");
    list.push_back("4");
    list.push_back("5");

    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list[0] + list[1] + list[2] + list[3] + list[4], "12345");

    list.swap(1, 3);
    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list[0] + list[1] + list[2] + list[3] + list[4], "14325");

    list.swap(0, list.size() - 1);
    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list[0] + list[1] + list[2] + list[3] + list[4], "54321");

    list.swap(0, 1);
    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list[0] + list[1] + list[2] + list[3] + list[4], "45321");

    list.swap(list.size() - 1, list.size() - 2);
    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list[0] + list[1] + list[2] + list[3] + list[4], "45312");
}

class CopyChecker {
public:
    static int counter;

    CopyChecker() = default;

    CopyChecker(const CopyChecker &other) {
        ++counter;
    }

    CopyChecker &operator=(const CopyChecker &other) {
        ++counter;
    }

    CopyChecker(CopyChecker &&other)  noexcept {
        ++counter;
    }

    CopyChecker &operator==(CopyChecker &&other) {
        ++counter;
    }
};

int CopyChecker::counter = 0;

TEST(List, SwapNoCopyObject) {
    auto list = DualList<CopyChecker>{};

    list.push_back({});
    list.push_back({});
    list.push_back({});
    list.push_back({});
    list.push_back({});

    EXPECT_EQ(list.size(), 5);

    CopyChecker::counter = 0;
    list.swap(1, 3);
    list.swap(0, list.size() - 1);
    list.swap(0, 1);
    list.swap(list.size() - 1, list.size() - 2);
    EXPECT_EQ(CopyChecker::counter, 0);

    list.push_back(*list.begin());
    EXPECT_GE(CopyChecker::counter, 1);
}

TEST(List, Sort) {
    auto list = DualList<std::string>{};

    list.push_back("7");
    list.push_back("4");
    list.push_back("1");
    list.push_back("6");
    list.push_back("8");

    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list[0] + list[1] + list[2] + list[3] + list[4], "74168");

    list.sort();
    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list[0] + list[1] + list[2] + list[3] + list[4], "87641");

    list.sort();
    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list[0] + list[1] + list[2] + list[3] + list[4], "87641");

    list.insert(2, "0");
    list.sort();
    EXPECT_EQ(list.size(), 6);
    EXPECT_EQ(list[0] + list[1] + list[2] + list[3] + list[4] + list[5], "876410");
}

class DestructChecker {
public:
    static int counter;

    explicit DestructChecker(int val) {
        ++counter;
    }

    DestructChecker(const DestructChecker &other) {
        ++counter;
    }

    DestructChecker &operator=(const DestructChecker &other) {
        ++counter;
    }

    DestructChecker(DestructChecker &&other)  noexcept {
        ++counter;
    }

    DestructChecker &operator==(DestructChecker &&other) {
        ++counter;
    }

    ~DestructChecker() {
        --counter;
    }

};

int DestructChecker::counter = 0;

TEST(List, DestructorDelete) {
    {
        auto list = DualList<DestructChecker>{};
        list.push_back(DestructChecker{1});
        list.push_back(DestructChecker{2});
        list.push_back(DestructChecker{3});
        list.push_back(DestructChecker{4});
        EXPECT_EQ(DestructChecker::counter, 4);
    }
    EXPECT_EQ(DestructChecker::counter, 0);
}
