#include <iostream>
using namespace std;

void BankersAlgorithm(){
    cout << endl << "SIMULATING BANKER'S ALGORITHM FOR DEADLOCK AVOIDANCE..." << endl;
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resource types: ";
    cin >> m;

    int alloc[10][10];    // Allocation matrix
    int maxNeed[10][10];  // Max matrix
    int need[10][10];     // Need matrix
    int avail[10];        // Available resources
    int finish[10] = {0}; // Finish flags
    int safeSeq[10];      // Safe sequence

    cout << "Enter Allocation matrix (" << n << " x " << m << ") row-wise:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> alloc[i][j];

    cout << "Enter Max matrix (" << n << " x " << m << ") row-wise:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> maxNeed[i][j];

    cout << "Enter Available resources (" << m << "):\n";
    for (int j = 0; j < m; j++)
        cin >> avail[j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = maxNeed[i][j] - alloc[i][j];

    int work[10];
    for (int j = 0; j < m; j++)
        work[j] = avail[j];

    int count = 0;
    while (count < n)
    {
        bool found = false;
        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool ok = true;
                for (int j = 0; j < m; j++)
                    if (need[i][j] > work[j])
                    {
                        ok = false;
                        break;
                    }
                if (ok)
                {
                    for (int j = 0; j < m; j++)
                        work[j] += alloc[i][j];
                    safeSeq[count] = i;
                    finish[i] = 1;
                    found = true;
                    count++;
                }
            }
        }
        if (!found)
            break;
    }

    if (count == n)
    {
        cout << "System is in SAFE state.\nSafe sequence: ";
        for (int i = 0; i < n; i++)
            cout << "P" << safeSeq[i] << (i + 1 < n ? " -> " : "\n");
    }
    else
    {
        cout << "System is NOT in a safe state.\n";
    }
}