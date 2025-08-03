#include <iostream>
#include <string>
#include <direct.h>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

// Function to display the main menu
int showMainMenu() {
    cout << "[1] List Files\n";
    cout << "[2] Create Directory\n";
    cout << "[3] Change Directory\n";
    cout << "[4] Exit\n";
    cout << "Enter Choice: ";
    return 0;
}

// Function to display the list files submenu
int showListFilesMenu() {
    cout << "[1] List All Files\n";
    cout << "[2] List Files by Extension (e.g., .txt)\n";
    cout << "[3] List Files by Pattern (e.g., moha*.*)\n";
    cout << "Enter choice: ";
    return 0;
}

// Function to list files based on user selection
int listFilesAction() {
    int choice;
    showListFilesMenu();
    while (!(cin >> choice)) {
        cout << "Invalid input. Enter a number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cin.ignore(); // Clear input buffer

    try {
        if (choice == 1) {
            cout << "\nFiles in current diretory:\n";
            for (const auto& entry : fs::directory_iterator(fs::current_path())) {
                cout << "- " << entry.path().filename().string() << endl;
            }
        }
        else if (choice == 2) {
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

    return 0;
}

// Function to create a new directory
int createDir() {
    string dirName;
    cout << "\nEnter new directory name: ";
    getline(cin, dirName);

    if (_access(dirName.c_str(), 0) == 0) {
        cout << "Error: Directory \"" << dirName << "\" already exists!\n";
    }
    else {
        try {
            if (fs::create_directory(dirName)) {
                cout << "Directory \"" << dirName << "\" created successfully.\n";
            }
            else {
                cout << "Error: Failed to create directory '" << dirName << "'!\n";
            }
        }
        catch (const fs::filesystem_error& e) {
            cout << "Filesystem error: " << e.what() << endl;
        }
    }

    return 0;
}

// Function to display the change directory submenu
int showChangeDirMenu() {
    cout << "\nChange Directory Menu\n";
    cout << "[1] Move to Parent Directory\n";
    cout << "[2] Move to Root Directory\n";
    cout << "[3] Enter Custom Path (e.g., C:\\Users\\Documents)\n";
    cout << "Enter choice: ";
    return 0;
}

// Function to change the current working directory
int changeDirectoryAction() {
    int choice;
    showChangeDirMenu();
    while (!(cin >> choice)) {
        cout << "Invalid input. Enter a number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cin.ignore(); // Clear input buffer

    try {
        if (choice == 1) {
            fs::path current = fs::current_path();
            fs::path parent = current.parent_path();
            if (parent != current) {
                fs::current_path(parent);
                cout << "Changed to parent directory: " << fs::current_path().string() << endl;
            }
            else {
                cout << "Error: Already at root or no parent directory exists!\n";
            }
        }
        else if (choice == 2) {
            fs::path root = fs::current_path().root_path();
            fs::current_path(root);
            cout << "Changed to root directory: " << fs::current_path().string() << endl;
        }
        else if (choice == 3) {
            string path;
            cout << "Enter new directory path (e.g., C:\\Users\\Documents): ";
            getline(cin, path);
            if (_chdir(path.c_str()) == 0) {
                cout << "Changed to directory: " << fs::current_path().string() << endl;
            }
            else {
                cout << "Error: Directory \"InvalidPath\" not found!\n";
            }
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
    catch (const fs::filesystem_error& e) {
        cout << "Filesystem error: " << e.what() << endl;
    }

    return 0;
}

// Function to handle the main menu and user interaction
int runMenuLoop() {
    int option;
    do {
        showMainMenu();
        while (!(cin >> option)) {
            cout << "Invalid input. Enter a number: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cin.ignore(); // Clear input buffer

        switch (option) {
            case 1:
                listFilesAction();
                break;
            case 2:
                createDir();
                break;
            case 3:
                changeDirectoryAction();
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (option != 4);

    return 0;
}

int main() {
    runMenuLoop();
    return 0;
}

