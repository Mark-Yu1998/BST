/*
 * G. Yu (Mark)
 * November 2, 2018
 * Version 1
 */

/*
 * This class would use the iostream, primeDupBST.h and stack and queue from the STL
 *
 * The default constructor would initialize the root to nullptr, and state to false where it only stores odd numbers(odd-false, true -even)
 *
 * The second constructor would take in user's choice if they want to store odd or even number. Otherwise it is default odd. The user would not have the ability to choose what type of number they
 * like to store after the object is created.
 *
 * The search method would first check if the root is empty, if not, continue to find if the number exists in the tree. It would traverse the tree log N time, when it finds the number
 * it would return its node, otherwise it return nullptr;
 *
 * The insert method traverse the tree iteratively, it would insert the new node in a appropriate location in the tree, it would increment the count field in the node if that node is in the
 * tree already. It will also check if the number is matching with the user's requirements.
 *
 * Inorder print, inorder traversal of the tree, and return a queue to the user as a sorted collection. It pushes all the left node, then pop it, then push it to the queue, and access the right node, repeat the operation to
 * traverse the entire list
 *
 * Remove method removes a node base on the input num. If the tree is empty, it will do nothing. Otherwise, it will first check if the number has been stored multiple times, if so, decrement the count. Whenever the
 * count go to zero or it has no duplicate, the method will delete the node from the tree. The method will automatically check for three cases: 1. leaf node 2. one child node 3. two children node. Each cases have their
 * corresponding private helper function. There is no need to check if the pointer is null in each function, because it is checked before passing in the helper functions.
 *
 * RemoveLeaf method would remove the leaf node if the node has no children. If the node is the root, just delete it. otherwise, it would check if it is the left child or right child of its parent node, then change the left or
 * right field to nullptr, then delete the node.
 *
 * TwoChildren method is removing the node with two children. It will accept the root of the tree, the current position of the node to be deleted and the previous node. First, it will find the max value in the left subtree,
 * also provide the previous node of the replacement node. When the previous node of the replacement node's right child is the replace node. set the node need to remove to the repalce node's value, then disconnect the replacement
 * node with the entire tree, then delete it.
 *
 * OnlyLeft and onlyRight methods would remove the node has only one child, either the left child or right child. If it is the root needs to be deleted, it will go to the next node, and delete the node
 * otherwise, determine weather it is the left or right of the parent node, and disconnect the parent node with the current node, connect the parent node with the current's right or left child, then delete the current node
 *
 * checkLeftOver would check if there is a special
 * case where the maximum is not the leaf node, e.g if trying to delete 20 from a tree, and the left child of 20 is 17, left child of 17 is 16, right child is 19, the left child of 19 is 18. In this case,
 * the maximum of the left subtree would be 19, but there is one child attach to it.
 *
 * findMax method would find the maximum of the left subtree. It accepts the left chlid of the current node, then go to the rightmost node, and return it.
 *
 * isEmpty method would return the true or false depends on if root is equal to nullptr
 *
 * The destructor will call the delete_All method, to destroy all the node created in the tree.
 */
#include <iostream>
#include "primeDupBST.h"
#include <stack>
#include <queue>

using namespace std;

parityBST::parityBST() {
    root = nullptr;
    state = false; // store odd numbers
}

parityBST::parityBST(bool odd_even) {
    root = nullptr;
    state = odd_even;
}

