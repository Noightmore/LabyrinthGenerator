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
    int gridSizeW = std::stoi(argv[1]);
    int gridSizeH = std::stoi(argv[2]);
    int seed = std::stoi(argv[3]);
    double zoom = std::stoi(argv[4]);

    Grid* grid = new Grid(&gridSizeW, &gridSizeH, &seed);
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
    auto **items = new QGraphicsPixmapItem*[gridSizeW];
    for (int i = 0; i < gridSizeH; i++)
    {
        items[i] = new QGraphicsPixmapItem[gridSizeH];
    }

    // Add the items to the scene and position them in a grid
    for (int i = 0; i < gridSizeW; i++) {
        for (int j = 0; j < gridSizeH; j++) {

            auto cisloGridu =  grid->getGridData_ByRowAndColIndex(&i, &j);
            switch(cisloGridu) {
                case 0x02:
                    obrazek = obrazky.at(0);
                    break;
                case 0x05:
                    obrazek = obrazky.at(1);
                    break;
                case 0x06:
                    obrazek = obrazky.at(2);
                    break;
                case 0x09:
                    obrazek = obrazky.at(3);
                    break;
                case 0x0C:
                    obrazek = obrazky.at(4);
                    break;
                case 0x0F:
                    obrazek = obrazky.at(5);
                    break;
                default:
                    obrazek = obrazky.at(0);
                    break;
            }


            items[j][i].setPixmap(*obrazek);
            items[j][i].setPos(j * zoom, i * zoom);
            items[j][i].setScale(zoom/10000.0);
            scene.addItem(&items[j][i]);
        }
    }
    view.show();

    grid->printGrid();

    return QApplication::exec();
}

#pragma clang diagnostic pop