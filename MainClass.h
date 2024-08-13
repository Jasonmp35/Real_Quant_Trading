#pragma once

#include <iostream>
#include <mutex>
#include <vector>
#include <functional>
#include <fstream>
#include <sstream>
#include <thread>

#include "future"
#include "chrono"

using namespace std;

class CMainClass
{
private:
	mutex mtx;
	vector<string> tickers;

public:
	CMainClass();
	void readCSVThread(const string& filename, vector<vector<vector<double>>>& allData, mutex& mtx);
	vector<string> getTickers();
	void Scrape( vector<string>& tickers, string s);
	void LoadTickerData();
	bool triggerSell();
	bool triggerBuy();
	void QuantMethod();
	vector<vector<double>> readCSV(const string& filename);

};

