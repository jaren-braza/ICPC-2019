#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    int roomWidth;
    int partitions;

    cin >> roomWidth >> partitions;
    
    vector<int> locations;

    locations.push_back(0);

    for (int i = 0; i < partitions; i++) {
        int location;
        cin >> location;
        locations.push_back(location);
    }

    locations.push_back(roomWidth);
    
    set<int> uniqueWidths;

    for (int range = 1; range <= partitions + 1; range++) {
        for (int i = 0; i < locations.size() - range; i++) {
            uniqueWidths.insert(locations[i + range] - locations[i]);
        }
    }

    for (auto width : uniqueWidths) {
        cout << width << " ";
    }

    return 0;
}