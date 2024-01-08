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
    std::map<int, std::string> acctMap;
    std::map<int, double> acctValue;
    std::string filePath = R"(C:\Users\BSHORT2\CLionProjects\ReportingGenerator\CurrentAccount.csv)";
    std::string outPath = R"(C:\Users\BSHORT2\CLionProjects\ReportingGenerator\Out.csv)";

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
        acctMap.emplace(investments[i].accountPos, investments[i].account);
    }
    for (auto const& account: std::views::values(acctMap)) {
        accounts.push_back(account);
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
    std::ofstream csvOut(outPath);
    csvOut << "\n";
    csvOut << "," << investments[0].period << "\n";
    csvOut << "," << "Account" << "," << "Position" << "," << "Value" << ","
    << "Benchmark" << "," << "% of Account" << "\n";
    for (int i = 0; i < investments.size(); i++) {
        csvOut << "," << investments[i].account << "," << investments[i].position
        << "," << std::fixed << std::setprecision(2) << investments[i].value << "," << investments[i].benchmark << ","
        << investments[i].value*100 / acctValue.find(investments[i].accountPos-1)->second << "\n";
    }
    std::cout << investments[0].accountPos << std::endl;
    std::cout << investments[0].account << std::endl;
    std::cout << investments[0].position << std::endl;
    std::cout << investments[0].benchmark << std::endl;
    std::cout << investments[0].value << std::endl;
}
int main(){
    genNew();
    return 0;
}
