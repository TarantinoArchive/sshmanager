#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <pwd.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <sys/types.h>
using namespace std;

bool pathExists(const string &s)
{
  struct stat buffer;
  return (stat (s.c_str(), &buffer) == 0);
}

int main(int argc, char *argv[]) {
    string homedir = getpwuid(getuid())->pw_dir;

    if (!pathExists(homedir+"/.sshmanager")) {
        if (!mkdir((homedir+"/.sshmanager").c_str(), 0777)) {
            cerr << "An error creating the data folder occurred";
        }
        if (!pathExists(homedir+"/.sshmanager/sshs")) {
            ofstream sshsfile (homedir+"/.sshmanager/sshs");
            sshsfile.close();
        }
    }

    if (argc <= 1) {
        cerr << "Not enough arguments";
    }
    if (argv[1] == "list") {
        vector<string> sshs;
        ifstream sshsfile (homedir+"/.sshmanager/sshs");
        string line;
        while(getline(sshsfile, line)) {
            sshs.push_back(line);
        }
        cout << "List of your SSHs" << endl;
        for (int i = 0; i < sshs.size(); i++) {
            cout << sshs[i] << endl;
        }
    }
}
