#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc51-cpp"

#include <iostream>
#include "Models/Headers/Grid.h"

#include "Models/Headers/mainwindow.h"

#include <QApplication>
#include <fstream>

int main([[maybe_unused]] int argc, char** argv)
{
//    // alokace parametru na stack
//    int width = std::stoi(argv[1]);
//    int height = std::stoi(argv[2]);
//    int seed = std::stoi(argv[3]);
//
//    std::cout << "Width: " << width << std::endl;
//    std::cout << "Height: " << height << std::endl;
//    std::cout << "seed: " << seed << std::endl;
//
//    // grid se alokuje na heap
//    Grid * grid = new Grid(&width, &height, &seed);
//
//    // vypis gridu
//    grid->printGrid();
//
//    // konec programu, jiz zadna data nepotrebujeme
//    grid->~Grid();


//    QApplication app(argc, argv);
//    MainWindow window;
//    //window.resize(320, 240);
//    window.show();
//    window.setWindowTitle(
//            QApplication::translate("toplevel", "Labyrinth Generator"));
//    return QApplication::exec();


    QApplication app(argc, argv);

    // Create a QGraphicsView widget
    QGraphicsView view;

    // Create a QGraphicsScene and add it to the view
    QGraphicsScene scene;
    view.setScene(&scene);

    // Set the size of the grid and the size of each image
    const int gridSize = 4;
    const int imageSize = 200;
    const int seed = 1242344;

    Grid* grid = new Grid(&gridSize, &gridSize, &seed);
    QPixmap *obrazek;

    std::ifstream test("../img/2.png");
    if (!test)
    {
        std::cout << "The file doesn't exist" << std::endl;
    }

    // Load the images from file
    std::vector<QPixmap*> obrazky = {
            new QPixmap("../img/2.png"),
            new QPixmap("../img/5.png"),
            new QPixmap("../img/6.png"),
            new QPixmap("../img/9.png"),
            new QPixmap("../img/c.png"),
            new QPixmap("../img/f.png")
    };

    // Create a 2D array of QGraphicsPixmapItem objects
    auto **items = new QGraphicsPixmapItem*[gridSize];
    for (int i = 0; i < gridSize; i++)
    {
        items[i] = new QGraphicsPixmapItem[gridSize];
    }

    // Add the items to the scene and position them in a grid
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {

            auto cisloGridu =  grid->getGridData_ByRowAndColIndex(&i, &j);
            std::cout << (int) cisloGridu << std::endl;
            switch(cisloGridu) {
                case 2:
                    obrazek = obrazky[0];
                    break;
                case 5:
                    obrazek = obrazky[1];
                    break;
                case 6:
                    obrazek = obrazky[2];
                    break;
                case 9:
                    obrazek = obrazky[3];
                    break;
                case 12:
                    obrazek = obrazky[4];
                    break;
                case 15:
                    obrazek = obrazky[5];
                    break;
                default:
                    obrazek = obrazky[0];
                    break;
            }

            items[i][j].setPixmap(*obrazek);

            items[i][j].setPos(i * imageSize, j * imageSize);
            items[i][j].setScale(0.02);

            // Add the item to the scene
            scene.addItem(&items[i][j]);
        }
    }
    // Show the view
    view.show();

    grid->printGrid();

    return QApplication::exec();
    return 0;
}

#pragma clang diagnostic pop