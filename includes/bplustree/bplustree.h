#ifndef BPLUSTREE_LUNG_H__
#define BPLUSTREE_LUNG_H__
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include "assert.h"
#include "btree_array_funcs.h"
using namespace std;

template <class T>
class BPlusTree
{
public:
    class Iterator{
    public:
        friend class BPlusTree;
        Iterator(BPlusTree<T>* _it=NULL, int _key_ptr = 0):
                                                it(_it), key_ptr(_key_ptr){}

        T operator *()
        {
            return (it->data[key_ptr]);
        }

        Iterator operator++(int un_used)
        {
            // BPlusTree<T>* Holder = it;
            // ++(it);
            // return Iterator(Holder,key_ptr);
            Iterator hold = *this;
            ++(*this);
            return hold;
            
            // int hold_key = key_ptr;
            
            // if (key_ptr == it->data_count)
            // {
            //     it = it->next;
            //     key_ptr = 0;
            // } else
            // {
            //     key_ptr++;
            // }
            // return Iterator(Holder, key_ptr);
        }
            

        Iterator operator++()
        {
            //BPlusTree<T>* Holder = it;
            //int hold_key = key_ptr;
            key_ptr++;
            if (key_ptr >= it->data_count)
            {
                it = it->next;
                key_ptr = 0;
            }
            
            return *this;
        }

        friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
        {
            // if(lhs.it == rhs.it){
            //     return true;
            // }
            // return false;
            return lhs.it == rhs.it && lhs.key_ptr == rhs.key_ptr;
        }
        
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
        {
            // if(lhs.it != rhs.it){
            //     return true;
            // }
            // return false;
            return !(lhs==rhs);
        }

        void print_Iterator(){
            if (it){
                cout<<"iterator: ";
                print_array(it->data, it->data_count, key_ptr);
            }
            else{
                cout<<"iterator: NULL, key_ptr: "<<key_ptr<<endl;
            }
        }
        bool is_null(){return !it;}
        void info(){
            cout<<endl<<"Iterator info:"<<endl;
            cout<<"key_ptr: "<<key_ptr<<endl;
            cout<<"it: "<<*it<<endl;
        }

    private:
        BPlusTree<T>* it;
        int key_ptr;
    };

    BPlusTree(bool dups = false);
    BPlusTree(T *a, int size, bool dups = false);