parityBST ::parityBST(const parityBST &ref) {
    state = ref.state;
    queue<int> q;
    queue<int> checkQ;
    preOrder_Check(ref.root,checkQ);
    q = preOrder(ref.root);
    while (!q.empty()){
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
    while (!checkQ.empty()){
        cout << checkQ.front() << " ";
        checkQ.pop();
    }
    cout << endl;

}
parityBST::TNode *parityBST::search(int num) {
    if (root) {
        TNode *current = root;
        if (current->data == num) {
            return current;
        }
        while (current != nullptr) {
            if (current->data == num) {
                return current;
            }
            if (current->data > num) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
    }
    return nullptr;
}

void parityBST::insert(int num) {
    if (state == false && num % 2 == 0) {
        return;
    } else if (state && num && num % 2 != 0) {
        return;
    }
    TNode *prev = nullptr;
    TNode *current = root;
    while (current != nullptr) {
        const int DIFF = num - current->data;
        prev = current;
        TNode* checkDup = search(num);
        if (checkDup != nullptr) {
            checkDup->count++;
            return;
        }
        if (DIFF > 0) {
            current = current->right;
        } else {
            current = current->left;
        }
    }
    TNode *newNode = new TNode(num);
    if (!prev) {
        root = newNode;
        return;
    }
    if (prev->data > num) {
        prev->left = newNode;
    } else {
        prev->right = newNode;
    }
}
queue<int> parityBST ::preOrder(TNode* overallRoot) {
    queue<int> pre;
    stack<TNode*> s;
    if (overallRoot){
        s.push(overallRoot);
        while (!s.empty()){
            TNode* temp = s.top();
            pre.push(temp->data);
            s.pop();

            if (temp ->right){
                s.push(temp->right);
            }
            if (temp->left){
                s.push(temp->left);
            }
        }

    }
    return pre;
}
queue<int> parityBST::inOrder_Print() {
    queue<int> num_q;
    if (root) {
        TNode *current = root;
        stack<TNode *> traverse_S;

        while (current != nullptr || traverse_S.empty() == false) {
            while (current != nullptr) {
                traverse_S.push(current);
                current = current->left;
            }
            current = traverse_S.top();
            traverse_S.pop();
            num_q.push(current->data);
            current = current->right;
        }
    }
    return num_q;


}

void parityBST :: preOrder_Check(TNode* overallRoot,std :: queue<int>& q){
    return preOrder_Check(q,overallRoot);
}
void parityBST ::preOrder_Check(std::queue<int> &q,TNode* overallRoot) {
    if (overallRoot){
        q.push(overallRoot->data);
        preOrder_Check(q,overallRoot->left);
        preOrder_Check(q,overallRoot->right);
    }
}
void parityBST::remove(int num) {
    if (!root) {
        return;
    }
    TNode *search_ptr = search(num);
    if (!search_ptr) {
        return;
    }
    if (search_ptr->count > 1) {
        search_ptr->count--;
        return;
    }
    TNode *prev = nullptr;
    TNode *current = root;
    while (current != nullptr) {
        const int DIFF = num - current->data;
        if (DIFF == 0) {
            if (current->left == nullptr && current->right == nullptr) {
                removeLeaf(root, current, prev, num);
            } else if (current->right == nullptr) {
                onlyLeft(root, current, prev, num);
            } else if (current->left == nullptr) {
                onlyRight(root, current, prev, num);
            } else {
                twoChildren(root, current, prev, num);
            }
        }
        prev = current;
        if (DIFF > 0) {
            current = current->right;
        } else {
            current = current->left;
        }
    }
}

void parityBST::removeLeaf(parityBST::TNode *&overallRoot, parityBST::TNode *&current, parityBST::TNode *&prev, int &num) {
    if (current == overallRoot) {
        root = nullptr;
        delete overallRoot;
        return;
    } else if (prev->left != nullptr) {
        if (prev->left->data == num) {
            prev->left = nullptr;
            delete current;
            return;
        } else {
            prev->right = nullptr;
            delete current;
            return;
        }
    } else if (prev->right != nullptr) {
        prev->right = nullptr;
        delete current;
        return;
    }
}

void parityBST::twoChildren(parityBST::TNode *&overallRoot, parityBST::TNode *&current, parityBST::TNode *&prev, int &num) {
    TNode *replace_node = findMax(current->left);
    TNode *prev_replace = current->left;
    if (prev_replace != nullptr) {
        while (prev_replace->right != nullptr && prev_replace->right != replace_node) {
            prev_replace = prev_replace->right;
        }
    }

    current->data = replace_node->data;
    if (prev_replace->data != current->data) {
        if (check_leftOver(replace_node)) {
            if (replace_node->left == nullptr) {
                prev_replace->right = replace_node->right;
            } else {
                prev_replace->right = replace_node->left;
            }
        } else {
            prev_replace->right = nullptr;
        }
    } else {
        current->left = nullptr;
    }
}

void parityBST::onlyRight(parityBST::TNode *&overallRoot, parityBST::TNode *&current, parityBST::TNode *&prev, int &num) {
    if (current == overallRoot) {
        overallRoot = current->right;
        delete current;
        return;
    }
    if (prev->left == current) {
        TNode *child = current->right;
        prev->left = child;
        current->right = nullptr;
        delete current;
        return;
    } else {
        TNode *child = current->right;
        prev->right = child;
        current->left = nullptr;
        delete current;
        return;
    }
}

void parityBST::onlyLeft(parityBST::TNode *&overallRoot, parityBST::TNode *&current, parityBST::TNode *&prev, int &num) {
    if (current == overallRoot) {
        overallRoot = current->left;
        delete current;
        return;
    }
    if (prev->left == current) {
        TNode *child = current->left;
        prev->left = child;
        current->left = nullptr;
        delete current;
        return;
    } else {
        TNode *child = current->left;
        prev->right = child;
        current->left = nullptr;
        delete current;
        return;
    }
}

bool parityBST::check_leftOver(parityBST::TNode *&overallRoot) {
    return ((overallRoot->left == nullptr && overallRoot->right == nullptr) ? false : (overallRoot->left == nullptr ||
                                                                                       overallRoot->right == nullptr));
}

parityBST::TNode *::parityBST::findMax(TNode *&curr_root) {
    TNode *current = curr_root;
    while (current->right != nullptr) {
        current = current->right;
    }
    return current;
}

bool parityBST::isEmpty() {
    return (root == nullptr);
}

void parityBST::delete_All(parityBST::TNode *overallRoot) {
    if (!overallRoot) {
        return;
    }
    delete_All(overallRoot->left);
    delete_All(overallRoot->right);
    delete overallRoot;

}

parityBST::~parityBST() {
    delete_All(root);
}