//
// Created by Bogdan on 13-Nov-22.
// [PalmLeaf-PL1]WN-P1b.csv

#include <iostream>
#include "Main.h"
#include <fstream>
#include <vector>
#include <sstream>

int main() {
    fstream file;
    file.open("input/mps-local/[DIBCO_2019]6.CSV", ios::in);

    if (!file) {
        cout << "Error opening file";
        return 1;
    }

    string line;
    while (file.peek() != EOF) {
        getline(file, line);
        if (line.empty()) {
            continue;
        }

        // split line by comma
        string delimiter = ",";

        size_t pos = 0;
        string token;
        while ((pos = line.find(delimiter)) != string::npos) {
            token = line.substr(0, pos);
            double value = stod(token);
            cout << value << " ";
            line.erase(0, pos + delimiter.length());
        }
        // Last value has no comma afterwards
        double value = stod(line);
        cout << value << " ";
        cout << '\n';
    }

    file.close();
    return 0;
}
