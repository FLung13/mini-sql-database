#ifndef MAP_LUNG_H__
#define MAP_LUNG_H__
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include "bplustree.h"
#include "pair.h"
using namespace std;

template <typename K, typename V>
class Map
{
public:
    typedef BPlusTree<Pair<K, V> > map_base;
    class Iterator{
    public:
        friend class Map;

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
        
        Pair<K, V> operator *()
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

    Map();
//  Iterators
    Iterator begin()
    {
        return Iterator(map.begin());
    }
    
    Iterator end()
    {
        return Iterator(map.end());
    }

//  Capacity
    int size() const;
    bool empty() const;

//  Element Access
    V& operator[](const K& key);
    V& at(const K& key);
    const V& at(const K& key) const;


//  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();
    V get(const K& key);

//  Operations:
    Iterator find(const K& key)
    {
        return map.find(key);
    }
    
    bool contains(const Pair<K, V>& target) const;

    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:

    Iterator lower_bound(const K& entry)
    {
        return Iterator(map.lower_bound(entry));
    }

    Iterator upper_bound(const K& entry)
    {
        return Iterator(map.upper_bound(entry));
    }

    Iterator equal_range(const K& entry)
    {
        return Iterator(map.equal_range(entry));
    }

    void print_lookup();

    bool is_valid(){return map.is_valid();}

    friend ostream& operator<<(ostream& outs, const Map<K, V>& print_me){
        outs<<print_me.map<<endl;
        return outs;
    }
private:
    int key_count;
    BPlusTree<Pair<K, V> > map;
};

//=========================================================================//
//=========================================================================//
//=========================================================================//
//=========================================================================//
//=========================================================================//
//=========================================================================//


template <typename K, typename V>
inline Map<K, V>::Map()
{
    map = new BPlusTree<Pair<K,V>>(false);
    key_count = 0;
}


template <typename K, typename V>
inline int Map<K, V>::size() const
{
    return map.size();
}

template <typename K, typename V>
inline bool Map<K, V>::empty() const
{
    if(map.empty())
    {
        return true;
    }
    return false;
}

template <typename K, typename V>
inline V &Map<K, V>::operator[](const K &key)
{
    return map.get(key).value;
}

template <typename K, typename V>
inline V &Map<K, V>::at(const K &key)
{
    return map.get_existing(key).value;
}

template <typename K, typename V>
inline const V &Map<K, V>::at(const K &key) const
{
    // BPlusTree<Pair<K, V>>* temp = nullptr;
    // temp = map.get(key);
    // return temp;
    return map.get(key).value;
}

template <typename K, typename V>
inline void Map<K, V>::insert(const K &k, const V &v)
{
    key_count++;
    Pair<K,V> entry(k,v);
    map.insert(entry);
}

template <typename K, typename V>
inline void Map<K, V>::erase(const K &key)
{
    map.remove(key);
}

template <typename K, typename V>
inline void Map<K, V>::clear()
{
    map.clear_tree();
}

template <typename K, typename V>
inline V Map<K, V>::get(const K &key)
{
    return map.get(key).value;
}

template <typename K, typename V>
inline bool Map<K, V>::contains(const Pair<K, V> &target) const
{
    return map.contains(target);
}

template <typename K, typename V>
inline void Map<K, V>::print_lookup()
{
    map.print_lookup();
}

#endif