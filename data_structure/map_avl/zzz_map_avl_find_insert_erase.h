#ifndef ZZZ_MAP_AVL_FIND_INSERT_DELETE
#define ZZZ_MAP_AVL_FIND_INSERT_DELETE

/*
int compare(const KeyT& k1, const KeyT& k2); // done

node* find_node(const KeyT& k,node* r); // done
node* find_min_node(node* r);
node* find_max_node(node* r);

node* &child_link(node* parent, const KeyT& k);
node* insert_node(const MapT& val, node*& r, node*& ptr);
std::pair<node*, node*&> find_or_insert(const KeyT& k, node*& r);

node* erase_node(const KeyT &key, node*& r);
void delete_all_nodes(node *r); // done

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
typename map_avl<KeyT, ValueT, Comp>::node*  map_avl<KeyT, ValueT, Comp>::find_min_node(node* r) {
    if(!r){ return r; }
    while(r->left) { r = r->left; }
    return r;
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::node*  map_avl<KeyT, ValueT, Comp>::find_max_node(node* r) {
    if(!r){ return r; }
    while(r->right) { r = r->right; }
    return r;
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::node*&  map_avl<KeyT, ValueT, Comp>::child_link(node* parent, const KeyT& k) {
    if(!parent) { return map_root; }
    return lesser(k, parent->data.first) ? parent->left : parent->right;
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::node* map_avl<KeyT, ValueT, Comp>::insert_node(const MapT& val, node*& r, node*& ptr) {
    if(!r) {
        map_size++;
        ptr = r = new node(val);
    }else{

        int not_equal = compare(val.first, r->data.first);
        if(not_equal < 0){
            r->set_left(insert_node(val, r->left, ptr));
        }else if(not_equal > 0){
            r->set_right(insert_node(val, r->right, ptr));
        }else{
            ptr = r;
        }

    }
    return r;
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::node* map_avl<KeyT, ValueT, Comp>::erase_node(const KeyT& k, node*& r) {
    if(!r){ return r; }
    int not_equal = compare(k, r->data.first);
    if(not_equal < 0) {
        r->set_left(erase_node(k, r->left));
    }else if(not_equal > 0) {
        r->set_right(erase_node(k, r->right));
    }else{
        if(!r->left || !r->right) {
            node* temp_node = r;
            r = (!r->left ? r->right : r->left);
            delete temp_node;
            map_size--;
        }else{
            node* replace_node = r->right;
            while(replace_node->left) {
                replace_node = replace_node->left;
            }
            r->data = replace_node->data;
            r->set_right(erase_node(replace_node->data.first, r->right));
        }
    }
    return r;
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