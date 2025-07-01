# Expense_Tracker
The Expense Tracker is a beginner-friendly C++ application that helps users monitor and manage their day-to-day expenses. Users can log expenses under different categories, define monthly budgets, and receive real-time alerts if they overspend. It also supports exporting data to CSV and visualizing expenses via pie charts.

Project Overview - 

📌 Features Included

1. Add expense with category, amount, and timestamp  
2. View category-wise spending summaries  
3. Set and track monthly budget limits  
4. Receive real-time overspending alerts  
5. Export data to CSV format  
6. Pie chart visualization

📌 How to Compile and Run

1. Make sure you have a C++ compiler (like g++) installed.
2. Compile the code:

    ```sh
    g++ ExpenseTracker.cpp -o ExpenseTracker
    ```

3. Run the program:

    ```sh
    ./ExpenseTracker
    ```

📌 File descriptions

- `ExpenseTracker.cpp` — Main C++ source code
- `expenses.txt` — Auto-generated file to store expenses (do not edit manually)
- `summary.csv` — Generated when you export summary

📌 Tech Stack

Language: C++  
Storage: Text/CSV files  
Data Structures: Maps for category aggregation  
Visualization: C++ graphics  

📌 Use Cases

Personal daily/monthly expense tracking  
Student budget planning  
Identifying overspending categories  
Generating budget summaries for export  

📌 Application Areas

Budget-conscious individuals  
College students  
Freelancers and home budgeters  
Early-stage personal finance apps  

📌 Future Improvements

Use SQLite/MySQL for more robust data storage  
Add login system with password protection <br>
Generate weekly/monthly graphs and insights  
Build mobile app integration (via API)  
Enable real-time cloud sync

