/*
 * G. Yu (Mark)
 * November 2, 2018
 * Version 1
 */

/*
 * Private members:
 * struct TNode:
 * 1.structure TNode which stores: 1. data field an integer 2. unsigned integer count to keep track of the number of duplicate values 3. left and right for the children node for more data insertion
 * 2. Constructor in TNode, default constructor: Initialize the data to zero and left and right children to be nullptr
 * 3. Second constructor in TNode, it accepts an number as input, then set the input to the data, increment the count, and set left and right children to nullptr
 *
 * data member 'root' refers to the top root of the BST, state would refer to the either store only odd number or even number
 * copying is suppressed for BST, because it is not efficient to copy the an entire BST
 * delete_All method is a private utility function for the destructor, which would delete node recursively in postorder.
 * findMax function is a private utility function for the remove method. It will find the maximum value in the left subtree of the node given
 *
 * checkLeftOver would check if there is a special case where the maximum is not the leaf node, e.g if trying to delete 20 from a tree, and the left child of 20 is 17, left child of 17 is
 * 16, right child is 19, the left child of 19 is 18. In this case, the maximum of the left subtree would be 19, but there is one child attach to it.
 *
 * removeLeaveNode method would remove the node when the node trying to remove is a leaf node
 *
 * onlyLeft method utilizes when the node it tries to delete has a left child.
 *
 * onlyLeft method would provide the ability to delete a node when there is only a right child/
 *
 * twoChildren method in which would organize the tree when it is trying to delete a node that has two children
 *
 * public members:
 *
 * The default constructor would initialize the root to nullptr, means there is nothing inside the tree
 *
 * The second constructor would allow user to input if they want the tree to store only odd or even numbers
 *
 * The destructor would call the delete_All function to delete all the node recursively
 *
 * The insert method would accept an integer from the user, and it will find the appropriate position to insert the node
 *
 * The remove method would get an integer that user wish to remove, and it will search for duplicate, decrement count or delete node. It will find the change the element accordingly base
 * on where the node is located
 *
 * inorder_print would do a in order traversal, and put all the element in a queue, and return the queue
 *
 * The search function would search if an element is in the tree, it would return a pointer to the node
 *
 * The isEmpty method check if the tree is empty
 */
#ifndef P3_PARITYBST_H
#define P3_PARITYBST_H

#include <queue>
class parityBST{
private:
    struct TNode{
        int data;
        unsigned int count = 0;
        TNode* left;
        TNode* right;

        TNode(){
            data = 0;
            left = nullptr;
            right = nullptr;
        }
        TNode(int input){
            data = input;
            left = nullptr;
            right = nullptr;
            count++;
        }
    };
    TNode* root;
    bool state;
    void operator=(const parityBST &ref);
    void delete_All(TNode* overallRoot);
    TNode* findMax(TNode*& overallRoot);

    void preOrder_Check(std :: queue<int>& q,TNode* overallRoot);
    bool check_leftOver(TNode*& overallRoot);
    void removeLeaf(TNode*& overallRoot,TNode*& current,TNode*& prev,int& num);
    void onlyLeft(TNode*& overallRoot,TNode*& current,TNode*& prev,int& num);
    void onlyRight(TNode*& overallRoot,TNode*& current,TNode*& prev,int& num);
    void twoChildren(TNode*& overallRoot,TNode*& current,TNode*& prev,int& num);
public:
    parityBST();
    parityBST(bool odd_even);
    std :: queue<int> preOrder(TNode* overallRoot);
    void preOrder_Check(TNode* overallRoot,std :: queue<int>& q);
    parityBST(const parityBST &ref);
    ~parityBST();
    void insert(int num);
    void remove(int num);
    std :: queue<int> inOrder_Print();
    TNode* search(int num);
    bool isEmpty();

};
#endif //P3_PARITYBST_H
