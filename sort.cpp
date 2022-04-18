#include "sort.h"

int Key::comparisons = 0;

int Key::the_key() const {
    return key;
}

Key::Key(int x) {
    key = x;
}

bool operator == (const Key &x, const Key &y)
{
    Key::comparisons++;
    return x.the_key() == y.the_key();
}

bool operator > (const Key &x, const Key &y)
{
    Key::comparisons++;
    return x.the_key() > y.the_key();
}

bool operator < (const Key &x, const Key &y)
{
    Key::comparisons++;
    return x.the_key() < y.the_key();
}

bool operator >= (const Key &x, const Key &y)
{
    Key::comparisons++;
    return x.the_key() >= y.the_key();
}

bool operator <=(const Key &x, const Key &y)
{
    Key::comparisons++;
    return x.the_key() <= y.the_key();
}

bool operator != (const Key &x, const Key &y)
{
    Key::comparisons++;
    return x.the_key() != y.the_key();
}

void initialize(int& target) {
    bool check = true;
    std::cout << "Welcome to use searching and sorting - app!\n"
              << "Choose on of following options:\n"
              << "[1] Sequential search\n"
              << "[2] Sequential search vs Binary Search comparison \n"
              << "[3] Insertion sort algorithm \n"
              << "[4] Selection sort algorithm \n"
              << "[5] Performance test with 3 sorting algorithms \n"
              << "[6] Quit program \n"
              << "Your option: ";
    std::cin >> target;
    while (check)
    {
        if (std::cin.fail() || target < 1 || target > 6)
        {
            std::cin.clear();
            std::cin.ignore(50, '\n');
            std::cout << "Sorry, wrong number or unrecognized input, try again\n"
                      << "Your choice:";
            std::cin >> target;
        }
        else
            check = false;
    }
}

void checkInt(int& target)
{
    bool check = true;
    while (check)
    {
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(50, '\n');
            std::cout << "Sorry, unrecognized input, try again\n"
                      << "Your choice:";
            std::cin >> target;
        }
        else
            check = false;
    }
}

