#include <iostream>
#include <fstream>
#include <set>
#include <vector>

#define BLANKS " \t\r\n"
#define COMMENT '#'
#define SEP ':'


using namespace std;

static string home = getenv("HOME");

string expandTilde(string inout) {
    const string what{"~"};
    const string& with = home;
    for (string::size_type pos{};
         inout.npos != (pos = inout.find(what.data(), pos, what.length()));
         pos += with.length()) {
        inout.replace(pos, what.length(), with.data(), with.length());
    }
    return inout;
}

// split str separated by sep into a vector
vector<string> split(string str, char sep) {
    vector<string> res;
    size_t index = 0;
    while (index < str.size()) {
        size_t found = str.find_first_of(sep, index);
        if (found == string::npos) {
            res.push_back(str.substr(index));
            break;
        } else {
            string p = str.substr(index, found-index);
            res.push_back(p);
            index = found + 1;
        }
    }
    return res;
}

// trim leading and trailing spaces.
string trim(string s) {
    s = s.erase(0, s.find_first_not_of(BLANKS));
    return s.erase(s.find_last_not_of(BLANKS)+1);
}

// read path directories from config file, line by line,
// skipping lines that start with #
vector<string> fromConfigFile(string file) {
    vector<string> res;
    fstream fin{file, ios::in};
    if (fin.is_open()) {
        for (string buf; getline(fin, buf); ) {
            buf = trim(buf);
            if (buf.starts_with(COMMENT)) {
                continue;
            }
            res.push_back(expandTilde(buf));
        }
        fin.close();
    } else {
        cerr << "failed to read config file: " << file  << endl;
    }
    return res;
}

// collect paths
void addIfNotExists(set<string>& seen, vector<string>& res, vector<string>& tmp) {
    for (auto it = tmp.begin(); it != tmp.end(); ++it) {
        string p = *it;

        if (seen.find(p) == seen.end()) {
            seen.insert(p);
            res.push_back(p);
        }
    }
}

void printPaths(vector<string> res) {
    bool first = true;
    for (auto it = res.begin(); it != res.end(); ++it) {
        if (first) {
            first = false;
        } else {
            cout << SEP ;
        }
        cout << *it ;
    }
    cout << endl;
}

int main (int argc, char* argv[]) {
    string file = expandTilde("~/.pathz");
    vector<string> paths = fromConfigFile(file);

    set<string> seen;
    vector<string> res;
    addIfNotExists(seen, res, paths);

    string env = getenv("PATH");

    paths = split(env, SEP);
    addIfNotExists(seen, res, paths);
    printPaths(res);

    return 0;
}

