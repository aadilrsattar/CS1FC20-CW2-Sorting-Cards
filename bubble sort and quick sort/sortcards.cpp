// SortCard.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "cardlib.h"

#include <string>
#include <iostream>
using namespace std;

const int maxCard = 20;     // a constant variable to dictate how many cards will be sorted
int compareCount;           // creates variables needed for the functions
int swapCount;             
int depthofrecursion;

aCard thePack[maxCard];     // creates array thePack with the length of maxCard

string cardToStr(aCard c) {                                         // function to return a card as a string
    string s1 = "HCDS";                                             // creates the suit as a string
    string s2 = "A23456789TJQK";                                    // creates the number as a string
    return s2.substr(c.cardVal - 1, 1) + s1.substr(c.cardSuit, 1);  // returns it as a single string, number + card 
}

string printPack(string mess) {                 // function to return the whole pack
    string list;                                // creates the variable list to add each of the cards to
    for (int ct = 0; ct < maxCard; ct++) {      // for a loop of length maxCard, it adds each of the values to list
        list = list + cardToStr(thePack[ct]);   
        if (ct < maxCard - 1)                   // if it isn't the last value, it will add a comma
            list = list + ", ";
    }
    return mess + " : " + list;                 // returns mess with the list
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

void swapCards(int n1, int n2) {    // function to swap two cards in thePack array
    swapCount+=3;                   // tracks how many swaps happen
    aCard temp = thePack[n1];       // creates temp card so nothing is lost
    thePack[n1] = thePack[n2];      
    thePack[n2] = temp;
}

void bubbleSort() {                                                 // function to sort cards using bubble sort algorithm
    for (int i = 0; i <= maxCard - 2; i++) {                        // uses the i to loop all the cards till the value maxCard-1
        for (int j = maxCard - 1; j >= i+1; j--) {                  // loops till j reaches i so that the array is checked one at time across it
            int compare = compareCards(thePack[j-1], thePack[j]);   // compares the card which is at value j-1 and the card after  
            if (compare == 1)                                       // swaps if card at j-1 is bigger than j 
                swapCards(j-1, j);                                
        }
    }
}

void quickSort(int lndx, int hndx, int depth) { // function to quick sort deck of cards, which requires two user inputed values that are the low and high indices
    aCard pivot = thePack[(lndx + hndx) / 2];   // generates the middle card as the pivot for quick sort and sorts it as pivot card
    int i = lndx;                               // storing the low and high index as i and j allows us to compare them to the intial values
    int j = hndx;
    while (i < j) {                             
        while (compareCards(pivot, thePack[i]) == 1) {  // loop to see if pivot is equal i value in thePack, adding to i till this happens
            i++;
        }
        while (compareCards(thePack[j], pivot) == 1) {  // loop to see if pivot is equal j value in thePack, minusing from to j till this happens
            j--;
        }
        if (i <= j) {                                   // if i is less than or equal to j add 1 to i and j
            if (i < j) {                                // also if i is only less than j swap i and j values
                swapCards(i, j);                        
            }
            i++;
            j--;
        }
    } 
    if (lndx < j) {                     // if lndx is less than loop j quicksorts using lndx as lower index and j as higher index
        quickSort(lndx, j, depth+1);    
    }
    if (i < hndx) {                     // if i is less than loop hndx quicksorts using i as lower index and hndx as higher index
        quickSort(i, hndx, depth+1);     
    }
    if (depth > depthofrecursion) {     // this was needed to output depth of recursion
        depthofrecursion = depth;    
    }
}

void randCardList() {                       // It was a bit of a hastle copy and pasting this multiple times
    cout << "\nNew Pack initailised \n";    
    for (int ct = 0; ct < maxCard; ct++) { 
        thePack[ct] = getCard("30004098");  // change to your student number
    }
}

int main() {
    cout << "Card Sorting!\n";              
    randCardList();                         // calls function to create new deck of cards to be used for next part
    compareCount = 0; swapCount = 0;        // zeros out compare and swap counts to make sure it is accurate
    cout << printPack("Unsorted") << "\n";  // prints out the unsorted deck of cards
    bubbleSort();                           // sorts the deck using bubblesort
    cout << printPack("Bubble Sort Sorted") << "\ncomparisons: " << compareCount << "\nswaps: " << swapCount << "\n";
                                            // outputs the sorted deck along with the comparisons and swaps

    randCardList();                         // calls function to creat new deck of cards to be used for next part
    compareCount = 0; swapCount = 0;        // zeros out compare and swap counts to make sure it is accurate
    cout << printPack("Unsorted") << "\n";  // prints out the unsorted deck of cards
    quickSort(0, maxCard - 1, 0);           // sorts the deck using quicksort
    cout << printPack("Quicksort Sorted") << "\ncomparisons: " << compareCount << "\nswaps: " << swapCount << "\nDepth of recursion = " << depthofrecursion << "\n";
                                            // outputs the sorted deck along with the comparisons, swaps and depth of recursion
}