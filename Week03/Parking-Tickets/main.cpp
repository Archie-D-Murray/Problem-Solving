#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct CarData {
    int visited = 0;
    int arrival = 0;
};

int tickets(std::vector<std::string>& registrations, std::vector<int>& times) {

    const int maxStay = 60;

    std::unordered_map<std::string, CarData> cars;
    std::unordered_set<std::string> ticketed;

    assert(registrations.size() == times.size());
    int tickets = 0;
    for (size_t i = 0; i < registrations.size(); i++) {
        CarData& data = cars[registrations[i]];
        data.visited++;

        if (data.visited % 2 == 0) {
            if (times[i] - data.arrival >= maxStay && ticketed.count(registrations[i]) == 0) {
                tickets++;
                ticketed.insert(registrations[i]);

                std::cout << "Ticketed: " << registrations[i] << " for reason: Overstay\n";
            }
            data.arrival = times[i];
        } else {
            if (data.arrival != 0) {
                if (times[i] - data.arrival <= maxStay && ticketed.count(registrations[i]) == 0) {
                    ticketed.insert(registrations[i]);
                    tickets++;
                    std::cout << "Ticketed: " << registrations[i] << " for reason: Came back too early\n";
                }
            }
            data.arrival = times[i];
        }
    }
    return tickets;
}

int main(void) {
    std::vector<std::vector<std::string>> registrationTests = {
        { "RG73ZYG", "AW11LFM", "RG73ZYG", "YE17FBX", "AW11LFM", "YE17FBX", "MS16XVT", "PL19FHT", "DJ64RAY", "AW11LFM", "DJ64RAY", "PL19FHT", "MS16XVT", "PL19FHT", "AW11LFM", "PL19FHT", "MS16XVT", "MS16XVT", "GS62CUS", "GS62CUS", "ZG61KHW", "ZG61KHW", "CC68AGT", "EC20TGG", "EC20TGG", "CC68AGT" },
    };
    std::vector<std::vector<int>> timeTests = {
        { 8, 81, 113, 116, 119, 180, 189, 209, 216, 218, 229, 251, 275, 276, 284, 308, 369, 393, 544, 561, 661, 766, 960, 972, 1004, 1010 },
    };

    std::unordered_map<std::string, std::vector<int>> mapped;

    for (size_t i = 0; i < registrationTests.size(); i++) {
        for (size_t j = 0; j < registrationTests[i].size(); j++)
        mapped[registrationTests[i][j]].push_back(timeTests[i][j]);
    }

    for (auto pair : mapped) {
        std::cout << "Reg: " << pair.first << " Time: [ ";
        for (size_t i = 0; i < pair.second.size(); i++) {
            if (i < pair.second.size() - 1) {
                std::cout << pair.second[i] << ", ";
            } else {
                std::cout << pair.second[i] << " ";
            }
        }

        std::cout << "]\n";
     }

    for (size_t i = 0; i < registrationTests.size(); i++) {
        int ticketCount = tickets(registrationTests[i], timeTests[i]);
        std::cout << "Tickets: " << ticketCount << "\n";
    }
}


