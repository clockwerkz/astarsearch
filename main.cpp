#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::string;
using std::vector;

enum class State
{
    kEmpty,
    kObstacle
};

vector<vector<State>> ReadBoardFile(string path)
{
    cout << "Loading the board file: " << path << std::endl;
    return vector<vector<State>>{};
}

int main()
{
    auto board = ReadBoardFile("1.board");
    return 0;
}