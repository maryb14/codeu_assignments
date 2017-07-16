#include <fstream>
#include <iostream>
#include <queue>

using namespace std;


class Solution {
    /* The solution uses a fill algorithm, but instead of recursion a queue is used which contains, over time, all the positions in the islands. */
public:
    Solution(const vector < vector <bool> > &inputArray){
        arrayToSolve = inputArray;
        exploredCells = vector < vector <bool> > (arrayToSolve.size(), vector < bool > (arrayToSolve[0].size(), false));
        islands = 0;
        solve();
    }
    void printSolution() {
        cout<<islands<<"\n";
    }
private:
    vector < vector <bool> > arrayToSolve;
    //exploredCells keeps track of whether a cell has been visited or not
    vector < vector <bool> > exploredCells;
    queue < pair <int, int> > positionsQueue;
    int islands;
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
    vector < pair <int, int> > generateNeighbours(pair <int, int> coords){
        vector < pair <int, int> > toAdd = {make_pair(1, 0), make_pair(-1, 0), make_pair(0, 1), make_pair(0, -1)};
        vector < pair <int, int> > positions;
        for(int i = 0; i < 4; ++i){
            positions.push_back(make_pair(coords.first + toAdd[i].first, coords.second + toAdd[i].second));
        }
        return positions;
    }
    bool isExplored(pair <int, int> position){
        return exploredCells[position.first][position.second];
    }
    bool isPartOfIsland(pair <int, int> position){
        return arrayToSolve[position.first][position.second];
    }
    bool isValid(pair <int, int> position){
        return (position.first < arrayToSolve.size() && position.first >= 0 && position.second >= 0 && position.second < arrayToSolve[0].size());
    }
    vector < pair <int, int> > getValidPositions(vector < pair <int, int> > positions){
        vector < pair <int, int> > validPositions;
        for(int i = 0; i < positions.size(); ++i){
            if(isValid(positions[i]))
                validPositions.push_back(positions[i]);
        }
        return validPositions;
    }

    void exploreFromPosition(int line, int column){
        pair <int, int> currentPos;
        positionsQueue.push(make_pair(line, column));
        while(!positionsQueue.empty()){
            currentPos = positionsQueue.front();
            positionsQueue.pop();
            exploredCells[currentPos.first][currentPos.second] = true;
            //now explore in the 4 directions from the correct position
            vector < pair <int, int> > validPositions = getValidPositions(generateNeighbours(currentPos));
            for(int i = 0; i < validPositions.size(); ++i){
                if(!isExplored(validPositions[i]) && isPartOfIsland(validPositions[i])){
                    positionsQueue.push(validPositions[i]);
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
        newSolution.printSolution();
    }
    return 0;
}
