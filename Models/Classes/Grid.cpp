#include <cstdlib>
#include "../Headers/Grid.h"

Grid::Grid(int *const width, int *const height, int *const seed)
{
    this->width = width;
    this->height = height;
    this->seed = seed;

    // allocate memory for the grid
    // allocate memory for the rows each row contains width times size of nibble
    this->grid = new char***[*(this->height)];
    for (int i = 0; i < *(this->height); i++)
    {
        this->grid[i] = new char**[*(this->width)];
    }

}

char Grid::getGridData_ByRowAndColIndex(const int *const row, const int *const col)
{
    return **this->grid[*row][*col];
}

Grid::~Grid()
{
    // free memory for the grid
    for (int i = 0; i < *(this->height); i++)
    {
        delete[] this->grid[i];
    }
    delete[] this->grid;

    delete this->height;
    delete this->width;

}

char Grid::getTileData_ByTileId(const int *const tileId)
{
    return this->tileData[*tileId];
}

void Grid::fillGrid_WithTileData()
{
    srand(*this->seed);
    // fill the grid with tile data
    for (int rowId = 0; rowId < *(this->height); rowId++)
    {
        for (int colId = 0; colId < *(this->width); colId++)
        {
            // generate random number between 0 and 5
            int random_variable = rand() % 6;
            *this->grid[rowId][colId] = (char *) this->tileData[random_variable];
        }
    }

}


