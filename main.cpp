// This file shows basic functions of reading in a CSV file using C++98
// Mohamed Mohamed 

/* Homework Objective: fix this program to match the requirements listed: 
  1. successfully reads all lines of the input file
  2. calculate the average price per brand, average price per category 
  3. writes to an output file
  4. for each unique year, list the count of skus and also print out the skus as a list i.e. 2000 (3): 111, 211, 311 and make a new line per year.
All programs must be able to compile in C++98 standard (the default version on Linux Machine). That means you cannot use the new features of C++11! :(
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

int main() {

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
    const char *inputPath = "./data.csv";
    const char *outputPath = "./output.txt";
    // accessing the input file using the created input stream
    in_stream.open(inputPath); //opening the file.
    out_stream.open(outputPath);

    if (!in_stream.fail()) { //if the file is open

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
        getline(in_stream, line); // Gets the first line of headers (we won't be using it)

        while (!in_stream.eof()) { //while the end of file is NOT reached

            // Fields: sku,brand,category,year,price

            // extracts all text from current file position (inclusive) to ',' (exclusive) and stores it into the declared variable sku (implicitly defined as a string)
            getline(in_stream, sku, ',');

            // stringstream is a stream class to operate on strings
            stringstream ssku(sku);
            int iSKU = 0;

            // using stringstream, we can set iSKU to equal sku through dynamic type conversion
            ssku >> iSKU;

            // creates an element at the end of the vector and assigns it the given value
            vSKU.push_back(iSKU);

            getline(in_stream, brand, ',');
            vBrand.push_back(brand);

            getline(in_stream, category, ',');
            vCategory.push_back(category);

            getline(in_stream, year, ',');
            stringstream syear(year);
            int iYear;
            syear >> iYear;
            vYear.push_back(iYear);

            // the following is delimited by the \n since this is the last value expected in a line in the input file
            getline(in_stream, price, '\n');
            stringstream sprice(price);
            float fPrice;
            sprice >> fPrice;
            vPrice.push_back(fPrice);


            // Feature 1: Brand
            bool brandExists = false;
            for (int j = 0; j < vUniqueBrands.size(); j++) {
                if (brand == vUniqueBrands[j]) {
                    brandExists = true;
                    // push price of item onto brands vector
                    vBrandAvgPrice[j].push_back(fPrice);
                    break;
                }
            }

            // if brand has not been added, add it to the unique brands vector and create a vector for it in the price brand vector
            if (!brandExists) {
                vUniqueBrands.push_back(brand);
                vector<float> newBrand;
                newBrand.push_back(fPrice);
                vBrandAvgPrice.push_back(newBrand);
            }


            // Feature 1: Category
            // Check if category has already been added
            bool categoryExists = false;
            for (int j = 0; j < vUniqueCategories.size(); j++) {
                if (category == vUniqueCategories[j]) {
                    categoryExists = true;
                    // push price of item onto categories vector
                    vCategoryAvgPrice[j].push_back(fPrice);
                    break;
                }
            }

            // if category has not been added, add it to the unique categories vector and create a vector for it in the categories price vector
            if (!categoryExists) {
                vUniqueCategories.push_back(category);
                vector<float> newCategory;
                newCategory.push_back(fPrice);
                vCategoryAvgPrice.push_back(newCategory);
            }

            // Feature 2: SKUs By Year
            bool yearExists = false;
            for (int j = 0; j < vUniqueYears.size(); j++) {
                if (year == vUniqueYears[j]) {
                    yearExists = true;
                    // push sku of item onto years sku vector
                    vSKUsByYear[j].push_back(sku);
                    break;
                }
            }

            // if year has not been added, add it to the unique years vector and create a vector for it in the year's sku vector
            if (!yearExists) {
                vUniqueYears.push_back(year);
                vector<string> newYear;
                newYear.push_back(sku);
                vSKUsByYear.push_back(newYear);
            }

        }

        in_stream.close(); //closing the file cout << "Number of entries: " << i-1 << endl;

    } else {
        cout << "Unable to open file";
    }

    //output values
    cout << "SKU" << "\t" << "Brand" << "\t" << "Category" << "\t" << "Year" << "\t" << "Price" << endl;
    out_stream << "SKU" << "\t\t" << "Brand" << "\t" << "Category" << "\t" << "Year" << "\t" << "Price" << endl;

    for (int j = 0; j < vSKU.size(); j++) {
        cout << vSKU[j] << "\t" << vBrand[j] << "\t" << vCategory[j] << "\t\t" << vYear[j] << "\t" << vPrice[j] << endl;
        out_stream << vSKU[j] << "\t\t" << vBrand[j] << "\t\t" << vCategory[j] << "\t\t\t" << vYear[j] << "\t" << vPrice[j] << endl;
    }

    cout << "\n" << endl;
    out_stream << "\n" << endl;

    // Feature 1: Brand - Calculating and printing out average price per brand
    cout << "Average Price by Brand\n" << endl;
    out_stream << "Average Price by Brand\n" << endl;
    for (int j = 0; j < vUniqueBrands.size(); j++) {
        double totalPrice = 0;
        for (int i = 0; i < vBrandAvgPrice[j].size(); i++) {
            totalPrice += vBrandAvgPrice[j][i];
        }
        int numberOfPrices = vBrandAvgPrice[j].size();
        double avgPrice = totalPrice/numberOfPrices;
        cout << "The average price for " << vUniqueBrands[j] << " brand items is " << avgPrice << "" << endl;
        out_stream << "The average price for " << vUniqueBrands[j] << " brand items is " << avgPrice << "" << endl;
    }

    cout << "\n" << endl;
    out_stream << "\n" << endl;

    // Feature 1: Category - Calculating and printing out average price per category
    cout << "Average Price by Category\n" << endl;
    out_stream << "Average Price by Category\n" << endl;
    for (int j = 0; j < vUniqueCategories.size(); j++) {
        double totalPrice = 0;
        for (int i = 0; i < vCategoryAvgPrice[j].size(); i++) {
            totalPrice += vCategoryAvgPrice[j][i];
        }
        int numberOfPrices = vCategoryAvgPrice[j].size();
        double avgPrice = totalPrice/numberOfPrices;
        cout << "The average price for items in the " << vUniqueCategories[j] << " category is " << avgPrice << endl;
        out_stream << "The average price for items in the " << vUniqueCategories[j] << " category is " << avgPrice << endl;
    }

    cout << "\n" << endl;
    out_stream << "\n" << endl;

    // Feature 2: SKUs by Year - Print out SKUs by Year
    cout << "SKUs By Year\n" << endl;
    out_stream << "SKUs By Year\n" << endl;
    for (int j = 0; j < vUniqueYears.size(); j++) {
        string skuList;
        for (int i = 0; i < vSKUsByYear[j].size(); i++) {
            skuList += vSKUsByYear[j][i];
            if (i + 1 != vSKUsByYear[j].size()) {
                skuList += ", ";
            }
        }
        cout << vUniqueYears[j] << " (" << vSKUsByYear[j].size() << "): " << skuList << endl;
        out_stream << vUniqueYears[j] << " (" << vSKUsByYear[j].size() << "): " << skuList << endl;
    }

    out_stream << endl;
    cout << endl;

}
