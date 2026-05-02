#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
using namespace std;
namespace fs = std::filesystem;

void FileExplorer() {
    cout << endl << "WELCOME TO FILE EXPLORER!" << endl;
    string cwd = std::filesystem::current_path().string();
    while(true) {
        cout << "Contents:" << endl;
        cout << "1) List\n2) Change Dir\n3) View File\n4) Create File\n5) Delete File\n6) Back to Menu\nChoose: ";
        int c;
        if (!(cin >> c)) {
            cin.clear();
            cin.ignore();
            continue;
        }
        if (c == 1) {
            cout << "Contents:" << endl;
            for (auto &entry : fs::directory_iterator(cwd)) {
                cout << (entry.is_directory() ? "[DIR] " : "[FILE] ") << entry.path().filename().string() << endl;
            }
        }
        else if (c == 2) {
            cout << "Enter directory path: ";
            string p;
            cin >> p;
            try {
                fs::current_path(p);
                cwd = fs::current_path().string();
            } 
            catch (...) {
                cout << "Invalid path." << endl;
            }
        }
        else if (c == 3) {
            cout << "Enter file name to view: ";
            string fn;
            cin >> fn;
            string path = (fs::path(cwd) / fn).string();
            if (!fs::exists(path)) {
                cout << "File not found." << endl;
                continue;
            }
            if (fs::is_directory(path)) {
                cout << "It is a directory." << endl;
                continue;
            }
            ifstream in(path);
            string line;
            cout << "--------------------" << endl;
        }
        else if (c == 4) {
            cout << "Enter file name to create: ";
            string fn;
            cin >> fn;
            string path = (fs::path(cwd) / fn).string();
            ofstream out(path);
            out << "";
            out.close();
            cout << "File created." << endl;
        }
        else if (c == 5) {
            cout << "Enter file name to delete: ";
            string fn;
            cin >> fn;
            string path = (fs::path(cwd) / fn).string();
            try {
                fs::remove(path);
                cout << "File deleted." << endl;
            } 
            catch (...) {
                cout << "Error deleting file." << endl;
            }
        }
        else if (c == 6) {
            cout << "Returning to main menu..." << endl;
            break;
        }
        else {
            cout << "Invalid choice. Try again." << endl;
        }
    }
}