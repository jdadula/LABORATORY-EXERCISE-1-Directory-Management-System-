#include <iostream>
#include <string>
#include <direct.h>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem; // Alias for std::filesystem namespace

// Function to display the main menu
void mainMenu() {
    cout << "[1] List Files\n";
    cout << "[2] Create Directory\n";
    cout << "[3] Change Directory\n";
    cout << "[4] Exit\n";
    cout << "Enter option: ";
}

// Function to display the list files submenu
void listFilesMenu() {
    cout << "[1] List All Files\n";
    cout << "[2] List Files by Extension (e.g., .txt)\n";
    cout << "[3] List Files by Pattern (e.g., moha*.*)\n";
    cout << "Enter choice: ";
}

// Function to list files based on user selection
void listFiles() {
    int choice;
    listFilesMenu();
    while (!(cin >> choice)) {
        cout << "Invalid input. Enter a number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cin.ignore(); 

    try {
        if (choice == 1) {
            // List all files in the current directory
            cout << "\nFiles in current diretory:\n";
            for (const auto& entry : fs::directory_iterator(fs::current_path())) {
                cout <<"- "<< entry.path().filename().string() << endl;
            } 
        }
        else if (choice == 2) {
            // List files by extension
            string ext;
            cout << "Enter file extension (include the dot, e.g., .txt): ";
            getline(cin, ext);
            cout << "\nListing files with extension " << ext << ":\n";
            bool found = false;
            for (const auto& entry : fs::directory_iterator(fs::current_path())) {
                if (entry.path().extension().string() == ext) {
                    cout << entry.path().filename().string() << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "No files found with extension " << ext << "!\n";
            }
        }
        else if (choice == 3) {
            
            string pattern;
            cout << "Enter file pattern (e.g., moha*.*): ";
            getline(cin, pattern);
            cout << "\nListing files matching pattern " << pattern << ":\n";
            bool found = false;
            
            size_t starPos = pattern.find('*');
            string prefix = (starPos != string::npos) ? pattern.substr(0, starPos) : pattern;
            for (const auto& entry : fs::directory_iterator(fs::current_path())) {
                string filename = entry.path().filename().string();
                if (filename.find(prefix) == 0) { 
                    cout << filename << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "No files found matching pattern " << pattern << "!\n";
            }
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
    catch (const fs::filesystem_error& e) {
        cout << "Filesystem error: " << e.what() << endl;
    }
}
void mainMenuLoop() {
    int option;
    do {
        mainMenu();
        while (!(cin >> option)) {
            cout << "Invalid input. Enter a number: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cin.ignore(); 

        switch (option) {
        case 1:
            listFiles();
            break;
        }
    } while (option != 4);
}

int main() {
    mainMenuLoop();
    return 0;
}

