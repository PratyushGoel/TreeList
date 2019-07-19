#include<bits/stdc++.h>

template <typename T>

class avlList{

    // forward delcaration
    private : class node; 
    public : class iterator;

    private : node *root;

    //constructor
    public: explicit avlList(){
        root = &node::EMPTY_NODE;
    }

    //destructor
    public: ~avlList(){
        // clear();
        if(root != &node::EMPTY_NODE){
            delete root;
            root = &node::EMPTY_NODE;
        }
    }

    public: bool empty(){
        return (root->size == 0);
    }

    public: std::size_t size(){
        return root->size;
    }

    public: void clear(){
        if(root!=&node::EMPTY_NODE){
            delete root;
            root = &node::EMPTY_NODE;
        }
    } 

    public: T &operator[](std::size_t index){
        if(index >= size())
            throw std::out_of_range("Index out of bounds");
        return root->getNodeAt(index)->data;
    }

    public: void push_back(T val){
        insert(size(), val);
    }

    public: void insert(std::size_t index, T val){
        if(index > size()){
            throw std::out_of_range("Index out of bounds");
        }
        if(size() == SIZE_MAX){
            throw std::length_error("Maximum size reached");
        }
        root = root->insertAt(index, val);
    }

    public: void erase(std::size_t index){
        if(index>=size()){
            throw std::out_of_range("Index out of bunds");
        }
        node *toDelete = NULL;
        root = root->removeAt(index, &toDelete);
        delete toDelete;
    }

    iterator begin(){
        iterator it(root);
        return it;
    }

    public: iterator end(){
        node *x = & node:: EMPTY_NODE;
        iterator it(x);
        return it;
    }

    public : class iterator{

        private : std::stack<node*> myStack;
        private : node *curr;

        //constructor
        public : iterator(node *root){
            this->curr = & node:: EMPTY_NODE;
            while(root != & node:: EMPTY_NODE){
                myStack.push(root);
                this->curr = root;
                root = root->left;
            } 
        }

        public : iterator(){
            curr = node::EMPTY_NODE;
        }

        //HERE IS THE PROBLEM
        public : iterator(const iterator& x){
            this->myStack = x.myStack;
            this->curr = x.curr;
        }

        public : void next(){
            if(curr == &node::EMPTY_NODE) throw std::out_of_range("Index out of bounds");
            myStack.pop();

            if(curr->right!= &node::EMPTY_NODE){
                myStack.push(curr->right);
                curr = curr->right;
            }
            while(curr->left != &node::EMPTY_NODE){
                myStack.push(curr->left);
                curr = curr->left;
            }
            if(myStack.size() == 0) curr = &node::EMPTY_NODE;
            else curr = myStack.top();
        }

        public : T &get(){
            if(curr == &node::EMPTY_NODE) throw std::out_of_range("Iterator does not point to a valid point");
            return curr->data;
        }

        public : bool operator!=(iterator x){
            if(x.curr != this->curr) return true;
            else return false;
        }

        public : T& operator*(){
            return get();
        }

        public : void operator++(){
            next();
        }

    };

    private: class node{

        private :  int height;

        public : 

        static node EMPTY_NODE;
        T data;
        size_t size;
        node *left;
        node *right; 

        node(){
            height = 0;
            size = 0;
            left = NULL;
            right = NULL;
        }

        node(T val){
            data = val;
            height = 1;
            size = 1;
            left = &EMPTY_NODE;
            right = &EMPTY_NODE;
        }

        ~node(){
            if(left!=&EMPTY_NODE) delete left;
            if(right!=&EMPTY_NODE) delete right;
        }

        node *getNodeAt(std::size_t index){
            assert(index<size);

            std::size_t leftSize = left->size;

            if(index<leftSize)
                return left->getNodeAt(index);
            else if(index>leftSize)
                return right->getNodeAt(index-leftSize-1);
            else
                return this;
        }

        node* insertAt(std::size_t index, T &val){
            assert(index<=size);

            if(this == &EMPTY_NODE)
                return new node(val);

            std::size_t leftSize = left->size;

            if(index <= leftSize)
                left = left->insertAt(index, val);
            else{
                right = right->insertAt(index-leftSize-1, val);
            }
            reCalculate();
            return balance();
        }

        node *removeAt(std::size_t index, node **toDelete){
            assert(index < size);

            std::size_t leftSize = left->size;

            if(index<leftSize){
                left = left->removeAt(index, toDelete);
            }
            else if(index>leftSize){
                right = right->removeAt(index-leftSize-1, toDelete);
            }
            else if(left == &EMPTY_NODE && right == &EMPTY_NODE){
                assert(*toDelete == NULL);
                *toDelete = this;
                return &EMPTY_NODE;
            }
            else if(left == &EMPTY_NODE){
                node *ans = right;
                right = NULL;
                *toDelete = this;
                return ans; 
            }
            else if(right == &EMPTY_NODE){
                node *ans = left;
                left = NULL;
                *toDelete = this;
                return ans;
            }
            else{
                node *temp = right;
                while(temp->left!=&EMPTY_NODE)
                    temp = temp->left;
                this->data = temp->data;
                right = right->removeAt(0, toDelete); 
            }
            reCalculate();
            return balance();
        }

        node *balance(){
            int bal = getBalance();
            assert(std::abs(bal)<=2);
            node *result = this;

            if(bal == -2){
                assert(std::abs(left->getBalance()) <= 1);
                if(left->getBalance() == 1)
                    left = left->rotateLeft();
                result = this->rotateRight();
            }
            else if(bal == 2){
                assert(std::abs(right->getBalance()) <= 1);
                if(right->getBalance() == -1)
                    right = right->rotateRight();
                result = this->rotateLeft();
            }
            assert(std::abs(result->getBalance()) <= 1);
            return result;
        }

        node *rotateLeft(){
            assert(right != &EMPTY_NODE);
            node *root = right;
            this->right = root->left;
            root->left = this;
            this->reCalculate();
            root->reCalculate();
            return root;
        }

        node *rotateRight(){
            assert(left != &EMPTY_NODE);
            node *root = this->left;
            this->left = root->right;
            root->right = this;
            this->reCalculate();
            root->reCalculate();
            return root;
        }

        void reCalculate(){
            assert(this != &EMPTY_NODE);
            assert(left->height >= 0 && right->height >= 0);
            assert(left->size >= 0 && right->size >= 0);
            height = std::max(left->height, right->height)+1;
            size = left->size + right->size + 1;
        }

        int getBalance(){
            return right->height - left->height;
        }
    };



};
//declaration for static object
template <typename T>
typename avlList<T>::node avlList<T>::node::EMPTY_NODE;