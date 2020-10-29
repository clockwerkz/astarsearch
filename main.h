#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using std::cout;
using std::string;
using std::vector;

enum class State
{
    kEmpty,
    kObstacle,
    kClosed
};