#include "writeFile.h"
struct thread_data
{
    int thread_id;
    long recordSize;
    long long fileSize;
    bool random;
};

void *create_files(void *threadarg)
{
    struct thread_data *td;
    td = (struct thread_data *)threadarg;
    string filename = "dataset-" + to_string(td->thread_id) + ".txt";

    ofstream file;
    file.rdbuf()->pubsetbuf(0, 0); //set the stream to not using a buffer(cache)
    file.open(filename.c_str());
    file << "/n";
    file.close();
    file.open(filename.c_str());
    if (!file)
    {
        cout << "Error in creating file.\n";
    }

    string record;
    for (int i = 0; i <= td->recordSize; i++)
    {
        record += "a";
    }
    for (int i = 0; i < td->fileSize / td->recordSize; i++)
    {
        if (td->random)
            file.seekp(8, ios::cur); //random access
        file << record;
    }
    pthread_exit(NULL);
}

void write_bench(long long total_data, int num_threads, long recordSize, bool random, bool iops, bool debug)
{
    int rc;
    int i;//10GB
    long long fileSize = total_data / num_threads;
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
        if (debug)
            cout << "main() : creating thread, " << i << endl;
        td[i].thread_id = i;
        td[i].recordSize = recordSize;
        td[i].fileSize = fileSize;
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
        if (debug)
        {
            cout << "Main: completed thread id :" << i;
            cout << "  exiting with status :" << status << endl;
        }
    }
    if (debug)
        cout << "Main: program exiting." << endl;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    double sec = (double)duration.count() / 1000;
    //cout << "|Time taken: " << sec << " seconds" << endl;
    if (iops)
        cout << total_data / recordSize / sec  << endl;
    else
        cout << total_data / 1024 / 1024 / sec << endl;
}