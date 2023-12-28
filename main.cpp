//
//  Project 1 Starter Code - DNA Profiling
//  Name:- Sharva Thakur
//  UIN:- 654135206
//
// This project takeS input in form of two files which are
// database and dna files.Then processes them with many commands
// to eventually find if the dna in the DNA file matches with
// anyone in the database. If no match is found this returns not
// found.

#include "ourvector.h"

#include <string>

#include <fstream>

#include <sstream>

using namespace std;

//
// struct Data
//
// This struct is used to store data from database.
//
struct Data {
    string name;
    ourvector < int > count;
};

//
// struct pros_data
//
// This struct is used to store the processed data.
//
struct pros_data {
    ourvector < char > dna;
    int total;
};

//
// Input_DNA
//
// Parameters are ourvector<ourvector<char>>, a string and a
// string stream everything is passed by refrence
//
// This function inputs the dna STR from the data base and stores
// them inside an ourvector of char and then stores the ourvector 
// or char into another ourvector<ourvector<char>>.
//
void input_DNA(ourvector < ourvector < char >> & dna_name,
string & temp, stringstream & parser) {
    ourvector < char > a;
    while (getline(parser, temp, ',')) {
        a.clear();
        for (char & c : temp) {
            // pushes each character into ourvector of c
            a.push_back(c);
        }
        // pushes ourvector into ourvector<ourvector<char>>
        dna_name.push_back(a);
    }
}

//
// Inputdata
//
// Parameters are ourvector<Data>, a string and string
// everything is passed by refrence
//
// This function inputs the data in database file and saves it
// into a struct which has name and a ourvector of integer. Then
// the struct is saved into an ourvector of struct Data.
//
void inputData(ourvector < Data > & data, string & temp) {
    stringstream parser;
    parser.str(temp);

    getline(parser, temp, ',');
    Data A;
    A.name = temp;
    while (getline(parser, temp, ',')) {
        int s = 0;
        s = stoi(temp);
        A.count.push_back(s);
    }
    data.push_back(A);
}

//
// load_db
//
// Parameters are ourvector<ourvector<char>> and ourvector<Data>
// passed by refrence.
//
// This function takes the filename from the user and checks if it
// is valid. If the file is valid this function calls input_DNA
// and inputData.
//
void load_db(ourvector < ourvector < char >> & dna_name,
ourvector < Data > & data) {
    data.clear();
    dna_name.clear();

    string filename;

    cin >> filename;

    cout << "Loading database..." << endl;

    ifstream infile(filename);

    // if the file is not good
    if (!infile.good()) {
        cout << "Error: unable to open '" << filename << "'" << endl;
        return;
    }

    string temp;
    stringstream parser;

    infile >> temp;
    // to skip the "name," in first line
    temp = temp.substr(5);
    parser.str(temp);
    input_DNA(dna_name, temp, parser);

    infile >> temp;

    while (!infile.eof()) {
        inputData(data, temp);
        infile >> temp;
    }
}

//
// dis_databse
//
// Parameter is an ourvector<Data> passed by refrence
//
// This function displays the loaded data
//
void dis_database(ourvector < Data > & data) {
    // If no data is loaded
    if (data.size() == 0) {
        cout << "No database loaded." << endl;
    } else {
        cout << "Database loaded: " << endl;
        for (Data & A : data) {
            // printing the name
            cout << A.name;
            for (int & S : A.count) {
                // printing the integers
                cout << " " << S;
            }
            cout << endl;
        }
        cout << endl;
    }
}

//
// dis_DNA
//
// Parameter is an ourvector<char> passed by refrence.
//
// This function displays the loaded DNA
//
void dis_DNA(ourvector < char > & dna) {
    // If no dna loaded
    if (dna.size() == 0) {
        cout << "No DNA loaded." << endl;
    } else {
        cout << "DNA loaded: " << endl;
        for (char & c : dna) {
            cout << c;
        }
        cout << endl;
    }
    cout << endl;
}

//
// dis_pros
//
// Parameter is an ourvector<pros_data> passed by refrence.
//
// This function displays the processed data which is STR type and
// the count in the loaded DNA.
//
void dis_pros(ourvector < pros_data > & p_data) {
    // if no dna is processed
    if (p_data.size() == 0) {
        cout << "No DNA has been processed." << endl;
    } else {
        cout << "DNA processed, STR counts: " << endl;
        for (pros_data & S : p_data) {
            for (char & c : S.dna) {
                cout << c;
            }
            cout << ": " << S.total << endl;
        }
        cout << endl;
    }
}

