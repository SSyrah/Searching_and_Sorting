#pragma once
#include "header.h"


class Key {
   int key;
public:
   static int comparisons;
   Key(int x);
   int the_key() const;
};

typedef Key Record;

template <typename Record>
class SortableList : public List<Record> {
public:
    Error_code sequential_search(const List<Record> &the_list,const Key &target, int &);
    int getComparisons() const;
    Error_code binary_search_1 (const SortableList<Record> &the_list, const Key &target, int &position);
    Error_code insertion_sort(SortableList<Record>&);
    Error_code selectionSort(SortableList<Record>&);
    void quick_sort(SortableList<Record>&);
private:
    int max_key(SortableList<Record>& ,int, int);
    void swap(SortableList<Record>& , int low, int high);
    void recursive_quick_sort(SortableList<Record>&, int low, int high);
    int partition(SortableList<Record>&, int low, int high);

};

//------------------- Function definitions--------------------------------//

void initialize(int &);
void checkInt(int &);

//  Declare overloaded comparison operators for keys.
bool operator ==(const Key &x, const Key &y);
bool operator > (const Key &x, const Key &y);
bool operator < (const Key &x, const Key &y);
bool operator >=(const Key &x, const Key &y);
bool operator <=(const Key &x, const Key &y);
bool operator !=(const Key &x, const Key &y);

template<typename Record>
void sequentialSearch(SortableList<Record> &slist, const Key& key);
template<typename Record>
void binary_search(SortableList<Record> &slist, const Key& key);
template<typename Record>
void insertion_sort(SortableList<Record>& sList, int size);
template<typename Record>
void selection_sort(SortableList<Record>& sList, int size);
template<typename Record>
void performance_test(SortableList<Record>& sList);



//------------METHODS--------------------//

template<typename Record>
int SortableList<Record>::getComparisons() const {
    return Key::comparisons;
}

//---Sequential Search---------------------
template<typename Record>
Error_code SortableList<Record>::sequential_search(const List<Record> &the_list, const Key &target, int &dest)
/*
Post: If an entry in the_list has key equal to target, then return
      success and the output parameter position locates such an entry
      within the list.
      Otherwise, return not_present and position becomes invalid.
*/
{
    int s = the_list.size();
    for (dest = 0; dest < s; dest++) {
        Record data;
        the_list.retrieve(dest, data);
        if (operator==(target, data)) return success;
        //if (data == target) return success;
    }
    return not_present;
}

//---Binary Search----------------------------
template<typename Record>
Error_code SortableList<Record>::binary_search_1(const SortableList<Record> &the_list,
                            const Key &target, int &position)
/*
Post: If a Record in the_list  has Key equal to target, then position locates
      one such entry and a code of success is returned.
      Otherwise, not_present is returned and position is undefined.
Uses: Methods for classes List and Record.
*/
{
    Record data;
    int bottom = 0, top = the_list.size() - 1;

    while (bottom < top) {
        int mid = (bottom + top) / 2;
        the_list.retrieve(mid, data);
        if (operator<(data , target))
            bottom = mid + 1;
        else
            top = mid;
    }
    if (top < bottom) return not_present;
    else {
        position = bottom;
        the_list.retrieve(bottom, data);
        if (operator==(data , target)) return success;
        else return not_present;
    }
}

//---Insertion sort----------------------
template <class Record>
Error_code SortableList<Record>::insertion_sort(SortableList<Record>& sList)
/*
Post: The entries of the Sortable_list have been rearranged so that
      the keys in all the  entries are sorted into nondecreasing order.
Uses: Methods for the class Record; the contiguous List implementation of
      Chapter 6
*/
{
    int first_unsorted;    //  position of first unsorted entry
    int position;          //  searches sorted part of list
    Record current;        //  holds the entry temporarily removed from list

    for (first_unsorted = 1; first_unsorted < sList.count; first_unsorted++)
        if (operator< (sList.entry[first_unsorted] , sList.entry[first_unsorted - 1])) {
            position = first_unsorted;
            current = sList.entry[first_unsorted];         //  Pull unsorted entry out of the list.
            do {               //  Shift all entries until the proper position is found.
                sList.entry[position] = sList.entry[position - 1];
                position--;                           //  position is empty.
            } while (position > 0 && sList.entry[position - 1] > current);
            sList.entry[position] = current;
        }
    return success;
}

//Selection sort methods-----------------
template <typename Record>
Error_code SortableList<Record>::selectionSort(SortableList<Record> &sList)
/*
Post: The entries of the Sortable_list have been rearranged so that
      the keys in all the entries are sorted into nondecreasing order.
Uses: max_key, swap.
*/
{
    for (int position = sList.count - 1; position > 0; position--) {
        int max = max_key(sList,0, position);
        swap(sList,max, position);
    }
    return success;
}

