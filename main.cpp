#include <iostream>
#include <vector>
using namespace std;
extern int max_priority = 40;


struct process {
    int proc_id;

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
            int running=0;
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
            total+= running_processes[i].response_time;
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








//Preemptive Shortest Job First(becomes Shortest Remaining Time First, SRTF)
//Round Robin(RR)
//First Come First Served(FCFS)
//Multilevel Feedback Queue(MLFQ)



int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    process* processes = new process[n];

    processes[0].proc_id = 1;
    processes[0].arrival_time = 2;
    processes[0].burst_time = 6;

    processes[1].proc_id = 2;
    processes[1].arrival_time = 5;
    processes[1].burst_time = 2;

    processes[2].proc_id = 3;
    processes[2].arrival_time = 1;
    processes[2].burst_time = 8;

    processes[3].proc_id = 4;
    processes[3].arrival_time = 0;
    processes[3].burst_time = 3;

    processes[4].proc_id = 5;
    processes[4].arrival_time = 4;
    processes[4].burst_time = 4;

    Non_preemptive_SJF(processes, n);
    return 0;
}


