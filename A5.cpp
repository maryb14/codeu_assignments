#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
private:
    enum VisitedStatus {
        NOT_VISITED,
        EXPLORATION_STARTED,
        EXPLORATION_FINISHED,
    };
    vector < vector <int> > edges;
    vector < int > verticesDfsFinishingTimes;
    vector < bool > relevantVertices;
    int numberOfVertices;
    //method dfs returns true is there is a cycle in the graph and false otherwise
    bool findCycleUsingDfs() {
        vector < VisitedStatus > visited (numberOfVertices, NOT_VISITED);
        for(int i = 0; i < numberOfVertices; ++i) {
            if(relevantVertices[i] && visited[i] == NOT_VISITED) {
                if(dfs_visit(i, visited)) {
                    return true;
                }
            }
        }
        return false;
    }
    bool dfs_visit(int vertex, vector < VisitedStatus > &visited) {
        bool foundCycle;
        visited[vertex] = EXPLORATION_STARTED;
        for(int j = 0; j < edges[vertex].size(); ++j) {
            int neighbour = edges[vertex][j];
            if(visited[neighbour] == NOT_VISITED) {
                foundCycle = dfs_visit(neighbour, visited);
                if(foundCycle) return true;
            }
            else if(visited[neighbour] == EXPLORATION_STARTED) {
                //this is a back edge in the graph => there is a cycle
                return true;
            }
        }
        verticesDfsFinishingTimes.push_back(vertex);
        visited[vertex] = EXPLORATION_FINISHED;
        return false;
    }
public:
    Graph(int vertexCount) {
        numberOfVertices = vertexCount;
        edges = vector < vector <int> > (numberOfVertices, vector <int> ());
        relevantVertices = vector <bool> (numberOfVertices, false);
    }
    void addEdge(int firstVertex, int secondVertex) {
        edges[firstVertex].push_back(secondVertex);
    }
    void addVertex(int vertexIndex) {
        relevantVertices[vertexIndex] = true;
    }
    //method topologicalSort returns true if there is a topological sorting of the graph i.e. there are no cycles
    bool topologicalSort(vector <int> &topSortVertices) {
        /* for topological sorting, the algorithm uses a simple dfs which adds the vertices in verticesDfsFinishing times
        in increasing order of finishing times
        to obtain a topological sorted sequence of vertices we simply need to reverse this vector */
        if(!findCycleUsingDfs()) {
            for(int i = verticesDfsFinishingTimes.size() - 1; i >= 0; --i) {
                topSortVertices.push_back(verticesDfsFinishingTimes[i]);
            }
            return true;
        }
        return false;
    }
};

void test(vector <string> orderedStrings);
bool solve(vector <char> &orderedChars, const vector <string> &orderedStrings);
bool findFirstDifferentChars(const string &firstString, const string &secondString, char &firstChar, char &secondChar);
vector <char> convertVerticesToChars(const vector <int> &topSortVertices);
void printOutput(vector <char> &orderedChars);
void addVertices(Graph &charsGraph, const vector <string> &orderedStrings);

int main()
{
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

//method solve returns true is there is a solution to the problem
//and false otherwise
bool solve(vector <char> &orderedChars, const vector <string> &orderedStrings) {
    /* the algorithm works by looking into consecutive strings and possibly extracting a pair of ordered characters from them
    such a pair is then added as an edge into a graph on which we will do topological sorting to obtain the sequence of ordered characters */
    vector <int> topSortVertices;
    char firstChar, secondChar;
    Graph charsGraph(256);
    addVertices(charsGraph, orderedStrings);
    for(int i = 1; i < orderedStrings.size(); ++i) {
        if(findFirstDifferentChars(orderedStrings[i-1], orderedStrings[i], firstChar, secondChar)) {
            charsGraph.addEdge((int)firstChar, (int)secondChar);
        }
    }
    bool orderExists = charsGraph.topologicalSort(topSortVertices);
    if(orderExists) {
        orderedChars = convertVerticesToChars(topSortVertices);
    }
    return orderExists;
}

void addVertices(Graph &charsGraph, const vector <string> &orderedStrings) {
    for(int i = 0; i < orderedStrings.size(); ++i) {
        for(int j = 0; j < orderedStrings[i].length(); ++j) {
            charsGraph.addVertex((int)orderedStrings[i][j]);
        }
    }
}

/* I considered returning a pair of characters instead of referencing the last two parameters,
however, I am not sure how to handle the case when there are no different chars i.e. the first string
is a prefix of the second one. */
bool findFirstDifferentChars(const string &firstString, const string &secondString, char &firstChar, char &secondChar) {
    int i = 0;
    while(i < firstString.length() && i < secondString.length() && firstString[i] == secondString[i]) {
        i++;
    }
    if(firstString.length() != i && secondString.length() != i) {
        firstChar = firstString[i];
        secondChar = secondString[i];
        return true;
    }
    return false;
}


vector <char> convertVerticesToChars(const vector <int> &topSortVertices) {
    vector <char> orderedChars;
    for(int i = 0; i < topSortVertices.size(); ++i) {
        orderedChars.push_back((char)topSortVertices[i]);
    }
    return orderedChars;
}

void printOutput(vector <char> &orderedChars) {
    for(int i = 0; i < orderedChars.size(); ++i) {
        cout << orderedChars[i] << " ";
    }
    cout << "\n";
}