template <typename Record>
int SortableList<Record>::max_key(SortableList<Record>& sList, int low, int high)
/*
Pre:  low and high are valid positions in the Sortable_list and low <= high.
Post: The position of the entry between low and high with the largest
      key is returned.
Uses: The class Record, the contiguous List implementation of Chapter 6.
*/
{
    int largest, current;
    largest = low;
    for (current = low + 1; current <= high; current++)
        if (operator <(sList.entry[largest] , sList.entry[current]))
            largest = current;
    return largest;
}


template <typename Record>
void SortableList<Record>::swap(SortableList<Record>& sList, int low, int high)
/*
Pre:  low and high are valid positions in the Sortable_list.
Post: The entry at position low is swapped with the entry at position high.
Uses: The contiguous List implementation of Chapter 6.
*/
{
    Record temp;
    temp = sList.entry[low];
    sList.entry[low] = sList.entry[high];
    sList.entry[high] = temp;
}
//-------------------------------------------------

//---Quick sort Methods:---------------------------
template <typename Record>
void SortableList<Record>::quick_sort(SortableList<Record>& sList)
/*
Post: The entries of the Sortable_list have been rearranged so
      that their keys are sorted into nondecreasing order.
Uses: The contiguous List implementation of Chapter 6, recursive_quick_sort.
*/
{
    auto begin = std::chrono::steady_clock::now();
    sList.recursive_quick_sort(sList,0, sList.count - 1);
    auto end = std::chrono::steady_clock::now();
    auto elapsed = end - begin;
    Record temp;
    /*
    for (int i = 0; i < sList.size(); i++){
        sList.retrieve(i, temp);
        std::cout << temp << " ";
    }*/
    std::cout << "\nQuick sort completed\n";
    std::cout << "Comparisons: " << sList.getComparisons() << std::endl;
    std::cout << "Elapsed time: " << elapsed.count() << std::endl;
    Key::comparisons = 0;
    elapsed.zero();
}

template <typename Record>
void SortableList<Record>::recursive_quick_sort(SortableList<Record>& sList, int low, int high)
/*
Pre:  low and high are valid positions in the Sortable_list.
Post: The entries of the Sortable_list have been
      rearranged so that their keys are sorted into nondecreasing order.
Uses: The contiguous List implementation of Chapter 6,
      recursive_quick_sort, and partition.
*/
{
    int pivot_position;
    if (operator<(low ,high)) {   //   Otherwise, no sorting is needed.
        pivot_position = partition(sList, low, high);
        recursive_quick_sort(sList,low, pivot_position - 1);
        recursive_quick_sort(sList,pivot_position + 1, high);
    }
}

template <typename Record>
int SortableList<Record>::partition(SortableList<Record>& sList, int low, int high)
/*
Pre:  low and high are valid positions of the Sortable_list, with low <= high.
Post: The center (or left center) entry in the range between indices
      low and high of the Sortable_list
      has been chosen as a pivot.  All entries of the Sortable_list
      between indices low and high, inclusive, have been
      rearranged so that those with keys less than the pivot come
      before the pivot and the remaining entries come
      after the pivot.  The final position of the pivot is returned.
Uses: swap(int i, int j) (interchanges entries in positions
      i and j of a Sortable_list), the contiguous List implementation
      of Chapter 6, and methods for the class Record.
*/
{
    Record pivot;
    int i,            //  used to scan through the list
    last_small;   //  position of the last key less than pivot
    swap(sList,low, (low + high) / 2);
    pivot = sList.entry[low];   //  First entry is now pivot.
    last_small = low;
    for (i = low + 1; i <= high; i++)
/*
At the beginning of each iteration of this loop, we have the following
conditions:
        If low < j <= last_small then entry[j].key < pivot.
        If last_small < j < i then entry[j].key >= pivot.
*/
        if (sList.entry[i] < pivot) {
            last_small = last_small + 1;
            swap(sList,last_small, i);  //  Move large entry to right and small to left.
        }
    swap(sList,low, last_small);      //  Put the pivot into its proper position.
    return last_small;
}






// --------------FUNCTIONS------------------------//

template<typename Record>
void sequentialSearch(SortableList<Record> &sList, const Key& key) {
    Error_code check;
    int pos;
    auto begin = std::chrono::steady_clock::now();
    check = sList.sequential_search(sList, key, pos);
    auto end = std::chrono::steady_clock::now();
    auto elapsed = end - begin;
    if (check == success) {
        std::cout << "Status: Successful" << std::endl;
        std::cout << "Found in position: " << pos << std::endl;
        std::cout << "Comparisons: " << sList.getComparisons() << std::endl;
        std::cout << "Elapsed time: " << elapsed.count() << std::endl;
    } else {
        std::cout << "Status: Unsuccessful" << std::endl;
        std::cout << "Sorry, no hits" << std::endl;
        std::cout << "Comparisons: " << sList.getComparisons() << std::endl;
        std::cout << "Elapsed time: " << elapsed.count() << std::endl;
    }
    std::cout << "\n\n";
    Key::comparisons = 0;
    elapsed.zero();
}

