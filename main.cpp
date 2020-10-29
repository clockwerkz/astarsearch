
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

void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &open, vector<vector<State>> &grid){
    vector<int> node = {x, y, g, h};
    open.push_back(node);
    grid[x][y] = State::kClosed;
}

vector<vector<State>> Search(vector<vector<State>> grid, int init[2], int goal[2])
{
    vector<vector<int>> open{};
    int x = init[0];
    int y = init[1];
    int g = 0;
    int h = Heuristic(x,y, goal[0], goal[1]);
    AddToOpen(x, y, g, h, open, grid); 
    cout << "No path found!\n";
    return vector<vector<State>>{};
}


int main()
{
    int init[2]{0, 0};
    int goal[2]{4, 5};
    auto board = ReadBoardFile("1.board");
    auto solution = Search(board, init, goal);
    return 0;
}