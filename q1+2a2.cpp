#include <iostream>
#include <vector>

using namespace std;

enum Child {
    Left,
    Right
};

class Tree {
private:
    struct node {
        int key;
        node *left, *right, *parent;
    };
public:
    Tree(int rootKey){
        root = new node;
        //setMembers - receives a pointer to a node and 4 values which it assigns to its 4 fields
        setMembers(root, rootKey, NULL, NULL, NULL);
    }
    bool ancestors(int keyToFind, vector <int> &ancestorsKey){
        //computes the ancestors of node with key keyToFind and returns them in vector ancestorsKey
        //method returns false if no node with key keyToFind has been found and true otherwise
        node *keyNode = findNode(keyToFind, root);
        if(keyNode == NULL){
            cout<<"There is no node with key "<<keyToFind<<" in the tree.\n";
            return false;
        }
        else {
            while(keyNode != NULL){
                ancestorsKey.push_back(keyNode -> key);
                keyNode = keyNode -> parent;
            }
        }
        return true;
    }
    bool commonAncestor(int keyToFind1, int keyToFind2, int &answer){
        //method to find the common ancestor of nodes with keys keyToFind1, keyToFind2
        //it works by computing the ancestors of both nodes and finds the one which is common and closest to the root by going through the ancestors arrays backwards
        vector <int> ancestorsKey1, ancestorsKey2;
        if(ancestors(keyToFind1, ancestorsKey1) && ancestors(keyToFind2, ancestorsKey2)){
            int i = ancestorsKey1.size() - 1, j = ancestorsKey2.size() - 1;
            while(i >= 0 && j >= 0 && ancestorsKey1[i] == ancestorsKey2[j]){
                i--; j--;
            }
            answer  = ancestorsKey1[i + 1];
            return true;
        }
        else return false;
    }
    void insert(int keyToInsert, int parentKey, Child c){
         //method which inserts a node into the tree, it receives as parameters the key of the node to be insert, the key of its parent, and whether it should be a left or right child
         node *parentNode = findNode(parentKey, root);
         if(parentNode == NULL){
            cout<<"Node with key "<<keyToInsert<<" could not be inserted because parent key could not be found.\n";
         }
         else {
            if(c == Left){
                if(parentNode -> left != NULL){
                    cout<<"Node with key "<<keyToInsert<<" could not be inserted because parent already has a left child.\n";
                }
                else {
                    parentNode -> left = new node;
                    setMembers(parentNode -> left, keyToInsert, NULL, NULL, parentNode);
                }
            }
            else {
                if(parentNode -> right != NULL){
                    cout<<"Node with key "<<keyToInsert<<" could not be inserted because parent already has a right child.\n";
                }
                else {
                    parentNode -> right = new node;
                    setMembers(parentNode -> right, keyToInsert, NULL, NULL, parentNode);
                }
            }
         }
    }
private:
    node *root;
    node *findNode(int keyToFind, node *current){
        //method to find a node with key keyToFind in tree with root at node current
        //it returns the node whose key is keyToFind
        node *findLeft;
        if(current == NULL){
            return NULL;
        }
        else {
            if(current -> key == keyToFind){
                return current;
            }
            else {
                findLeft = findNode(keyToFind, current -> left);
                if(findLeft != NULL){
                    return findLeft;
                }
                else {
                    return findNode(keyToFind, current -> right);
                }
            }
        }
    }
    void setMembers(node *current, int keyToSet, node *leftChild, node *rightChild, node *parentNode){
        current -> key = keyToSet;
        current -> left = leftChild;
        current -> right = rightChild;
        current -> parent = parentNode;
    }
};

Tree buildTreeFromInput(){
    int treeSize, rootKey, keyToInsert, parentKey;
    char child;
    cout<<"Give size of the tree: "; cin>>treeSize;
    cout<<"Give key of the root: "; cin>>rootKey;
    Tree t(rootKey);
    cout<<"Give keys to be inserted, the key of the parent to which the new node should be appended and whether it should be its left (input L) or right (input R) child:\n";
    for(int i = 1; i < treeSize; ++i){
        cin>>keyToInsert>>parentKey;
        cin.get(); //read the space after parent
        cin>>child;
        if(child == 'L') {
            t.insert(keyToInsert, parentKey, Left);
        }
        else if(child == 'R') {
            t.insert(keyToInsert, parentKey, Right);
        }
        else {
            cout<<"Child input is not valid";
        }
    }
    return t;
}

int main()
{
    Tree currentTree = buildTreeFromInput();
    int problem;
    cout<<"Input the index of the question you want to solve: "; cin>>problem;
    if(problem == 1){
        vector <int> ancestorsKey;
        int keyInput;
        cout<<"Input key of the node:\n"; cin>>keyInput;
        if(currentTree.ancestors(keyInput, ancestorsKey)){
            for(int i = 0; i < ancestorsKey.size(); ++i){
                cout<<ancestorsKey[i]<<" ";
            }
            cout<<"\n";
        }
    }
    else if (problem == 2) {
        int keyInput1, keyInput2, answer = 0;
        cout<<"Input the keys of the two nodes:\n"; cin>>keyInput1>>keyInput2;
        if(currentTree.commonAncestor(keyInput1, keyInput2, answer)){
            cout<<answer<<"\n";
        }
    }
    return 0;
}

/*

Tests:

Example in question statement
8
16
9 16 L
18 16 R
3 9 L
14 9 R
19 18 R
1 3 L
5 3 R

1.1. Input: 5
Output: 5 3 9 16

1.2. Input: 9
Output: 9 16

1.3. Input: 16 //input is the key of the root
Output: 16

1.4. Input: 25 //input key is not present in the tree
Output: There is no node with key 25 in the tree.

2.1. Input: 5 14
Output: 9

2.2. Input: 16 19 //one of the keys is the one of the root
Output: 16

2.3. Input: 1 9 //one of the nodes is an ancestor of the other
Output: 9

2.4. Input: 16 8 //one of the keys does not exist in the tree
Output: There is no node with key 8 in the tree.

*/
