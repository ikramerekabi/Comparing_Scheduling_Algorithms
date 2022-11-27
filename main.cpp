#include <iostream>
//#include <bits/stdc++.h>

using namespace std;
//extern int max_priority = 40; 
struct process {
    string proc_id;
    double arrival_time;
    double burst_time;
    int priority;
    string state;
    double time_quantum;
    double turnaround_time;
    double waiting_time;
    double response_time;
    double submission_time;
    double completion_time;

};
struct algorithm_output {
    double Avg_turnaround_time;
    double Avg_waiting_time;
    double Avg_response_time;

};

void findWaitingTime(process processes[], int n)
{
    // waiting time for first process is 0
   // wt[0] = 0;
    processes[0].waiting_time = 0;

    // calculating waiting time
    for (int i = 1; i < n; i++)
    {
        processes[i].waiting_time = processes[i - 1].burst_time + processes[i - 1].waiting_time;
    }

}

// Function to calculate turn around time
void findTurnAroundTime(process processes[], int n)
//  int processes[], int n,int bt[], int wt[], int tat[])
{
    // calculating turnaround time by adding
    // bt[i] + wt[i]
    for (int i = 0; i < n; i++)
    {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
    }
    // tat[i] = bt[i] + wt[i];
}

//Function to calculate average time
double findavgTime(process processes[], int n)

{
    
    double Average_Waiting_Time;
    double total_waiting_time = 0;
   
    findWaitingTime(processes, n);
    
    for (int i = 0; i < n; i++)
    {
        total_waiting_time = total_waiting_time + processes[i].waiting_time;
        
    }
    Average_Waiting_Time = total_waiting_time / n;
    
    return Average_Waiting_Time;
}

double findavgTurnaroundTime(process processes[], int n)
{
    double Average_Turnaround_Time;
    double total_turnaround_time = 0;
    findTurnAroundTime(processes, n);
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
    //process id's
    // int processes[] = { 1, 2, 3};
    //int n = sizeof processes / sizeof processes[0];

    //Burst time of all processes
   // int  burst_time[] = {10, 5, 8};

    output.Avg_waiting_time = findavgTime(processes, n);
    output.Avg_turnaround_time = findavgTurnaroundTime(processes, n);
    return output;
}
int main()
{
    int n;
    cout << "Enter the number of processes\n";
    cin >> n;
    process *processes_input= new process[n];
    algorithm_output alg_out;
    for (int i = 0; i < n; i++)
    {
        //cout<<"enter the process id\n";
        //cin>>processes_input[i].proc_id; 
        processes_input[i].proc_id = i;

        cout << "enter the process burst time \n";
        cin >> processes_input[i].burst_time;
        cout << "enter the ";
    }

    alg_out = FCFS(processes_input, n);
    printf("\nProcess\t    Burst Time    \tWaiting Time\t\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        //processes_input[i].turnaround_time = processes_input[i].burst_time + processes_input[i].waiting_time;
        //total += processes[i].turnaround_time;
        cout << processes_input[i].proc_id << "\t\t" << processes_input[i].burst_time << "\t\t\t" << processes_input[i].waiting_time << "\t\t\t" << processes_input[i].turnaround_time << "\n";
    }

    
   

    cout << "the average waiting time is: \t" << alg_out.Avg_waiting_time<<endl;
    cout << "the average turnaround time is: \t" << alg_out.Avg_turnaround_time;


    return 0;
}







