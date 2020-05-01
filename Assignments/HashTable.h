//
//  HashTable.hpp
//  LinkedList
//
//  Created by Sara Tagarot on 4/7/20.
//  Copyright © 2020 DataAbs. All rights reserved.
//


template<typename K,typename V,typename Hash>
class HashMap {
    Hash hashFunction;
    // Data to store the hash table and the number of elements.
    
    // Suggestion for the hash table: either
    vector<vector<pair<K,V>>> table;
    // or
    // vector<list<pair<K,V>>> table;
    // would work well for the chaining approach.
    int sz = 0;
    

public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator;

    class iterator {
        // NOTE: These might be different depending on how you store your table.
        typename std::remove_reference<decltype(table.begin())>::type mainIter;
        typename std::remove_reference<decltype(table.begin())>::type mainEnd;
        typename std::remove_reference<decltype(table[0].begin())>::type subIter;
    public:
        friend class const_iterator;

        // NOTE: These might be different depending on how you store your table.
        iterator(const decltype(mainIter) mi,const decltype(mainEnd) me):mainIter(mi),mainEnd(me) {
            if(mainIter!=mainEnd) subIter = mainIter->begin();
            while(mainIter!=mainEnd && subIter == mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
        }
        iterator(const decltype(mainIter) mi,
                const decltype(mainEnd) me,
                const decltype(subIter) si):
                mainIter(mi),mainEnd(me),subIter(si) {
                    //TODO???
                    
                }

        bool operator==(const iterator &i) const { return mainIter==i.mainIter && (mainIter==mainEnd || subIter==i.subIter); }
        bool operator!=(const iterator &i) const { return !(*this==i); }
        std::pair<K,V> &operator*() { return *subIter; }
        iterator &operator++() {
            ++subIter;
            while(mainIter!=mainEnd && subIter==mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
            return *this;
        }
        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
    };

    class const_iterator {
        // NOTE: These might be different depending on how you store your table.
        typename std::remove_reference<decltype(table.cbegin())>::type mainIter;
        typename std::remove_reference<decltype(table.cbegin())>::type mainEnd;
        typename std::remove_reference<decltype(table[0].cbegin())>::type subIter;
    public:
        // NOTE: These might be different depending on how you store your table.
        const_iterator(const decltype(table.cbegin()) mi,const decltype(table.cbegin()) me):mainIter(mi),mainEnd(me) {
            if(mainIter!=mainEnd) subIter = mainIter->begin();
            while(mainIter!=mainEnd && subIter == mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
        }
        // NOTE: These might be different depending on how you store your table.
        const_iterator(const decltype(table.cbegin()) mi,
            const decltype(table.cbegin()) me,
            const decltype(table[0].cbegin()) si):
                mainIter(mi),mainEnd(me),subIter(si) {}
        const_iterator(const decltype(table.begin()) mi,
            const decltype(table.begin()) me,
            const decltype(table[0].begin()) si):
                mainIter(mi),mainEnd(me),subIter(si) {}


        const_iterator(const iterator &i):mainIter(i.mainIter),mainEnd(i.mainEnd),subIter(i.subIter) {
            //TODO???
        }

        bool operator==(const const_iterator &i) const { return mainIter==i.mainIter && (mainIter==mainEnd || subIter==i.subIter); }
        bool operator!=(const const_iterator &i) const { return !(*this==i); }
        const std::pair<K,V> &operator*() const { return *subIter; }
        const_iterator &operator++() {
            ++subIter;
            while(mainIter!=mainEnd && subIter==mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
    };

        HashMap(const Hash &hf){
            hashFunction = hf;
            table.resize(sz);
            //cnt = 0;
        }
   
       // HashMap(const HashMap<K,V,Hash> &that);// Only if needed.

    // HashMap &operator=(const HashMap<K,V,Hash> &that); // Only if needed.

        bool empty() const{
            sz = 0;
            return sz;
        }

        unsigned int size() const{
            return sz;
        }

        iterator find(const key_type& k){
            //storing k
            int index = hashFunction(k) % table.size();
            for(auto i = table[index].begin(); i != table[index].end(); ++i){
                if (k == i->first) {
                    return iterator(table.begin()+index,table.end(),i);
                }
                
            }
            return end();
        }

        const_iterator find(const key_type& k) const{
            int index = hashFunction(k) % table.size(); //storing k
            for(auto j = table[index].begin(); j != table[index].end(); ++j){
                if (k == j->first) {
                    return const_iterator(table.begin()+index,table.end(),j);
                }
            }
            return end();
        }

        int count(const key_type& k) const{
            if (find(k) ==end()) {
                return 0;
            }
            return 1; //else 1
        }

        std::pair<iterator,bool> insert(const value_type& val){
            int index = hashFunction(val.first) % table.size();
            for(auto it = table[index].begin(); it != table[index].end(); ++it){
                if (val.first == it->first) {
                    return make_pair(iterator(table.begin()+index,table.end(),it),false);
                }
                
            }
            //table[index].push_back(val);
            table[index].insert(table[index].end(), val);
            return make_pair(iterator(table.begin()+index,table.end(),subIt),true);
        }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for(auto i = first; i != last; i++){
            insert(*i);
        }
    }

        iterator erase(const_iterator position){
            auto mainIt = position.mainIter;
            int index = mainIt-table.begin(); //get index --> get reader right access
            table[index].erase(...);
            
        }

        int erase(const key_type& k){
            //TODO
        }

        void clear(){
            for (auto i: table) {
                i.clear();
            }
            sz = 0;
        }

        mapped_type &operator[](const K &key){
            auto it = insert(make_pair(key,V())).first;
            return (*it).second;
        }

        bool operator==(const HashMap<K,V,Hash>& rhs) const{
            for(const_iterator i = rhs.begin(): rhs.end(): ++i){
                if (count((*i).first) == 0){
                    return false;
                }
            }
            return sz = rhs.size();
        }

    bool operator!=(const HashMap<K,V,Hash>& rhs) const {
        return !(*this==rhs);}

    // NOTE: These might be different depending on how you store your table
    iterator begin() {
        return iterator(table.begin(),table.end());
    }

    const_iterator begin() const{
        return const_iterator(table.begin(),table.end());
    }

    iterator end(){
        return iterator(table.end(),table.end());
    }

    const_iterator end() const{
        return const_iterator(table.end(),table.end());
    }

    const_iterator cbegin() const{
        return const_iterator(table.begin(),table.end());
    }

    const_iterator cend() const{
        return const_iterator(table.end(),table.end());
    }

private:
    void growTableAndRehash(); //TODO???
};
