#ifndef ZZZ_MAP_AVL_HEAD_HEAD
#define ZZZ_MAP_AVL_HEAD_HEAD

#include <iostream>

namespace zzz {
template <typename KeyT, typename ValueT, typename Comp = std::less<KeyT>> //    
class map_avl {
    protected:    
        typedef std::pair<KeyT, ValueT> MapT;
        class  node {
            friend class map_avl;
            protected:
                MapT data;
                node* left;
                node* right;
                node* parent;
                int height;
                
                node();
                node(const MapT& m);
                node(const MapT& m, node* l, node* r, node* p); 

                void set_height();
                int get_height(node* n);
                int balance_value();
                void set_left(node* n);            
                void set_right(node* n);            
                void set_parent(node* papa, node* n);            
        };

        class tree_iterator {
            protected:
                node* ptr;
            public:
                tree_iterator();            
                tree_iterator(node* p);            

                MapT& operator * ();            
                MapT* operator -> ();            
                bool  operator == (const tree_iterator& other);            
                bool  operator != (const tree_iterator& other);            
                
                tree_iterator& operator++();
                tree_iterator& operator--(); // not test
                tree_iterator operator++(int); // not test    
                tree_iterator operator--(int); // not test   
        };   

        class reverse_tree_iterator {
            protected:
                node* ptr;
            public:
                reverse_tree_iterator();
                reverse_tree_iterator(node* p);

                MapT& operator * ();
                MapT* operator -> ();
                bool  operator == (const reverse_tree_iterator& other);
                bool  operator != (const reverse_tree_iterator& other);   

                reverse_tree_iterator& operator++(); 
                reverse_tree_iterator& operator--(); // not test
                reverse_tree_iterator operator++(int); // not test   
                reverse_tree_iterator operator--(int); // not test   
        };

    protected:
        node* map_root;
        size_t map_size;
        Comp lesser;
        
        int compare(const KeyT& k1, const KeyT& k2);            
        node* find_node(const KeyT& k,node* n, node* &parent);            
        node* find_min_node(node* n);            
        node* find_max_node(node* n);            
        node* &child_link(node* parent, const KeyT& k);            
        node* insert_node(const MapT& val, node*& n, node*& ptr); // not using
        node* erase_node(const KeyT &key, node*& n);
        void delete_all_nodes(node *n);            
        node* rebalance(node* n);            
        node* rotate_left_child(node* n);            
        node* rotate_right_child(node* n);             
        node* copy(node* src); // not test

        // debug
        void show_left_right(node* n);
        void pre_order(node* r);

    public:
        typedef tree_iterator iterator;
        typedef reverse_tree_iterator reverse_iterator; 

        map_avl(const Comp& c = Comp());// default constructor            
        ~map_avl();            
        map_avl(const map_avl<KeyT,ValueT,Comp> & other);// copy constructor // not test     
        map_avl<KeyT,ValueT,Comp>& operator = (map_avl<KeyT,ValueT,Comp> other);// copy assignment // not test 
        
        void clear();            
        bool empty();            
        size_t size();            
        
        iterator begin();            
        reverse_iterator rbegin();            
        iterator end();            
        reverse_iterator rend();            
        iterator find(const KeyT &key);            
        
        ValueT& operator[](const KeyT& key);            
        std::pair<iterator, bool> insert(const MapT& key_val);            
        bool erase(const KeyT& k);               

        // debug
        void show_structure(){ // pre-order travesal
            pre_order(map_root);
        }
    
};
}

template <typename KeyT, typename ValueT, typename Comp>
void zzz::map_avl<KeyT, ValueT, Comp>::pre_order(typename zzz::map_avl<KeyT, ValueT, Comp>::node* n) {
    if(!n){ return; }
    show_left_right(n);
    pre_order(n->left);
    pre_order(n->right);
}


template <typename KeyT, typename ValueT, typename Comp>
void zzz::map_avl<KeyT, ValueT, Comp>::show_left_right(typename zzz::map_avl<KeyT, ValueT, Comp>::node* r) {
    if(r->left){
        auto [a, b] = r->left->data;
        // std::cout << "<" << a << "," << b << ">";
        std::cout << "<" << a << "," << ">";
    }else{
        std::cout << "<none>";
    }
    // std::cout << "[" << r->data.first << "," << r->data.second << "]";
    std::cout << "[" << r->data.first << ", p = ";
    if(r->parent){
        std::cout << r->parent->data.first;
    }else{
        std::cout << "_";
    }
    std::cout << "]";
    if(r->right){
        auto [a, b] = r->right->data;
        // std::cout << "<" << a << "," << b << ">";
        std::cout << "<" << a << ">";
    }else{
        std::cout << "<none>";
    }
    std::cout << "\n";
}

#endif