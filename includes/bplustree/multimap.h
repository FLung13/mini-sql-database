#ifndef MULTIMAP_LUNG_H__
#define MULTIMAP_LUNG_H__
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include "bplustree.h"
#include "mpair.h"

using namespace std;

template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator{
    public:
        friend class MMap;

        Iterator()
        {
            _it = NULL;
        }

        Iterator(typename map_base::Iterator it)
        {
            _it = it;
        }

        Iterator operator ++(int unused)
        {
            typename map_base::Iterator holder = _it;
            ++_it;
            
            return holder;
        }

        Iterator operator ++()
        {
            return ++_it;
        }

        MPair<K, V> operator *()
        {
            return *_it;
        }

        friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
        {
            return lhs._it == rhs._it;
        }

        friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
        {
            return !(lhs==rhs);        
        }

    private:
        typename map_base::Iterator _it;
    };

    MMap();

//  Iterators
    Iterator begin()
    {
        return Iterator(mmap.begin());
    }

    Iterator end()
    {
        return Iterator(mmap.end());

    }

//  Capacity
    int size() const;
    bool empty() const;

//  Element Access
    const vector<V>& operator[](const K& key) const;
    vector<V>& operator[](const K& key);

//  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();

//  Operations:
    bool contains(const K& key) const ;
    vector<V> &get(const K& key);

    Iterator find(const K& key)
    {
        return Iterator(mmap.find(key));
    }
    
    int count(const K& key);
    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:

    Iterator lower_bound(const K& entry)
    {
        // return mmap.lower_bound(entry);
        return Iterator(mmap.lower_bound(entry));
    }

    Iterator upper_bound(const K& entry)
    {
        return Iterator(mmap.upper_bound(entry));
        // return mmap.upper_bound(entry);
    }

    Iterator equal_range(const K& entry)
    {
        return Iterator(mmap.equal_range(entry));
        // return mmap.equal_range(entry);
    }

    vector<V> &at(const K& key);

    void print_lookup();

    bool is_valid();

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me){
        outs<<print_me.mmap<<endl;
        return outs;
    }

private:
    BPlusTree<MPair<K, V> > mmap = new BPlusTree<MPair<K,V>>(true);
};


//=========================================================================//
//=========================================================================//
//=========================================================================//
//=========================================================================//
//=========================================================================//
//=========================================================================//


template <typename K, typename V>
inline MMap<K, V>::MMap()
{
    mmap = new BPlusTree<MPair<K,V>>(true);
}


template <typename K, typename V>
inline int MMap<K, V>::size() const
{
    return mmap.size();
}

template <typename K, typename V>
inline bool MMap<K, V>::empty() const
{
    return mmap.empty();
}

template <typename K, typename V>
inline const vector<V> &MMap<K, V>::operator[](const K &key) const
{
    return mmap.get(key).value_list;
}

template <typename K, typename V>
inline vector<V> &MMap<K, V>::operator[](const K &key)
{
    return mmap.get(key).value_list;
}

template <typename K, typename V>
inline void MMap<K, V>::insert(const K &k, const V &v)
{
    MPair<K,V> entry(k,v);
    mmap.insert(entry);
}

template <typename K, typename V>
inline void MMap<K, V>::erase(const K &key)
{
    mmap.remove(key);
}

template <typename K, typename V>
inline void MMap<K, V>::clear()
{
    mmap.clear_tree();
}

template <typename K, typename V>
inline bool MMap<K, V>::contains(const K &key) const
{
    return mmap.contains(key);
}

template <typename K, typename V>
inline vector<V> &MMap<K, V>::get(const K &key)
{
    return mmap.get(key).value_list;
}

template <typename K, typename V>
inline int MMap<K, V>::count(const K &key)
{
    return mmap.size();
}

template <typename K, typename V>
inline vector<V> &MMap<K, V>::at(const K &key)
{
    return mmap.get_existing(key).value_list;
}

template <typename K, typename V>
inline void MMap<K, V>::print_lookup()
{
    mmap.print_lookup();    
}

template <typename K, typename V>
inline bool MMap<K, V>::is_valid()
{
    return false;
}

#endif