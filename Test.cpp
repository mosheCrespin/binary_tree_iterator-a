#include "BinaryTree.hpp"
#include "doctest.h"
using namespace ariel;
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstdlib> 
using namespace std;


/*
            1
        2       3
     4    5    6 


     inorder traversal {4,2,5,1,6,3} 
     preorder traveral {1,2,4,5,3,6}
     postorder traversl {4,5,2,6,3,1}

*/



void build_tree(BinaryTree<int> & t){
    t.add_root(1)
        .add_left(1,2)
            .add_right(1,3)
                .add_left(2,4)
                    .add_right(2,5)
                        .add_left(3,6);
                    
}



TEST_CASE("add root function")
{
    auto t = new BinaryTree<int>;
    CHECK_NOTHROW(t->add_root(1););
    CHECK_EQ(t->get_root(), 1);
    CHECK_NOTHROW(t->add_root(2););
    CHECK_EQ(t->get_root(), 2);
}

TEST_CASE("add left functiom")
{
    BinaryTree<int> tree;
    build_tree(tree);
    //add left to an existance parnet and child
    CHECK_NOTHROW(tree.add_left(2,8));
    CHECK_EQ(tree.get_left_child(2),8);
    //add left to an existance parent but no child
    CHECK_NOTHROW(tree.add_left(6,10));
    CHECK_EQ(tree.get_left_child(6),10);
    //add left to not existing parent
    CHECK_THROWS(tree.add_left(12,2));
}

TEST_CASE("add right functiom")
{
    BinaryTree<int> tree;
    build_tree(tree);
    //add right to an existance parnet and child
    CHECK_NOTHROW(tree.add_right(2,8));
    CHECK_EQ(tree.get_right_child(2),8);
    //add right to an existance parent but no child
    CHECK_NOTHROW(tree.add_right(6,10));
    cout<<tree.get_right_child(6)<<endl;
    CHECK_EQ(tree.get_right_child(6),10);
    //add right to not existing parent
    CHECK_THROWS(tree.add_right(12,2));
}

    // inorder traversal {4,2,5,1,6,3} 
    //  preorder traveral {1,2,4,5,3,6}
    //  postorder traversl {4,5,2,6,3,1}
	


 TEST_CASE("Tree with only one vertex")
 {
      BinaryTree<int> tree;
      tree.add_root(1);
      CHECK_EQ(*(tree.begin_inorder()), 1);
      CHECK_EQ(*(tree.begin_preorder()), 1);
      CHECK_EQ(*(tree.begin_postorder()), 1);	
 	
 
 }
 
 
 
	



 TEST_CASE("Tree traversal")
 {
     BinaryTree<int> tree;
     build_tree(tree);
     vector<int> in = {4,2,5,1,6,3};
     vector<int> pre = {1,2,4,5,3,6};
     vector<int> post = {4,5,2,6,3,1};
     size_t i=0;
     for(auto it = tree.begin_inorder(); it != tree.end_inorder();++it)
     {
     	
         CHECK_EQ((*it), in[i]);
         i++;
     }
     i=0;
     for(auto it = tree.begin_preorder(); it != tree.end_preorder();++it)
     {
     	
         CHECK_EQ((*it), pre[i]);
         i++;
     }
     i=0;
     for(auto it = tree.begin_postorder(); it != tree.end_postorder();++it)
     {
         CHECK_EQ((*it), post[i]);
         i++;
     }
 }

 TEST_CASE("deep copy"){
     BinaryTree<int> tree;
     build_tree(tree);
     BinaryTree<int> copy;
     CHECK_NOTHROW(copy = tree);
     CHECK_NOTHROW(copy.add_left(2,12));
     CHECK_EQ(copy.get_left_child(2), 12); 
     CHECK_EQ(tree.get_left_child(2), 4);//the old val shoud be the same as before
 }

