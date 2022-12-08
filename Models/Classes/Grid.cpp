#include <cstdlib>
#include <iostream>
#include "../Headers/Grid.h"


Grid::Grid(int *const width, int *const height, int *const seed)
{
    this->width = width;
    this->height = height;
    this->seed = seed;
    this->grid = new char ***[*height];
    for (int i = 0; i < *height; i++)
    {
        this->grid[i] = new char **[*width];
        for (int j = 0; j < *width; j++)
        {
            this->grid[i][j] = new char *[1];
            this->grid[i][j][0] = nullptr;
        }
    }
    this->fillGrid_WithTileData();
}

Grid::~Grid()
{
    for (int i = 0; i < *this->height; i++)
    {
        for (int j = 0; j < *this->width; j++)
        {
            delete[] this->grid[i][j];
        }
        delete[] this->grid[i];
    }
    delete[] this->grid;
    delete this->width;
    delete this->height;
    delete this->seed;
}

char Grid::getGridData_ByRowAndColIndex(const int *const row, const int *const col)
{
    return *this->grid[*row][*col][0];
}

char Grid::getTileData_ByTileId(const int *tileId)
{
    return this->tileData[*tileId];
}

void Grid::fillGrid_WithTileData()
{
    srand(*this->seed); // seed the random number generator
    for (int rowId = 0; rowId < *this->height; rowId++)
    {
        for (int colId = 0; colId < *this->width; colId++)
        {
            // generate random number between 0 and 5
            int random_variable = rand() % sizeof(this->tileData);
            // assign the random number to the grid
            this->grid[rowId][colId][0] =
                     &this->tileData[random_variable];
        }
    }
}

// THIS METHOD IS FOR DEBUGGING PURPOSES ONLY
void Grid::printGrid()
{
    for (int i = 0; i < *this->height; i++)
    {
        for (int j = 0; j < *this->width; j++)
        {
            std::cout << std::hex << (int) this->getGridData_ByRowAndColIndex(&i, &j) << " ";
        }
        std::cout << std::endl;
    }
}
