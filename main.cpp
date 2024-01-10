#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

#define SIZE 5
#define LINE_MAX 1024

struct PSimulator {
    int Name;//Name
    int burstT; // Burst-Time
    int arrivalT; // Arrival-Time
    int waitingT; // Waiting-Time
    int p;     // Priority
    int sr;    // Show Result
};
void FCFserve(std::vector<PSimulator>& processes) {
    std::sort(processes.begin(),processes.end(), [](const PSimulator& a, const PSimulator& b) {
        return a.arrivalT < b.arrivalT;
    });
    int totalWaitingTime = 0;

    for (int i = 1; i < SIZE; i++) {
        processes[i].waitingT = processes[i - 1].burstT + processes[i - 1].arrivalT + processes[i - 1].waitingT - processes[i].arrivalT;
        totalWaitingTime += processes[i].waitingT;
    }
    double averageWaitingTime = static_cast<double>(totalWaitingTime) / SIZE;

    std::ofstream outputFile("output.txt", std::ios::app);
    outputFile << "\nScheduling Method: First Come First Served\nProcess Waiting Times:\n";

    for (int i = 0; i < SIZE; i++) {
        outputFile << "\nP" << processes[i].Name << ": " << processes[i].waitingT << " ms";
    }

    outputFile << "\nAverage waiting time: " << averageWaitingTime << " ms\n";
    std::cout << "\nOutput is stored in the output file\n";
}

void SJF(std::vector<PSimulator>& processes) {
    std::sort(processes.begin(), processes.end(), [](const PSimulator& a, const PSimulator& b) {
        return a.burstT < b.burstT;
    });

    int totalWaitingTime = 0;

    for (int i = 1; i < SIZE; i++) {
        processes[i].waitingT = processes[i - 1].burstT + processes[i - 1].arrivalT + processes[i - 1].waitingT;
        totalWaitingTime += processes[i].waitingT;
    }

    double averageWaitingTime = static_cast<double>(totalWaitingTime) / SIZE;

    std::ofstream outputFile("output.txt", std::ios::app);
    outputFile << "\nScheduling Method: Shortest Job First\nProcess Waiting Times:\n";

    for (int i = 0; i < SIZE; i++) {
        outputFile << "\nP" << processes[i].Name << ": " << processes[i].waitingT << " ms";
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
        processes[i].waitingT = processes[i - 1].burstT + processes[i - 1].arrivalT + processes[i - 1].waitingT;
        totalWaitingTime += processes[i].waitingT;
    }
    double averageWaitingTime = static_cast<double>(totalWaitingTime) / SIZE;

    std::ofstream outputFile("output.txt", std::ios::app);
    outputFile << "\nScheduling Method: Priority Scheduling\nProcess Waiting Times:\n";

    for (int i = 0; i < SIZE; i++) {
        outputFile << "\nP" << processes[i].Name << ": " << processes[i].waitingT << " ms";
    }

    outputFile << "\nAverage waiting time: " << averageWaitingTime << " ms\n";
    std::cout << "\nOutput is stored in the output file\n";
}

void RoundR(std::vector<PSimulator>& processes, int quantumTime) {
    std::queue<PSimulator> PSimulatorQueue;
    int currentTime = 0;

    while (!PSimulatorQueue.empty() || currentTime < SIZE) {
        while (currentTime < SIZE && processes[currentTime].arrivalT <= currentTime) {
            PSimulatorQueue.push(processes[currentTime]);
            currentTime++;
        }

        if (!PSimulatorQueue.empty()) {
            PSimulator currentPSimulator = PSimulatorQueue.front();
            PSimulatorQueue.pop();

            int executionTime = std::min(quantumTime, currentPSimulator.burstT);
            currentPSimulator.burstT -= executionTime;

            for (int i = currentTime; i < currentTime + executionTime; i++) {
                processes[i].waitingT += executionTime;
            }

            currentTime += executionTime;

            if (currentPSimulator.burstT > 0) {
                PSimulatorQueue.push(currentPSimulator);
            }
        } else {
            currentTime++;
        }
    }

    int totalWaitingTime = 0;
    for (int i = 0; i < SIZE; i++) {
        totalWaitingTime += processes[i].waitingT;
    }

    double averageWaitingTime = static_cast<double>(totalWaitingTime) / SIZE;

    std::ofstream outputFile("output.txt", std::ios::app);
    outputFile << "\nScheduling Method: RoundR\nProcess Waiting Times:\n";

    for (int i = 0; i < SIZE; i++) {
        outputFile << "\nP" << processes[i].Name << ": " << processes[i].waitingT << " ms";
    }

    outputFile << "\nAverage waiting time: " << averageWaitingTime << " ms\n";
    std::cout << "\nOutput is stored in the output file\n";
}

int main(int argc, char** argv) {
    std::vector<PSimulator> processes(SIZE);

    int i = 0;
    int mode = 0;
    int option = 0;
    int option2 = 0;
    int quantumTime = 0;

    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "file error input file\n";
        return 1;
    }

    while (inputFile >> processes[i].burstT >> processes[i].arrivalT >> processes[i].p) {
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
        switch (option) {
            case 1:
                if (mode == 0)
                    std::cout << "\n\n\n\n MODE : Preemptive\n";
                else if (mode == 1)
                    std::cout << "\nMODE : Non-Preemptive\n";

                std::cout << "1) FCFserve\n";
                std::cout << "2) SJF\n";
                std::cout << "3) Priority Scheduling\n";
                std::cout << "4) RoundR\n";
                std::cout << "5) Back\n";
                std::cout << "\n\n";
                std::cout << "Option> ";
                std::cin >> option2;

                switch (option2) {
                    case 1:
                        FCFserve(processes);
                        break;
                    case 2:
                        SJF(processes);
                        break;
                    case 3:
                        PriorityScheduling(processes);
                        break;
                    case 4:
                        std::cout << "Enter Quantum Time: ";
                        std::cin >> quantumTime;
                        RoundR(processes, quantumTime);
                        break;
                    case 5:
                        break;
                    default:
                        std::cout << "Invalid Option Please select From 1 - 5\n";
                        break;
                }
                           break;
            case 2:
                mode = 0;
                break;
            case 3:
                mode = 1;
                break;
            case 4:
                resultFile.open("output.txt");
                std::cout << resultFile.rdbuf();
                resultFile.close();
                break;
            case 5:
                break;
            default:
                std::cout << "\n opps Invalid entry! Please pick between 1 - 5 \n";
                break;
        }
    } while (option != 5);

    return 0;
}
