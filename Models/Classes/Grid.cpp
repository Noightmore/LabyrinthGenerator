#include <cstdlib>
#include <iostream>
#include "../Headers/Grid.h"


Grid::Grid(int *const width, int *const height, int *const seed)
{
    this->width = width;
    this->height = height;
    this->seed = seed;
    this->grid = new char **[*height];
    this->allocateGrid();
    this->fillGrid_WithTileData();
}

Grid::~Grid()
{
    this->deallocateGrid();
    delete this->width;
    delete this->height;
    delete this->seed;
}

char Grid::getGridData_ByRowAndColIndex(const int *const row, const int *const col)
{
    return *this->grid[*row][*col];
}

[[maybe_unused]] char Grid::getTileData_ByTileId(const int *tileId)
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
            auto tile_id = getCompatibleTileId(&rowId, &colId);
            // assign the random number to the grid
            this->grid[rowId][colId] =
                     &this->tileData[tile_id];
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

int Grid::getCompatibleTileId(const int *const rowId, const int *const colId)
{
    int random_variable = rand() % sizeof(this->tileData);
    if(*colId == 0 && *rowId == 0)
    {
        // if colId is 0, and the rowId is 0, then the tile is in the top left corner,
        // and we return the random value as it is
        return random_variable;
    }

    // if colId is 0, then the tile is in the first column, and we need to check the tile above it
    if(*colId == 0 && *rowId != 0)
    {
        auto tile_above_rowId = *rowId - 1;
        auto tile_above = getGridData_ByRowAndColIndex(&tile_above_rowId, colId);
        // if the tile above is compatible with the current tile, then we return the random value
        while(!checkTopCompatibility(&tile_above, &this->tileData[random_variable]))
        {
            random_variable = rand() % sizeof(this->tileData);
        }
        return random_variable;
    }

    // first row case
    if(*rowId == 0 && *colId != 0)
    {
        auto tile_left_colId = *colId - 1;
        auto tile_left = getGridData_ByRowAndColIndex(rowId, &tile_left_colId);
        // if the tile left is compatible with the current tile, then we return the random value
        while(!checkLeftCompatibility(&tile_left, &this->tileData[random_variable]))
        {
            random_variable = rand() % sizeof(this->tileData);
        }
        return random_variable;
    }

    if(*rowId != 0 && *colId != 0)
    {
        auto tile_above_rowId = *rowId - 1;
        auto tile_above = getGridData_ByRowAndColIndex(&tile_above_rowId, colId);
        auto tile_left_colId = *colId - 1;
        auto tile_left = getGridData_ByRowAndColIndex(rowId, &tile_left_colId);

        while(!checkLeftCompatibility(&tile_left, &this->tileData[random_variable])
              && !checkTopCompatibility(&tile_above, &this->tileData[random_variable]))
        {
            random_variable = rand() % sizeof(this->tileData);
        }
        return random_variable;
    }
}

bool Grid::checkTopCompatibility(const char *const topTileData, const char *const currentTileData)
{
    const char topTileDataMask = 0b00000100;
    // bit shift left the top tile data by 2 bits
    // to align the bit representing the bottom pointing arrow of the top tile
    // with the bit representing the top pointing arrow of the current tile
    auto shifted_top_tile_data = *topTileData << 2;

    // mask out all the bytes but those representing the arrows pointing towards each other
    auto masked_top_tile_data = shifted_top_tile_data & topTileDataMask;
    auto masked_current_tile_data = *currentTileData & topTileDataMask;

    auto result = masked_top_tile_data == masked_current_tile_data;

    return result; // returns the existence of the connection
}

bool Grid::checkLeftCompatibility(const char *const leftTileData, const char *const currentTileData)
{
    const char leftTileDataMask = 0b00001000;

    auto shifted_left_tile_data = *leftTileData << 2;
    auto masked_left_tile_data = shifted_left_tile_data & leftTileDataMask;
    auto masked_current_tile_data = *currentTileData & leftTileDataMask;

    auto result = masked_left_tile_data == masked_current_tile_data;
    return result;
}

void Grid::allocateGrid()
{
    for (int i = 0; i < *this->height; i++)
    {
        this->grid[i] = new char *[*this->width];
        for (int j = 0; j < *this->width; j++)
        {
            this->grid[i][j] = nullptr;
        }
    }
}

void Grid::deallocateGrid()
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
}
