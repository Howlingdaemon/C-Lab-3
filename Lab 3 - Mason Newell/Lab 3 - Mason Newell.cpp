#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

// you must type 4 integers in the "inMeanStd.dat" file for the file to be read correctly. if not integers are inputed youll get a result that you werent looking for.

class Stat {
public:
    // Constructor
    Stat(const std::string& inputFile, const std::string& outputFile)
        : inputFile(inputFile), outputFile(outputFile) {}

    // User values
    void inputValuesFromUser() {
        std::cout << "Enter four integers one at a time.";
        for (int i = 0; i < 4; i++) {
            int value;
            std::cin >> value;
            userValues.push_back(value);
        }
    }

    // File values
    void inputValuesFromFile() {
        std::ifstream inFile(inputFile);

        // Checks if file is open in an if statement
        if (inFile.is_open()) {
            for (int i = 0; i < 4; i++) {
                int value;
                inFile >> value;
                fileValues.push_back(value);
            }
            inFile.close();
        }
        else {
            std::cout << "Error: Unable to open input file '" << inputFile << "'." << std::endl;
        }
    }

    // Calculating the mean
    double calculateMean(const std::vector<int>& values) {
        double sum = 0;
        for (int value : values) {
            sum += value;
        }
        return sum / values.size();
    }

    // Calculating the population standard deviation
    double calculateStdDev(const std::vector<int>& values, double mean) {
        double sumOfSquares = 0;
        for (int value : values) {
            sumOfSquares += std::pow(value - mean, 2);
        }
        return std::sqrt(sumOfSquares / values.size());
    }

    // Displaying and saving results to output file
    void displayAndSaveResults() {
        double userMean = calculateMean(userValues);
        double userStdDev = calculateStdDev(userValues, userMean);
        double fileMean = calculateMean(fileValues);
        double fileStdDev = calculateStdDev(fileValues, fileMean);

        std::cout << "User-Inputted Values:" << std::endl;
        displayStatistics(userMean, userStdDev);

        std::cout << "\nFile-Inputted Values:" << std::endl;
        displayStatistics(fileMean, fileStdDev);

        std::ofstream outFile(outputFile);
        // Check if file is open
        if (outFile.is_open()) {
            outFile << "User-Inputted Values:" << std::endl;
            saveStatistics(outFile, userMean, userStdDev);

            outFile << "\nFile-Inputted Values:" << std::endl;
            saveStatistics(outFile, fileMean, fileStdDev);

            outFile.close();
        }
        else {
            std::cout << "Error: Unable to open output file '" << outputFile << "'." << std::endl;
        }
    }

private:
    // Creating variable placeholders
    std::string inputFile;
    std::string outputFile;
    std::vector<int> userValues;
    std::vector<int> fileValues;

    // Helper method to display statistics
    void displayStatistics(double mean, double stdDev) {
        std::cout << "Mean: " << std::fixed << std::setprecision(2) << mean << std::endl;
        std::cout << "Population Standard Deviation: " << std::fixed << std::setprecision(2) << stdDev << std::endl;
    }

    // Helper method to save statistics to a file
    void saveStatistics(std::ofstream& outFile, double mean, double stdDev) {
        outFile << "Mean: " << std::fixed << std::setprecision(2) << mean << std::endl;
        outFile << "Population Standard Deviation: " << std::fixed << std::setprecision(2) << stdDev << std::endl;
    }
};

int main() {
    // Specify the input and output file
    std::string inputFile = "inMeanStd.dat";
    std::string outputFile = "outMeanStd.dat";

    Stat calculator(inputFile, outputFile);

    // Displaying and saving results to screen
    calculator.inputValuesFromUser();
    calculator.inputValuesFromFile();
    calculator.displayAndSaveResults();

    return 0;
}
