#include "utils.h"

/*
 * INPUT / OUTPUT
 */

void
line(int size, char ch) {
    cout << setfill(ch) << setw(size) << "" << endl << setfill(' ');
}

void
cinERR(const string &message) {
    cerr << message;
    cout << endl;
    cin.clear();
}

void
getOption(int &dest, const string &message, function<bool(int)> cond) {
    string str;

    while (true) {
        try {
            cout << endl << message;
            getline(cin, str);

            if (not cond(stoi(str))) {
                str = "";
                cinERR("ERROR: Invalid entry, try again");
                continue;
            }
            dest = stoi(str);
            break;
        }
        catch (invalid_argument &e) {
            str = "";
            cinERR("ERROR: Invalid entry, try again");
        }
    }
}

void
getOptionList(vector<int> &dest, const string &message, function<bool(int)> cond) {
    string str;

    while (true) {
        try {
            cout << endl << message;
            getline(cin, str);

            if (not cond(stoi(str))) {
                str = "";
                cinERR("ERROR: Invalid entry, try again");
                continue;
            }

            dest.push_back(stoi(str));
        }
        catch (invalid_argument &e) {
            if (str == "*") {
                return;
            }

            str = "";
            cinERR("ERROR: Invalid entry, try again");
        }
    }
}

void
getDouble(double &dest, const string &message) {

    string str;

    while (true) {
        try {
            cout << endl << message;
            getline(cin, str);
            cout << endl;

            dest = stod(str);

            break;
        } catch (invalid_argument &e) {
            str = "";
            cinERR("ERROR: Invalid entry, try again");
        }
    }
}

void
enterWait(const string &message) {
    string str;
    cout << message << endl;
    getline(cin,str);
}


/*
 * CALC
 */

int
rng(int lower, int upper){
    random_device rd;        // obtain a random number from hardware
    mt19937 eng(rd());       // seed the generator

    uniform_int_distribution<> distr(lower, upper);

    return distr(eng);
}


/*
 * TEXT
 */

// To Uppercase
string
toUpper(string s){
    for (auto& ch : s) ch = toupper(ch);
    return s;
}

// Left Trim
void
ltrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](int ch) {
        return !isspace(ch);
    }));
}

// Right Trim
void
rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), s.end());
}

// Trim
void
trim(string &s) {
    ltrim(s);
    rtrim(s);
}

// Split
template<typename t>
void
split(const string& s, char delim, t result){
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim))
        *result++ = item;
}

vector<string>
split(const string &s, char delim){
    vector<string> v;
    split(s, delim, back_inserter(v));
    return v;
}


/*
 * FILES
 */

// Empty Check
bool
fileIsEmpty(ifstream& file){
    return file.peek() == ifstream::traits_type::eof();
}

// Make File
void
makeFile(string filename){
    ofstream newFile(filename);
    newFile.close();
}

// Read File
ifstream
readFile(string filename) {
    ifstream file(filename);

    if (!file){
        cout << endl << filename << " does not exist!\n";
        cout << "creating " << filename << "...\n";

        makeFile(filename);

        cout << filename << " created successfully!\n";

        ifstream newFile(filename);
        return newFile;
    };

    return file;
}

// Write to File
void
writeToFile(vector<string> &data, string filename){
    ofstream file(filename);
    ostream_iterator<string> out_it(file, "\n");
    copy(data.begin(), data.end(), out_it);
}

void
writeToFile(string &data, string filename){
    ofstream file(filename);
    file << data << endl;
    file.close();
}

// Write Data
void
writeData(string data, string filename){

    ifstream file = readFile(filename);

    if (not fileIsEmpty(file)){
        vector<string> fileData = parseFile(file);
        fileData.push_back(data);

        deleteFileData(filename);

        ofstream file;
        file.open(filename);

        for (auto line : fileData)
            file << line << endl;

        file.close();
    } else
        writeToFile(data, filename);
}

// Parse File Data
vector<string>
parseFile(ifstream &file){
    string line;
    vector<string> data;

    while (getline(file, line)) data.push_back(line);

    file.close();
    return data;
}

// Delete Data
void
deleteFileData(string filename){
    ofstream file(filename, ofstream::out | ofstream::trunc);
}