    //big three:
    BPlusTree(const BPlusTree<T>& other);
    ~BPlusTree();
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS);

    void copy_tree(const BPlusTree<T>& other);  //copy other into this object
    void copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node);

    void insert(const T& entry);   //insert entry into the tree
    void remove(const T& entry);   //remove entry from the tree
    void clear_tree();             //clear this object (delete all nodes etc.)

    bool contains(const T& entry) const; //true if entry can be found
    T& get(const T& entry);              //return a reference to entry
    const T& get(const T& entry)const;   //return a reference to entry
    T& get_existing(const T& entry);     //return a reference to entry
    Iterator find(const T& key)
    {      
        int i = first_ge(data, data_count, key);
        bool found = (i<data_count && data[i]==key);

        if(found && is_leaf())
        {
            return Iterator(this, i);
        } 
        else if(is_leaf() && !found)
        {
            return Iterator();
        } 
        else if(found && !is_leaf())
        {
            return subset[i+1]->find(key);
        }  
        else if(!found && !is_leaf())
        {
            return subset[i]->find(key);
        }                            //return an iterator to this key.
        return Iterator();                         //     NULL if not there.

    }         
    Iterator lower_bound(const T& key)
    {
                                         //return first that goes NOT BEFORE
                                         // key entry or next if does not
                                         // exist: >= entry
        // return find(key);
        // int i = first_ge(data, data_count, key);
        // // bool found = (i<data_count && key<=data[i]);
        // if(key <= data[i] && is_leaf())
        // {
        //     return Iterator(this, i);
        // } 
        // else if(key <= data[i] && !is_leaf())
        // {
        //     return subset[i]->lower_bound(key);
        // }  
        //                                  //return an iterator to this key.
        // return Iterator(NULL);    
        int i = 0;
        for (; i < data_count; i++)
        {
            if(key <= data[i])
            {
                break;
            } 
            // else if (data[i] >= entry)
            // {
            //     return i;
            // }
        }
        // cout << i << endl;
        bool found = key == data[i];
        // cout << i << endl;
        // cout << boolalpha << found << endl;
        if(is_leaf() && i < data_count)
        {
            Iterator l(this, i);
            // l++;
            return l;
        } 
        else if(is_leaf() && !found)
        {
            Iterator l(this, i);
            l++;
            return l;
        } 
        else if(found && !is_leaf())
        {
            return subset[i+1]->lower_bound(key);
        }  
        else if(!found && !is_leaf())
        {
            return subset[i]->lower_bound(key);
        }                            //return an iterator to this key.
        return Iterator();                      //return an iterator to this key.
          
    }

    Iterator upper_bound(const T& key)   
    {                                    //return first that goes AFTER key
                                         //exist or not, the next entry  >entry   
        // int i = first_ge(data, data_count, key);
        // // bool found = (i<data_count && key<=data[i]);
        // if(key < data[i] && is_leaf())
        // {
        //     return Iterator(this, i);
        // } 
        // else if(key < data[i] && !is_leaf() && key < subset[i]->data[0])
        // {
        //     return subset[i]->upper_bound(key);
        // }
        // else if(key < data[i] && !is_leaf() && key < subset[i+1]->data[0])
        // {
        //     return subset[i+1]->upper_bound(key);
        // }
        //                                  //return an iterator to this key.
        // return Iterator(NULL);     
        int i = 0;
        // cout << "Datac: " << data_count << endl;
        // cout << data[i] << endl;
        for (; i < data_count; i++)
        {
            // cout << i << endl;
            if(key < data[i])
            {
                break;
            } 
        }
        bool found = key == data[i] && i < data_count;
        // cout << data[i] << endl;
        // cout << i << endl;
        // cout << boolalpha << found << endl;
        if(is_leaf() && i < data_count)
        {
            Iterator l(this, i);
            // l++;
            return l;
        } 
        else if(is_leaf() && !found)
        {
            Iterator l(this, i);
            l++;
            return l;
        } 
        else if(found && !is_leaf())
        {
            return subset[i+1]->upper_bound(key);
        }  
        else if(!found && !is_leaf())
        {
            return subset[i]->upper_bound(key);
        }                            //return an iterator to this key.
        return Iterator();  


    }

    Iterator equal_range(const T& key)
    {
        return find(key);
    }

    int size() const;                    //count the number of elements

    bool empty() const;                  //true if the tree is empty

    void print_tree(int level = 0,
                    ostream &outs=cout) const;
    friend ostream& operator<<(ostream& outs,
                               const BPlusTree<T>& print_me){
        print_me.print_tree(0, outs);
        return outs;
    }

    bool is_valid();
    string in_order();
    string pre_order();
    string post_order();

    void print_lookup();

    Iterator begin()
    {
        return Iterator(get_smallest_node());
        // return Iterator();
    }

    Iterator end()
    {
        return Iterator(NULL);
    }

    ostream& list_keys(Iterator from = NULL, Iterator to = NULL){
        if (from == NULL) from = begin();
        if (to == NULL) to = end();
        for (Iterator it = from; it != to; it++)
            cout<<*it<<" ";
        return cout;

    }

private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok = false;                //true if duplicate keys are allowed
    int data_count = 0;                  //number of data elements
    T data[MAXIMUM + 1];                 //holds the keys
    int child_count = 0;                 //number of children
    BPlusTree* subset[MAXIMUM + 2];      //subtrees
    BPlusTree* next = nullptr;
    bool is_leaf() const
    {return child_count==0;}             //true if this is a leaf node

    T* find_ptr(const T& entry);         //return a pointer to this key.
                                         // NULL if not there.

    //insert element functions
    void loose_insert(const T& entry);   //allows MAXIMUM+1 data elements in
                                         //   the root
    void fix_excess(int i);              //fix excess in child i

    //remove element functions:
    void loose_remove(const T& entry);  //allows MINIMUM-1 data elements
                                        //  in the root

    BPlusTree<T>* fix_shortage(int i);  //fix shortage in child i
    // and return the smallest key in this subtree
    BPlusTree<T>* get_smallest_node();
    void get_smallest(T& entry);      //entry := leftmost leaf
    void get_biggest(T& entry);       //entry := rightmost leaf
    void remove_biggest(T& entry);    //remove the biggest child of tree->entry
    void transfer_left(int i);        //transfer one element LEFT from child i
    void transfer_right(int i);       //transfer one element RIGHT from child i
    BPlusTree<T> *merge_with_next_subset(int i); //merge subset i with  i+1

};


