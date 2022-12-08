#ifndef LABYRINTHGENERATOR_GRID_H
#define LABYRINTHGENERATOR_GRID_H


class Grid
{
private:
    int *width;
    int *height;
    char ***grid;

public:
    Grid(int *width, int *height);
    ~Grid();
    char GetGridData_ByRowAndColIndex(const int *row, const int *col);

};


#endif //LABYRINTHGENERATOR_GRID_H
