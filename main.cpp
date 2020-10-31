
#include "main.h"

vector<State> ParseLine(string line)
{
    vector<State> row;
    int num;
    char c;
    std::istringstream myStream(line);
    while (myStream >> num >> c && c == ',')
    {
        row.push_back(num == 0 ? State::kEmpty : State::kObstacle);
    }
    return row;
}

vector<vector<State>> ReadBoardFile(string path)
{
    std::fstream fileName(path);
    if (!fileName)
    {
        cout << "There was an error loading the file.\n";
        return vector<vector<State>>{};
    }
    string line;
    vector<vector<State>> board;
    while (getline(fileName, line))
    {
        board.push_back(ParseLine(line));
    }
    return board;
}

string CellString(State cell)
{
    switch (cell)
    {
    //case State::kObstacle: return "⛰️   ";
    case State::kObstacle:
        return "X   ";
    case State::kClosed:
        return "C   ";
    case State::kPath:
        return "P   ";
    default:
        return "0   ";
    }
}

void PrintBoard(vector<vector<State>> board)
{
    for (auto row : board)
    {
        for (auto cell : row)
        {
            cout << CellString(cell);
        }
        cout << std::endl;
    }
}

int Heuristic(int x1, int y1, int x2, int y2)
{
    return abs(x2 - x1) + abs(y2 - y1);
}
// Sorts in desc order (A > B)
bool CompareValues(vector<int> pointA, vector<int> pointB)
{
    int f1 = pointA[2] + pointA[3];
    int f2 = pointB[2] + pointB[3];
    return f1 > f2;
}

void CellSort(vector<vector<int>> *v){
    std::sort(v->begin(), v->end(), CompareValues);
}

void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &open, vector<vector<State>> &grid)
{
    State nodeStatus = grid[x][y];
    if (nodeStatus != State::kEmpty)
    {
        return;
    }
    vector<int> node = {x, y, g, h};
    open.push_back(node);
    grid[x][y] = State::kClosed;
}

bool CheckValidCell(int x, int y, const vector<vector<State>> &grid)
{
    if (x < 0 || x >= grid.size()) return false;
    if (y < 0 || y >= grid[0].size()) return false;
    if (grid[x][y] != State::kEmpty) return false;
    return true;
}

/* A Star Search Function */
vector<vector<State>> Search(vector<vector<State>> grid, int init[2], int goal[2])
{
    vector<vector<int>> open{};
    int x = init[0];
    int y = init[1];
    int g = 0;
    int h = Heuristic(x, y, goal[0], goal[1]);
    //Add starting point to Open list
    AddToOpen(x, y, g, h, open, grid);
    while (open.size() > 0)
    {
        CellSort(&open);
        //last element will be the smallest f value
        vector<int> currentNode = open.back();
        open.pop_back();
        x = currentNode[0];
        y = currentNode[1];
        if (x == goal[0] && y == goal[1])
        {
            return grid;
        }
        //TODO: Break out this operation into another function - NEED to calculate NEW H value on projected neighbor coord
        if (CheckValidCell(x, y - 1, grid)) AddToOpen(x, y - 1, g + 1, h, open, grid);
        if (CheckValidCell(x - 1, y, grid))  AddToOpen(x - 1, y, g + 1, h, open, grid);
        if (CheckValidCell(x, y + 1, grid)) AddToOpen(x, y + 1, g + 1, h, open, grid);
        if (CheckValidCell(x + 1, y, grid)) AddToOpen(x + 1, y, g + 1, h, open, grid);

    }
    cout << "No path found!\n";
    return vector<vector<State>>{};
}

void PrintList(vector<vector<int>> list)
{
    for (auto row : list)
    {
        int fValue = row[2] + row[3];
        for (auto cell : row)
        {
            cout << cell << "  "; 
        }
        cout << "f value: " << fValue << std::endl;
    }
}

void TestSortingFunction()
{
    vector<vector<int>> openList{
        {0,0,3,0},
        {0,1,2,0},
        {0,2,1,0},
        {3,3,4,5},
        {4,0,5,5}
    };
    cout << "Before sorting:\n";
    cout << "-----------------\n";
    PrintList(openList);
    CellSort(&openList);
    cout << "After Sorting\n";
    cout << "-----------------\n";
    PrintList(openList);
}

int main()
{
    int init[2]{0, 0};
    int goal[2]{4, 5};
    auto board = ReadBoardFile("3.board");
    cout << "Board:\n";
    PrintBoard(board);
    auto solution = Search(board, init, goal);
    cout << "\n\nSolution:\n";
    PrintBoard(solution);
    //Testing Sorting Function
    //------------------------
    //TestSortingFunction();
    return 0;
}