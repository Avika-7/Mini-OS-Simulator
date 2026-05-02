#include <iostream>
#include <filesystem>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;
namespace fs = std::filesystem;

void MiniShell() {
    cout << endl << "WELCOME TO THE MINI SHELL!" << endl;
    cout << "miniShel : Simple Commands : ls, cd <dir>, cat <file>, mkdir <dir>, rm <file>, run <cmd>, exit" << endl;
    string cwd = fs::current_path().string();
    while (true) {
        cout << cwd << " $ ";
        string cmd;
        if (!(cin >> cmd)) {
            cin.clear();
            cin.ignore();
            continue;
        }
        if (cmd == "exit") {
            break;
        }
        else if (cmd == "ls") {
            for (auto &e : fs::directory_iterator(cwd)) {
                cout << e.path().filename().string() << endl;
            }    
        }
        else if (cmd == "cd") {
            string dir;
            cin >> dir;
            try {
                fs::current_path(dir);
                cwd = fs::current_path().string();
            } 
            catch (...) {
                cout << "cd: No such directory" << endl;
            }    
        }
        else if (cmd == "cat") {
            string file;
            cin >> file;
            string path = (fs::path(cwd) / file).string();
            if (!fs::exists(path)) {
                cout << "cat: No such file found" << endl;
                continue;
            }
            if (fs::is_directory(path)) {
                cout << "cat: Is a directory" << endl;
                continue;
            }
            ifstream in(path);
            string line;
            while (getline(in, line)) {
                cout << line << endl;
            }
        }
        else if (cmd == "mkdir") {
            string d;
            cin >> d;
            fs::create_directory(fs::path(cwd) / d);
            cout << "mkdir: Directory created" << endl;
        }
        else if (cmd == "rm") {
            string f;
            cin >> f;
            fs::remove(fs::path(cwd) / f);
            cout << "rm: File/Directory removed" << endl;
        }
        else if (cmd == "run") {
            string rest;
            getline(cin, rest);
            if (!rest.empty() && rest[0] == ' ') {
                rest = rest.erase(0, 1);
            }
            if (rest.empty()) {
                system(rest.c_str());
            }
            else {
                cout << "run: No command specified" << endl;
            }
        }
        else {
            cout << "Unknown command: " << cmd << endl;
        }
    }
}