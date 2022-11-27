//
// Created by Bogdan on 13-Nov-22.
// [PalmLeaf-PL1]WN-P1b.csv

#include <iostream>
#include "Main.h"
#include <fstream>
#include <utility>
#include <vector>
#include <sstream>
#include <cmath>
// Valoare pixel	Clasa pixel	Average threshold	Midrange threshold	White threshold	Bernsen threshold	Niblack threshold	Sauvola threshold	Wolf threshold	Phansalkar threshold	Nick threshold	Gaussian threshold

// create abstract class for a generic pixel

class Pixel {
private:
    double reference;
    vector<double> thresholds;

public:
    Pixel() {
        reference = 0;
        thresholds = vector<double>();
    }

    Pixel(double reference, vector<double> thresholds) {
        this->reference = reference;
        this->thresholds = std::move(thresholds);
    }

    double getReference() const {
        return reference;
    }

    vector<double> getThresholds() {
        return thresholds;
    }

    void setReference(double value) {
        this->reference = value;
    }

    void setThresholds(vector<double> value) {
        this->thresholds = std::move(value);
    }
};

class GlobalPixel : public Pixel {
private:
    vector<double> fMeasures;
public:
    GlobalPixel() : Pixel() {
        fMeasures = vector<double>();
    }

    GlobalPixel(double reference, const vector<double> &thresholds, vector<double> fMeasures) : Pixel(reference,
                                                                                                      thresholds) {
        this->fMeasures = std::move(fMeasures);
    }

    vector<double> getFMeasures() {
        return fMeasures;
    }

    void setFMeasures(vector<double> value) {
        this->fMeasures = std::move(value);
    }
};

// create a class LocalPixel extends GlobalPixel
class LocalPixel : public Pixel {
private:
    double pixelClass;

public:
    LocalPixel(double reference, vector<double> thresholds, double pixelClass) :
            Pixel(reference, std::move(thresholds)) {
        this->pixelClass = pixelClass;
    }

    double getPixelClass() const {
        return pixelClass;
    }

    void setPixelClass(double value) {
        this->pixelClass = value;
    }
};

vector<LocalPixel> pixels;

int parseLocal() {
    fstream file;
    file.open("input/mps-local/[DIBCO_2019]6.CSV", ios::in);

    if (!file) {
        // // cout << "Error opening file";
        return 1;
    }

    string line;


    while (file.peek() != EOF) {
        vector<double> thresholds = vector<double>();
        LocalPixel pixel = LocalPixel(0, thresholds, 0);

        getline(file, line);
        if (line.empty()) {
            continue;
        }

        // split line by comma
        string delimiter = ",";

        size_t pos = 0;
        string token;

        // // cout << "P: ";

        pos = line.find(delimiter); // find comma
        token = line.substr(0, pos);
        pixel.setReference(stod(token));
        // // cout << "r: " << pixel.getReference() << " ";
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter); // find comma
        token = line.substr(0, pos);
        pixel.setPixelClass(stoi(token));
        // // cout << "c: " << pixel.getPixelClass() << " ";
        line.erase(0, pos + delimiter.length());

        // // cout << "thr: ";
        while ((pos = line.find(delimiter)) != string::npos) {
            token = line.substr(0, pos);

            thresholds.push_back(stod(token));
            // // cout << thresholds.back() << " ";
            line.erase(0, pos + delimiter.length());
        }
        // Last value has no comma afterwards
        token = line.substr(0, pos);
        thresholds.push_back(stod(token));
        // // cout << thresholds.back() << " ";
        line.erase(0, pos + delimiter.length());

        pixel.setThresholds(thresholds);
        pixels.push_back(pixel);
        // // cout << '\n';
    }

    file.close();
    return 0;
}

GlobalPixel pixel;

int parseGlobal() {
    fstream file;
    file.open("input/mps-global/[AVE_INT] 2_1.CSV", ios::in);

    if (!file) {
        // cout << "Error opening file";
        return 1;
    }
    string line;
    pixel = GlobalPixel();

    // Read line of thresholds
    getline(file, line);
    if (line.empty()) {
        return 1;
    }

    // split line by comma
    string delimiter = ",";

    size_t pos = 0;
    string token;

    // cout << "P: ";

    // todo move to function
    pos = line.find(delimiter); // find comma
    token = line.substr(0, pos);
    pixel.setReference(stod(token));
    // cout << "r: " << pixel.getReference() << " ";

    // cout << "thr: ";
    vector<double> thresholds = vector<double>();


    while ((pos = line.find(delimiter)) != string::npos) {
        token = line.substr(0, pos);

        thresholds.push_back(stod(token));

        // cout << thresholds.back() << " ";
        line.erase(0, pos + delimiter.length());
    }
    // Last value has no comma afterwards
    token = line.substr(0, pos);
    thresholds.push_back(stod(token));
//    // cout << thresholds.back() << " ";
    line.erase(0, pos + delimiter.length());
    pixel.setThresholds(thresholds);
    // cout << '\n';

    vector<double> fMeasures = vector<double>();

    // read next line
    getline(file, line);
    if (line.empty()) {
        return 1;
    }
    // cout << "F-measures: ";
    while ((pos = line.find(delimiter)) != string::npos) {
        token = line.substr(0, pos);

        try {
            fMeasures.push_back(stod(token));
        }
        catch (const std::invalid_argument &e) {
            // cout << "Invalid argument: " << e.what() << '\n';
        }

        // cout << fMeasures.back() << " ";
        line.erase(0, pos + delimiter.length());
    }

    if (!line.empty()) {
        // Last value has no comma afterwards
        token = line.substr(0, pos);
        fMeasures.push_back(stod(token));
        // cout << fMeasures.back() << " ";
        line.erase(0, pos + delimiter.length());
    }
    pixel.setFMeasures(fMeasures);

    // cout << '\n';
    return 0;
}

double getFMeasure(double threshold) {
    int idLine = (int) floor(threshold * 255);
    return pixel.getFMeasures()[idLine];
}

int main() {
    // cout << "Local: \n\n";
    int result = parseLocal();

    // cout << "Global: \n";
    result &= parseGlobal();

    double fMeasure = getFMeasure(0.5);
    cout << "F-measure: " << fMeasure << '\n';

    return result;
}
