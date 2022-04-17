#pragma once

#include "utility.h"

const int max_list = 5000;
 
template <class List_entry>
class List {
public:
//  methods of the List ADT
   List();
   int size() const;
   bool full() const;
   bool empty() const;
   void clear();
   void traverse(void (*visit)(List_entry &));
   Error_code retrieve(int position, List_entry &x) const;
   Error_code replace(int position, const List_entry &x);
   Error_code remove(int position, List_entry &x);
   Error_code insert(int position, const List_entry &x);
   int getMaxSize();

protected:
//  data members for a contiguous list implementation
   int count;
   List_entry entry[max_list];
};

template <typename List_entry>
List<List_entry>::List()
/* 
 
Post: The List is initialized to be empty.
 
*/

{
   count = 0;
}
 
//  clear:  clear the List.
/* 
 
Post: The List is cleared.
 
*/

template <typename List_entry>
void List<List_entry>::clear()
{
   count = 0;
}
 
template <typename List_entry>
int List<List_entry>::size() const
/* 
 
Post: The function returns the number of entries in the List.
 
*/
{
   return count;
}
 
//  empty: returns non-zero if the List is empty.
/* 
 
Post: The function returns true or false
according as the List is empty or not.
 
*/

template <typename List_entry>
bool List<List_entry>::empty() const
{
   return count <= 0;
}
 
//  full: returns non-zero if the List is full.
/* 
 
Post: The function returns true or false
according as the List is full or not.
 
*/

template <typename List_entry>
bool List<List_entry>::full() const
{
   return count >= max_list;
}
 
template <typename List_entry>
void List<List_entry>::traverse(void (*visit)(List_entry &))
/* 
 
Post: The action specified by function (*visit) has been performed on every
entry of the List, beginning at position 0 and doing each in turn.
 
*/
{
   for (int i = 0; i < count; i++)
      (*visit)(entry[i]);
}
 
template <typename List_entry>
Error_code List<List_entry>::insert(int posit, const List_entry &x)
/* 
 
Post: If the List is not full and 0 <= position <= n,
where n is the number of entries in the List,
the function succeeds:
Any entry formerly at
position and all later entries have their
position numbers increased by 1 and
x is inserted at position of the List.

 
Else:
The function fails with a diagnostic error code.
 
*/

{
   if (full())
      return overflow;

   if (posit < 0 || posit > count)
      return utility_range_error;

   for (int i = count - 1; i >= posit; i--)
      entry[i + 1] = entry[i];

   entry[posit] = x;
   count++;
   return success;
}
 
template <typename List_entry>
Error_code List<List_entry>::retrieve(int position, List_entry &x) const
/* 
 
Post: If the List is not full and 0 <= position < n,
where n is the number of entries in the List,
the function succeeds:
The entry in position is copied to x.
Otherwise, the function fails with an error code of range_error.
 
*/

{
   if (position < 0 || position >= count) return utility_range_error;
   x = entry[position];
   return success;
}
 
template <typename List_entry>
Error_code List<List_entry>::replace(int position, const List_entry &x)
/* 
 
Post: If 0 <= position < n,
where n is the number of entries in the List,
the function succeeds:
The entry in position is replaced by x,
all other entries remain unchanged.
Otherwise, the function fails with an error code of range_error.
 
*/

{
   if (position < 0 || position >= count) return utility_range_error;
   entry[position] = x;
   return success;
}
 
/* 
 
Post: If 0 <= position < n,
where n is the number of entries in the List,
the function succeeds:
The entry in position is removed
from the List, and the entries in all later positions
have their position numbers decreased by 1.
The parameter x records a copy of
the entry formerly in position.
Otherwise, the function fails with a diagnostic error code.
 
*/

template <typename List_entry>
Error_code List<List_entry>::remove(int position, List_entry &x)
{
   if (count == 0) return underflow;
   if (position < 0 || position >= count) return utility_range_error;

   x = entry[position];
   count--;
   while (position < count) {
      entry[position] = entry[position + 1];
      position++;
   }
   return success;
}

template<class List_entry>
int List<List_entry>::getMaxSize() {
    return max_list;
}

template <typename List_entry> 
Error_code insert_first(const List_entry &x, List<List_entry> &a_list)
/* 
 
Post:
Entry x is inserted at
position 0 of List a_list.
 
*/
{
   return a_list.insert(0, x);
}

template <typename List_entry>
Error_code remove_first(List_entry &x, List<List_entry> &a_list)
/* 
 
Post:
A code of underflow is returned if List a_list is
empty.  Otherwise,
the first entry
of List a_list is removed and reported as x.
 
*/
{
   return a_list.remove(0, x);
}

template <typename List_entry> 
Error_code insert_last(const List_entry &x, List<List_entry> &a_list)
/* 
 
Post:
Parameter x is inserted
as the last entry of the List a_list.
 
*/
{
   return a_list.insert(a_list.size(), x);
}

