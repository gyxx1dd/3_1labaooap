#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <iomanip>
#include <string>
#include <sstream>


using namespace std;

class SalesCounter {
private:
    int foodCount = 0;
    int medicineCount = 0;
    int clothesCount = 0;
    double totalRevenue = 0.0;
    ofstream logFile;

    SalesCounter() {
        logFile.open("sales_log.txt", ios::app);  
        if (!logFile.is_open()) {
            cerr << "Error opening file!" << endl;
            exit(1);
        }
    }

    ~SalesCounter() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    SalesCounter(const SalesCounter&) = delete;
    SalesCounter& operator=(const SalesCounter&) = delete;

    string getCurrentTime() {
        time_t now = time(nullptr);
        tm localTime;
        localtime_s(&localTime, &now);  

        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &localTime);
        return string(buffer);
    }

public:
    static SalesCounter& getInstance() {
        static SalesCounter instance;
        return instance;
    }

    void addSale(const string& category, double basePrice) {
        double finalPrice = basePrice;

        if (category == "food") {
            finalPrice += basePrice * 0.05;
            foodCount++;
        }
        else if (category == "medicine") {
            finalPrice += basePrice * 0.10;
            medicineCount++;
        }
        else if (category == "clothes") {
            finalPrice += basePrice * 0.15;
            clothesCount++;
        }

        totalRevenue += finalPrice;

        logFile << getCurrentTime() << " - Sold " << category << " for $" << finalPrice << endl;

        cout << "Sold " << category << " for $" << finalPrice << endl;
    }

    void printReport() const {
        cout << "Sales report:" << endl;
        cout << "Food sold: " << foodCount << endl;
        cout << "Medicine sold: " << medicineCount << endl;
        cout << "Clothes sold: " << clothesCount << endl;
        cout << "Total revenue: $" << totalRevenue << endl;
    }
};

double generateRandomPrice() {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_real_distribution<> dis(10.0, 100.0);  
    return dis(gen);
}

int main() {
    SalesCounter& counter = SalesCounter::getInstance();

    counter.addSale("food", generateRandomPrice());
    counter.addSale("medicine", generateRandomPrice());
    counter.addSale("clothes", generateRandomPrice());
    counter.addSale("food", generateRandomPrice());

    counter.printReport();

    return 0;
}