//=========================================================================//
//=========================================================================//
//=========================================================================//
//=========================================================================//
//=========================================================================//
//=========================================================================//


template <class T>
inline BPlusTree<T>::BPlusTree(bool dups)
{
    dups_ok = dups;
    data_count = 0;
    child_count = 0;
    next = nullptr;
}

template <class T>
inline BPlusTree<T>::BPlusTree(T *a, int size, bool dups)
{
    dups_ok = dups;
    data_count = 0;
    child_count = 0;
    next = nullptr;
    for (int i = 0; i < size; i++)
    {
        insert(a[i]);
    }
}

template <class T>
inline BPlusTree<T>::BPlusTree(const BPlusTree<T> &other)
{
    dups_ok = other.dups_ok;
    copy_tree(other);
}

template <class T>
inline BPlusTree<T>::~BPlusTree()
{
    clear_tree();
}

template <class T>
inline BPlusTree<T> &BPlusTree<T>::operator=(const BPlusTree<T> &RHS)
{
    if (this == &RHS)
    {
        return *this;
    }
    dups_ok = RHS.dups_ok;
    clear_tree();
    copy_tree(RHS);

    return *this;
}

template <class T>
inline void BPlusTree<T>::copy_tree(const BPlusTree<T> &other)
{
    BPlusTree<T>* last = nullptr;
    copy_tree(other,last);
} 
    
template <class T>
inline void BPlusTree<T>::copy_tree(const BPlusTree<T> &other, BPlusTree<T> *&last_node)
{
    copy_array(data, other.data, data_count, other.data_count);
    child_count = other.child_count;
    
    for (int i = 0; i < other.child_count; i++)
    {
        BPlusTree<T>* new_node = new BPlusTree(dups_ok);
        if(other.subset[i] && !other.subset[i]->is_leaf())
        {
            new_node->copy_tree(*other.subset[i]);
            
        } 
        else if (other.subset[i] && other.subset[i]->is_leaf())
        {
            new_node->copy_tree(*other.subset[i]);
            if (last_node == nullptr)
            {
                last_node = this;
            } 
            else
            {
                last_node->next = this;
                last_node = this;
            }
            next = nullptr;
        }
        
        subset[i] = new_node;
    }
}

template <class T>
inline void BPlusTree<T>::insert(const T &entry)
{
    loose_insert(entry);
    if(data_count > MAXIMUM)
    {
        BPlusTree<T>* Growtree = new BPlusTree(dups_ok);
        copy_array(Growtree->data, data, Growtree->data_count, data_count);
        copy_array(Growtree->subset, subset, Growtree->child_count, child_count);
        data_count = 0;
        child_count = 1;
        subset[0] = Growtree;
        next = nullptr;
        fix_excess(0);
    }
}

template <class T>
inline void BPlusTree<T>::remove(const T &entry)
{
    loose_remove(entry);

    if (data_count < MINIMUM && !is_leaf())
    {
        // cout << "Shrinking tree\n";
        BPlusTree<T>* shrinkptr = subset[0];
        copy_array(data, shrinkptr->data, data_count, shrinkptr->data_count);
        copy_array(subset, shrinkptr->subset, child_count, shrinkptr->child_count);
        shrinkptr->data_count = 0;
        shrinkptr->child_count = 0;
        delete shrinkptr;
        shrinkptr = nullptr;
    }

}

template <class T>
inline void BPlusTree<T>::clear_tree()
{
    if(!empty())
    {
        if(!is_leaf())
        {
            for (int i = 0; i < data_count; i++)
            {
                subset[i]->clear_tree();
                delete subset[i];
                subset[i] = nullptr;
            }

        }
        
        data_count = 0;
        child_count = 0;

    }
}

template <class T>
inline bool BPlusTree<T>::contains(const T &entry) const
{
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i]==entry);

    if(is_leaf())
    {
        if(found)
        {
            return true;
        } 
        else
        {
            return false;
        }
    } 
    else if (found)
    {
        return subset[i+1]->contains(entry);
    }
    else
    {
        return subset[i]->contains(entry);
    }
    return false;
}

template <class T>
inline T &BPlusTree<T>::get(const T &entry)
{
    // assert(contains(entry));
    if (!contains(entry))
    {
        insert(entry);
    }

    return get_existing(entry);
}

