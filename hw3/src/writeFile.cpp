#include "writeFile.h"

// TODO: part 1b, create the files in directories D1 to D7.
/*
~/.../team-25/hw3/src/data/D1
~/.../team-25/hw3/src/data/D2
~/.../team-25/hw3/src/data/D3
...etc
*/
struct thread_data
{
    int thread_id;
    int recordSize; 
    bool random;
};

void *create_files(void *threadarg)
{
    struct thread_data *td;
    td = (struct thread_data *)threadarg;
    string filename = "dataset-" + to_string(td->thread_id) + ".txt";

    ofstream file;
    file.rdbuf()->pubsetbuf(0, 0); //set the stream to not using a buffer(cache)
    file.open(filename);
    if (!file)
    {
        cout << "Error in creating file.\n";
    }

    string text;
    
    for (int i = 1; i <= dataSize; i++)
    {
        if (td->random)
            file.seekp(16, ios::cur); //random access
        if (i % td->recordSize == 0)
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
    
}

void thread_test(int num_threads, int recordSize, bool random)
{
    int rc;
    int i;
    pthread_t threads[num_threads];
    pthread_attr_t attr;
    void *status;
    struct thread_data td[num_threads];

    // Initialize and set thread joinable
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    auto start = high_resolution_clock::now();

    for (i = 0; i < num_threads; i++)
    {
        cout << "main() : creating thread, " << i << endl;
        td[i].thread_id = i;
        td[i].recordSize = recordSize;
        td[i].random = random;
        rc = pthread_create(&threads[i], &attr, create_files, (void *)&td[i]);
        if (rc)
        {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
    }

    // free attribute and wait for the other threads
    pthread_attr_destroy(&attr);
    for (i = 0; i < num_threads; i++)
    {
        rc = pthread_join(threads[i], &status);
        if (rc)
        {
            cout << "Error:unable to join," << rc << endl;
            exit(-1);
        }
        cout << "Main: completed thread id :" << i;
        cout << "  exiting with status :" << status << endl;
    }

    //cout << "Main: program exiting." << endl;
    //pthread_exit(NULL);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    // To get the value of duration use the count()
    // member function on the duration object
    cout << "Time taken: " << (double)duration.count() / 1000 << " seconds" << endl;
}