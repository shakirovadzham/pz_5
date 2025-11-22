#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>
#include <chrono>

using namespace std;

string getCurrentTimeString() {
    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);
    tm localTime = *localtime(&time);
    
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H-%M", &localTime);
    return string(buffer);
}

class MyArray {
protected:
    int* data;
    int size;

public:
    MyArray(int n) {
        size = n;
        data = new int[size];
        for (int i = 0; i != size; i += 1) {
            data[i] = 0;
        }
    }

    MyArray(const MyArray& other) {
        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; i += 1) {
            data[i] = other.data[i];
        }
    }

    ~MyArray() {
        delete[] data;
    }

    void setValue(int index, int value) {
        if (0 <= index and index < size) {
            if (-100 <= value and value <= 100) {
                data[index] = value;
            } else {
                cout << "Error in the value" << endl;
                return;
            }
        } else {
            cout << "Error in the index" << endl;
            return;
        }
    }

    int getValue(int index) {
        if (0 <= index and index < size) {
            return data[index];
        } else {
            cout << "Index error" << endl;
            return 0;
        }
    }

    virtual void print() {
        cout << data[0];
        for (int i = 1; i != size; i += 1) {
            cout << " " << data[i];
        }
        cout << endl;
    }

    void addValue(int value) {
        if (-100 <= value and value <= 100) {
            int* newData = new int[size + 1];
            for (int i = 0; i < size; i += 1) {
                newData[i] = data[i];
            }
            newData[size] = value;
            delete[] data;
            data = newData;
            size += 1;
        } else {
            cout << "Value error" << endl;
        }
    }

    void add(const MyArray& other) {
        int minSize = min(size, other.size);
        for (int i = 0; i < minSize; i += 1) {
            data[i] += other.data[i];
        }
    }

    void sub(const MyArray& other) {
        int minSize = min(size, other.size);
        for (int i = 0; i < minSize; i += 1) {
            data[i] -= other.data[i];
        }
    }
};

class ArrTxt : public MyArray {
public:
    ArrTxt(int n) : MyArray(n) {}

    void print() override {
        string time = getCurrentTimeString() + ".txt";
        ofstream fout;
        fout.open(time);
        if (!fout.is_open()) {
            cout << "File recording error";
            return;
        }
        fout << size << endl;
        fout << data[0];
        for (int i = 1; i != size; i += 1) {
            fout << " " << data[i];
        }
        fout << endl;
        fout.close();
        cout << "The data is saved to a file: " << time << endl;
    }
};

class ArrCSV : public MyArray {
public:
    ArrCSV(int n) : MyArray(n) {}

    void print() override {
        string time = getCurrentTimeString() + ".csv";
        ofstream fout;
        fout.open(time);
        if (!fout.is_open()) {
            cout << "File recording error";
            return;
        }
        fout << size << endl;
        fout << data[0];
        for (int i = 1; i != size; i += 1) {
            fout << ";" << data[i];
        }
        fout << endl;
        fout.close();
        cout << "The data is saved to a file: " << time << endl;
    }
};

int main() {
    system("chcp 65001");

    ArrTxt a(8);
    a.setValue(0, 1);
    a.setValue(1, 2);
    a.setValue(2, 3);
    a.setValue(3, 4);
    a.setValue(4, 5);
    a.setValue(5, 6);
    a.setValue(6, 7);
    a.setValue(7, 8);
    a.print();

    ArrCSV b(8);
    b.setValue(0, 1);
    b.setValue(1, 2);
    b.setValue(2, 3);
    b.setValue(3, 4);
    b.setValue(4, 5);
    b.setValue(5, 6);
    b.setValue(6, 7);
    b.setValue(7, 8);
    b.print();

    return 0;
}