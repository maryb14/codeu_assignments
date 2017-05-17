#include <iostream>
#include <vector>
#define MAX_DIM 100000

using namespace std;

struct node {
    int value;
    node *next;
};

node *head;

node* arrayToList(vector <int> a){
    //this method converts the vector a to a singly linked list
    //use a dummy header and iter, which points to the last element in the list at a given point
    node *start = new node;
    node *iter = start;
    for(int i = 0; i < a.size(); ++i){
        node *temp = new node;
        temp -> value = a[i];
        temp -> next = NULL;
        iter -> next = temp;
        iter = iter -> next;
    }
    return start -> next;
}

node* kthToLast(node *start, int k){
    //this method returns NULL if the list has less than k + 1 elements, otherwise it returns the kth to last node from the list
    int i = 1;
    node *iter = start;
    //use two pointers, firstly move the second one kth positions down the list from the start
    //and then move the two pointers simultaneously
    //when the second one (iter) gets to the end of the list, the first one (start) is at the kth to last element
    while(i <= k && iter != NULL){
        iter = iter -> next;
        i++;
    }
    if(i <= k) {
        return NULL;
    }
    else {
        while(iter -> next != NULL){
            iter = iter -> next;
            start = start -> next;
        }
        return start;
    }
}

int main()
{
    vector <int> a;
    int k, number;
    node *kthToLastNode;
    cin>>k;
    //read input into an array
    while(cin >> number){
        a.push_back(number);
    }
    //convert the array into a singly linked list
    head = arrayToList(a);

    kthToLastNode = kthToLast(head, k);
    if (kthToLastNode != NULL) {
        cout << kthToLastNode -> value << "\n";
    }
    else {
        cout << "The list has less than k + 1 elements.\n";
    }
    return 0;
}
