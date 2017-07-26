#include <iostream>
#include <vector>

using namespace std;

//Input: const vector <int> &initial_permutation, const vector <int> &final_permutation - two permutations
//of consecutive natural numbers 0 to N
//Output: vector < pair <int, int> > - a sequence of moves which transform the initial permutation into the final permutation
//Time complexity: linear in the size of the input permutations - O(N)
vector < pair <int, int> > Solve(const vector <int> &initial_permutation, const vector <int> &final_permutation);

//Input: const vector <int> &permutation - a permutation of consecutive natural numbers: 0 to N
//Output: vector <int> - a mapping from the natural numbers to their position in the permutation
//Time complexity: linear in the size of the input permutation vector - O(N)
vector <int> GetPositions(const vector <int> &permutation);

//Input: int &move_from, int &move_to - positions between which next move is happening
//Input: vector < pair <int, int> &moves - array recording a list of moves made so far
//Output: vector < pair <int, int> > &moves - an updated array of moves, with the next move added
//Time complexity: constant - O(1)
void RegisterNextMove(int &move_from, int &move_to, vector < pair <int, int> > &moves);

vector < pair <int, int> > Test(vector <int> initial_permutation, vector <int> final_permutation);

void PrintOutput(const vector < pair <int, int> > &moves_to_final_permutation);

int main()
{
    //TEST 1: test from assignment
    vector < pair <int, int> > moves_to_final_permutation = Test({1, 2, 0, 3}, {3, 1, 2, 0});
    PrintOutput(moves_to_final_permutation);
    /*
    move from 1 to 2
    move from 0 to 1
    move from 3 to 0
    */
    //TEST 2: correct placement from the start
    moves_to_final_permutation = Test({1, 2, 0, 3, 4, 5}, {1, 2, 0, 3, 4, 5});
    PrintOutput(moves_to_final_permutation);
    /* no output */
    //TEST 3: inverse order
    moves_to_final_permutation = Test({1, 4, 2, 0, 5, 3}, {3, 5, 0, 1, 4, 2});
    PrintOutput(moves_to_final_permutation);
    /*
    move from 0 to 3
    move from 5 to 0
    move from 2 to 5
    move from 2 to 1
    move from 4 to 1
    move from 2 to 4
    */
    //TEST 4: only two numbers swapped
    moves_to_final_permutation = Test({1, 2, 5, 3, 4, 0}, {1, 2, 4, 3, 5, 0});
    PrintOutput(moves_to_final_permutation);
    /*
    move from 5 to 4
    move from 2 to 4
    move from 5 to 2
    */
    //TEST 5: numbers shifted by 1 positions
    moves_to_final_permutation = Test({1, 5, 3, 2, 0, 4}, {5, 3, 2, 0, 4, 1});
    PrintOutput(moves_to_final_permutation);
    /*
    move from 5 to 4
    move from 0 to 5
    move from 1 to 0
    move from 2 to 1
    move from 3 to 2
    */
    //TEST 6: everything misplaced except for 0
    moves_to_final_permutation = Test({3, 2, 0, 1, 5, 4}, {2, 4, 0, 5, 1, 3});
    PrintOutput(moves_to_final_permutation);
    /*
    move from 3 to 2
    move from 4 to 3
    move from 2 to 4
    move from 1 to 2
    move from 5 to 1
    move from 0 to 5
    move from 2 to 0
    */
    return 0;
}

vector < pair <int,  int> > Solve(const vector <int> &initial_permutation, const vector <int> &final_permutation) {
    vector <int> current_positions = GetPositions(initial_permutation);
    vector <int> final_positions = GetPositions(final_permutation);
    pair <int, int> next_move;
    vector < pair <int, int> > moves;
    for(int i = 1; i < current_positions.size(); ++i){
        while(current_positions[0] != final_positions[0]) {
            //as long as 0 is misplaced, swap the number which should go into 0's position with 0
            int number_to_swap_with_0 = final_permutation[current_positions[0]];
            RegisterNextMove(current_positions[number_to_swap_with_0], current_positions[0], moves);
        }
        if(current_positions[i] != final_positions[i]) {
            int misplaced_number = i;
            //swap 0 with some misplaced number
            RegisterNextMove(current_positions[misplaced_number], current_positions[0], moves);
        }
    }
    return moves;
}

vector <int> GetPositions(const vector <int> &permutation) {
    vector <int> positions(permutation.size());
    for(int i = 0; i < permutation.size(); ++i) {
        positions[permutation[i]] = i;
    }
    return positions;
}

void RegisterNextMove(int &move_from, int &move_to, vector < pair <int, int> > &moves) {
    pair <int, int> next_move = make_pair(move_from, move_to);
    swap(move_from, move_to);
    moves.push_back(next_move);
}

vector < pair <int, int> > Test(vector <int> initial_permutation, vector <int> final_permutation) {
    return Solve(initial_permutation, final_permutation);
}

void PrintOutput(const vector < pair <int, int> > &moves_to_final_permutation) {
    for(int i = 0; i < moves_to_final_permutation.size(); ++i){
        pair <int, int> current_move = moves_to_final_permutation[i];
        cout << "move from " << current_move.first << " to " << current_move.second << "\n";
    }
    cout<<"\n";
}
