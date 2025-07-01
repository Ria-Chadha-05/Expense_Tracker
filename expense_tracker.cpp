#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <map>

using namespace std;

class Expense {
public:
    string category;
    string note;
    string date;
    float amount;

    void input() {
        cout << "Enter amount: ₹";
        cin >> amount;
        cin.ignore();

        cout << "Enter category (e.g., Food, Travel): ";
        getline(cin, category);

        cout << "Enter note: ";
        getline(cin, note);

        cout << "Enter date (DD-MM-YYYY): ";
        getline(cin, date);
    }

    void display() const {
        cout << left << setw(10) << date
             << setw(10) << category
             << setw(10) << amount
             << "  " << note << endl;
    }
};

vector<Expense> expenses;
map<string, float> categoryBudgets;

void loadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) return;

    Expense e;
    while (inFile >> e.amount) {
        inFile.ignore();
        getline(inFile, e.category);
        getline(inFile, e.note);
        getline(inFile, e.date);
        expenses.push_back(e);
    }
    inFile.close();
}

void saveToFile(const string& filename) {
    ofstream outFile(filename);
    for (const auto& e : expenses) {
        outFile << e.amount << "\n"
                << e.category << "\n"
                << e.note << "\n"
                << e.date << "\n";
    }
    outFile.close();
}

void addExpense() {
    Expense e;
    e.input();
    expenses.push_back(e);
    cout << "✅ Expense added!\n";

    if (categoryBudgets.count(e.category)) {
        float newTotal = 0;
        for (const auto& exp : expenses) {
            if (exp.category == e.category)
                newTotal += exp.amount;
        }

        float budgetLimit = categoryBudgets[e.category];
        if (newTotal > budgetLimit) {
            cout << "⚠️ WARNING: You've exceeded the budget for '" << e.category << "'!\n";
            cout << "🔴 Budget: ₹" << budgetLimit << ", Current total: ₹" << newTotal << endl;
            cout << "⛔ Over budget by ₹" << newTotal - budgetLimit << "\n";
        } else {
            cout << "📊 You're within budget. ₹" << budgetLimit - newTotal << " remaining.\n";
        }
    } else {
        cout << "ℹ️ No budget set for this category.\n";
    }
}

void viewAllExpenses() {
    cout << "\n--- All Expenses ---\n";
    cout << left << setw(10) << "Date"
         << setw(10) << "Category"
         << setw(10) << "Amount"
         << "Note\n";
    cout << "-----------------------------------------\n";
    for (const auto& e : expenses) {
        e.display();
    }
}

void totalByCategory() {
    string cat;
    cin.ignore();
    cout << "Enter category: ";
    getline(cin, cat);

    float total = 0;
    for (const auto& e : expenses) {
        if (e.category == cat) {
            total += e.amount;
        }
    }

    cout << "💸 Total spent in " << cat << ": ₹" << total << endl;

    if (categoryBudgets.count(cat)) {
        float limit = categoryBudgets[cat];
        cout << "📉 Budget set: ₹" << limit << endl;
        if (total > limit) {
            cout << "⚠️ Budget exceeded by ₹" << total - limit << "!\n";
        } else {
            cout << "✅ Within budget. ₹" << limit - total << " remaining.\n";
        }
    } else {
        cout << "ℹ️ No budget set for this category.\n";
    }
}

void exportToCSV(const string& filename = "summary.csv") {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "❌ Error writing to file.\n";
        return;
    }

    outFile << "Date,Category,Amount,Note\n";
    for (const auto& e : expenses) {
        outFile << e.date << ","
                << e.category << ","
                << e.amount << ","
                << e.note << "\n";
    }
    outFile.close();
    cout << "📁 Summary exported to '" << filename << "'\n";
}

void pieChartView() {
    map<string, float> categoryTotals;
    float grandTotal = 0;

    for (const auto& e : expenses) {
        categoryTotals[e.category] += e.amount;
        grandTotal += e.amount;
    }

    cout << "\n📊 Expense Distribution (Pie Chart - Approx):\n";
    for (const auto& pair : categoryTotals) {
        string cat = pair.first;
        float percent = (pair.second / grandTotal) * 100;

        cout << setw(12) << left << cat << " | ";
        int bars = percent / 2;
        for (int i = 0; i < bars; ++i) cout << "█";
        cout << " " << fixed << setprecision(1) << percent << "%\n";
    }
}

void setBudget() {
    string category;
    float amount;
    cin.ignore();
    cout << "Enter category: ";
    getline(cin, category);
    cout << "Enter budget limit for " << category << ": ₹";
    cin >> amount;

    categoryBudgets[category] = amount;
    cout << "✅ Budget set: ₹" << amount << " for category '" << category << "'\n";
}

int main() {
    const string filename = "expenses.txt";
    loadFromFile(filename);

    int choice;
    do {
        cout << "\n💰 Expense Tracker Menu:\n";
        cout << "1. Add Expense\n";
        cout << "2. View All Expenses\n";
        cout << "3. View Total by Category\n";
        cout << "4. Export Summary to CSV\n";
        cout << "5. View Pie Chart\n";
        cout << "6. Set/Update Budget\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addExpense(); saveToFile(filename); break;
            case 2: viewAllExpenses(); break;
            case 3: totalByCategory(); break;
            case 4: exportToCSV(); break;
            case 5: pieChartView(); break;
            case 6: setBudget(); break;
            case 7: cout << "💾 Saving and exiting...\n"; saveToFile(filename); break;
            default: cout << "❌ Invalid option. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
