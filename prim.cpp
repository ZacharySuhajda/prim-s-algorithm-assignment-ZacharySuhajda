#include "prim.h"

int main() {
    string myText;

    ifstream MyReadFile("C:/Users/suhajdaz3219/Desktop/Algorithms/Prims Algorithm/prim-s-algorithm-assignment-ZacharySuhajda/testdata.txt");

    if (MyReadFile.is_open()) {
        while (std::getline(MyReadFile, myText)) {
            cout << myText << endl;
        }
        MyReadFile.close();
    } else {
        cerr << "Error: Unable to open the file." << endl;
    }

    return 0;
}