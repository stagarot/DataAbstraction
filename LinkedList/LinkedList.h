//
//  LinkedList.h
//  LinkedList
//
//  Created by Sara Tagarot
//  Copyright © 2020 DataAbs. All rights reserved.
//


//#include <stdio.h>

//#endif /* LinkedList_hpp */
template<typename T>
class LinkedList {
                struct Node {
                    T data;
                    Node* prev;
                    Node* next;
                    
                };
        Node* sentinel = new Node;
        int sz;
                // TODO - Your data
        public:
                typedef T value_type;

                class iterator {
                    Node* ptr;
                        public:
                                //Constructors
                    iterator(Node* i){
                        ptr-i;}
                    iterator(){
                        ptr-nullptr;}
                    iterator(iterator &i){
                        ptr = i.ptr; }
                    iterator(const iterator &i){
                        ptr = i.ptr;}
                    
                                T &operator*() {
                                    return ptr->data;
                                }
                                bool operator==(const iterator &i) const {
                                    return (ptr==i.ptr);
                                }
                                bool operator!=(const iterator &i) const {
                                    return (ptr != i.ptr);
                                }
                                iterator &operator=(const iterator &i) {
                                    ptr = i.ptr;
                                    return *this;
                                }
                                iterator &operator++() {
                                    ptr = ptr->next;
                                    return *this;
                                }
                                iterator &operator--() {
                                    ptr = ptr->prev;
                                    return *this;
                                }
                                iterator operator++(int) {
                                        auto temp = *this;
                                        ptr = ptr->next;
                                        return temp;
                                }
                                iterator operator--(int) {
                                        auto temp = *this;
                                        ptr = ptr->prev;
                                        return temp;
                                    
                                }
                                friend class const_iterator;
                                friend class LinkedList;
                };
                class const_iterator {
                    Node* ptr;
                        public:
                                //Constructors:
                    const_iterator(Node* i){
                        ptr-i;
                    }
                    const_iterator(){
                        ptr-nullptr;
                    }
                    const_iterator(const iterator &i){
                        ptr = i.ptr;
                    }
                    const_iterator(const const_iterator &i){
                        ptr = i.ptr;
                    }
                                
                    //Include a constructor that converts from a regular iterator.
                                const T &operator*() {
                                    return ptr->data;
                                }
                                bool operator==(const const_iterator &i) const {
                                    return (ptr==i.ptr);
                                    
                                }
                                bool operator!=(const const_iterator &i) const {
                                    return (ptr != i.ptr);
                                }
                                const_iterator &operator=(const const_iterator &i) {
                                    ptr = i.ptr;
                                    return *this;
                                }
                                const_iterator &operator++() {
                                    ptr = ptr->next;
                                    return *this;
                                }
                                const_iterator &operator--() {
                                    ptr = ptr->prev;
                                    return *this;
                                    
                                }
                                
                    const_iterator operator++(int) {
                                    auto temp = *this;
                                    ptr = ptr->next;
                                    return temp;
                                }
                                const_iterator operator--(int) {
                                    auto temp = *this;
                                    ptr = ptr->prev;
                                    return temp;
                                }
                };

                // General Methods

                //Constructors:
    
    LinkedList(){
        sentinel = new Node;
        //from prev to sentinel and next to sentinel
        sentinel->prev = sentinel;
        sentinel->next = sentinel;
        sz =0;
    }
    LinkedList(const LinkedList &a1){
        sentinel = new Node;
        //from prev to sentinel and next to sentinel
        sentinel->prev = sentinel;
        sentinel->next = sentinel;
        sz =0;
        for( auto x:a1){
            push_back(x);
        }
        
    }

                LinkedList &operator=(const LinkedList &al) {
                    clear();
                    for(auto x:al){
                        push_back(x);
                    }
                }
                ~LinkedList() {
                    clear();
                    delete sentinel;
                }
                void push_back(const T &t){ //CHECK IF WE NEED TO CHECK FOR EMPTY LL
                    iterator itr = iterator(sentinel);
                    insert(itr, t); //insert at itr position = end of linked list
                    
                }           // add to the end.
                void pop_back(){
                    iterator itr = iterator(sentinel->prev); //ignore the last element and make new end -1
                    erase(itr);
                    sz--;
                    
                }                     // remove last element.
    int size() const{
        return sz;
    }
    void clear(){
        for (int i = sz; i !=0; i--) {
            pop_back();
        }
    }
                iterator insert(iterator position,const T &t){
                    Node* node = new Node(t, position.ptr, position.ptr->prev);
                    //from prev to node
                    position.ptr->prev->next = node;
                    //from next to node
                    position.ptr->prev = node;
                    sz++;
                    return iterator(node);
                    
                }    // insert this element before the given index.
                const T &operator[](int index) const{
                    
                } // get the element at index.
                T &operator[](int index){
        
                }            // get the element at index.
                iterator erase(iterator position){
                    iterator itr = iterator(position.ptr->next);
                    //from prev to next
                    position.ptr->prev->next = position.ptr->next;
                    //from next to prev
                    position.ptr->next->prev = position.ptr->prev;
                    
                    sz--; //remove one node
                    return itr;
                }               // remove the item at the given index.

    iterator begin(){
        return iterator(sentinel->next);
    }
    const_iterator begin() const{
        return const_iterator(sentinel->next);
    }
    iterator end(){
        return iterator(sentinel);
    }
    const_iterator end() const{
        return const_iterator(sentinel);
    }
    const_iterator cbegin() const{
        return const_iterator(sentinel->next);
    }
    const_iterator cend() const{
        return const_iterator(sentinel);
    }
};
