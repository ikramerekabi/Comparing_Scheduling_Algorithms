


#include <iostream>
#include <fstream>
//#include <bits/stdc++.h>

using namespace std;
//extern int max_priority = 40; 

void write_to_file() {
    
    ofstream myfile;
    myfile.open("example.csv");
    myfile << "a,b,c,\n";
    myfile.close();

}
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
    int i, smallest, count = 0, time;
    int* temp = new int[num_proc];
    double wait_time = 0, turnaround_time = 0, end;
    float average_waiting_time, average_turnaround_time;
    processes[9].burst_time = 9999;
    for (i = 0; i < num_proc; i++)
    {
        temp[i] = processes[i].burst_time;
    }
    for (time = 0; count != num_proc; time++)
    {
        smallest = 9;
        for (i = 0; i < num_proc; i++)
        {
            if (processes[i].arrival_time <= time && processes[i].burst_time < processes[smallest].burst_time && processes[i].burst_time > 0)
            {
                smallest = i;
            }
        }
        processes[smallest].burst_time--;
        if (processes[smallest].burst_time == 0)
        {
            count++;
            end = time + 1;
            wait_time = wait_time + end - processes[smallest].arrival_time - temp[smallest];
            turnaround_time = turnaround_time + end - processes[smallest].arrival_time;
        }
    }
    average_waiting_time = wait_time / num_proc;
    average_turnaround_time = turnaround_time / num_proc;

    struct algorithm_output output;
    output.Avg_waiting_time = wait_time;
    output.Avg_turnaround_time = turnaround_time;
    output.Avg_response_time = wait_time;

    return output;
}




int main()
{
    int n;
    cout << "Enter the number of processes\n";
    cin >> n;
    process* processes_input = new process[n];
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
    printf("\nProcess\t    Burst Time    \tWaiting Time\t\tTurnaround Time\t \t Response Time\n");
    for (int i = 0; i < n; i++)
    {
        //processes_input[i].turnaround_time = processes_input[i].burst_time + processes_input[i].waiting_time;
        //total += processes[i].turnaround_time;
        cout << processes_input[i].proc_id << "\t\t" << processes_input[i].burst_time << "\t\t\t" << processes_input[i].waiting_time << "\t\t\t" << processes_input[i].waiting_time << "\t\t\t" << processes_input[i].turnaround_time << "\n";
    }




    cout << "the average waiting time is: \t" << alg_out.Avg_waiting_time << endl;
    cout << "the average turnaround time is: \t" << alg_out.Avg_turnaround_time << endl;
    cout << "the average tutime is: \t" << alg_out.Avg_turnaround_time << endl;



    return 0;
}