//
// display
//
// Parameters are ourvector<ourvector<char>>, ourvector<Data>,
// ourvector<char>,ourvector<pros_data> passed by refrence.
//
// This function displays the loaded data , dna and processed data
// by calling the functions.
//
void display(ourvector < ourvector < char >> & dna_name, ourvector 
< Data > & data, ourvector < char > & dna, 
ourvector < pros_data > & p_data) {
    // calling dis_database function
    dis_database(data);
    // calling dis_DNA function
    dis_DNA(dna);
    // display dis_pros function
    dis_pros(p_data);
}

//
// load_dna
//
// Parameter is an ourvector<char>
//
// This function takes the DNA file checks if it's valid 
// and if the file is valid
// this function stores the DNA into ourvector of char
//
void load_dna(ourvector < char > & dna) {
    // clearing ourvector<char> dna
    dna.clear();
    string filename;
    cin >> filename;
    cout << "Loading DNA..." << endl;
    ifstream infile(filename);
    // if file does not load
    if (!infile.good()) {
        cout << "Error: unable to open '" << filename << "'" << endl;
        return;
    }
    string temp;
    infile >> temp;
    for (char & c : temp) {
        dna.push_back(c);
    }
}

//
// match
//
// Parameters are two ourvector<char> passed by refrence and an integer
//
// This function compares the STR to the STR in the DNA file and
// returns true if it matches.
//
bool match(ourvector < char > & a, ourvector < char > & dna, int i) {
    for (int j = 0; j < a.size(); j++) {
        // If i is greater or equal to size of the dna
        if (i >= dna.size()) {
            return false;
        }
        // If the count doesnot match up
        if (a[j] != dna[i]) {
            return false;
        }

        i++;
    }

    return true;
}

//
// process_one_str
//
// Parameters are two ourvector<char>.
//
// This function processes one STR at a time to find if STR exists
// in the DNA then it finds the longest chain of STR and reutrns
// the number of STR in the chain.
//
int process_one_str(ourvector < char > & a, ourvector < char > & dna) {
    int t = 0;
    int s = 0;
    for (int i = 0; i < dna.size(); i++) {
        if (dna[i] == a[0]) {
            // it loops through the consecutive chain of str
            while (match(a, dna, i) == true) {
                s++;
                i = i + a.size();
            }
            // checks if the consecutive chain is bigger than previous
            if (t <= s) {
                t = s;
            }
            s = 0;
        }
    }
    // returns longest consecutive chain
    return t;
}

//
// process
//
// Parameters are ourvector<ourvector<char>> and ourvector<char>
// passed by refrence.
//
// This function finds the STR present in the DNA file and then
// saves the name of STR and the count into a struct made of
// ourvector of char and integer. Then stores the struct into an
// ourvector
//
void process(ourvector < ourvector < char >> & dna_name, 
ourvector < char > & dna,
    ourvector < pros_data > & p_data) {
    // if database not loaded
    p_data.clear();
    if (dna_name.size() == 0) {
        cout << "No database loaded." << endl;
    } else if (dna.size() == 0) {
        cout << "No DNA loaded." << endl;
    } else {
        cout << "Processing DNA..." << endl;
        pros_data temp;
        for (ourvector < char > & a : dna_name) {
            int S = process_one_str(a, dna);  // str count
            temp.dna = a;
            temp.total = S;
            p_data.push_back(temp);  // stores str name into ourvector<char>
        }
    }
}

//
// compare
//
// Parametes are ourvector<pros_data> and a struct Data both pass
// by refrence.
//
// This function compares the number of STR from the database to
// the DNA processed
//
bool compare(ourvector < pros_data > & p_data, Data & a) {
    for (int i = 0; i < p_data.size(); i++) {
        // checks if the count matches the dna count from data base
        if (p_data[i].total == a.count[i]) {} else {
            // if doesnot match returns false
            return false;
        }
    }
    return true;
}

