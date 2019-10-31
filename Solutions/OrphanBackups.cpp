#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

// Returns a sorted set of filenames
set<string> parseFiles();

// Returns a sorted mapping of filenames to sorted associated fully-qualified backup names.
// We have to maintain the associated backup names to output later.
// Ex: { payroll.xls : [payroll.xls_1539199053_INCR, payroll.xls_1539112653_INCR] }.
map<string, set<string>> parseBackups();

// For a string formatted as "filename_integer_type", returns "filename".
string getFileName(string fullBackupName);


// Parse input to get files and backups (which is file names and versioning).
// 
// - For each entry {filename : [fullBackupNames]} in the backups:
// --- If the filename is not in our files:
// ----- Print each fully-qualified backup name associated with that filename
// - For each filename in the files:
// --- If the filename is not in our backups:
// ----- Print the filename
// - If nothing was printed:
// --- Print that there were no orphan files
//
// Also, because set and map are sorted, we know the answer is printed alphabetically!
int main() {
    set<string> files = parseFiles();
    map<string, set<string>> backups = parseBackups();
    bool hasAnyOrphanFile = false;

    for (auto entry : backups) {
        string filename = entry.first;
        set<string> fullBackupNames = entry.second;

        if (files.find(filename) == files.end()) {
            hasAnyOrphanFile = true;

            for (string fullBackupName : fullBackupNames)
                cout << "F " << fullBackupName << endl;
        }
    }

    for (string filename : files) {
        if (backups.find(filename) == backups.end()) {
            hasAnyOrphanFile = true;
            cout << "I " << filename << endl;
        }
    }

    if (!hasAnyOrphanFile)
        cout << "No mismatches." << endl;

    return 0;
}


set<string> parseFiles() {
    set<string> files;
    string filename;

    while (getline(cin, filename)) {
        if (filename.empty())
            break;

        files.insert(filename);
    }

    return files;
}

map<string, set<string>> parseBackups() {
    map<string, set<string>> backups;
    string fullBackupName;

    while (getline(cin, fullBackupName)) {
        string filename = getFileName(fullBackupName);
        backups[filename].insert(fullBackupName);
    }

    return backups;
}

string getFileName(string fullBackupName) {
    int underscoreCount = 0;
    int i = fullBackupName.size() - 1;

    while (i >= 0) {
        if (fullBackupName[i] == '_')
            underscoreCount++;
        
        if (underscoreCount == 2)
            break;

        i--;
    }

    // Copy up to the second to last underscore
    return fullBackupName.substr(0, i);
}
