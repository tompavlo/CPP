#include <iostream>
#include <vector>

using namespace std;

class TV {
public:
    string manufacture;
    double sizeInInches;
    int price;
    TV(string manufacture, double size, int price) : manufacture(manufacture), sizeInInches(size), price(price){}
    static void sort(vector<TV>& array) {
        int size = array.size();
        for (int gap = size / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < size; i++) {
                TV temp = array[i];
                int j;
                for (j = i; j >= gap && array[j - gap].sizeInInches > temp.sizeInInches; j -= gap) {
                    array[j] = array[j - gap];
                }
                array[j] = temp;
            }
        }

    }
};
int main() {
    vector<TV> tvs = {
        TV("Sony", 55.0, 1200),
        TV("Samsung", 65.0, 1500),
        TV("LG", 50.0, 1000),
        TV("Toshiba", 40.0, 700)
    };

    TV::sort(tvs);

    for (auto tv : tvs) {
        cout << tv.manufacture << " " << tv.sizeInInches << " inches $" << tv.price << endl;
    }
    return 0;
}
