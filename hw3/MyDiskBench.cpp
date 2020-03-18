#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

#define dataSize 20*1024*1024
#define recordSize 1024*1024


int main(){
    ofstream file;
    file.rdbuf()->pubsetbuf(0, 0); //set the stream to not using a buffer(cache)
    file.open("dataset.txt");
    if (!file)
    {
        cout << "Error in creating file.\n";
    }

    string text;
    auto start = high_resolution_clock::now();
    for (int i = 1; i <= dataSize; i++)
    {
        if (i % recordSize == 0)
        {
            text += "\n";
            file << text;
            text = "";
        }
        else
        {
            text += "a";
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    // To get the value of duration use the count()
    // member function on the duration object
    cout << "Time taken: " << (double) duration.count()/1000 << " seconds" << endl;
}