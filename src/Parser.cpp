//
// Created by Bogdan on 13-Nov-22.
// [PalmLeaf-PL1]WN-P1b.csv
#include "Parser.h"

// Valoare globalPixel	Clasa globalPixel	Average threshold	Midrange threshold	White threshold	Bernsen threshold	Niblack threshold	Sauvola threshold	Wolf threshold	Phansalkar threshold	Nick threshold	Gaussian threshold

int Parser::parseLocal(vector<LocalPixel> &pixels, string filePath) {
    fstream file;
    file.open(filePath, ios::in);

    if (!file) {
        return 1;
    }
    string line;
    while (file.peek() != EOF) {
        vector<double> thresholds = vector<double>();
        LocalPixel localPixel = LocalPixel(0, thresholds, 0);

        getline(file, line);
        if (line.empty()) {
            continue;
        }

        // split line by comma
        string delimiter = ",";

        size_t pos = 0;
        string token;

        pos = line.find(delimiter); // find comma
        token = line.substr(0, pos);
        localPixel.setReference(stod(token));
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter); // find comma
        token = line.substr(0, pos);
        localPixel.setPixelClass(stoi(token));
        line.erase(0, pos + delimiter.length());

        while ((pos = line.find(delimiter)) != string::npos) {
            token = line.substr(0, pos);

            thresholds.push_back(stod(token));
            line.erase(0, pos + delimiter.length());
        }
        // Last value has no comma afterwards
        token = line.substr(0, pos);
        thresholds.push_back(stod(token));
        line.erase(0, pos + delimiter.length());

        localPixel.setThresholds(thresholds);
        pixels.push_back(localPixel);
    }

    file.close();
    return 0;
}


int Parser::parseGlobal(GlobalPixel &globalPixel, string filePath) {
    fstream file;
    file.open(filePath, ios::in);

    if (!file) {
        return 1;
    }
    string line;
    globalPixel = GlobalPixel();

    // Read line of thresholds
    getline(file, line);
    if (line.empty()) {
        return 1;
    }

    // split line by comma
    string delimiter = ",";

    size_t pos = 0;
    string token;

    // todo move to function
    pos = line.find(delimiter); // find comma
    token = line.substr(0, pos);
    globalPixel.setReference(stod(token));

    vector<double> thresholds = vector<double>();


    while ((pos = line.find(delimiter)) != string::npos) {
        token = line.substr(0, pos);

        thresholds.push_back(stod(token));
        line.erase(0, pos + delimiter.length());
    }
    // Last value has no comma afterwards
    token = line.substr(0, pos);
    thresholds.push_back(stod(token));
    line.erase(0, pos + delimiter.length());
    globalPixel.setThresholds(thresholds);

    vector<double> fMeasures = vector<double>();

    // read next line
    getline(file, line);
    if (line.empty()) {
        return 1;
    }
    while ((pos = line.find(delimiter)) != string::npos) {
        token = line.substr(0, pos);

        try {
            fMeasures.push_back(stod(token));
        }
        catch (const std::invalid_argument &e) {
            cout << "Invalid argument: " << e.what() << '\n';
        }
        line.erase(0, pos + delimiter.length());
    }

    if (!line.empty()) {
        // Last value has no comma afterwards
        token = line.substr(0, pos);
        fMeasures.push_back(stod(token));
        line.erase(0, pos + delimiter.length());
    }
    globalPixel.setFMeasures(fMeasures);

    // cout << '\n';
    return 0;
}

double Parser::getFMeasure(double threshold) {
    int idLine = (int) floor(threshold * 255);
    return globalPixel.getFMeasures()[idLine];
}

__attribute__((unused)) void Parser::printLocal() {
    cout << "Local localPixels - " << localPixels.size() << ": \n";
    for (auto &pixel: localPixels) {
        cout << pixel.toString() << '\n';
    }
    cout << "\n\n";
}

__attribute__((unused)) void Parser::printGlobal() {
    cout << "Global pixel: \n";
    cout << globalPixel.toString() << '\n';
    cout << "\n\n";
}

int main() {
    Parser main = Parser();
    int result = main.parseLocal(main.localPixels, "input/mps-local/[DIBCO_2019]6.CSV");
    result &= main.parseGlobal(main.globalPixel, "input/mps-global/[AVE_INT] 2_1.CSV");

    main.printLocal();
    main.printGlobal();

    double fMeasure = main.getFMeasure(0.5);
    cout << "F-measure: " << fMeasure << '\n';

    return result;
}