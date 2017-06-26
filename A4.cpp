#include <fstream>
#include <iostream>
#include <queue>

using namespace std;


class Solution {
    /* The solution uses a fill algorithm, but instead of recursion a queue is used which contains, over time, all the positions in the islands. */
public:
    Solution(const vector < vector <bool> > &inputArray){
        arrayToSolve = inputArray;
        initializeExplored();
        islands = 0;
        solve();
        cout<<islands<<"\n";
    }
private:
    vector < vector <bool> > arrayToSolve;
    //exploredCells keeps track of whether a cell has been visited or not
    vector < vector <bool> > exploredCells;
    queue < pair <int, int> > positionsQueue;
    int islands;
    void initializeExplored(){
        for(int i = 0; i < arrayToSolve.size(); ++i){
            exploredCells.push_back(vector <bool> ());
            for(int j = 0; j < arrayToSolve[i].size(); ++j)
                exploredCells[i].push_back(false);
        }
    }
    void solve(){
        for(int i = 0; i < arrayToSolve.size(); ++i){
            for(int j = 0; j < arrayToSolve[i].size(); ++j){
                //if the cell is part of an island and has not been explored
                //i.e. it is not reachable from any island discovered so far
                //then it is part of a new island and we start exploration from it
                if(arrayToSolve[i][j] && !exploredCells[i][j]){
                    islands += 1;
                    exploreFromPosition(i, j);
                }
            }
        }
    }
    void exploreFromPosition(int line, int column){
        pair <int, int> currentPos;
        positionsQueue.push(make_pair(line, column));
        while(!positionsQueue.empty()){
            currentPos = positionsQueue.front();
            positionsQueue.pop();
            exploredCells[currentPos.first][currentPos.second] = true;
            //now explore in the 4 directions from the correct position
            if(currentPos.first - 1 >= 0){
                if(!exploredCells[currentPos.first - 1][currentPos.second] && arrayToSolve[currentPos.first - 1][currentPos.second]){
                    positionsQueue.push(make_pair(currentPos.first - 1, currentPos.second));
                }
            }
            if(currentPos.first + 1 < arrayToSolve.size()){
                if(!exploredCells[currentPos.first + 1][currentPos.second] && arrayToSolve[currentPos.first + 1][currentPos.second]){
                    positionsQueue.push(make_pair(currentPos.first + 1, currentPos.second));
                }
            }
            if(currentPos.second - 1 >= 0){
                if(!exploredCells[currentPos.first][currentPos.second - 1] && arrayToSolve[currentPos.first][currentPos.second - 1]){
                    positionsQueue.push(make_pair(currentPos.first, currentPos.second - 1));
                }
            }
            if(currentPos.second + 1 < arrayToSolve[0].size()){
                if(!exploredCells[currentPos.first][currentPos.second + 1] && arrayToSolve[currentPos.first][currentPos.second + 1]){
                    positionsQueue.push(make_pair(currentPos.first, currentPos.second + 1));
                }
            }
        }
    }

};


bool getInput(vector < vector <bool> > &inputArray){
    int lines, columns;
    char inputValue;
    ifstream infile("inputFile.in");
    infile>>lines>>columns;
    for(int i = 0; i < lines; ++i){
        inputArray.push_back(vector <bool> ());
        for(int j = 0; j < columns; ++j){
            infile>>inputValue;
            if(inputValue == 'T')
                inputArray[i].push_back(true);
            else if (inputValue == 'F') inputArray[i].push_back(false);
            else return false;
        }
    }
    return true;
}


int main()
{
    vector < vector <bool> > inputArray;
    if(!getInput(inputArray)) {
        cout<<"Input is invalid!\n";
    }
    else {
        Solution newSolution(inputArray);
    }
    return 0;
}