//
// Search
//
// Parameters are ourvector<pros_data>, ourvector<Data>
// ourvector<char>, ourvector<ourvector<char>> all passed by
// refrence
//
// This fucntion searches for the match to the dna.
//
void search(ourvector < pros_data > & p_data, ourvector < Data > & data,
    ourvector < char > & dna, ourvector < ourvector < char >> & dna_name) {

    bool found = false;
    // if database not loaded
    if (dna_name.size() == 0) {
        cout << "No database loaded." << endl;
    } else if (dna.size() == 0) {
        cout << "No DNA loaded." << endl;
    } else if (p_data.size() == 0) {
        cout << "No DNA processed." << endl;
    } else {
        cout << "Searching database..." << endl;
        for (Data & a : data) {
            if (compare(p_data, a) == true) {
                cout << "Found in database!  DNA matches: " << a.name << endl;
                found = true;
                break;
            }
        }
        if (found == false) {
            cout << "Not found in database." << endl;
        }
    }
}

//
// load_mult_dna(creative comnponent)
//
// The parameters are ourvector<char> and a srtring both passed by
// refrence
//
// This function takes input of dna for my creative function without
// the user continously needing to input the file name one by one.
//
void load_mult_dna(ourvector < char > & dna, string & file) {
    dna.clear();
    ifstream infile(file);

    if (!infile.good()) {
        cout << "Error: unable to open '" << file << "'" << endl;
        return;
    }
    string temp;
    infile >> temp;

    for (char & c : temp) {
        dna.push_back(c);
    }
}

//
// process_multiple_dna(creative component)
//
// The parameters are ourvector<ourvector<char>>, ourvector<Data>,
// ourvector<char> passed by refrence.
//
// This function processes multiple DNA with at a time. It compares the
// DNA with the database file.
// This function then finds the chain of dna from each file and display
// the data.
//
void process_multiple_dna(ourvector < ourvector < char >> & dna_name,
    ourvector < Data > & data, ourvector < char > & dna,
    ourvector < pros_data > & p_data, ourvector < string > & files) {
    // inputs database file
    cout << "Enter a database file" << endl;
    load_db(dna_name, data);
    // inputs dna file
    cout << "Enter dna files and # when done." << endl;
    string filename;
    cin >> filename;
    cout << "Loading DNA..." << endl;
    while (filename != "#") {
        files.push_back(filename);
        cin >> filename;
    }

    // processes and displays the files
    for (string & S : files) {
        load_mult_dna(dna, S);
        process(dna_name, dna, p_data);
        cout << endl;
        cout << "Output of DNA file '" << S << "'" << endl;

        display(dna_name, data, dna, p_data);
    }
    files.clear();
}

//
// process command
//
// The parameters are ourvector<ourvector<char>>, ourvector<Data>,
// ourvector<char>, ourvector<pros_data>, ourvector<string> all passed
// by reference.
//
// This function takes user's input and processes the commands
//
void process_commands(ourvector < ourvector < char >> & dna_name,
    ourvector < Data > & data, ourvector < char > & dna,
    ourvector < pros_data > & p_data, ourvector < string > & files) {
    string command;
    cin >> command;

    while (command != "#") {
        if (command == "load_db") {
            load_db(dna_name, data);
        } else if (command == "display") {
            display(dna_name, data, dna, p_data);
        } else if (command == "load_dna") {
            load_dna(dna);
        } else if (command == "process") {
            process(dna_name, dna, p_data);
        } else if (command == "search") {
            search(p_data, data, dna, dna_name);
        } else if (command == "pros_mult_dna") {
            process_multiple_dna(dna_name, data, dna, p_data, files);
        }
        cout << "Enter command or # to exit: ";
        cin >> command;
    }
}

//
// Main
//
int main() {
    cout << "Welcome to the DNA Profiling Application." << endl;

    cout << "Enter command or # to exit: ";

    // declaring ourvector<ourvector<char>>
    ourvector < ourvector < char >> dna_name;
    // declaring ourvector<Data>
    ourvector < Data > data;
    // declaring ourvector<char>
    ourvector < char > dna;
    // declaring ourvector<string>
    ourvector < string > files;
    // declaring ourvector<pros_data>
    ourvector < pros_data > p_data;

    // Processing all the commands
    process_commands(dna_name, data, dna, p_data, files);

    return 0;
}