template <class T>
inline const T &BPlusTree<T>::get(const T &entry) const
{
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i]==entry);

    if(is_leaf())
    {
        if(found)
        {
            const T *ptr = &data[i];
            return *ptr;
        } 
        else
        {
            return nullptr;
        }
    } 
    if (found)
    {
        return subset[i+1]->contains(entry);
    }
    else
    {
        return subset[i]->contains(entry);
    }
    return nullptr;   
    
}

template <class T>
inline T &BPlusTree<T>::get_existing(const T &entry)
{
    assert(contains(entry));
    const bool debug = false;
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i]==entry);
    
    if (is_leaf())
    {
        if (found)
        {
            T *ptr = &data[i];
            return *ptr;
        }
        else
        {
            if (debug) cout<<"get_existing was called with nonexistent entry"<<endl;
            assert(found && "Found but doesn't exist");
        }
    }
    if (found)
    {
        return subset[i+1]->get(entry);
    }
    else
    {
        return subset[i]->get(entry);
    }
}

template <class T>
inline int BPlusTree<T>::size() const
{
    return data_count;
}

template <class T>
inline bool BPlusTree<T>::empty() const
{
    return (data_count ==0);
    // return true;
}

template <class T>
inline void BPlusTree<T>::print_lookup()
{
    if(!is_leaf())
    {
        // outs << setw(6*level) << "\u23B4" << endl;
        for(int i = 0; i <= data_count; i++)
        {
            if (subset[i])
            {
                subset[i]->print_lookup();
            }
        }
    
    } else if (is_leaf())
    {
        for (int i = 0; i < data_count; i++)
        {   
            cout << setw(10) << data[i] << endl;        
        }
    }
}

template <class T>
inline void BPlusTree<T>::print_tree(int level, ostream &outs) const
{
    if(!is_leaf())
    {
        subset[child_count-1]->print_tree(level+1);
        // outs << setw(6*level) << "\u23B4" << endl;
        for(int i = data_count-1; i >= 0; i--)
        {
            outs << setw(6*level) << " " << "[" << data[i] << "]" << endl;
            // outs << setw(8*level) << " " << "[" << data[i] << "][D: " << data_count << "][C: " << child_count << "]" << endl;
            // print_array(data, data_count-1, level);
            subset[i]->print_tree(level+1);
        }
        // outs << setw(6*level) << "\u23B5" << endl;
    
    } else if (is_leaf())
    {
        // outs << setw(6*level) << "\u23B4" << endl;
        print_array(data, data_count, level);
        // for(int i = data_count-1; i >= 0; i--)
        // {
            // outs << setw(8*level) << " " << "[" << data[i] << "][D: " << data_count << "][C: " << child_count << "]" << endl;
            // outs << setw(6*level) << " " << "[" << data[i] << "]" << endl;
        // }
        // outs << setw(6*level) << "\u23B5" << endl;
    }
}

template <class T>
inline bool BPlusTree<T>::is_valid()
{
    return false;
}

template <class T>
inline string BPlusTree<T>::in_order()
{
    if(!data_count) {return string();}
    string result;

    for (int i = 0; i < data_count; i++)
    {
        if(is_leaf())
        {
            for (int j = 0; j < data_count; j++)
            {
                result = result + to_string(data[j]) + "|";
            }
            return result;
        }
        result += subset[i]->in_order();
        result = result  + to_string(data[i]) + "|";
        if(subset[child_count-1] && i == data_count - 1){
            result += subset[child_count-1]->in_order();
        }

    }

    return result;
}

template <class T>
inline string BPlusTree<T>::pre_order()
{
 if(!data_count) {return string();}
    string result;

    for (int i = 0; i < data_count; i++)
    {
        if(is_leaf())
        {
            for (int j = 0; j < data_count; j++)
            {
                result = result + to_string(data[j]) + "|";
            }
            return result;
        }
        result = result  + to_string(data[i]) + "|";
        result += subset[i]->pre_order();
        if(subset[child_count-1] && i == data_count - 1){
            result += subset[child_count-1]->pre_order();
        }
    }

    return result;
}

template <class T>
inline string BPlusTree<T>::post_order()
{
    if(!data_count) {return string();}
    string result;

    for (int i = 0; i < data_count; i++)
    {
        if(child_count)
        {
            result += subset[i]->post_order();
            // result += subset[i+1]->post_order();
        }
        if(is_leaf())
        {
            for (int j = 0; j < data_count; j++)
            {
                result = result + to_string(data[j]) + "|";
            }
            return result;
        }
        if(subset[child_count-1] && i == data_count - 1){
            if (i != 0)
            {
                result = result  + to_string(data[i-1]) + "|";
            }
            
            result += subset[child_count-1]->post_order();
            result = result  + to_string(data[i]) + "|";
        }
        
    }

    return result;
}

