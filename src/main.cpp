#include <iostream>
#include <string>
#include <regex>
#include <fstream>
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

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

int main(int argc, char *argv[]) {
    string homedir = getpwuid(getuid())->pw_dir;

    if (!pathExists(homedir+"/.sshmanager")) {
        mkdir((homedir+"/.sshmanager").c_str(), 0777);
        if (!pathExists(homedir+"/.sshmanager/sshs")) {
            ofstream sshsfile (homedir+"/.sshmanager/sshs");
            sshsfile.close();
        }
    }

    if (argc <= 1) {
        cerr << "Not enough arguments" << endl;
        return 1;
    }
    if (strcmp(argv[1], "list") == 0) {
        ifstream sshsfile (homedir+"/.sshmanager/sshs");
        string line;
        int count = 0;
        cout << "List of your SSHs" << endl;
        while(getline(sshsfile, line)) {
            cout << "[" << count << "] " << line << endl;
            count++;
        }
        return 0;
    } else if (strcmp(argv[1], "add") == 0) {
        string username, host;
        cout << "Insert username: ";
        cin >> username;
        if (!regex_match(username, regex("^[a-z_]([a-z0-9_-]{0,31}|[a-z0-9_-]{0,30}\$)$"))) {
            cerr << "Username may be wrong, it doesn't follow Linux rules" << endl;
            return 1;
        }
        cout << "Insert host of the SSH: ";
        cin >> host; 
        if (!(regex_match(host, regex(
            "^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$"
            )) || regex_match(host, regex(
            "^(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\-]*[a-zA-Z0-9])\.)*([A-Za-z0-9]|[A-Za-z0-9][A-Za-z0-9\-]*[A-Za-z0-9])$"
            )))
        ) {
            cerr << "Host is not an hostname or an IP address" << endl;
            return 1;
        }

        ofstream sshsfile (homedir+"/.sshmanager/sshs", ios::app);
        sshsfile << username+"@"+host << endl;

        return 0;
    } else if (strcmp(argv[1], "remove") == 0) {
        ifstream sshsfile (homedir+"/.sshmanager/sshs");
        string line, strindex, file;
        int fileLen = 0, index;
        cout << "Insert index of the SSH you want to remove: ";
        cin >> strindex; 
        if (!is_number(strindex)) {
            cerr << "Input is not a valid number. Please enter a positive integer." << endl;
            return 1;
        }
        index = stoi(strindex);
        while (getline(sshsfile, line)) {
            if (index != fileLen) file += line+"\n";
            fileLen++;
        }
        sshsfile.close();
        ofstream osshsfile (homedir+"/.sshmanager/sshs");
        osshsfile << file;
        osshsfile.close();
        return 0;
    } else if (strcmp(argv[1], "connect") == 0) {
        ifstream sshsfile (homedir+"/.sshmanager/sshs");
        string line, strindex;
        int index, fileLen = 0;
        cout << "Choose the index of the host you want to connect to: ";
        cin >> strindex;
        if (!is_number(strindex)) {
            cerr << "Input is not a valid number. Please enter a positive integer." << endl;
            return 1;
        }
        index = stoi(strindex);
        while (getline(sshsfile, line)) {
            if (index == fileLen) system(("ssh "+line).c_str());
            break;
        }
        return 0;
    } else if (strcmp(argv[1], "help") == 0) {
        cout << "This is a simple CLI to manage SSHs made by Gianluca Tarantino (check my Github for other cool projects, not like this one)" << endl <<
                "`sshmanager list` to list all saved SSHs" << endl <<
                "`sshmanager add` to add a new SSH host" << endl << 
                "`sshmanager remove <index> to remove the specified index from the list`" << endl <<
                "`sshmanager connect <index> to connect to the ssh in that specified index`" << endl <<
                "Not storing passwords for security reasons" << endl;
    } 
}
