#include "pch.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

TEST(file_operations, test)
{
    fstream fs;
    fs.open("temp.txt", ios::in | ios::out);
    if (!fs.is_open())
        cout << "couldn't open file" << endl;

    cout << "p : " << fs.tellp() << " g : " << fs.tellg() << endl;
    fs << "aaabbbbcccc\n";

    cout << "p : " << fs.tellp() << " g : " << fs.tellg() << endl;
    fs.seekg(0);
    cout << "p : " << fs.tellp() << " g : " << fs.tellg() << endl;
    string line;
    getline(fs, line);
    cout << "p : " << fs.tellp() << " g : " << fs.tellg() << endl;
    fs.seekp(0);
    fs.seekg(0);
    fs << "vvvmmmm\n";
    cout << "p : " << fs.tellp() << " g : " << fs.tellg() << endl;
    fs.seekp(0);
    getline(fs, line);
    cout << "p : " << fs.tellp() << " g : " << fs.tellg() << endl;
    cout << line << endl;
    cout << "p : " << fs.tellp() << " g : " << fs.tellg() << endl;
    fs.seekp(line.length() + 2);
    getline(fs, line);
    cout << line << endl;
    cout << "p : " << fs.tellp() << " g : " << fs.tellg() << endl;
    fs.seekp(0, ios_base::end);
    cout << "p : " << fs.tellp() << " g : " << fs.tellg() << endl;
    fs.seekp(0);
    cout << "p : " << fs.tellp() << " g : " << fs.tellg() << endl;
    char c;
    fs.get(c);
    cout << "p : " << fs.tellp() << " g : " << fs.tellg() << endl;
    EXPECT_TRUE(false);
}
