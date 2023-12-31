#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

#define SIZE 5
#define LINE_MAX 1024

struct PSimulator {
    int Name;//Name
    int bTime; // Burst Time
    int aTime; // Arrival Time
    int wTime; // Waiting Time
    int pr;     // Priority
    int sr;    // Show Result
};

void FCFserve(std::vector<PSimulator>& processes) {
    std::sort(processes.begin(),processes.end(), [](const PSimulator& a, const PSimulator& b) {
        return a.aTime < b.aTime;
    });

    int totalWaitingTime = 0;

    for (int i = 1; i < SIZE; i++) {
        processes[i].wTime = processes[i - 1].bTime + processes[i - 1].aTime + processes[i - 1].wTime - processes[i].aTime;
        totalWaitingTime += processes[i].wTime;
    }

    double averageWaitingTime = static_cast<double>(totalWaitingTime) / SIZE;

    std::ofstream outputFile("output.txt", std::ios::app);
    outputFile << "\nScheduling Method: First Come First Served\nProcess Waiting Times:\n";

    for (int i = 0; i < SIZE; i++) {
        outputFile << "\nP" << processes[i].Name << ": " << processes[i].wTime << " ms";
    }

    outputFile << "\nAverage waiting time: " << averageWaitingTime << " ms\n";
    std::cout << "\nOutput is stored in the output file\n";
}

void SJF(std::vector<PSimulator>& processes) {
    std::sort(processes.begin(), processes.end(), [](const PSimulator& a, const PSimulator& b) {
        return a.bTime < b.bTime;
    });

    int totalWaitingTime = 0;

    for (int i = 1; i < SIZE; i++) {
        processes[i].wTime = processes[i - 1].bTime + processes[i - 1].aTime + processes[i - 1].wTime;
        totalWaitingTime += processes[i].wTime;
    }

    double averageWaitingTime = static_cast<double>(totalWaitingTime) / SIZE;

    std::ofstream outputFile("output.txt", std::ios::app);
    outputFile << "\nScheduling Method: Shortest Job First\nProcess Waiting Times:\n";

    for (int i = 0; i < SIZE; i++) {
        outputFile << "\nP" << processes[i].Name << ": " << processes[i].wTime << " ms";
    }

    outputFile << "\nAverage waiting time: " << averageWaitingTime << " ms\n";
    std::cout << "\nOutput is stored in the output file\n";
}

void PriorityScheduling(std::vector<PSimulator>& processes) {
    std::sort(processes.begin(), processes.end(), [](const PSimulator& a, const PSimulator& b) {
        return a.p < b.p;
    });

    int totalWaitingTime = 0;

    for (int i = 1; i < SIZE; i++) {
        processes[i].wTime = processes[i - 1].bTime + processes[i - 1].aTime + processes[i - 1].wTime;
        totalWaitingTime += processes[i].wTime;
    }

    double averageWaitingTime = static_cast<double>(totalWaitingTime) / SIZE;

    std::ofstream outputFile("output.txt", std::ios::app);
    outputFile << "\nScheduling Method: Priority Scheduling\nProcess Waiting Times:\n";

    for (int i = 0; i < SIZE; i++) {
        outputFile << "\nP" << processes[i].Name << ": " << processes[i].wTime << " ms";
    }

    outputFile << "\nAverage waiting time: " << averageWaitingTime << " ms\n";
    std::cout << "\nOutput is stored in the output file\n";
}

void RoundR(std::vector<PSimulator>& processes, int quantumTime) {
    std::queue<PSimulator> PSimulatorQueue;
    int currentTime = 0;

    while (!PSimulatorQueue.empty() || currentTime < SIZE) {
        while (currentTime < SIZE && processes[currentTime].aTime <= currentTime) {
            PSimulatorQueue.push(processes[currentTime]);
            currentTime++;
        }

        if (!PSimulatorQueue.empty()) {
            PSimulator currentPSimulator = PSimulatorQueue.front();
            PSimulatorQueue.pop();

            int executionTime = std::min(quantumTime, currentPSimulator.bTime);
            currentPSimulator.bTime -= executionTime;

            for (int i = currentTime; i < currentTime + executionTime; i++) {
                processes[i].wTime += executionTime;
            }

            currentTime += executionTime;

            if (currentPSimulator.bTime > 0) {
                PSimulatorQueue.push(currentPSimulator);
            }
        } else {
            currentTime++;
        }
    }

    int totalWaitingTime = 0;
    for (int i = 0; i < SIZE; i++) {
        totalWaitingTime += processes[i].wTime;
    }

    double averageWaitingTime = static_cast<double>(totalWaitingTime) / SIZE;

    std::ofstream outputFile("output.txt", std::ios::app);
    outputFile << "\nScheduling Method: RoundR\nProcess Waiting Times:\n";

    for (int i = 0; i < SIZE; i++) {
        outputFile << "\nP" << processes[i].Name << ": " << processes[i].wTime << " ms";
    }

    outputFile << "\nAverage waiting time: " << averageWaitingTime << " ms\n";
    std::cout << "\nOutput is stored in the output file\n";
}

int main(int argc, char** argv) {
    std::vector<PSimulator> processes(SIZE);

    int i = 0;
    int mode = 0;
    int option = 0;
    int option1 = 0;
    int quantumTime = 0;

    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file\n";
        return 1;
    }

    while (inputFile >> processes[i].bTime >> processes[i].aTime >> processes[i].p) {
        processes[i].Name = i + 1;
        i++;
    }
 inputFile.close(); 
    std::ofstream outputFile("output.txt", std::ios::trunc);

    std::cout << "\t\t\t\t\t CPU-Scheduler Simulator\n";

    std::ifstream resultFile; // show-here
     do {
        if (mode == 0)
            std::cout << "\nMODE : Preemptive\n\n";
        else if (mode == 1)
            std::cout << "\nMODE : Non-Preemptive\n";

        std::cout << "1) Scheduling Method (None)\n";
        std::cout << "2) Preemptive Mode\n";
        std::cout << "3) Non-Preemptive Mode\n";
        std::cout << "4) Show Result\n";
        std::cout << "5) End Program\n";
        std::cout << "Option> ";
        std::cin >> option;
