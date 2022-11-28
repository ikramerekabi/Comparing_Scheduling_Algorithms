#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <queue>
#pragma pack(1)
//#include <bits/stdc++.h>

using namespace std;
//extern int max_priority = 40; 
struct process {
    int proc_id;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;


};
struct process_total {
    process* processes;
    int N;


};
process_total read_from_file() {
    string fname;
    cout << "Enter the file name: ";
    cin >> fname;
    cout << endl;
    vector<vector<string>> content;
    vector<string> row;
    string line, word;

    fstream file(fname, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();

            stringstream str(line);

            while (getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }
    }
    process_total Processes;
    Processes.processes = new process[content.size() - 1];
    Processes.N = content.size() - 1;
    for (int j = 1; j < content.size(); j++)
    {
        Processes.processes[j-1].proc_id = stoi(content[j][0]);
        Processes.processes[j-1].arrival_time = stoi(content[j][1]);
        Processes.processes[j-1].burst_time = stoi(content[j][2]);
    }
    return Processes;
}

struct algorithm_output {
    double Avg_turnaround_time;
    double Avg_waiting_time;
    double Avg_response_time;

};
bool comparator1(process p1, process p2)
{
    return p1.arrival_time < p2.arrival_time;
}

bool comparator2(process p1, process p2)
{
    return p1.proc_id < p2.proc_id;
}

