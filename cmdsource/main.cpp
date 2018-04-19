#include "../Algorithms/headers/algorithm.h"
#include "../client/src/TCPClient.h"

double convertTimeToScore(double time) {
    double score = (.001/time)*10000000;
    return score;
}
int main(int argc, char *argv[])
{
    std::cout << "<<<Press Enter to Begin>>>\n";
    std::cin.ignore();
    std::vector<Algorithm> algList;

    double times[5];
    double scores[5];
    std::string names[5];
    int count = 0;
    algList.push_back(new NBody());
    algList.push_back(new PiDigits());
    algList.push_back(new Mandelbrot());
    algList.push_back(new SpectralNorm());
    algList.push_back(new BinaryTrees());

    std::cout << "Running!\n";
    double TotalTime = 0;
    double TotalScore = 0;

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
    count = 0;
    std::cout << "\n\n";
    std::cout.flush();

    for (double i: times) {
        std::cout << names[count] << " | ";
        std::cout << i << "\n";
        count++;
    }
    count = 0;

    std::cout.flush();
    std::cout << "Submit? (y/n)\n";
    std::cout.flush();
    char choice;
    std::cin >> choice;

    if(choice == 'y') {
        std::cout << "Give a name for your run: ";
        std::string str;
        std::cin >> str;
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
        TCPClient tcp;

        if(tcp.setup("72.219.21.177", 47002) != true ) {
            std::cout << "Failure!";
        }
        else {
            srand(time(NULL));
            std::cout << str;
            tcp.Send(str);

            string rec = tcp.receive();

            if( rec != "" )
            {
                std::cout << "Server Response:" << rec;
                std::cout.flush();
                tcp.exit();
            }
            else {
                std::cout << "Failure!";
                std::cout.flush();
                tcp.exit();
            }
        }
    }
}
