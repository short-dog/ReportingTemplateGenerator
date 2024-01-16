#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <ranges>
#include <sstream>
#include <vector>
struct Investment {
    std::string period;
    int accountPos;
    std::string account;
    std::string position;
    std::string benchmark;
    double value;
};
void genNew() {
    std::vector<Investment> investments;
    std::vector<std::string> accounts;
    std::vector<std::string> benchmarks;
    std::map<int, std::string> acctMap;
    std::map<int, double> acctValue;
    std::map<std::string, double> benchmarkValue;
    std::map<std::string, std::string> benchmarkMap;
    std::string filePath = R"(..\CurrentAccount.csv)";
    std::string outPath = R"(..\Out.csv)";
    double portfolioTotal = 0;

    std::ifstream file(filePath);
    std::string line;
    getline(file, line);

    while (getline(file, line)) {
        std::istringstream stream(line);
        std::vector<std::string> columns;
        std::string column;
        while (getline(stream, column, ',')) {
            columns.push_back(column);
        }
        Investment investment;
        investment.period = columns[0];
        investment.accountPos = stoi(columns[1]);
        investment.account = (columns[2]);
        investment.position = (columns[3]);
        investment.benchmark = (columns[4]);
        investment.value = stod(columns[5]);
        investments.push_back(investment);
    }
    for (int i = 0; i < investments.size(); i++) {
        portfolioTotal += investments[i].value;
    }
    for (int i = 0; i < investments.size(); i++) {
        acctMap.emplace(investments[i].accountPos, investments[i].account);
    }
    for (int i = 0; i < investments.size(); i++) {
        benchmarkMap.emplace(investments[i].benchmark, investments[i].benchmark);
    }
    for (auto const& account: std::views::values(acctMap)) {
        accounts.push_back(account);
    }
    for (auto const& benchmark: std::views::values(benchmarkMap)) {
        benchmarks.push_back(benchmark);
    }
    for (int i = 0; i < accounts.size(); i++) {
        double total = 0;
        for (int ii = 0; ii < investments.size(); ii++) {
            if (investments[ii].account == accounts[i]) {
                total+=investments[ii].value;
            }
        }
        acctValue.emplace(i,total);
    }
    for (int i = 0; i < benchmarks.size(); i++) {
        double total = 0;
        for (int ii = 0; ii < investments.size(); ii++) {
            if (investments[ii].benchmark == benchmarks[i]) {
                total+=investments[ii].value;
            }
        }
        benchmarkValue.emplace(benchmarks[i],total);
    }
    std::ofstream csvOut(outPath, std::ios::app);
    csvOut << "\n";
    csvOut << "," << investments[0].period << "\n";
    csvOut << "," << "Account" << "," << "Position" << "," << "Value" << ","
    << "Benchmark" << "," << "% of Account" << "\n";
    for (int i = 0; i < investments.size(); i++) {
        csvOut << "," << investments[i].account << "," << investments[i].position
        << "," << std::fixed << std::setprecision(2) << investments[i].value << "," << investments[i].benchmark << ","
        << investments[i].value*100 / acctValue.find(investments[i].accountPos-1)->second << "\n";
    }
    csvOut << "\n" << "," << "Consolidated:" << "\n";
    csvOut << "," << "Benchmark" << "," << "Amount" << "," << "%" << "\n";
    for (int i = 0; i < benchmarks.size(); i++) {
        csvOut << "," << benchmarks[i] << "," << benchmarkValue.find(benchmarks[i])->second
        << "," << std::fixed << std::setprecision(2) << benchmarkValue.find(benchmarks[i])->second*100/portfolioTotal << "\n";
    }
    csvOut.close();
    std::cout << investments[0].accountPos << std::endl;
    std::cout << investments[0].account << std::endl;
    std::cout << investments[0].position << std::endl;
    std::cout << investments[0].benchmark << std::endl;
    std::cout << investments[0].value << std::endl;
    std::cout << std::fixed <<  portfolioTotal;
}
int main(){
    genNew();
    return 0;
}
