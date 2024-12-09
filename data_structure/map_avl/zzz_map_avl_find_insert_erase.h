#ifndef ZZZ_MAP_AVL_FIND_INSERT_DELETE
#define ZZZ_MAP_AVL_FIND_INSERT_DELETE

/*
int compare(const KeyT& k1, const KeyT& k2);

node* find_node(const KeyT& k,node* r);
node* find_min_node(node* r);
node* find_max_node(node* r);

node* &child_link(node* parent, const KeyT& k);
node* insert_node(const KeyT& key);
node* insert_node_recursive(const MapT& val, node*& r, node*& ptr);

node* erase_node(const KeyT& key, node* n);
node* erase_node_recursive(const KeyT &key, node*& r);
void delete_all_nodes(node *r);

node* rebalance(node* n);
node* rotate_left_child(node* n); 
node* rotate_right_child(node* n);
*/

#include "zzz_hh_map_avl.h"

namespace zzz {

template <typename KeyT, typename ValueT, typename Comp>
int map_avl<KeyT, ValueT, Comp>::compare(const KeyT& k1, const KeyT& k2) {
    if(lesser(k1, k2)) { return -1; }
    if(lesser(k2, k1)) { return 1; }
    return 0;
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::node*  map_avl<KeyT, ValueT, Comp>::find_node(const KeyT& k, 
                                                                                    typename map_avl<KeyT, ValueT, Comp>::node* pointer,
                                                                                    typename map_avl<KeyT, ValueT, Comp>::node*& parent) {
    while(pointer){
        int not_equal = compare(k, pointer->data.first);
        if(!not_equal){ return pointer; }
        parent = pointer;
        pointer = not_equal < 0 ? pointer->left : pointer->right;
    }
    return NULL;
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::node*  map_avl<KeyT, ValueT, Comp>::find_min_node() {
    node* n = map_root;
    if(!n){ return n; }
    while(n->left) { n = n->left; }
    return n;
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::node*  map_avl<KeyT, ValueT, Comp>::find_max_node() {
    node* n = map_root;
    if(!n){ return n; }
    while(n->right) { n = n->right; }
    return n;
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::node*&  map_avl<KeyT, ValueT, Comp>::child_link(node* parent, const KeyT& k) {
    if(!parent) { return map_root; }
    return lesser(k, parent->data.first) ? parent->left : parent->right;
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::node* map_avl<KeyT, ValueT, Comp>::insert_node(const KeyT& key) {
    node* _parent = NULL;
    node* that_node = find_node(key, map_root, _parent);
    if(!that_node){
        ++map_size;
        that_node = new node(std::make_pair(key, ValueT()), NULL, NULL, _parent);
        child_link(_parent, key) = that_node;
        while(_parent) {
            _parent = rebalance(_parent);
            map_root = _parent;
            _parent = _parent->parent;
        }
    }
    return that_node;
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::node* map_avl<KeyT, ValueT, Comp>::insert_node_recursive(const MapT& val, node*& n, node*& ptr) {
    if(!n) {
        map_size++;
        ptr = n = new node(val);
    }else{

        int not_equal = compare(val.first, n->data.first);
        if(not_equal < 0){
            n->set_left(insert_node(val, n->left, ptr));
        }else if(not_equal > 0){
            n->set_right(insert_node(val, n->right, ptr));
        }else{
            ptr = n;
        }

    }
    return n;
}


template <typename KeyT, typename ValueT, typename Comp>
void map_avl<KeyT, ValueT, Comp>::erase_node(const KeyT& key, node* n) {
    while(n){
        int not_equal = compare(key, n->data.first);
        if(not_equal < 0) {
            n = n->left;
        }else if(not_equal > 0) {
            n = n->right;
        }else{
            if(n->left && n->right){
                node* replace = n->right;
                while(replace->left){
                    replace = replace->left;
                }
                n->data = replace->data;
                n = replace;
            }
            node* temp = n;
            node* _parent  = n->parent;
            node* replace = (!n->left ? n->right : n->left);
            --map_size;
            if(_parent) {
                if(_parent->left == n){
                    _parent->left = replace;
                }else{
                    _parent->right = replace;
                }
            }else{
                map_root = replace;
            }
            if(replace){
                replace->parent = _parent;
            }
            while(_parent){
                _parent = rebalance(_parent);
                map_root = _parent;
                _parent = _parent->parent;
            }
            delete temp;
            break;
        }
    }
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::node* map_avl<KeyT, ValueT, Comp>::erase_node_recursive(const KeyT& k, node*& n) {
    if(!n){ return n; }
    int not_equal = compare(k, n->data.first);
    if(not_equal < 0) {
        n->set_left(erase_node_recursive(k, n->left));
    }else if(not_equal > 0) {
        n->set_right(erase_node_recursive(k, n->right));
    }else{
        if(!n->left || !n->right) {
            node* temp_node = n;
            n = (!n->left ? n->right : n->left);
            delete temp_node;
            map_size--;
        }else{
            node* replace_node = n->right;
            while(replace_node->left) {
                replace_node = replace_node->left;
            }
            n->data = replace_node->data;
            n->set_right(erase_node_recursive(replace_node->data.first, replace_node));
        }
    }
    return n;
}


template <typename KeyT, typename ValueT, typename Comp>
void map_avl<KeyT, ValueT, Comp>::delete_all_nodes(node* n){
    if(!n){ return; }
    delete_all_nodes(n->left);
    delete_all_nodes(n->right);
    delete n;
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::node*  map_avl<KeyT, ValueT, Comp>::rebalance(node* n) {
    if(!n){ return n; }
    int balance_factor = n->balance_value();
    if(balance_factor > 1) {
        if(n->right->balance_value() < 0){
            n->set_right( rotate_left_child(n->right) );
        }
        n = rotate_right_child(n);
    } else if (balance_factor < -1) {
        if(n->left->balance_value() > 0){
            n->set_left( rotate_right_child(n->left) );
        }
        n = rotate_left_child(n);
    }
    n->set_height();
    return n;
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::node*  map_avl<KeyT, ValueT, Comp>::rotate_left_child(node* old_root) {

    node* new_root = old_root->left;
    new_root->set_parent(old_root->parent, old_root);
    old_root->set_left(new_root->right);
    new_root->set_right(old_root);

    new_root->right->set_height();
    new_root->set_height();
    return new_root;
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::node*  map_avl<KeyT, ValueT, Comp>::rotate_right_child(node* old_root) {
    
    node* new_root = old_root->right;
    new_root->set_parent(old_root->parent, old_root);
    old_root->set_right(new_root->left);
    new_root->set_left(old_root);

    new_root->left->set_height();
    new_root->set_height();
    return new_root;    
}


}
#endif
