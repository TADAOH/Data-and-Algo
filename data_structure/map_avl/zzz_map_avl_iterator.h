#ifndef ZZZ_MAP_AVL_ITERATOR
#define ZZZ_MAP_AVL_ITERATOR

/*
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
map_avl<KeyT, ValueT, Comp>::tree_iterator::tree_iterator(typename map_avl<KeyT, ValueT, Comp>::node* r, 
                                                                   map_avl<KeyT, ValueT, Comp>* c): ptr(r), container(c) {}


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
        ptr = container->find_min_node();
        return *this;
    }
    if(ptr->right){
        ptr = ptr->right;
        while(ptr->left){
            ptr = ptr->left;
        }
    }else{
        node* _parent = ptr->parent;
        while(_parent && _parent->right == ptr){
            ptr  = _parent;
            _parent = _parent->parent;
        }
        ptr = _parent;
    }
    return *this;
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::tree_iterator&  map_avl<KeyT, ValueT, Comp>::tree_iterator::operator--() {
    if(!ptr){
        ptr = container->find_max_node();
        return *this;
    }
    if(ptr->left){
        ptr = ptr->left;
        while(ptr->right){
            ptr = ptr->right;
        }
    }else{
        node* _parent = ptr->parent;
        while(_parent && _parent->left == ptr){
            ptr = _parent;
            _parent = _parent->parent;
        }
        ptr  = _parent;
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
