#include "header.h"

int main()
{
    // Error_code check;
    bool operand = true;
    int target, key;
    SortableList<int> theList;
    int size{500};

    Random rand;

    while (operand) {
        initialize(target);

        if (target == 1 || target == 2){
            std::cout << "Enter number for searching: ";
            std::cin >> key;
            checkInt(key);
            std::cout << "\n";
            for (int i = 0; i < size; i++) {
                theList.insert(i,i+2 );
            }
        }

        else if (target >= 3 && target <= 5) {
            for (int i = 0; i < size; i++) {
                theList.insert(i, rand.random_integer(1, 10000));
            }
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
                performance_test(theList);
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
