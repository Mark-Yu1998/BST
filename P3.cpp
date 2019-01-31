/*
 * G. Yu (Mark)
 * November 2, 2018
 * Version 1
 */
/*
 * The driver file would use iostream, primeDubBST.h, STL queue, string and fstream
 *
 * The init function will generate 100 random number to the array from -20 to 200
 *
 * The insertion function will accept the array with all the random numbers, and insert them into the binary search tree
 *
 * The random operation function will do 50 random operation(either remove or insert) from the tree. There is a operation const variable to store a random number. If it is even, it will insert a random number, otherwise, remove a
 * random number
 *
 * outFile function would write out all remaining data to a file. It accepts a file name, and write it to that file name. Using fstream
 *
 * the main function would accept an input from the user, to determine the even/odd state of the BST, then it will call all the functions to finish the tasks.
 */
#include <iostream>
#include "primeDupBST.h"
#include <queue>
#include <string>
#include <fstream>
using namespace std;

void init(int nums[], const int &SIZE) {
    srand(time(NULL));
    const int MAX = 200;
    const int MIN = -20;
    //generate random numbers
    for (int i = 0; i < SIZE; i++) {
        nums[i] = rand() % MAX + MIN;
    }
}

void insertion(parityBST &tree, int nums[], const int &SIZE) {
    for (int i = 0; i < SIZE; i++) {
        tree.insert(nums[i]);
    }
}

void randomOperation(parityBST &tree) {
    const int FREQ = 50;
    srand(time(NULL));
    const int MAX = 150;
    const int MIN = -20;
    //This will run 50 times
    for (int i = 0; i < FREQ; i++) {
        const int OPERATION = rand();
        int num = rand() % MAX + MIN;
        if (OPERATION % 2 == 0) {
            tree.insert(num);
        } else {
            tree.remove(num);
        }
    }

}

void outFile(const string FILE_NAME,parityBST& tree){
    ofstream out;
    out.open(FILE_NAME);
    queue<int> tree_Q = tree.inOrder_Print();
    while (!tree_Q.empty()){
        int val = tree_Q.front();
        out << val << " ";
        tree_Q.pop();
    }
    out << "\n";
    out.close();
}
int main() {
    //Input only postive integer
    unsigned int input;
    cout << "Select an option: Enter 1 for store only odd numbers; Enter 2 for store only even numbers:" << " ";
    cin >> input;
    const bool EVEN = (input % 2 == 0);
    bool state = (EVEN) ? true : false;
    parityBST tree(state);
    const int SIZE = 100;
    int nums[SIZE];
    //Initialization of data
    init(nums, SIZE);
    //Insertion, and output
    insertion(tree, nums, SIZE);
    parityBST t2(tree);


//    const string OUT_I1 = "P3outI1.txt";
//    outFile(OUT_I1,tree);
//    //Random operation and output
//    randomOperation(tree);
//    const string OUT_I2 = "P3outI2.txt";
//    outFile(OUT_I2,tree);
    return 0;
}