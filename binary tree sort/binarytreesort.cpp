#include "cardlib.h"

#include <string>
#include <iostream>
using namespace std;

const int maxCard = 20;
int compareCount;
int swapCount;

aCard thePack[maxCard];

string cardToStr(aCard c) {                                         // function to return a card as a string
    string s1 = "HCDS";                                             // creates the suit as a string
    string s2 = "A23456789TJQK";                                    // creates the number as a string
    return s2.substr(c.cardVal - 1, 1) + s1.substr(c.cardSuit, 1);  // returns it as a single string, number + card 
}

int compareCards(aCard c1, aCard c2) {      // function to compare 2 cards and output a value
    compareCount++;                         // tracks how many compares happen
    if (c1.cardSuit == c2.cardSuit) {       // checks suit first as they are the more important 
        if (c1.cardVal < c2.cardVal)        // if suits are the same checks values and returns -1/0/1 depending c1 and c2
            return -1;
        else if (c1.cardVal == c2.cardVal)
            return 0;
        else if (c1.cardVal > c2.cardVal)
            return 1;
    }
    else if (c1.cardSuit < c2.cardSuit)     // if suits are different and returns -1 or 1 depending on suit of c1 and c2
        return -1;
    else if (c1.cardSuit > c2.cardSuit)
        return 1;
}

struct treeNode {
    aCard data;                     // actual data
    treeNode* less, * more;         // pointers to node with data less or more than in this node
};

treeNode* treeTop;                  // pointer to top of tree

treeNode* newNode(aCard c) {        // create a new node with data c, return pointer to it
    treeNode* p = new treeNode;     // create space for node
    p->data = c;                    // add data
    p->less = NULL;                 // pointers less and more are set to NULL
    p->more = NULL;
    return p;                       // return pointer to this new node 
}

void printTree(treeNode* p) {                   // print the tree from node p
    if (p != NULL) {
        printTree(p->less);                     // print any nodes in less sub tree
        cout << cardToStr(p->data) << ", ";     // print this node
        printTree(p->more);                     // print any nodes in more sub tree
    }
}

treeNode* insertTree(treeNode* p, aCard c) {    // insert string s searching from node p, returns pointer to this node (normally unchanged)
    treeNode* ans = p;
    if (p == NULL) ans = newNode(c);            // if found NULL pointer, create new node and this is returned connecting to node above
    else if (compareCards(p->data, c) >= 0) p->less = insertTree(p->less, c);    // insert in less subtree
    else p->more = insertTree(p->more, c);      // insert in more subtree change above line if want repeat items in tree
    return ans;                                 // return pointer to new node, or to this node, as appropriate
}

int main()
{
    cout << "Aadil's adaption of RJM's Tree Program!\n";
    treeTop = NULL;                             // initialise a new empty tree
    for (int i = 0; i < maxCard; i++) {
        treeTop = insertTree(treeTop, getCard("30004098"));     //initialises each card and puts it through the insert tree function
    }
    cout << "Tree sorted: ";
    printTree(treeTop);                         
    cout << "\n";
}