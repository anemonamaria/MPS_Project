//
// Created by Bogdan on 13-Nov-22.
// [PalmLeaf-PL1]WN-P1b.csv

#include <iostream>
#include "Main.h"
#include <fstream>
#include <utility>
#include <vector>
#include <sstream>
// Valoare pixel	Clasa pixel	Average threshold	Midrange threshold	White threshold	Bernsen threshold	Niblack threshold	Sauvola threshold	Wolf threshold	Phansalkar threshold	Nick threshold	Gaussian threshold

class Pixel {
private:
    double reference;
    bool pixelClass;
    vector<double> thresholds;

public:
    Pixel(double reference, bool pixelClass, vector<double> thresholds) {
        this->reference = reference;
        this->pixelClass = pixelClass;
        this->thresholds = std::move(thresholds);
    }

    double getReference() const {
        return reference;
    }

    bool getPixelClass() const {
        return pixelClass;
    }

    vector<double> getThresholds() {
        return thresholds;
    }

    void setReference(double value) {
        this->reference = value;
    }

    void setPixelClass(bool value) {
        this->pixelClass = value;
    }

    void setThresholds(vector<double> value) {
        this->thresholds = std::move(value);
    }
};


int main() {
    fstream file;
    file.open("input/mps-local/[DIBCO_2019]6.CSV", ios::in);

    if (!file) {
        cout << "Error opening file";
        return 1;
    }

    string line;

    vector<Pixel> pixels;

    while (file.peek() != EOF) {
        vector<double> thresholds = vector<double>();
        Pixel pixel(0, false, thresholds);

        getline(file, line);
        if (line.empty()) {
            continue;
        }

        // split line by comma
        string delimiter = ",";

        size_t pos = 0;
        string token;

        cout << "P: ";

        pos = line.find(delimiter); // find comma
        token = line.substr(0, pos);
        pixel.setReference(stod(token));
        cout << "r: " << pixel.getReference() << " ";
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter); // find comma
        token = line.substr(0, pos);
        pixel.setPixelClass(stoi(token));
        cout << "c: " << pixel.getPixelClass() << " ";
        line.erase(0, pos + delimiter.length());

        cout << "thr: ";
        while ((pos = line.find(delimiter)) != string::npos) {
            token = line.substr(0, pos);

            thresholds.push_back(stod(token));
            cout << thresholds.back() << " ";
            line.erase(0, pos + delimiter.length());
        }
        // Last value has no comma afterwards
        token = line.substr(0, pos);
        thresholds.push_back(stod(token));
        cout << thresholds.back() << " ";
        line.erase(0, pos + delimiter.length());

        pixel.setThresholds(thresholds);
        pixels.push_back(pixel);
        cout << '\n';
    }

    file.close();
    return 0;
}
