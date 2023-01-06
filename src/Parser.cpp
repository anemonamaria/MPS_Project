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
        // Last threshold has no comma afterwards
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
    // Last threshold has no comma afterwards
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
        // Last threshold has no comma afterwards
        token = line.substr(0, pos);
        fMeasures.push_back(stod(token));
        line.erase(0, pos + delimiter.length());
    }
    globalPixel.setFMeasures(fMeasures);

    // cout << '\n';
    return 0;
}

double Parser::getFMeasureGlobal(double threshold) {
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

string Parser::createFunctionChainGlobal() {
    // Create intial nodes (leafs) from the thresholds of the global pixel
    vector<double> thresholds = globalPixel.getThresholds();

    vector<Node *> treeGlobal = vector<Node *>();

    int index = 0;
    for (auto &threshold: thresholds) {
        Node *node = new Node(threshold);
        node->identifier = "thresholds[" + to_string(index) + "]";
        treeGlobal.push_back(node);
        index++;
    }

    // Create random new node
    time_t timeVar;
    srand((unsigned) time(&timeVar));

    Node *newNode;
    double limit = 0;
    for (const auto &item: globalPixel.getFMeasures()) {
        if (item > limit) {
            limit = item;
        }
    }
    limit -= 15;
    cout << "Trying to find a node with fMeasure > " << limit << '\n';

    // Generate nodes until fMeasure is bigger than desired value
    while (true) {
        Node *leftParent = treeGlobal[rand() % treeGlobal.size()];
        Node *rightParent = treeGlobal[rand() % treeGlobal.size()];
        newNode = new Node(leftParent, rightParent);

        double fMeasure = getFMeasureGlobal(newNode->threshold);

        treeGlobal.push_back(newNode);

        // get maximum of the fMeasures and minus 5

        if (fMeasure > limit) {
            // This node is root
            cout << "Root node: " << newNode->threshold << " with fMeasure: " << fMeasure << '\n';
            break;
        }
    }

    //  newNode is the root of the tree
    string functionChain = printTree(newNode);
    return functionChain;
}

string Parser::printTree(Node *node) {
    if (node == nullptr) {
        return "";
    }

    if (node->leftParent == nullptr || node->rightParent == nullptr) {
        return node->identifier;
    }
    string left = printTree(node->leftParent);
    string right = printTree(node->rightParent);
    string functionString = node->functionName;
    return functionString + "(" + left + ", " + right + ")";
}

double Parser::getFMeasureLocal(int noTruePositives, int noFalsePositives, int noTrueNegatives, int noFalseNegatives) {
    double numerator = noTruePositives;
    double denominator = noTruePositives + 0.5 * (noFalsePositives + noFalseNegatives);
    return numerator / denominator;
}

string Parser::createFunctionChainLocal() {

    int noTruePositives = 0, noFalsePositives = 0, noFalseNegatives = 0, noTrueNegatives = 0;
    for (auto &localPixel: localPixels) {
        cout << "\nLocal pixel:\n";

        // Create intial nodes (leafs) from the thresholds of the global pixel
        vector<double> thresholds = localPixel.getThresholds();

        vector<Node *> treeLocal = vector<Node *>();

        int index = 0;
        for (auto &threshold: thresholds) {
            Node *node = new Node(threshold);
            node->identifier = "thresholds[" + to_string(index) + "]";
            treeLocal.push_back(node);
            index++;
        }

        // Create random new node
        time_t timeVar;
        srand((unsigned) time(&timeVar));

        Node *newNode;

        // Generate 100 nodes
        int idNewNode = 0;
        while (idNewNode < 100) {
            Node *leftParent = treeLocal[rand() % treeLocal.size()];
            Node *rightParent = treeLocal[rand() % treeLocal.size()];
            newNode = new Node(leftParent, rightParent);
            treeLocal.push_back(newNode);
            ++idNewNode;
        }

        // Calculate which pixels are true/false positive/negative
        for (auto &threshold: thresholds) {
            if (threshold < localPixel.getReference()) {
                // White
                if (localPixel.getPixelClass() == 0) {
                    // True positive
                    ++noTruePositives;
                    cout << "TP ";
                } else {
                    // False positive
                    ++noFalsePositives;
                    cout << "FP ";
                }
            } else {
                // Black
                if (localPixel.getPixelClass() == 1) {
                    // True negative
                    ++noTrueNegatives;
                    cout << "TN ";
                } else {
                    // False negative
                    ++noFalseNegatives;
                    cout << "FN ";
                }
            }
        }
    }

    cout << "\nFound " << noTruePositives << " true positives, " << noFalsePositives << " false positives, "
         << noTrueNegatives << " true negatives and " << noFalseNegatives << " false negatives.\n";

    return "";
}


int main() {
    // Fill output with defines for functions

    std::string outputFileInitialContent;
    outputFileInitialContent += "#include <algorithm>\n";
    outputFileInitialContent += "#include <cmath>\n";
    outputFileInitialContent += "#define arithmeticMean(x, y) ((x + y) / 2)\n";
    outputFileInitialContent += "#define geometricMean(x, y) (sqrt(x * y))\n";
    outputFileInitialContent += "#define harmonicMean(x, y) (2 / ((1 / x) + (1 / y)))\n";
    outputFileInitialContent += "#define minFunction(x, y) (min(x, y))\n";
    outputFileInitialContent += "#define maxFunction(x, y) (max(x, y))\n";
    outputFileInitialContent += "using namespace std;\n";
    outputFileInitialContent += "\ndouble binarization(double* thresholds){\n";

    // get all csv inputFiles in the directory from inputFiles.txt
    ifstream inputFiles;
    inputFiles.open("input/mps-global/input_files.txt");
    if (!inputFiles) {
        exit(1);
    }
    int result = 0;

    while (!inputFiles.eof()) {
        string inputFile;
        getline(inputFiles, inputFile);
        if (inputFile.empty()) {
            continue;
        }
        if (inputFile.find(".CSV") == string::npos && inputFile.find(".csv") == string::npos) {
            continue;
        }

        cout << "Parsing " << inputFile << "\n";

        Parser main = Parser();


//    result = main.parseLocal(main.localPixels, "input/mps-local/[DIBCO_2019]6.CSV");

        // run the function and wait for 15 seconds, if it takes longer, kill it

        result &= main.parseGlobal(main.globalPixel, "input/mps-global/" + inputFile);

//    main.printLocal();
        main.printGlobal();

        string functionChainGlobal = main.createFunctionChainGlobal();
//    string functionChainLocal = main.createFunctionChainLocal();

        // Append to output

        string outputPath = "output/mps-global/";
        outputPath += "global_output_" + inputFile;
        outputPath = outputPath.substr(0, outputPath.find_last_of('.')) + ".cpp"; // replace .csv with .cpp
        // remove spaces
        outputPath.erase(remove(outputPath.begin(), outputPath.end(), ' '), outputPath.end());
        ofstream output;

        cout << "Writing to " << outputPath << "\n";
        output.open(outputPath, fstream::out);

        if (!output) {
            cout << "Could not open output file " << outputPath << "\n";
            exit(1);
        }
        output << outputFileInitialContent;

        output << "\treturn " << functionChainGlobal << ";\n}\n";
        output.close();

        cout << "----------------------------------------\n";
    }

    return result;


}
