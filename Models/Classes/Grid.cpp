#include "../Headers/Grid.h"

Grid::Grid(int *const width, int *const height)
{
    this->width = width;
    this->height = height;

    // allocate memory for the grid
    // allocate memory for the rows each row contains width times size of nibble
    this->grid = new char**[*(this->height)];
    for (int i = 0; i < *(this->height); i++)
    {
        this->grid[i] = new char*[*(this->width)];
    }

}

char Grid::GetGridData_ByRowAndColIndex(const int *const row, const int *const col)
{
    return *this->grid[*row][*col];
}

Grid::~Grid()
{
    // free memory for the grid
    for (int i = 0; i < *(this->height); i++)
    {
        delete[] this->grid[i];
    }
    delete[] this->grid;
}