template <typename List_entry> 
Error_code remove_last(List_entry &x, List<List_entry> &a_list)
/* 
 
Post:
A code of underflow is returned if List a_list is
empty.  Otherwise,
the last entry
of List a_list is removed and reported as x.
 
*/
{
   return a_list.remove(a_list.size() - 1 , x);
}

template <typename List_entry> 
Error_code median_list(List_entry &x, List<List_entry> &a_list)
/* 
 
Post:
A code of underflow is returned if List a_list is
empty.  Otherwise,
the median entry
of List a_list is reported as x.
 
*/
{
   return a_list.retrieve((a_list.size() - 1) / 2, x);
}

template <typename List_entry> 
Error_code interchange(int pos1, int pos2, List<List_entry> &a_list)
/* 
 
Post:
Any entries at positions pos1 and pos2 of List a_list
are interchanged.  If either entry is missing a code of
range_error is returned.
 
*/
{
   List_entry entry1, entry2;
   Error_code outcome = a_list.retrieve(pos1, entry1);
   if (outcome == success)
      a_list.retrieve(pos2, entry2);
   if (outcome == success)
      a_list.replace(pos1, entry2);
   if (outcome == success)
      a_list.replace(pos2, entry1);
   return outcome;
}


template< class List_entry >
void reverse_traverse_list(List<List_entry> &a_list,
                                 void (*visit)(List_entry &))
/* 
 
Post:
The List a_list is traversed, in reverse order,
and the function *visit is applied to all entries.
 
*/
{
   List_entry item;
   for (int i = a_list.size() - 1; i >= 0; i--) {
      a_list.retrieve(i, item);
      (*visit)(item);
   }
}

// E10:
template <typename List_entry>
bool reverse(List<List_entry> &a_list)
/* 
Post: Reverses the order of all entries in a_list.
A code of fail is returned in case the reversal cannot
be completed.
*/
{
   List<List_entry> temp;
   List_entry item;
   Error_code outcome = success;
   for (int i = 0; i < a_list.size(); i++) {
       a_list.retrieve(i, item);
       if (temp.insert(i, item) != success)
           outcome = fail;
   }

   for (int j = 0; j < a_list.size(); j++) {
       temp.retrieve(j, item);
       a_list.replace(a_list.size() - 1 - j, item);
   }
   return outcome;
}

// E11:
template <typename List_entry> 
Error_code split(List<List_entry> &source, List<List_entry> &oddlist, List<List_entry> &evenlist)
/* 
 
Post:
Copies all entries from
source so that those in odd-numbered positions make up oddlist and those
in even-numbered positions make up evenlist.
Returns an error code of overflow in case either output list
fills before the copy is complete.
 
*/
{
   List_entry item;
   Error_code outcome = success;
   for (int i = 0; i < source.size(); i++) {
       source.retrieve(i, item);
       if (i % 2 != 0) {
          if (oddlist.insert(oddlist.size(), item) == overflow)
              outcome = overflow;
       }
       else
          if (evenlist.insert(evenlist.size(), item) == overflow)
              outcome = overflow;
   }
   return outcome;
}

template <typename List_entry> 
Error_code copy(List<List_entry> &dest, const List<List_entry> &source)
/* 
 
Post:
All entries are copied from
source into dest; source remains unchanged.
A code of fail is returned if a complete copy
cannot be made.
 
*/
{
   List_entry item;
   Error_code outcome = success;
   while (!dest.empty()) dest.remove(0, item);
   for (int i = 0; i < source.size(); i++) {
	   if (source.retrieve(i, item) != success) {
		   outcome = fail;
		   while (!dest.empty()) dest.remove(0, item);
		   return outcome;
	   }
       if (dest.insert(i, item) != success) {
		   outcome = fail;
		   while (!dest.empty()) dest.remove(0, item);
		   return outcome;
	   }
   }
   return outcome;
}

template <typename List_entry> 
Error_code join(List<List_entry> &list1, List<List_entry> &list2)
/*
Post:
All entries from
list1 are copied onto the end of list2.
A code of overflow is returned if list2 is filled up
before the copying is complete.
*/
{
   List_entry item;
   for (int i = 0; i < list1.size(); i++) {
       list1.retrieve(i, item);
       if (list2.insert(list2.size(), item) != success)
             return overflow;
   }
   return success;
}
/*
void write_entry(char &c)
{
    cout << c << " ";
}

void insert_1_to_entry(char &c)
{
    c++;
}

template <class List_entry> 
void printList( const char *text_p , List<List_entry> &list )
{
	cout << text_p << endl;
	if ( list.size() > 0 ) {
		list.traverse( write_entry );
		cout << endl;
	}
	else
		cout << "empty." << endl;
}
*/