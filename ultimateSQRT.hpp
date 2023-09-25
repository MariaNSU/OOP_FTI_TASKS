#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

template <typename T>
class sqrtTraits;

template<typename T>
class sqrtTraits<std::vector<T>> {
    typedef std::vector<T> sqrtType;
};

template <typename K, typename V>
class sqrtTraits<std::map<K, V>>{
public:
    typedef std::map<K, V> sqrtType;
};

template <typename T>
T sqrT(const T & x){
    if (x >= 0) return sqrt(x);
    else return 0;
}

template <typename T>
auto sqrT(const T & inp){
    typedef typename sqrtTraits<T>::sqrtType sqrtType;
    sqrtType out;
    return out;






}

template <typename T>
std::list<T> sqrT(const std::list<T> & l) {
    std::list<T> res(l.size());
    std::transform(l.begin(), l.end(), res.begin(), [](T element){return sqrT(element);} );
    return res;
}

template <typename T>
std::forward_list<T> sqrT(const std::list<T> & l){
    std::list<T> res(l.size());
    std::transform(l.begin(), l.end(), res.begin(), [](const T & element){return sqrT(element);} );
    return res;
}

template <typename T>
std::set<T> sqrT(const std::set<T> & s){
    std::set<T> res;
    for(auto el: s) res.insert(sqrT(el));
    return res;
}

template <typename T>
std::unordered_set<T> sqrT(const std::unordered_set<T> & s){
    std::unordered_set<T> res;
    for(auto el: s) res.insert(sqrT(el));
    return res;
}


template <typename K, typename V>
std::unordered_map<K, V> sqrT(const std::unordered_map<K, V> & m){
    std::unordered_map<K, V> res;
    for(auto el: m) res.insert(sqrT(el));
    return res;
}

template <typename K, typename V>
std::map<K, V> sqrT(const std::map<K, V> & m) {
    std::map<K, V> res;
    for(auto el: m) res.insert(sqrT(el));
    return res;
}

template <typename K, typename V>
std::pair<K, V> sqrT(const std::pair <K, V> &p ) {
    return std::make_pair(p.first,sqrT(p.second));
}