template<typename Record>
void binary_search(SortableList<Record>&sList, const Key& key) {
    Error_code check;
    int position{};
    auto begin = std::chrono::steady_clock::now();
    check = sList.binary_search_1(sList, key, position);
    auto end = std::chrono::steady_clock::now();
    auto elapsed = end - begin;
    if (check == success) {
        std::cout << "Found in position: " << position << std::endl;
        std::cout << "Comparisons: " << sList.getComparisons() << std::endl;
        std::cout << "Elapsed time: " << elapsed.count() << std::endl;
    } else {
        std::cout << "Sorry, no hits" << std::endl;
        std::cout << "Comparisons: " << sList.getComparisons() << std::endl;
        std::cout << "Elapsed time: " << elapsed.count() << std::endl;
    }
    std::cout << "\n\n";
    Key::comparisons = 0;
    elapsed.zero();
}

template<typename Record>
void insertion_sort(SortableList<Record>& sList, int size)
{
    // Error_code check;
    Record temp;
    Random rand;
    int listSize{};
    std::cout << "How many position from list you want to print before and after sorting?  ";
    std::cin >> listSize;
    checkInt(listSize);

    if (listSize < 0 || listSize <= sList.getMaxSize()) {
        std::cout << "\nLet's print first " << listSize << " numbers before sorting:\n";
        /*
        for (int i = 0; i < size; i++) {
            sList.insert(i, rand.random_integer(1, 10000));
        }
        */
        for (int i = 0; i < listSize; i++) {
            sList.retrieve(i, temp);
            std::cout << temp << " ";
        }
        std::cout << std::endl;
        auto begin = std::chrono::steady_clock::now();
        sList.insertion_sort(sList);
        auto end = std::chrono::steady_clock::now();
        auto elapsed = end - begin;
        std::cout << "Now, let's print first " << listSize << " numbers after sorting:\n";
        for (int i = 0; i < listSize; i++) {
            sList.retrieve(i, temp);
            std::cout << temp << " ";
        }
        std::cout << "\nElapsed time: " << elapsed.count() << std::endl;
        std::cout << "\n";
        elapsed.zero();
        Key::comparisons = 0;
    }
    else{
        std::cout << "Entered list size is too low or too high\n";
    }
}
template<typename Record>
void selection_sort(SortableList<Record>& sList, int size)
{
    Record temp;
    Random rand;
    int listSize{};
    std::cout << "How many position from list you want to print before and after sorting?  ";
    std::cin >> listSize;
    checkInt(listSize);

    if (listSize < 0 || listSize <= sList.getMaxSize()) {
        std::cout << "\nLet's print first " << listSize << " numbers before sorting:\n";
        /*
        for (int i = 0; i < size; i++) {
            sList.insert(i, rand.random_integer(1, 10000));
        }
        */
        for (int i = 0; i < listSize; i++) {
            sList.retrieve(i, temp);
            std::cout << temp << " ";
        }
        std::cout << std::endl;
        auto begin = std::chrono::steady_clock::now();
        sList.selectionSort(sList);
        auto end = std::chrono::steady_clock::now();
        auto elapsed = end - begin;
        std::cout << "Now, let's print first " << listSize << " numbers after sorting:\n";
        for (int i = 0; i < listSize; i++) {
            sList.retrieve(i, temp);
            std::cout << temp << " ";
        }
        std::cout << "\nElapsed time: " << elapsed.count() << std::endl;
        std::cout << "\n";
        Key::comparisons = 0;
        elapsed.zero();

    }
    else{
        std::cout << "Entered list size is too low or too high\n";
    }

}

template<typename Record>
void performance_test(SortableList<Record>& sList)
{
    SortableList<Record> templist, templist2;
    copy(templist, sList);
    copy(templist2,sList);
    for (int i = 0; i < 5; i++){
    sList.quick_sort(sList);
    auto begin = std::chrono::steady_clock::now();
    templist.insertion_sort(templist);
    auto end = std::chrono::steady_clock::now();
    auto elapsed = end - begin;
    std::cout << "Insertion sort completed.\n";
    std::cout << "Comparisons: " << templist.getComparisons() << std::endl;
    std::cout << "Elapsed time: " << elapsed.count() << std::endl;
    Key::comparisons = 0;
    auto begin2 = std::chrono::steady_clock::now();
    templist2.selectionSort(templist2);
    auto end2 = std::chrono::steady_clock::now();
    auto elapsed2 = end - begin;
    std::cout << "Selection sort completed.\n";
    std::cout << "Comparisons: " << templist2.getComparisons() << std::endl;
    std::cout << "Elapsed time: " << elapsed2.count() << "\n\n";
    Key::comparisons = 0;
    elapsed.zero(), elapsed2.zero();
    }
}