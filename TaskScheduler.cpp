#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Proc {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int finish;
};

void printGantt(int ganttPid[], int ganttDur[], int ganttCount) {
    cout << "Gantt: ";
    for (int i = 0; i < ganttCount; i++)
        cout << "[P" << ganttPid[i] << ":" << ganttDur[i] << "] ";
    cout << '\n';
}

void TaskScheduler() {
    cout << endl << "TASK SCHEDULER MODULE!" << endl;
    cout << "Task Scheduler - simulate FCFS / SJF (non-preemptive) / Round Robin\n";
    cout << "Enter number of processes: ";
    int n;
    cin >> n;

    Proc procs[50]; // assuming max 50 processes.
    for (int i = 0; i < n; i++) {
        procs[i].pid = i;
        cout << "Arrival time P" << i << ": ";
        cin >> procs[i].arrival;
        cout << "Burst time P" << i << ": ";
        cin >> procs[i].burst;
        procs[i].remaining = procs[i].burst;
        procs[i].finish = -1;
    }

    cout << "Choose algorithm: 1) FCFS 2) SJF 3) Round Robin\n";
    int alg;
    cin >> alg;

    if (alg == 1) {
        // FCFS
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (procs[j].arrival > procs[j + 1].arrival) {
                    Proc temp = procs[j];
                    procs[j] = procs[j + 1];
                    procs[j + 1] = temp;
                }
            }
        }

        int time = 0;
        double totalWT = 0, totalTAT = 0;
        int ganttPid[100], ganttDur[100], gCount = 0;

        for (int i = 0; i < n; i++) {
            if (time < procs[i].arrival) time = procs[i].arrival;
            int start = time;
            time += procs[i].burst;
            procs[i].finish = time;

            int tat = procs[i].finish - procs[i].arrival;
            int wt = start - procs[i].arrival;
            totalTAT += tat;
            totalWT += wt;

            ganttPid[gCount] = procs[i].pid;
            ganttDur[gCount++] = procs[i].burst;

            cout << "P" << procs[i].pid << " start " << start
                 << " finish " << procs[i].finish
                 << " TAT " << tat << " WT " << wt << "\n";
        }

        printGantt(ganttPid, ganttDur, gCount);
        cout << fixed << setprecision(2)
             << "Avg TAT: " << totalTAT / n
             << " Avg WT: " << totalWT / n << "\n";
    }

    else if (alg == 2) { 
        // SJF (Non-preemptive)
        bool done[50] = {false};
        int finished = 0, time = 0;
        double totalWT = 0, totalTAT = 0;
        int ganttPid[100], ganttDur[100], gCount = 0;

        while (finished < n) {
            int idx = -1, best = 1e9;
            for (int i = 0; i < n; i++) {
                if (!done[i] && procs[i].arrival <= time && procs[i].burst < best) {
                    best = procs[i].burst;
                    idx = i;
                }
            }
            if (idx == -1) {
                time++;
                continue;
            }

            int start = time;
            time += procs[idx].burst;
            procs[idx].finish = time;
            done[idx] = true;
            finished++;

            ganttPid[gCount] = procs[idx].pid;
            ganttDur[gCount++] = procs[idx].burst;

            int tat = procs[idx].finish - procs[idx].arrival;
            int wt = tat - procs[idx].burst;
            totalTAT += tat;
            totalWT += wt;

            cout << "P" << procs[idx].pid
                 << " start " << start
                 << " finish " << procs[idx].finish
                 << " TAT " << tat
                 << " WT " << wt << "\n";
        }

        printGantt(ganttPid, ganttDur, gCount);
        cout << fixed << setprecision(2)
             << "Avg TAT: " << totalTAT / n
             << " Avg WT: " << totalWT / n << "\n";
    }

    else if (alg == 3) { 
        // Round Robin
        int q;
        cout << "Enter quantum: ";
        cin >> q;

        int rem[50];
        for (int i = 0; i < n; i++) rem[i] = procs[i].burst;

        int time = 0, finished = 0;
        int ganttPid[500], ganttDur[500], gCount = 0;

        while (finished < n) {
            bool progressed = false;
            for (int i = 0; i < n; i++) {
                if (procs[i].arrival <= time && rem[i] > 0) {
                    int run = (rem[i] < q) ? rem[i] : q;
                    rem[i] -= run;
                    time += run;
                    ganttPid[gCount] = procs[i].pid;
                    ganttDur[gCount++] = run;

                    if (rem[i] == 0) {
                        finished++;
                        procs[i].finish = time;
                        int tat = procs[i].finish - procs[i].arrival;
                        int wt = tat - procs[i].burst;
                        cout << "P" << procs[i].pid
                             << " finished at " << time
                             << " TAT " << tat
                             << " WT " << wt << "\n";
                    }
                    progressed = true;
                }
            }
            if (!progressed) time++;
        }

        printGantt(ganttPid, ganttDur, gCount);
    }

    else {
        cout << "Invalid algorithm\n";
    }
}