template <class T>
inline T *BPlusTree<T>::find_ptr(const T &entry)
{
    BPlusTree<T>* ptr = nullptr;
    ptr = get(entry);
    return ptr;
}

template <class T>
inline void BPlusTree<T>::loose_insert(const T &entry)
{
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i] == entry);

    if (found && is_leaf())
    {
        if (!dups_ok)
        {
            data[i] = entry;
        }
        else
        {
            // cout << data[i] << endl;
            data[i] = data[i] + entry;
        }  
    } 
    else if (found && !is_leaf())
    {
        subset[i+1]->loose_insert(entry);
        fix_excess(i+1);
    } 
    else if (!found && is_leaf())
    {
        insert_item(data, i, data_count, entry);
    } 
    else if (!found && !is_leaf())
    {
        subset[i]->loose_insert(entry);
        fix_excess(i);
    }
}

template <class T>
inline void BPlusTree<T>::fix_excess(int i)
{
    if(subset[i]->data_count > MAXIMUM)
    {
        BPlusTree<T>* Newone = new BPlusTree(dups_ok);
        T _midItem;
        split(subset[i]->data, subset[i]->data_count, Newone->data, Newone->data_count);
        split(subset[i]->subset, subset[i]->child_count, Newone->subset, Newone->child_count);
        detach_item(subset[i]->data, subset[i]->data_count, _midItem);
        insert_item(data, i, data_count, _midItem);
        shift_right(subset, child_count, i);
        subset[i+1] = Newone;

        if(subset[i]->is_leaf())
        {
            insert_item(subset[i+1]->data, 0, subset[i+1]->data_count, _midItem);
            subset[i+1]->next = subset[i]->next;
            subset[i]->next = subset[i+1];
        }
    }   
}

template <class T>
inline void BPlusTree<T>::loose_remove(const T &entry)
{
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i]==entry);
    T hold;
    // cout << "i: " << i << endl;
    
    // cout << "data[i]: " << data[i] << endl;
    if(!found && is_leaf())
    {
        // cout << "Not found and is leaf\n";
        return;
    } 
    else if(found && is_leaf())
    {
        // cout << "Found and is leaf\n";
        delete_item(data, i, data_count, hold);
        // cout << "i: " << i << endl;
        
        // cout << "Deleted item: "<< hold << endl;
    } 
    else if (!is_leaf() && !found)
    {
        // cout << "Not found and is not leaf\n";
        subset[i]->loose_remove(entry);
        fix_shortage(i);
    } 
    else if (!is_leaf() && found)
    {
        // cout << "Found and is not leaf\n";
        subset[i+1]->loose_remove(entry);
        fix_shortage(i+1);
        
        i = first_ge(data, data_count, entry);
        if (i<data_count && data[i]==entry)
        {
            subset[i+1]->get_smallest(data[i]);
        }
        cout << data[i] << endl;
  
    }
}

template <class T>
inline BPlusTree<T> *BPlusTree<T>::fix_shortage(int i)
{
    // cout << "Fix shortage\n";
    if(is_leaf() || subset[i]->data_count >= MINIMUM){return nullptr;}

    if(i - 1 >= 0 && subset[i-1]->data_count > MINIMUM)
    {
        cout << "Transfering right\n";
        transfer_right(i);
    } 
    else if(i + 1 < child_count && subset[i+1]->data_count > MINIMUM)
    {
        cout << "Transfering left\n";
        transfer_left(i);
    } 
    else if(i + 1 < child_count)
    {
        cout << "Merge with right child\n";
        merge_with_next_subset(i);
    }
    else
    {
        cout << "Merge with left child\n";
        merge_with_next_subset(i-1);
    }
    return nullptr;
}

template <class T>
inline BPlusTree<T> *BPlusTree<T>::get_smallest_node()
{
    BPlusTree<T>* smallest = nullptr;
    if (subset[0]->is_leaf())
    {   
        smallest = subset[0];
        return smallest;
    } else
    {
        return subset[0]->get_smallest_node();
    } 
}

template <class T>
inline void BPlusTree<T>::get_smallest(T &entry)
{
    if (is_leaf())
    {
        entry = data[0];
    } else
    {
        subset[0]->get_smallest(entry);
    } 
}

