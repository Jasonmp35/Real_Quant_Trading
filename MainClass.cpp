/*  Well, here. we. go  */

#include "MainClass.h"

CMainClass::CMainClass() :
    // List of top company tickers
    tickers({
        "AAPL", "MSFT", "AMZN", "GOOGL", "META",
        "TSLA", "BRK.A", "BRK.B", "JNJ", "NVDA",
        "V", "JPM", "WMT", "PG", "UNH",
        "MA", "BAC", "HD", "INTC", "NFLX", "TSM"
        , "AMD", "SMCI"}) {}

void CMainClass::Scrape(vector<string>& tickers, string s) {

}

// Function to read CSV and store data in the shared vector
void CMainClass::readCSVThread(const string& filename, vector<vector<vector<double>>>& allData, mutex& mtx) {
    vector<vector<double>> data = readCSV(filename);
    lock_guard<mutex> lock(mtx);
    allData.push_back(data);
}

/**
 * @brief Loads ticker data from multiple CSV files concurrently.
 *
 * This function retrieves a list of CSV filenames, and for each filename,
 * it starts a new thread that reads the CSV file and stores its data in a
 * shared vector. The shared vector is protected by a mutex to ensure thread-safe
 * operations. Each thread runs the readCSVThread member function, which reads
 * the CSV file and appends the data to the shared vector.
 *
 * The function waits for all threads to complete before returning.
 */
void CMainClass::LoadTickerData() {

    vector<string> tickers = getTickers();
    vector<thread> threads;
    vector<vector<vector<double>>> allData;
    mutex mtx;

    for (const string& filename : tickers) {
        threads.emplace_back(
            bind(&CMainClass::readCSVThread, this, filename, ref(allData), ref(mtx))
        );
    }

    // Wait for all threads to finish
    for (thread& t : threads) {
        t.join();
    }
}


vector<string> CMainClass::getTickers() {
    return tickers;
}

bool CMainClass::triggerSell() {
    return true;    
}

bool CMainClass::triggerBuy() {
    return true;
}

void CMainClass::QuantMethod() {
    
}

// Function to read a CSV file and return the data as a vector of vectors of doubles
vector<vector<double>> CMainClass::readCSV(const string& filename) {
    ifstream file(filename);
    vector<vector<double>> data;
    string line;
    while (getline(file, line)) {
        vector<double> row;
        stringstream lineStream(line);
        string cell;
        while (getline(lineStream, cell, ',')) {
            row.push_back(stod(cell));
        }
        data.push_back(row);
    }
    return data;
}

