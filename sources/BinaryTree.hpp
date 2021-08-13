
#include <iostream>
#include <queue>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
namespace ariel {
    enum TRAVERSAL {
        INORDER, PREORDER, POSTORDER
    };
    template <typename T>
    class BinaryTree {

        struct Node {
            T _val;
             std::shared_ptr<Node> _left_child;
             std::shared_ptr<Node> _right_child;
            explicit Node(T val) : _val(val),_left_child(nullptr), _right_child(nullptr){}
        };

        class Iterator {
        private:
             std::shared_ptr<Node> _curr;
            std::queue< std::shared_ptr<Node>> q;
        public:
            Iterator( std::shared_ptr<Node> root, TRAVERSAL method) {
                if(root == nullptr){
                    _curr = nullptr;
                    return;}
                bool first_time = true;
                if (method == INORDER) {
                    init_inorder(root, first_time);
                } else if (method == PREORDER) {
                    init_preorder(root, first_time);
                }
                else {
                    init_postorder(root, first_time);
                }
                _curr = q.front();
                q.pop();
            }
            ////////////////////////////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////--init traversal--///////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////////////////////////
            void set( std::shared_ptr<Node> curr, bool &first_time)
            {
                q.push(curr);
            }

            void init_inorder( std::shared_ptr<Node> curr, bool &first_time) {
                if (curr == nullptr) { return; }
                init_inorder(curr->_left_child, first_time);
                set(curr, first_time);
                init_inorder(curr->_right_child,first_time);
            }

            void init_preorder( std::shared_ptr<Node> curr, bool &first_time) {
                if (curr == nullptr) { return; }
                set(curr, first_time);
                init_preorder(curr->_left_child, first_time);
                init_preorder(curr->_right_child, first_time);
            }

            void init_postorder( std::shared_ptr<Node> curr, bool &first_time) {
                if (curr == nullptr) { return; }
                init_postorder(curr->_left_child, first_time);
                init_postorder(curr->_right_child, first_time);
                set(curr, first_time);
            }

            void op(){
                if(q.empty()){
                    _curr = nullptr;
                }else {
                    _curr = q.front();
                    q.pop();
                }
            }


            //++i
            Iterator &operator++() {
                op();
                return *this;
            }

            //i++
            Iterator operator++(int flag) {
                Iterator tmp = *this;
                op();
                return tmp;
            }
            bool operator!=(const Iterator &other){
                return _curr != other._curr;

            }
            bool operator==(const Iterator &other){
                return this->_curr == other._curr;
            }
            T& operator*(){
                return _curr->_val;
            }

            T* operator->(){
                return &(_curr->_val);
            }
        };

    private:
         std::shared_ptr<Node> root;
         std::shared_ptr<Node> found_node; //for the find method

        //recursive find
        bool find_node( std::shared_ptr<Node> curr, T data) {
            if (curr == nullptr) { return false; }
            if (curr->_val == data) {
                found_node = curr;
                return true;
            }
            return find_node(curr->_left_child, data) || find_node(curr->_right_child, data);
        }

    public:
        BinaryTree &add_root(T data) {
            if(root == nullptr){
                root = std::make_shared<Node>(data);
            }
            else{
                root->_val = data;
            }
            return *this;
        }
        ~BinaryTree() {}



        BinaryTree &add_left(T parent, T left_val) {
            if (!find_node(root, parent)) {
                throw std::invalid_argument("parent does not exists");
            }
            if (found_node->_left_child == nullptr) {
                found_node->_left_child = std::make_shared<Node>(left_val);
            } else {
                found_node->_left_child->_val = left_val;
            }
            return *this;
        }

        BinaryTree &add_right(T parent, T right_val) {
            if (!find_node(root, parent)) {
                throw std::invalid_argument("parent does not exists");
            }
            if (found_node->_right_child == nullptr) {
                found_node->_right_child = std::make_shared<Node>(right_val);
            }else{
                found_node->_right_child->_val = right_val;
            }
            return *this;
        }
        BinaryTree() : root(nullptr){};


        //move constructor
        BinaryTree(BinaryTree &&rhs) noexcept{
            root = rhs.root;
            rhs.root = nullptr;
        }

        // move assignment
        BinaryTree& operator=(BinaryTree&& rhs) noexcept
        {
            root = rhs.root;
            rhs.root = nullptr;
            return *this;
        }

        // copy constructor
        BinaryTree(const BinaryTree &rhs){//deep copy
            add_root(rhs.root->_val);
            deep_copy(root, rhs.root);
        }

        // copy assignment
        BinaryTree& operator=(const BinaryTree& rhs)
        {
            if(this == &rhs){
                return *this;
            }
            add_root(rhs.root->_val);
            deep_copy(root, rhs.root);
            return *this;
        }

        void deep_copy( std::shared_ptr<Node> dst,const  std::shared_ptr<Node> src)
        {
            if(src->_left_child) //if this node is not null
            {
                dst->_left_child = std::make_shared<Node>(src->_left_child->_val);
                deep_copy(dst->_left_child, src->_left_child);
            }
            if(src->_right_child){
                dst->_right_child = std::make_shared<Node>(src->_right_child->_val);
                deep_copy(dst->_right_child, src->_right_child);
            }

        }
        /////////for testing//////////////
        T& get_root(){return this->root->_val;}
      
        T& get_left_child(T parent){
            if(find_node(root, parent)){
                if (found_node->_left_child == nullptr) {
                    throw std::invalid_argument("left child does not exists");
                }
                return found_node->_left_child->_val;
        }

        throw std::invalid_argument("parent does not exists");
        }
        T& get_right_child(T parent){
            if(find_node(root, parent)){
                if (found_node->_right_child == nullptr) {
                    throw std::invalid_argument("right child does not exists");
                }
                return found_node->_right_child->_val;
        }
        
        throw std::invalid_argument("parent does not exists");
        }







      






        //////end for testing////////////////
          Iterator begin_inorder(){
            return Iterator(this->root, INORDER);
        }
        Iterator begin_preorder(){
            return Iterator(this->root, PREORDER);
        }

        Iterator begin_postorder(){
            return Iterator(this->root, POSTORDER);
        }

        Iterator end_preorder(){
            return Iterator(nullptr, PREORDER);
        }
        Iterator end_inorder(){
            return Iterator(nullptr, INORDER);
        }
        Iterator end_postorder(){
            return Iterator(nullptr, POSTORDER);
        }
        Iterator begin(){
            return begin_inorder();
        }
        Iterator end(){
            return end_inorder();
        }
        friend std::ostream &operator<<(std::ostream &out, BinaryTree &bt){
            out << std::endl<<"=======tree printer(inorder)========"<<std::endl;
            for(auto it = bt.begin(); it != bt.end(); ++it) {
                out << " " << (*it);
            }
            out<<std::endl<<"=======end printer========="<<std::endl;
            return out;
        }
    };


}
