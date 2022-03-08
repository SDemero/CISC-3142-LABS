// This file shows basic functions of reading in a CSV file using C++98
// Mohamed Mohamed

/* Homework Objective: fix this program to match the requirements listed: 
  1. successfully reads all lines of the input file
  2. calculate the average price per brand, average price per category 
  3. writes to an output file
  4. for each unique year, list the count of skus and also print out the skus as a list i.e. 2000 (3): 111, 211, 311 and make a new line per year.
All programs must be able to compile in C++98 standard (the default version on Linux Machine). That means you cannot use the new features of C++11! :(
*/
#include "my_class.h"

struct labData {
    // define variables
    string sku, brand, category, year, price; // Defining several string variables

    // Defining dynamic storage space (vectors) for several variables of different types
    vector<int>vSKU;
    vector<string>vBrand;
    vector<string>vCategory;
    vector<int>vYear;
    vector<float>vPrice;

    // Feature 1
    vector<string> vUniqueBrands;
    vector< vector<float> > vBrandAvgPrice;

    vector<string> vUniqueCategories;
    vector< vector<float> > vCategoryAvgPrice;

    // Feature 2
    vector<string> vUniqueYears;
    vector< vector<string> > vSKUsByYear;

    ifstream in_stream;  // creating an input stream to read the input file
    ofstream out_stream; // creating an output stream to create an output file

    // Change *path variable to the path of your data file
    char *inputPath;
    char *outputPath;

    void printSKUsByYear(FILE *pFile) {
        printf("SKUs By Year\n\n");
        fprintf(pFile, "SKUs By Year\n\n");
        for (int j = 0; j < vUniqueYears.size(); j++) {
            string skuList;
            for (int i = 0; i < vSKUsByYear[j].size(); i++) {
                skuList += vSKUsByYear[j][i];
                if (i + 1 != vSKUsByYear[j].size()) {
                    skuList += ", ";
                }
            }
            printf("%s (%d): %s\n", vUniqueYears[j].c_str(), vSKUsByYear[j].size(), skuList.c_str());
            fprintf(pFile, "%s (%d): %s\n", vUniqueYears[j].c_str(), vSKUsByYear[j].size(), skuList.c_str());
        }

        printf("\n\n");
        fprintf(pFile, "\n\n");
    }

};