template <class T>
inline void BPlusTree<T>::get_biggest(T &entry)
{
    if (is_leaf())
    {
        entry = data[data_count-1];
    } else
    {
        subset[data_count]->get_biggest(entry);
    } 
}

template <class T>
inline void BPlusTree<T>::remove_biggest(T &entry)
{
    if (is_leaf())
    {
        detach_item(data, data_count, entry);
    } else
    {
        subset[data_count]->remove_biggest(entry);
        fix_shortage(data_count);
    } 
}

template <class T>
inline void BPlusTree<T>::transfer_left(int i)
{
    if (subset[i]->is_leaf())
    {
        T hold;
        delete_item(subset[i+1]->data, 0, subset[i+1]->data_count, hold);
        attach_item(subset[i]->data, subset[i]->data_count, hold);
        data[i] = subset[i+1]->data[0];
    }

    else
    {
        attach_item(subset[i]->data, subset[i]->data_count, data[i]);
        if (subset[i]->child_count != 0)
        {
            insert_item(subset[i]->subset, subset[i]->data_count, subset[i]->child_count, subset[i+1]->subset[0]);
        }
        delete_item(subset[i+1]->data, 0, subset[i+1]->data_count, data[i]);
        shift_left(subset[i+1]->subset, subset[i+1]->child_count, 0);
    } 
    
    
}

template <class T>
inline void BPlusTree<T>::transfer_right(int i)
{
    if (subset[i]->is_leaf())
    {
        T hold;
        detach_item(subset[i-1]->data, subset[i-1]->data_count, hold);
        insert_item(subset[i]->data, 0,subset[i]->data_count, hold);
        data[i-1] = subset[i]->data[0];
        if (i < child_count-1)
        {
            data[i] = subset[i+1]->data[0];
        }
        
    }
    else
    {
        T holder = data[i-1];
        insert_item(subset[i]->data, 0, subset[i]->data_count, holder);
        if (subset[i-1]->child_count != 0)
        {
            // cout << "C: " << child_count << endl;
            // cout << "Sub[i-1]->C: " << subset[i-1]->child_count << endl; 
            insert_item(subset[i]->subset, 0, subset[i]->child_count, subset[i-1]->subset[i+1]);
            attach_item(subset[i-1]->subset, subset[i-1]->child_count, subset[i-1]->subset[i]);
            subset[i-1]->child_count = subset[i-1]->data_count;
            // cout << "Sub[i-1]->C: " << subset[i-1]->child_count << endl; 
        }
        detach_item(subset[i-1]->data, subset[i-1]->data_count, holder);
        data[i-1] = holder;
    }
}

template <class T>
inline BPlusTree<T> *BPlusTree<T>::merge_with_next_subset(int i)
{
    T hold;
    BPlusTree<T>* temp = subset[i+1]; // 5. Delete subset[i+1] (Store in a temp ptr)
    if(subset[i]->is_leaf())
    {
        subset[i]->next = temp->next;
        delete_item(data, i, data_count, hold); // 1. Remove data [i]
        if (subset[i+1]->data_count != 0)
        {
            merge(subset[i]->data, subset[i]->data_count, subset[i+1]->data, subset[i+1]->data_count); // 3. Move data items from i+1 to i
        }
        return subset[i];
    }
    else
    {
        delete_item(data, i, data_count, hold); // 1. Remove data [i]

        if (!subset[i]->is_leaf()) // 2. If not leaf, append it to child[i]->data
        {
            ordered_insert(subset[i]->data, subset[i]->data_count, hold);
        }
        

        merge(subset[i]->data, subset[i]->data_count, subset[i+1]->data, subset[i+1]->data_count); // 3. Move data items from i+1 to i

        if (!subset[i]->is_leaf()) // 4. Move sub pointers from i+1 to i
        {
            merge(subset[i]->subset, subset[i]->child_count, subset[i+1]->subset, subset[i+1]->child_count);
        }

        // BPlusTree<T>* temp = subset[i+1]; // 5. Delete subset[i+1] (Store in a temp ptr)
        
        shift_left(subset, child_count, i+1); 

        if (subset[i]->is_leaf()) // 6. If leaf point subset[i]->next to temp->next
        {
            subset[i]->next = temp->next;
        }
        

        temp->data_count = 0; // 7. Delete temp ptr
        temp->child_count = 0;
        temp = nullptr;
    }
    


    return subset[i];
}

#endif