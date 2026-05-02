#include <iostream>

#include "Headers/FileExplorer.h"
#include "Headers/MiniShell.h"
#include "Headers/TaskScheduler.h"
#include "Headers/Deadlock.h"
#include "Headers/Compressor.h"

using namespace std;

int main() {
    int choice;
    while (true)
    {
        cout << endl << "MINI OPERATING SYSTEM MAIN MENU:" << endl;
        cout << "1. File Explorer" << endl;
        cout << "2. Mini Shell" << endl;
        cout << "3. Task Scheduler" << endl;
        cout << "4. Deadlock Simulation" << endl;
        cout << "5. File Compressor" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice){
            case 1: FileExplorer(); break;
            case 2: MiniShell(); break;
            case 3: TaskScheduler(); break;
            case 4: BankersAlgorithm(); break;
            case 5: FileCompressor(); break;
            case 0: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice.\n"; break;
        }
    }
}