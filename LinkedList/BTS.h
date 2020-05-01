//
//  BTS.hpp
//  LinkedList
//
//  Created by Sara Tagarot on 4/22/20.
//  Copyright © 2020 DataAbs. All rights reserved.
//


#include <stdio.h>

template<typename K,typename V>
class BSTMap {
    struct Node{
        std::pair<K, V> data; //nodes
        Node* parent; //node to parent
        //if parent node has no children then these nodes are nullptr
        Node* left;
        Node* right;
        
    };
    // TODO: specify whatever member data you need.
    Node* root = nullptr; //pointer to top node or node - at first there is no root therefore =nullptr
    int sz = 0; //size  - at first it is empty therefore = 0
    static Node* minimum(Node* node){
        Node* cur  = node;
        while(cur->left != nullptr){
            cur = cur->left; //gets successor/s
        }
        return cur;
        
    }
    static Node* successor(Node* node){
        Node* x = node->right;
        if (x != nullptr){
           return minimum(x);
            
        }else{
            while(node->parent != nullptr && node->parent->right == node ){
                node = node->parent;// predecessor of node
            }
            return node->parent;
        }
            
    }
    
    
public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator;

    class iterator {
        // TODO: Iterator data.
        //Need to be able to go back from end, i.e. --end() should
        //give last element.
        //One approach is to keep a Node* and a bool that tells me if
        //it is at end.
        //If just keeping Node* and use nullptr to indicate end(), then
        //operator-- need a case for nullptr, in which case to get the
        //maximum element. But to get the maximum element, we need to
        //store information about the tree, e.g. the root pointer, as member.
        Node* node;
        bool atnd = false;
        
    public:
        friend class const_iterator;
        
        iterator(Node* nod, bool tof) {
            node = nod;
            atnd = tof;
        }
        // TODO: Other constructors as needed.
        iterator(const iterator &it){
            node = it.node;
            atnd = it.atnd;
        }
        iterator(const const_iterator &it){
            node = it.node;
            atnd = it.atnd;
        }

        bool operator==(const iterator &i) const { return (*this==i); }
        bool operator!=(const iterator &i) const { return !(*this==i); }
        std::pair<K,V> &operator*() {return node->data; }
        iterator &operator++() {
            auto s = successor(node); //successor
            if(s!= nullptr){
                node = s;
            }else{
                atnd = true;
            }
            return *this;
        }
        iterator &operator--() {
            if(atnd){
                atnd = false;
            }else{
                node = predecessor(node);
            }
            return *this;
        }
        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        iterator operator--(int) {
            iterator tmp(*this);
            --(*this);
            return tmp;
        }
    };

    class const_iterator {
        Node* node;
        bool atnd = false;
    public:
        friend class BSTMap<K,V>;  // You might not need this in your code, but it helped me.
        ////////
         const_iterator(Node* nod, bool tof) {
                   node = nod;
                   atnd = tof;
               }
               // TODO: Other constructors as needed.
        const_iterator(const iterator &iter){
                   node = iter.node;
                   atnd = iter.atnd;
               }
       

        bool operator==(const const_iterator &i) const { return (*this==i); }
        bool operator!=(const const_iterator &i) const { return !(*this==i); }
        const std::pair<K,V> &operator*() { return node->data; }
        
        const_iterator &operator++() {
            auto s = successor(node); //successor
            if(s!= nullptr){
                node = s;
            }else{
                 atnd = true;
            }
            return *this;
        }
        const_iterator &operator--() {
             if(atnd){
                 atnd = false;
             }else{
                 node = predecessor(node);
             }
             return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        const_iterator operator--(int) {
            const_iterator tmp(*this);
            --(*this);
            return tmp;
        }
    };



    BSTMap() {
        root= nullptr;
        sz = 0;
    }
    ~BSTMap() {
        clear();//delete evewrything from the root on
        
    }
    Node* CopyThis(Node* cur, Node* parnt){
        if(cur==nullptr){//if tree to copy is empty return empty tree
            return nullptr;
        }else{
            Node* copiedNode= new Node; //new empty copy
            
            //copying everything into the empty copy
            copiedNode->data = cur->data;
            copiedNode->parent= cur->parnt;
            copiedNode->left = copyThis(cur->left,copiedNode);
            copiedNode->right= copyThis(cur->right,copiedNode);
            
            return copiedNode;//returns the filled copied node
            
        }
    }
    BSTMap(const BSTMap<K,V> &that) {
        root = copyThis(that.root, nullptr);
        sz = that.sz;//sets it to the size of  'that'
    }

    BSTMap &operator=(const BSTMap<K,V> &that) {
        clear();
        root = CopyThis(that->root, nullptr);
    }

    bool empty() const { return size() == 0; }

    unsigned size() const { return sz;}

    iterator find(const key_type& k){
        Node *p = root;
        while (p!= nullptr) {
            if(k == p->data.first){
                return iterator(p); //return something "it has beeen found"
            }else if(k< p->data.first){
                p = p->left;
            }else{
                p = p->right;
            }
        }return end();
        
    }

    const_iterator find(const key_type& k) const{
        Node *p = root;
        while (p!= nullptr) {
            if(k == p->data.first){
                return const_iterator(p); //return something "it has beeen found"
            }else if(k< p->data.first){
                p = p->left;
            }else{
                p = p->right;
            }
        }return end();
    }

    unsigned int count(const key_type& k) const {
        if(find(k)!=cend()) return 1;
        else return 0;
    }

    std::pair<iterator,bool> insert(const value_type& val);

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for(auto iter = first; iter!=last; ++iter) {
            insert(*iter);
        }
    }

    iterator erase(const_iterator position){
        Node* node = position.node;
        if(node->left == nullptr && node->right == nullptr){
            if(node->parent ==nullptr){
                root = nullptr;
            }else if(node->parent->left==node){
                node->parent->left = nullptr;
            }else{
                node->parent->right = nullptr;
                delete node;
                sz--;
            }
        }else if(node->left == nullptr || node->right == nullptr){
            //3 cases
            Node* child = nullptr;
            if(node->parent==nullptr){
                root=child;
            }else if(node->parent->left == node){
                node->parent->left= child;
            }else{
                node->parent->right = child;
            }
            delete node;
            sz--;}
        else{
            auto s= successor(node);
            node->data = s->data;
            sz--;
        }
        return iterator(node,false);
    }

    unsigned int erase(const key_type& k){
        const_iterator it = find(k);
        if (it!=cend()) {
            erase(it);
            return 1;
        }
        else {
            return 0;
        }
    }

    void clear(){
        sz=0;
        root = nullptr;
    }

    mapped_type &operator[](const K &key){
        return (*insert(make_pair(key, V())).first).second;
    }

    bool operator==(const BSTMap<K,V>& rhs) const{
        for(const_iterator i = begin(); i!=end();i++){
           // ...
        }
    }

    bool operator!=(const BSTMap<K,V>& rhs) const { return ! (*this == rhs); }

    iterator begin() { return iterator(root,false); }

    const_iterator begin() const { return const_iterator(root, false); }

    iterator end() { return iterator(nullptr,true); }

    const_iterator end() const { return const_iterator(nullptr,true); }

    const_iterator cbegin() const { return const_iterator(root,false); }

    const_iterator cend() const { return const_iterator(nullptr,true); }

};