algorithm_output round_roubin(struct process* process, int n) {
    struct algorithm_output output;
    int time_quantum = 2;  //
    struct process arr[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    float cpu_utilisation;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    float throughput;
    int* burst_remaining= new int[n];
    int eligibal_proc;
    int current_time = 0;
    int completed = 0;
    int mark[100];
    mark[0] = 1;

    queue<int> q;
    sort(arr, arr + n, comparator1);  // sort based on the arriving time.
    memset(mark, 0, sizeof(mark)); // set all processs to uncomplete


    q.push(0);

    while (completed != n) {
        eligibal_proc = q.front();
        q.pop();

        if (burst_remaining[eligibal_proc] == arr[eligibal_proc].burst_time) {
            arr[eligibal_proc].start_time = max(current_time, arr[eligibal_proc].arrival_time);
            current_time = arr[eligibal_proc].start_time;
        }

        if (burst_remaining[eligibal_proc] - time_quantum > 0) {
            burst_remaining[eligibal_proc] -= time_quantum;
            current_time += time_quantum;
        }
        else {
            current_time += burst_remaining[eligibal_proc];
            burst_remaining[eligibal_proc] = 0;
            completed++;

            arr[eligibal_proc].completion_time = current_time;
            arr[eligibal_proc].turnaround_time = arr[eligibal_proc].completion_time - arr[eligibal_proc].arrival_time;
            arr[eligibal_proc].waiting_time = arr[eligibal_proc].turnaround_time - arr[eligibal_proc].burst_time;
            arr[eligibal_proc].response_time = arr[eligibal_proc].start_time - arr[eligibal_proc].arrival_time;

            total_turnaround_time += arr[eligibal_proc].turnaround_time;
            total_waiting_time += arr[eligibal_proc].waiting_time;
            total_response_time += arr[eligibal_proc].response_time;
        }

        for (int i = 1; i < n; i++) {
            if (burst_remaining[i] > 0 && arr[i].arrival_time <= current_time && mark[i] == 0) {
                q.push(i);
                mark[i] = 1;
            }
        }
        if (burst_remaining[eligibal_proc] > 0) {
            q.push(eligibal_proc);
        }

        if (q.empty()) {
            for (int i = 1; i < n; i++) {
                if (burst_remaining[i] > 0) {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }


    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;
    avg_response_time = (float)total_response_time / n;

    output.Avg_waiting_time = avg_waiting_time;
    output.Avg_turnaround_time = avg_turnaround_time;
    output.Avg_response_time = avg_response_time;
    return output;
}
void findWaitingTime_FCFS(process processes[], int n)
{

    processes[0].waiting_time = 0;
    for (int i = 1; i < n; i++)
    {
        processes[i].waiting_time = processes[i - 1].burst_time + processes[i - 1].waiting_time;
    }

}

// Function to calculate turn around time
void findTurnAroundTime_FCFS(process processes[], int n)
{
    for (int i = 0; i < n; i++)
    {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
    }

}

double findavgTime_FCFS(process processes[], int n)

{

    double Average_Waiting_Time;
    double total_waiting_time = 0;

    findWaitingTime_FCFS(processes, n);

    for (int i = 0; i < n; i++)
    {
        total_waiting_time = total_waiting_time + processes[i].waiting_time;

    }
    Average_Waiting_Time = total_waiting_time / n;

    return Average_Waiting_Time;
}

double findavgTurnaroundTime_FCFS(process processes[], int n)
{
    double Average_Turnaround_Time;
    double total_turnaround_time = 0;
    findTurnAroundTime_FCFS(processes, n);
    for (int i = 0; i < n; i++)
    {
        total_turnaround_time = total_turnaround_time + processes[i].turnaround_time;
    }
    Average_Turnaround_Time = total_turnaround_time / n;
    return Average_Turnaround_Time;
}

algorithm_output FCFS(process processes[], int n)
{
    struct algorithm_output output;

    output.Avg_waiting_time = findavgTime_FCFS(processes, n);
    output.Avg_turnaround_time = findavgTurnaroundTime_FCFS(processes, n);
    output.Avg_response_time = output.Avg_waiting_time;
    return output;
}

//Non-Preemptive SJF Scheduling
algorithm_output Non_preemptive_SJF(struct process* processes, int num_proc)
{
    float avg_wt, avg_tat, avg_rt, avg_rp;
    int total = 0, pos, temp;
    int  time = 0;
    int sum_burst_time = 0;
    vector<process> ready_processes;
    vector<process> running_processes;
    vector<process> total_processes;
    for (int i = 0; i < num_proc; i++)
    {
        sum_burst_time += processes[i].burst_time;
    }

    for (int i = 0; i < num_proc; i++)
    {
        total_processes.push_back(processes[i]);
    }

    for (time; time < sum_burst_time;)
    {
        for (int z = 0; z < total_processes.size(); z++) {
            if (total_processes[z].arrival_time <= time) {
                ready_processes.push_back(total_processes[z]);
                total_processes.erase(total_processes.begin() + z);
            }
        }
        int min = 9999;
        int running = 0;
        for (int j = 0; j < ready_processes.size(); j++)
        {
            if (ready_processes[j].burst_time < min)
            {
                min = ready_processes[j].burst_time;
                running = j;
            }

        }
        running_processes.push_back(ready_processes[running]);
        time += ready_processes[running].burst_time;
        ready_processes.erase(ready_processes.begin() + running);


    }

    running_processes[0].waiting_time = 0;
    for (int i = 1; i < running_processes.size(); i++)
    {
        running_processes[i].waiting_time = 0;
        for (int j = 0; j < i; j++) {
            running_processes[i].waiting_time += running_processes[j].burst_time;
        }
        running_processes[i].waiting_time -= running_processes[i].arrival_time;
        total += running_processes[i].waiting_time;
    }

    avg_wt = (float)total / num_proc;
    total = 0;

    for (int i = 0; i < running_processes.size(); i++)
    {
        running_processes[i].response_time = 0;
        for (int j = 0; j < i; j++) {
            running_processes[i].response_time += running_processes[j].burst_time;
        }
        running_processes[i].response_time -= running_processes[i].arrival_time;
        total += running_processes[i].response_time;
    }

    avg_rt = (float)total / num_proc;
    total = 0;

    for (int i = 0; i < running_processes.size(); i++)
    {
        running_processes[i].turnaround_time = 0;
        for (int j = 0; j < i; j++) {
            running_processes[i].turnaround_time += running_processes[j].burst_time;
        }
        running_processes[i].turnaround_time += running_processes[i].burst_time;
        total += running_processes[i].turnaround_time;
    }
    avg_tat = (float)total / num_proc;


    struct algorithm_output output;
    output.Avg_waiting_time = avg_wt;
    output.Avg_turnaround_time = avg_tat;
    output.Avg_response_time = avg_rt;
    //cout<<"Non Preemptive SJF"<<endl;
    //printf("\nProcess\t    Arrival Time\t    Burst Time    \tWaiting Time\t\tTurnaround Time\t\tResponse Time\n");
    //for (int i = 0; i < running_processes.size(); i++) {
    //    cout << running_processes[i].proc_id << "\t\t" << running_processes[i].arrival_time << "\t\t\t" << running_processes[i].burst_time << "\t\t\t" << running_processes[i].waiting_time << "\t\t\t" << running_processes[i].turnaround_time << "\t\t\t" << running_processes[i].response_time << "\n";
    //}

    return output;
}

//Preemptive SJF Scheduling
algorithm_output Preemptive_SJF(struct process* processes, int num_proc) {

    int* rt= new int[num_proc];
    int* wt= new int[num_proc];
    int* tat=new int[num_proc];
    int total_wt = 0;
     int   total_tat = 0;

    for (int i = 0; i < num_proc; i++)
        rt[i] = processes[i].burst_time;

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;

    while (complete != num_proc) {

        for (int j = 0; j < num_proc; j++) {
            if ((processes[j].arrival_time <= t) &&
                (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }

        if (check == false) {
            t++;
            continue;
        }

        rt[shortest]--;

        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        if (rt[shortest] == 0) {

            complete++;
            check = false;

            finish_time = t + 1;

            wt[shortest] = finish_time - processes[shortest].burst_time - processes[shortest].arrival_time;

            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
    }

    for (int i = 0; i < num_proc; i++)
        tat[i] = processes[i].burst_time + wt[i];

    for (int i = 0; i < num_proc; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << processes[i].proc_id << "\t\t"
            << processes[i].burst_time << "\t\t " << wt[i]
            << "\t\t " << tat[i] << endl;
    }

    cout << "\nAverage waiting time = "
        << (float)total_wt / (float)num_proc;
    cout << "\nAverage turn around time = "
        << (float)total_tat / (float)num_proc;


    struct algorithm_output output;
    output.Avg_waiting_time = (float)total_wt / (float)num_proc;
    output.Avg_turnaround_time = (float)total_tat / (float)num_proc;
    output.Avg_response_time = (float)total_wt / (float)num_proc;

    return output;
    }




int main()
{
   process_total processes_input;
    algorithm_output alg_out1, alg_out2, alg_out3, alg_out4;
    processes_input = read_from_file();
    int size = processes_input.N;

    alg_out1 = FCFS(processes_input.processes, size);
    alg_out2 = Preemptive_SJF(processes_input.processes, size);
    alg_out3 = Non_preemptive_SJF(processes_input.processes, size);
    //alg_out4 = round_roubin(processes_input.processes, size);
    printf("\nProcess\t    Burst Time    \tWaiting Time\t\tTurnaround Time\t \t Response Time\n");
    for (int i = 0; i < size; i++)
    {
        //processes_input[i].turnaround_time = processes_input[i].burst_time + processes_input[i].waiting_time;
        //total += processes[i].turnaround_time;
        cout << processes_input.processes[i].proc_id << "\t\t" << processes_input.processes[i].burst_time << "\t\t\t" << processes_input.processes[i].waiting_time << "\t\t\t" << processes_input.processes[i].waiting_time << "\t\t\t" << processes_input.processes[i].turnaround_time << "\n";
    }




    cout << "the average waiting time for the FCFS algorithm is: \t" << alg_out1.Avg_waiting_time << endl;
    cout << "the average turnaround time for the FCFS algorithm is: \t" << alg_out1.Avg_turnaround_time << endl;
    cout << "the average tutime for the FCFS algorithm is: \t" << alg_out1.Avg_turnaround_time << endl;


    cout << "the average waiting time for the Preemptive_SJF algorithm is: \t" << alg_out2.Avg_waiting_time << endl;
    cout << "the average turnaround time for the Preemptive_SJF algorithm is: \t" << alg_out2.Avg_turnaround_time << endl;
    cout << "the average tutime for the Preemptive_SJF algorithm is: \t" << alg_out2.Avg_turnaround_time << endl;

    cout << "the average waiting time for the Non_preemptive_SJF algorithm is: \t" << alg_out3.Avg_waiting_time << endl;
    cout << "the average turnaround time for the Non_preemptive_SJF algorithm is: \t" << alg_out3.Avg_turnaround_time << endl;
    cout << "the average tutime for the Non_preemptive_SJF algorithm is: \t" << alg_out3.Avg_turnaround_time << endl;

    //cout << "the average waiting time for the round_roubin algorithm is: \t" << alg_out4.Avg_waiting_time << endl;
    //cout << "the average turnaround time for the round_roubin algorithm is: \t" << alg_out4.Avg_turnaround_time << endl;
    //cout << "the average tutime for the round_roubin algorithm is: \t" << alg_out4.Avg_turnaround_time << endl;





    return 0;
}





