#ifndef ZZZ_MAP_AVL_ITERATOR
#define ZZZ_MAP_AVL_ITERATOR

/*
tree_iterator();
tree_iterator(node* p);

MapT& operator * ();
MapT* operator -> ();
bool  operator == (const tree_iterator& other);
bool  operator != (const tree_iterator& other);

tree_iterator& operator++();
tree_iterator& operator--();
tree_iterator operator++(int);    
tree_iterator operator--(int);    
*/

#include "zzz_hh_map_avl.h"

namespace zzz {

template <typename KeyT, typename ValueT, typename Comp>
map_avl<KeyT, ValueT, Comp>::tree_iterator::tree_iterator(): ptr(NULL) {}


template <typename KeyT, typename ValueT, typename Comp>
map_avl<KeyT, ValueT, Comp>::tree_iterator::tree_iterator(typename map_avl<KeyT, ValueT, Comp>::node* r): ptr(r) {}


template <typename KeyT, typename ValueT, typename Comp>
std::pair<KeyT, ValueT>& map_avl<KeyT, ValueT, Comp>::tree_iterator::operator * () {
    return ptr->data;
}


template <typename KeyT, typename ValueT, typename Comp>
std::pair<KeyT, ValueT>* map_avl<KeyT, ValueT, Comp>::tree_iterator::operator -> () {
    return &(ptr->data);
}


template <typename KeyT, typename ValueT, typename Comp>
bool map_avl<KeyT, ValueT, Comp>::tree_iterator::operator == (const typename map_avl<KeyT, ValueT, Comp>::tree_iterator& other) {
    return ptr == other.ptr;
}


template <typename KeyT, typename ValueT, typename Comp>
bool map_avl<KeyT, ValueT, Comp>::tree_iterator::operator != (const typename map_avl<KeyT, ValueT, Comp>::tree_iterator& other) {
    return ptr != other.ptr;
}

template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::tree_iterator&  map_avl<KeyT, ValueT, Comp>::tree_iterator::operator++() {
    if(!ptr){
        return *this;
    }
    if(ptr->right){
        ptr = ptr->right;
        while(ptr->left){
            ptr = ptr->left;
        }
    }else{
        node* papa = ptr->parent;
        while(papa && papa->right == ptr){
            ptr  = papa;
            papa = papa->parent;
        }
        ptr = papa;
    }
    return *this;
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::tree_iterator&  map_avl<KeyT, ValueT, Comp>::tree_iterator::operator--() {
    if(!ptr){
        return *this;
    }
    if(ptr->left){
        ptr = ptr->left;
        while(ptr->right){
            ptr = ptr->right;
        }
    }else{
        node* papa = ptr->parent;
        while(papa && papa->left == ptr){
            ptr = papa;
            papa = papa->parent;
        }
        ptr  = papa;
    }
    return *this;
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::tree_iterator  map_avl<KeyT, ValueT, Comp>::tree_iterator::operator++(int) {
    tree_iterator temp = (*this);
    ++(*this);
    return temp;
}



template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::tree_iterator  map_avl<KeyT, ValueT, Comp>::tree_iterator::operator--(int) {
    tree_iterator temp = (*this);
    --(*this);
    return temp;
}


}
#endif