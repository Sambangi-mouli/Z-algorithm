#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void getZarr(string str, int Z[]);


void search(string text, string pattern, ofstream& outFile) {
    string concat = pattern + "$" + text;
    int l = concat.length();
    int *Z = new int[l];
    getZarr(concat, Z);

    bool found = false;
    for (int i = 0; i < l; ++i) {
        if (Z[i] == pattern.length()) {
            outFile << "Pattern found at index " << i - pattern.length() - 1 << endl;
            found = true;
        }
    }
    
    if (!found) {
        outFile << "Pattern not found." << endl;
    }

    delete[] Z;
}

// Fills Z array for given string str[]
void getZarr(string str, int Z[]) {
    int n = str.length();
    int L, R, k;

    L = R = 0;
    Z[0] = 0; // Z[0] is always 0
    for (int i = 1; i < n; ++i) {
        if (i > R) {
            L = R = i;
            while (R < n && str[R] == str[R - L])
                R++;
            Z[i] = R - L;
            R--;
        } else {
            k = i - L;
            if (Z[k] < R - i + 1) 
                Z[i] = Z[k];
            else {
                L = i;
                while (R < n && str[R] == str[R - L])
                    R++;
                Z[i] = R - L;
                R--;
            }
        }
    }
}


int main() {
	
	
    ifstream textFile("filename.txt"), patternFile("patternfile.txt");
    ofstream outFile("output.txt");

    if (!textFile.is_open() || !patternFile.is_open() || !outFile.is_open()) {
        cerr << "Error opening files!" << endl;
        return 1;
    }

    string text, pattern;

    getline(patternFile, pattern);
    getline(textFile, text);

    search(text, pattern, outFile);

    textFile.close();
    patternFile.close();
    outFile.close();

    return 0;
}

