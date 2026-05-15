// ##########################################################
// Tarea Corta 5 - Estructuras de Datos
// Edwin Andrey Muñoz Sandí 2025075200
// ############################################################

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <string>
#include <sstream>
#include "Matrix.h"

using std::cout;

static int readInt(const std::string& prompt) {
    while (true) {
        cout << prompt;
        std::string line;
        std::getline(std::cin, line);

        std::istringstream iss(line);
        int value{};
        if ((iss >> value) && (iss >> std::ws).eof())
            return value;
        cout << "Not a valid integer. Try again.\n";
    }
}

static int readIntInRange(const std::string& prompt, int min, int max) {
    while (true) {
        int value = readInt(prompt);

        if (value >= min && value <= max)
            return value;
        cout << "Integer must be between " << min << " and " << max << ". Try again.\n";
    }
}

static void showMenu() {
    cout << "\n\tOperations\n";
    cout << "1. Get value\n";
    cout << "2. Set value\n";
    cout << "3. Get rows\n";
    cout << "4. Get columns\n";
    cout << "5. Set all\n";
    cout << "6. Transpose\n";
    cout << "7. Add row\n";
    cout << "8. Add column\n";
    cout << "9. Remove row\n";
    cout << "10. Remove column\n";
    cout << "11. Fill with random values (0-99)\n";
    cout << "0. Exit\n";
}

static void fillRandom(Matrix<int>& matrix) {
    for (int r = 0; r < matrix.getRows(); r++)
        for (int c = 0; c < matrix.getColumns(); c++)
            matrix.setValue(r, c, std::rand() % 100);
}

static void pressToContinue() {
    std::cout << "\nPress ENTER to continue...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

int main() {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Cualquier cosa los índices en la interfaz de usuario se leen en la
    // forma humana, es decir, empezando desde 1 hasta n. Lo hice así para
    // que sea más fácil y natural usar la intefaz.

    cout << "\tCreate Matrix\n";
    int rows = readInt("Number of rows: ");
    int cols = readInt("Number of columns: ");

    Matrix<int>* matrix = nullptr;
    try {
        matrix = new Matrix<int>(rows, cols);
    }
    catch (const std::runtime_error& e) {
        cout << "Could not create matrix: " << e.what() << '\n';
        return 1;
    }

    int option = -1;
    while (option != 0) {
        cout << "\nCurrent Matrix:\n";
        matrix->print();
        showMenu();
        option = readIntInRange("Choose an option: ", 0, 11);

        cout << '\n';
        try {
            if (option == 1) {
                int r = readInt("Row (1 to " + std::to_string(matrix->getRows()) + "): ");
                int c = readInt("Column (1 to " + std::to_string(matrix->getColumns()) + "): ");
                int value = matrix->getValue(r - 1, c - 1);
                cout << "\nValue at (" << r << "," << c << "): " << value << '\n';
            }
            else if (option == 2) {
                int r = readInt("Row (1 to " + std::to_string(matrix->getRows()) + "): ");
                int c = readInt("Column (1 to " + std::to_string(matrix->getColumns()) + "): ");
                int value = readInt("Value: ");
                matrix->setValue(r - 1, c - 1, value);
            }
            else if (option == 3) {
                cout << "Rows: " << matrix->getRows() << '\n';
            }
            else if (option == 4) {
                cout << "Columns: " << matrix->getColumns() << '\n';
            }
            else if (option == 5) {
                int value = readInt("Value to set in every cell: ");
                matrix->setAll(value);
            }
            else if (option == 6) {
                matrix->transpose();
            }
            else if (option == 7) {
                int value = readInt("Value to fill the new row with: ");
                matrix->addRow(value);
            }
            else if (option == 8) {
                int value = readInt("Value to fill the new column with: ");
                matrix->addColumn(value);
            }
            else if (option == 9) {
                int r = readInt("Row to remove (1 to " + std::to_string(matrix->getRows()) + "): ");
                matrix->removeRow(r - 1);
            }
            else if (option == 10) {
                int c = readInt("Column to remove (1 to " + std::to_string(matrix->getColumns()) + "): ");
                matrix->removeColumn(c - 1);
            }
            else {
                fillRandom(*matrix);
            }
        }
        catch (const std::runtime_error& e) {
            cout << "\nOperation failed: " << e.what() << '\n';
        }
        if (option != 0) pressToContinue();
    }

    delete matrix;
    return 0;
}