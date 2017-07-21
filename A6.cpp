#include <iostream>
#include <vector>

using namespace std;

vector <int> getPositions(vector <int> &permutation) {
    vector <int> positions(permutation.size());
    for(int i = 0; i < permutation.size(); ++i) {
        positions[permutation[i]] = i;
    }
    return positions;
}

void printOutput(vector < pair <int, int> > &movesToFinalPermutation) {
    for(int i = 0; i < movesToFinalPermutation.size(); ++i){
        pair <int, int> carMove = movesToFinalPermutation[i];
        cout << "move from " << carMove.first << " to " << carMove.second << "\n";
    }
    cout<<"\n";
}

void registerNextMove(int &moveFrom, int &moveTo, vector < pair <int, int> > &moves) {
    pair <int, int> nextMove = make_pair(moveFrom, moveTo);
    swap(moveFrom, moveTo);
    moves.push_back(nextMove);
}

vector < pair <int,  int> > solve(vector <int> &initialPermutation, vector <int> &finalPermutation) {
    vector <int> currentPositions = getPositions(initialPermutation);
    vector <int> finalPositions = getPositions(finalPermutation);
    pair <int, int> nextMove;
    vector < pair <int, int> > moves;
    for(int i = 1; i < currentPositions.size(); ++i){
        while(currentPositions[0] != finalPositions[0]) {
            int numberToSwapWith0 = finalPermutation[currentPositions[0]];
            registerNextMove(currentPositions[numberToSwapWith0], currentPositions[0], moves);
        }
        if(currentPositions[i] != finalPositions[i]) {
            int misplacedNumber = i;
            //swap 0 with misplaced number
            registerNextMove(currentPositions[0], currentPositions[misplacedNumber], moves);
        }
    }
    return moves;
}

vector < pair <int, int> > testing(vector <int> initialPermutation, vector <int> finalPermutation) {
    return solve(initialPermutation, finalPermutation);
}

int main()
{
    //TEST 1: test from assignment
    vector < pair <int, int> > movesToFinalPermutation = testing({1, 2, 0, 3}, {3, 1, 2, 0});
    printOutput(movesToFinalPermutation);
    /*
    move from 1 to 2
    move from 0 to 1
    move from 3 to 0
    */
    //TEST 2: correct placement from the start
    movesToFinalPermutation = testing({1, 2, 0, 3, 4, 5}, {1, 2, 0, 3, 4, 5});
    printOutput(movesToFinalPermutation);
    /* no output */
    //TEST 3: inverse order
    movesToFinalPermutation = testing({1, 4, 2, 0, 5, 3}, {3, 5, 0, 1, 4, 2});
    printOutput(movesToFinalPermutation);
    /*
    move from 0 to 3
    move from 5 to 0
    move from 2 to 5
    move from 2 to 1
    move from 4 to 1
    move from 2 to 4
    */
    //TEST 4: only two numbers swapped
    movesToFinalPermutation = testing({1, 2, 5, 3, 4, 0}, {1, 2, 4, 3, 5, 0});
    printOutput(movesToFinalPermutation);
    /*
    move from 5 to 4
    move from 2 to 4
    move from 5 to 2
    */
    return 0;
}
