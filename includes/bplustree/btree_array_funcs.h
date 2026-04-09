#ifndef BTREE_ARRAY_FUNCS_LUNG_H__
#define BTREE_ARRAY_FUNCS_LUNG_H__
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
using namespace std;

template <class T>
T maximal(const T& a, const T& b);                      //return the larger of the two items

template <class T>
void swap(T& a, T& b);  //swap the two items

template <class T>
int index_of_maximal(T data[ ], int n);                 //return index of the largest item in data

template <class T>
void ordered_insert(T data[ ], int& n, T entry);        //insert entry into the sorted array
                                                        //data with length n

template <class T>
int first_ge(const T data[ ], int n, const T& entry);   //return the first element in data that is
                                                        //not less than entry

template <class T>
void attach_item(T data[ ], int& n, const T& entry);    //append entry to the right of data

template <class T>
void insert_item(T data[ ], int i, int& n, T entry);    //insert entry at index i in data

template <class T>
void detach_item(T data[ ], int& n, T& entry);          //remove the last element in data and place
                                                        //it in entry

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry);   //delete item at index i and place it in entry

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2);   //append data2 to the right of data1

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2);   //move n/2 elements from the right of data1
                                                        //and move to data2

template <class T>
void copy_array(T dest[], const T src[],
                int& dest_size, int src_size);              //copy src[] into dest[]

template <class T>
void print_array(const T data[], int n, int pos = -1);  //print array data

template <class T>
bool is_gt(const T data[], int n, const T& item);       //item > all data[i]

template <class T>
bool is_le(const T data[], int n, const T& item);       //item <= all data[i]

template <class T>
void shift_right(T *a, int &size, int shift_here);

template <class T>
void shift_left(T *a, int& size, int shift_here);

template <class T>
void shift_right(T *a, int& size, T* mark);

template <class T>
void shift_left(T *a, int& size, T* mark);

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list); //print vector list

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme); //list.push_back addme


//=================================================================================
//=================================================================================
//=================================================================================
//=================================================================================
//=================================================================================


template <class T>
inline T maximal(const T &a, const T &b)
{
    return T(max(a,b));
}

template <class T>
inline void swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
inline int index_of_maximal(T data[], int n)
{
    return 0;
}

template <class T>
inline void ordered_insert(T data[], int &n, T entry)
{
    if (n == 0)
    {
        n++;
        data[0] = entry;
        return;
    }
    
    for (int i = 0; i < n; i++)
    {
        if(entry <= data[i])
        {
            shift_right(data, n, i);
            data[i] = entry;
            break;
        }
    }
    // if(n != 0 && entry > data[n-1]){
    //     data[n] = entry;
    //     n++;
    // }
    
}

template <class T>
inline int first_ge(const T data[], int n, const T &entry)
{
    // if (n > 0)
    // {
        for (int i = 0; i < n; i++)
        {
            if(entry <= data[i])
            {
                return i;
            } 
            // else if (data[i] >= entry)
            // {
            //     return i;
            // }
        }
    // }
    return n;
}

template <class T>
inline void attach_item(T data[], int &n, const T &entry)
{
    n++;
    data[n-1] = entry;
}

template <class T>
inline void insert_item(T data[], int i, int &n, T entry)
{
    // cout << "n: " << n << endl;
    // cout << "entry: " << entry << endl;

    if (n > 0)
    {
        shift_right(data, n, i);
        data[i] = entry;
    } else
    {
        n++;
        data[i] = entry;
    }
        
    // n++;
    // for (int j = n; j > i; j--)
    // {

    //     data[j] = data[j-1];   
        
    // }
    
    // data[i] = entry;
    
}

template <class T>
inline void detach_item(T data[], int &n, T &entry)
{
    entry = data[n-1];
    n--;
}

template <class T>
inline void delete_item(T data[], int i, int &n, T &entry)
{
    entry = data[i];
    shift_left(data, n, i);
}

template <class T>
inline void merge(T data1[], int &n1, T data2[], int &n2)
{
    for(int i = 0; i < n2; i++){
        data1[n1++] = data2[i];
    }
    n2 = 0;
}

template <class T>
inline void split(T data1[], int &n1, T data2[], int &n2)
{
    n2 = n1/2;
    int j = 0;
    if (n1 % 2 == 0)
    {
        for (int i = n2; i < n1; i++)
        {
            data2[j] = data1[i];
            j++;
        }
    }
    else 
    {
        for (int i = n2; i < n1; i++)
        {
            data2[j] = data1[i];
        }
    }
    n1 -= n2;
}

template <class T>
inline void copy_array(T dest[], const T src[], int &dest_size, int src_size)
{
    dest_size = src_size;
    for(int i = 0; i < src_size; i++)
    {
        dest[i] = src[i];
    }
}

template <class T>
inline void print_array(const T data[], int n, int pos)
{
    if (n == 0){return;}
    
    // cout << setw(7*pos) << "^" << endl;
    for (int i = n-1; i >= 0; i--)
    {
        cout << setw(6*pos) << "" << "[" << data[i] << "]" << endl;        
    }

}

template <class T>
inline bool is_gt(const T data[], int n, const T &item)
{
    return false;
}

template <class T>
inline bool is_le(const T data[], int n, const T &item)
{
    return false;
}

template <typename T>
inline ostream &operator<<(ostream &outs, const vector<T> &list)
{
    for (int i = 0; i < list.size(); i++)
    {
        outs << list[i] << " ";
    }
    
    return outs;
}

template <typename T>
inline vector<T> &operator+=(vector<T> &list, const T &addme)
{
    list.push_back(addme);
    return list;
}

template <typename T>
inline void shift_right(T *a, int &size, int shift_here){
    
    // shift right in position using index
    size++;
    for(int i = size-1; i > shift_here; i--){
        a[i] = a[i-1];
    } 
}

template <class T>
inline void shift_left(T *a, int& size, int shift_here){

    if(size == shift_here) {return;}
                           // shift left in position using index
    for (int i = shift_here; i < size; i++)
    {
        a[i] = a[i+1];
    }
    size--;

}

template <class T>
inline void shift_right(T *a, int& size, T* mark){

    T index = mark-a;                                   // Get address of index
    assert(index<size);                                 // Assert that index is less than size 
    shift_right(a, size, index);                        // Call function to shift left passing index pos
}

template <class T>
inline void shift_left(T *a, int &size, T *mark)
{
    T index = mark-a;                                   // Get address of index
    assert(index<size);                                 // Call function to shift left passing index pos
    shift_left(a, size, index);
}

#endif

