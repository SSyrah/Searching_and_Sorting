#include "header.h"

int main()
{
    // Error_code check;
    bool operand = true;
    int target, key;
    SortableList<int> theList;
    int size{500};

    Random rand;
    for (int i = 0; i < size; i++) {
        theList.insert(i, rand.random_integer(1, 100));
    }

    while (operand) {
        initialize(target);
        if (target != 6 && target != 3) {
            std::cout << "Enter number for searching: ";
            std::cin >> key;
            checkInt(key);
            std::cout << "\n";
        }
        switch (target) {
            case 1:
                sequentialSearch(theList,key);
                break;
            case 2:
                sequentialSearch(theList,key);
                binary_search(theList, key);
                break;
            case 3:
                insertion_sort(theList, size);
                break;
            case 4:
                selection_sort(theList, size);
                break;
            case 5:
                std::cout << "placeholder 5\n";
                break;
            case 6:
                std::cout << "Ending program, thank you for using!\n";
                operand = false;
                break;
            default:
                std::cout << "Sorry, wrong input\n";
        }
    }




    return EXIT_SUCCESS;
}
