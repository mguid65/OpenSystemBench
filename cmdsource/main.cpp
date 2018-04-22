#include "../Algorithms/headers/algorithm.h"
#include "../client/src/TCPClient.h"
#include <iomanip>

void submitResult(std::string str) {
    TCPClient tcp;

    if(tcp.setup("72.219.21.177", 47002) != true ) {    //checks if open connection was succesful
        std::cout << "\nFailure: Unable to Connect to Server\n";
        std::cout.flush();
    }
    else {
        srand(time(NULL));
        std::cout << str;
        tcp.Send(str);

        string rec = tcp.receive();

        if( rec != "" )
        {
            std::cout << "\nServer Response: " << rec << "\n";
            std::cout.flush();
            tcp.exit();
        }
        else {
            std::cout << "\nFailure: Empty Response\n";
            std::cout.flush();
            tcp.exit();
        }
    }
}

double convertTimeToScore(double time) { // takes lowerisbetter time to higherisbetter score
    return (.001/time)*10000000;
}

int main() {
    std::cout << "<<<Press Enter to Begin>>>\n";
    std::cin.ignore();

    //Allocate arrays to hold output

    double times[5];
    double scores[5];
    std::string names[5];

    //create indexing variable count
    int count = 0;

    //Create a vector of Algorithms to run.
    std::vector<Algorithm> algList;

    algList.push_back(new NBody());
    algList.push_back(new PiDigits());
    algList.push_back(new Mandelbrot());
    algList.push_back(new SpectralNorm());
    algList.push_back(new BinaryTrees());

    std::cout << "Running...\n";

    //Create variables to accumulate total time and score
    double TotalTime = 0;
    double TotalScore = 0;

    // Run each algorithm and record data
    for (Algorithm &alg : algList ) {
        names[count] = alg.getName();
        std::cout << names[count] << "\n";
        std::cout.flush();
        alg.runAlgorithm();

        times[count] = alg.getTime();
        scores[count] = convertTimeToScore(times[count]);

        TotalTime += times[count];
        TotalScore += scores[count];


        std::cout << times[count] << "\n";
        std::cout.flush();
        count++;
    }
    //reset indexing variable count to 0
    count = 0;
    std::cout << "\n\n";
    std::cout.flush();

    //print simple table to std output
    for (double i: times) {
        std::cout << std::left << std::setw(14) << names[count] << " | ";
        std::cout << std::left << std::setw(10) << i << " | ";
        std::cout << scores[count] << "\n";
        count++;
    }
    std::cout << std::left << std::setw(14) << "Totals" << " | ";
    std::cout << std::left << std::setw(10) << TotalTime << " | ";
    std::cout << TotalScore << "\n";
    //reset count to 0
    count = 0;

    std::cout.flush();
    std::cout << "\nSubmit to leaderboard? (y/n)\n";
    std::cout.flush();
    char choice;
    std::cin >> choice;

    if(choice == 'y') {
        //build data string for submission
        std::cout << "Give a name for your run (1 - 40 characters): ";
        std::string str;
        while(true) {
            std::cin >> str;
            if(str.length() < 1 || str.length() > 40) {
                std::cout << "Invalid Name: Names must be between 1 and 40 characters!\n";
                std::cout.flush();
                std::cout << "Give a name for your run: ";
                std::cout.flush();
            } else { break; }
        }

        str.append(";");
        for(std::string s: names) {
            str.append(s);
            str.append(";");
            str.append(std::to_string(times[count]));
            str.append(";");
            str.append(std::to_string(scores[count]));
            str.append(";");
            count++;
        }
        str.append(std::to_string(TotalTime));
        str.append(";");
        str.append(std::to_string(TotalScore));
        str.append(";");

        std::cout << "Is this machine overclocked? (y/n)\n";
        std::cout.flush();

        char oc;
        std::cin >> oc;

        if(oc == 'y') {
            str.append("1");
        }
        else {
            str.append("0");
        }
        std::cout << str << "\n";
        std::cout.flush();

        std::cout << "Are you sure you want to submit? (y/n)\n";
        std::cout.flush();
        std::cin >> choice;

        if(choice == 'y') {
            submitResult(str);
        }
    }
}
