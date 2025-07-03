#include "console.h"
#include "simpio.h"
#include <fstream>
#include "grid.h"
#include "queue.h"
#include "set.h"
using namespace std;

struct Coordinate
{
    int row;
    int col;
};


const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};


Vector<Coordinate> findPath_bfs(Grid<int>& maze, Coordinate begin, Coordinate end) {

    Queue<Vector<Coordinate>> toSearch;
    toSearch.enqueue(Vector<Coordinate>(1, begin));

    Set<Vector<int>> reachedPosition;
    reachedPosition.add(Vector<int>{begin.row,begin.col});

    while (!toSearch.isEmpty()) {
        Vector<Coordinate> currentPath = toSearch.dequeue();
        Coordinate currentPosition = currentPath[currentPath.size() - 1];

        if (currentPosition.row == end.row && currentPosition.col == end.col)
        {
            return currentPath;
        }
        else
        {
            for (int i = 0; i < 4; ++i)
            {
                Coordinate newPosition = {currentPosition.row + dx[i], currentPosition.col + dy[i]};

                if (maze.inBounds(newPosition.row, newPosition.col) &&
                    maze[newPosition.row][newPosition.col] == 0 &&
                    !reachedPosition.contains(Vector<int>{newPosition.row,newPosition.col}))
                {
                    reachedPosition.add(Vector<int>{newPosition.row,newPosition.col});
                    Vector<Coordinate> newPath = currentPath;
                    newPath.add(newPosition);
                    toSearch.enqueue(newPath);
                }
            }
        }
    }
    return {};
}

int main() {
    Coordinate start, end;
    Grid<int> maze;
    int n, m;

    ifstream fin("testcase0.txt");
    fin >> start.row >> start.col;
    fin >> end.row >> end.col;
    fin >> n >> m;
    maze.resize(n, m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            fin >> maze[i][j];
        }
    }
    fin.close();

    Vector<Coordinate> path = findPath_bfs(maze, start, end);

    if (path.isEmpty())
    {
        cout << "无解" << endl;
    }
    else
    {

        for (const Coordinate& coord : path)
        {
            maze[coord.row][coord.col] = 2;
        }

        maze[start.row][start.col] = 'S';
        maze[end.row][end.col] = 'T';


        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (maze[i][j] == 'S' || maze[i][j] == 'T')
                {
                    cout << static_cast<char>(maze[i][j]);
                }
                else
                {
                    cout << maze[i][j];
                }
                cout << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
