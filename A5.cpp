#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
private:
	vector < vector <int> > edges;
	vector < int > verticesDfsFinishingTimes;
	int numberOfVertices;
	//method dfs returns true is there is a cycle in the graph and false otherwise
	bool dfs() {
		vector < int > visited (numberOfVertices, -1);
		/* in order to find cycles we need to identify back edges
		we do this by using the vector visited
		visited[i] = -1 if the vertex i exploration from i has not started yet
		visited[i] = 0 if exploration started but did not finish
		visited[i] = 1 if exploration from i is already finished */
		bool foundCycle;
		for(int i = 0; i < numberOfVertices; ++i) {
			if(visited[i] < 0){
				foundCycle = dfs_visit(i, visited);
				if(foundCycle) {
                    return foundCycle;
				}
			}
		}
	}
	bool dfs_visit(int vertex, vector < int > &visited) {
	    bool foundCycle;
		visited[vertex] = 0;
		for(int j = 0; j < edges[vertex].size(); ++j) {
			if(visited[edges[vertex][j]] < 0) {
				foundCycle = dfs_visit(edges[vertex][j], visited);
				if(foundCycle) return true;
			}
			else if(visited[edges[vertex][j]] == 0){
                //this is a back edge in the graph => there is a cycle
                return true;
			}
		}
		verticesDfsFinishingTimes.push_back(vertex);
		visited[vertex] = 1;
		return false;
	}
public:
	Graph(int vertexCount) {
	    numberOfVertices = vertexCount;
		edges = vector < vector <int> > (numberOfVertices, vector <int> ());
	}
	void addEdge(int firstVertex, int secondVertex) {
		edges[firstVertex].push_back(secondVertex);
	}
	//method topologicalSort returns true if there is a topological sorting of the graph i.e. there are no cycles
    bool topologicalSort(vector <int> &topSortVertices) {
        /*
        for topological sorting, the algorithm uses a simple dfs which adds the vertices in verticesDfsFinishing times
        in increasing order of finishing times
        to obtain a topological sorted sequence of vertices we simply need to reverse this vector
        */
		bool foundCycle = dfs();
		if(!foundCycle){
            for(int i = numberOfVertices - 1; i >= 0; --i) {
                topSortVertices.push_back(verticesDfsFinishingTimes[i]);
            }
		}
		return (!foundCycle);
	}
};

void findPresentCharacters(vector <bool> &charactersPresent, vector <string> &orderedStrings) {
    for(int i = 0; i < orderedStrings.size(); ++i) {
        for(int j = 0; j < orderedStrings[i].length(); ++j) {
            charactersPresent[(int)orderedStrings[i][j]] = true;
        }
    }
}

bool extractInfoFromConsecutiveStrings(string &firstString, string &secondString, char &firstChar, char &secondChar){
    /*
    extracting such information amounts to finding the first index of different characters in the two strings
    as long as the first string is not a prefix of the second one, we can deduce an order between the pair of different characters identified
    */
	int i = 0;
	while(i < firstString.length() && i < secondString.length() && firstString[i] == secondString[i]) {
		i++;
	}
	if(firstString.length() != i) {
		firstChar = firstString[i]; secondChar = secondString[i];
	}
	return (firstString.length() != i);
}

/*
the graph will have 256 vertices, one for each character
however, we are interested only in the ones present in the input strings
this method deletes the ones which are not present in the strings
*/
void eliminateAbsentCharacters(vector <int> &topSortVertices, vector <bool> &charactersPresent) {
    int i = 0;
    while(i < topSortVertices.size()) {
        if(!charactersPresent[topSortVertices[i]]) {
            topSortVertices.erase(topSortVertices.begin() + i);
        }
        else {
            i++;
        }
    }
}

void convertVerticesToChars(vector <int> &topSortVertices, vector <char> &orderedChars) {
	for(int i = 0; i < topSortVertices.size(); ++i) {
		orderedChars.push_back((char)topSortVertices[i]);
	}
}

//method solve returns true is there is a solution to the problem
//and false otherwise
bool solve(vector <char> &orderedChars, vector <string> &orderedStrings) {
    /*
    the algorithm works by looking into consecutive strings and possibly extracting a pair of ordered characters from them
    such a pair is then added as an edge into a graph on which we will do topological sorting to obtain the sequence of ordered characters
    */
	vector <int> topSortVertices;
	vector <bool> charactersPresent(256, false);
	findPresentCharacters(charactersPresent, orderedStrings);
	char firstChar, secondChar;
	Graph charsGraph(256);
	for(int i = 1; i < orderedStrings.size(); ++i) {
		if(extractInfoFromConsecutiveStrings(orderedStrings[i-1], orderedStrings[i], firstChar, secondChar)){
			charsGraph.addEdge((int)firstChar, (int)secondChar);
		}
	}
	bool orderExists = charsGraph.topologicalSort(topSortVertices);
    if(orderExists) {
        eliminateAbsentCharacters(topSortVertices, charactersPresent);
        convertVerticesToChars(topSortVertices, orderedChars);
	}
	return orderExists;
}

void printOutput(vector <char> &orderedChars) {
	for(int i = 0; i < orderedChars.size(); ++i) {
		cout << orderedChars[i] << " ";
	}
	cout << "\n";
}

void test(vector <string> orderedStrings) {
    vector <char> orderedChars;
    bool solutionExists;
    solutionExists = solve(orderedChars, orderedStrings);
	if(solutionExists) {
        printOutput(orderedChars);
	}
	else {
        cout << "Input is not valid. No character order can be derived from the input strings.\n";
	}
}

int main() {
    test({"ART", "RAT", "CAT", "CAR"}); //test from assignment
    //output: T A R C
    test({"ART", "ARTA", "ARTAR", "ARTART"}); //prefixes
    //output: T R A
    test({"ART", "CCT", "CAT"}); //test with error
    //output: Input is not valid. No character order can be derived from the input strings.
    test({"%^*($", "%^*$", "^%*", "(%^"}); //test with unusual characters
    //output: * % ^ ( $
	return 0;
}