int main() {

    labData testDataOne;

    // Change *path variable to the path of your data file
    testDataOne.inputPath = "C:\\Users\\makmn\\CLionProjects\\CISC-3142-LAB-1\\data.csv";
    testDataOne.outputPath = "C:\\Users\\makmn\\CLionProjects\\CISC-3142-LAB-1\\output.txt";
    FILE *pFile = fopen("C:\\Users\\makmn\\CLionProjects\\CISC-3142-LAB-1\\output.txt", "w");

    // accessing the input file using the created input stream
    testDataOne.in_stream.open(testDataOne.inputPath); //opening the file.
    testDataOne.out_stream.open(testDataOne.outputPath);

    if (!testDataOne.in_stream.fail()) { //if the file is open

        // declaring variable line of type string (only used for first getline call to skip headers)
        string line;

        /* SKIP LINE BUG
         * get line gets one line from the given input stream and stores it into the line argument
         * Using this to check for the end of file is not ideal since it extracts the line into the line argument variable
         * The problem with this is we don't use this line, and we continue extracting forward.
         * We could possibly split the line string using the same delimiters, but a way I found and prefer
         * is to check if the end of file flag has been raised on the stream.
         * The flag will be raised on the last getline call for price, where the delimeter '\n' is not reached (because it doesn't exist)
         * and the eof is reached instead, thereby raising the eof flag.
         */
        getline(testDataOne.in_stream, line); // Gets the first line of headers (we won't be using it)

        while (!testDataOne.in_stream.eof()) { //while the end of file is NOT reached

            // Fields: sku,brand,category,year,price

            // extracts all text from current file position (inclusive) to ',' (exclusive) and stores it into the declared variable sku (implicitly defined as a string)
            getline(testDataOne.in_stream, testDataOne.sku, ',');

            // stringstream is a stream class to operate on strings
            stringstream ssku(testDataOne.sku);
            int iSKU = 0;

            // using stringstream, we can set iSKU to equal sku through dynamic type conversion
            ssku >> iSKU;

            // creates an element at the end of the vector and assigns it the given value
            testDataOne.vSKU.push_back(iSKU);

            getline(testDataOne.in_stream,testDataOne.brand, ',');
            testDataOne.vBrand.push_back(testDataOne.brand);

            getline(testDataOne.in_stream, testDataOne.category, ',');
            testDataOne.vCategory.push_back(testDataOne.category);

            getline(testDataOne.in_stream, testDataOne.year, ',');
            stringstream syear(testDataOne.year);
            int iYear;
            syear >> iYear;
            testDataOne.vYear.push_back(iYear);

            // the following is delimited by the \n since this is the last value expected in a line in the input file
            getline(testDataOne.in_stream, testDataOne.price, '\n');
            stringstream sprice(testDataOne.price);
            float fPrice;
            sprice >> fPrice;
            testDataOne.vPrice.push_back(fPrice);


            // Feature 1: Brand
            bool brandExists = false;
            for (int j = 0; j < testDataOne.vUniqueBrands.size(); j++) {
                if (testDataOne.brand == testDataOne.vUniqueBrands[j]) {
                    brandExists = true;
                    // push price of item onto brands vector
                    testDataOne.vBrandAvgPrice[j].push_back(fPrice);
                    break;
                }
            }

            // if brand has not been added, add it to the unique brands vector and create a vector for it in the price brand vector
            if (!brandExists) {
                testDataOne.vUniqueBrands.push_back(testDataOne.brand);
                vector<float> newBrand;
                newBrand.push_back(fPrice);
                testDataOne.vBrandAvgPrice.push_back(newBrand);
            }


            // Feature 1: Category
            // Check if category has already been added
            bool categoryExists = false;
            for (int j = 0; j < testDataOne.vUniqueCategories.size(); j++) {
                if (testDataOne.category == testDataOne.vUniqueCategories[j]) {
                    categoryExists = true;
                    // push price of item onto categories vector
                    testDataOne.vCategoryAvgPrice[j].push_back(fPrice);
                    break;
                }
            }

            // if category has not been added, add it to the unique categories vector and create a vector for it in the categories price vector
            if (!categoryExists) {
                testDataOne.vUniqueCategories.push_back(testDataOne.category);
                vector<float> newCategory;
                newCategory.push_back(fPrice);
                testDataOne.vCategoryAvgPrice.push_back(newCategory);
            }

            // Feature 2: SKUs By Year
            bool yearExists = false;
            for (int j = 0; j < testDataOne.vUniqueYears.size(); j++) {
                if (testDataOne.year == testDataOne.vUniqueYears[j]) {
                    yearExists = true;
                    // push sku of item onto years sku vector
                    testDataOne.vSKUsByYear[j].push_back(testDataOne.sku);
                    break;
                }
            }

            // if year has not been added, add it to the unique years vector and create a vector for it in the year's sku vector
            if (!yearExists) {
                testDataOne.vUniqueYears.push_back(testDataOne.year);
                vector<string> newYear;
                newYear.push_back(testDataOne.sku);
                testDataOne.vSKUsByYear.push_back(newYear);
            }

        }

        testDataOne.in_stream.close(); //closing the file cout << "Number of entries: " << i-1 << endl;

    } else {
        printf("Unable to open file");
    }

    //output values
    printf( "SKU\t\tBrand\tCategory\tYear\tPrice\n");
    fprintf(pFile, "SKU\t\tBrand\tCategory\tYear\tPrice\n");

    for (int j = 0; j < testDataOne.vSKU.size(); j++) {
        printf("%d\t\t%s\t\t%s\t\t\t%d\t%4.2f\n", testDataOne.vSKU[j], testDataOne.vBrand[j].c_str(), testDataOne.vCategory[j].c_str(), testDataOne.vYear[j], testDataOne.vPrice[j]);
        fprintf(pFile, "%d\t\t%s\t\t%s\t\t\t%d\t%4.2f\n", testDataOne.vSKU[j], testDataOne.vBrand[j].c_str(), testDataOne.vCategory[j].c_str(), testDataOne.vYear[j], testDataOne.vPrice[j]);
    }

    printf("\n\n");
    fprintf(pFile, "\n\n");

    // Feature 1: Brand - Calculating and printing out average price per brand
    printf("Average Price by Brand\n\n");
    fprintf(pFile, "Average Price by Brand\n\n");

    for (int j = 0; j < testDataOne.vUniqueBrands.size(); j++) {
        double totalPrice = 0;
        for (int i = 0; i < testDataOne.vBrandAvgPrice[j].size(); i++) {
            totalPrice += testDataOne.vBrandAvgPrice[j][i];
        }
        int numberOfPrices = testDataOne.vBrandAvgPrice[j].size();
        double avgPrice = totalPrice/numberOfPrices;
        printf("The average price for %s brand items is %4.2f\n", testDataOne.vUniqueBrands[j].c_str(), avgPrice);
        fprintf(pFile, "The average price for %s brand items is %4.2f\n", testDataOne.vUniqueBrands[j].c_str(), avgPrice);
    }

    printf("\n\n");
    fprintf(pFile, "\n\n");

    // Feature 1: Category - Calculating and printing out average price per category
    printf("Average price by Category\n\n");
    fprintf(pFile, "Average price by Category\n\n");
    for (int j = 0; j < testDataOne.vUniqueCategories.size(); j++) {
        double totalPrice = 0;
        for (int i = 0; i < testDataOne.vCategoryAvgPrice[j].size(); i++) {
            totalPrice += testDataOne.vCategoryAvgPrice[j][i];
        }
        int numberOfPrices = testDataOne.vCategoryAvgPrice[j].size();
        double avgPrice = totalPrice/numberOfPrices;
        printf("The average price for items in the %s category is %4.2f\n", testDataOne.vUniqueCategories[j].c_str(), avgPrice);
        fprintf(pFile, "The average price for items in the %s category is %4.2f\n", testDataOne.vUniqueCategories[j].c_str(), avgPrice);
    }

    printf("\n\n");
    fprintf(pFile, "\n\n");

    // Feature 2: SKUs by Year - Print out SKUs by Year
    testDataOne.printSKUsByYear(pFile);
//    printf("SKUs By Year\n\n");
//    fprintf(pFile, "SKUs By Year\n\n");
//    for (int j = 0; j < testDataOne.vUniqueYears.size(); j++) {
//        string skuList;
//        for (int i = 0; i < testDataOne.vSKUsByYear[j].size(); i++) {
//            skuList += testDataOne.vSKUsByYear[j][i];
//            if (i + 1 != testDataOne.vSKUsByYear[j].size()) {
//                skuList += ", ";
//            }
//        }
//        printf("%s (%d): %s\n", testDataOne.vUniqueYears[j].c_str(), testDataOne.vSKUsByYear[j].size(), skuList.c_str());
//        fprintf(pFile, "%s (%d): %s\n", testDataOne.vUniqueYears[j].c_str(), testDataOne.vSKUsByYear[j].size(), skuList.c_str());
//    }
//
//    printf("\n\n");
//    fprintf(pFile, "\n\n");

}


