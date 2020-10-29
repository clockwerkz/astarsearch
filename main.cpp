
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

int main()
{
    auto board = ReadBoardFile("1.board");
    PrintBoard(board);
    return 0;
}