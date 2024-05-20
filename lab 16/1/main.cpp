#include <iostream>
#include <vector>

using namespace std;

class Train {
public:
    int trainNumb;
    string station;
    double trip;
    int departureHour;
    int departureMinute;
    int ariveHour;
    int ariveMinute;
    int timeInTrip;

    Train(int trainNumb, string station, double tripDistance, int depHour, int depMin,
          int ariveHour, int ariveMinute, int timeInTrip) : trainNumb(trainNumb),
                                                            station(station), trip(tripDistance),
                                                            timeInTrip(timeInTrip) {
        if (depHour >= 0 && depHour <= 23 && depMin >= 0 && depMin <= 59
            && ariveHour >= 0 && ariveHour <= 23 && ariveMinute >= 0 && ariveMinute <= 59) {
            departureHour = depHour;
            departureMinute = depMin;
            this->ariveHour = ariveHour;
            this->ariveMinute = ariveMinute;
        } else {
            throw invalid_argument("Invalid time");
        }
    }
};

int partition(vector<Train> &array, int low, int high) {
    int pivotValue=array[high].timeInTrip;
    int i=low;
    for(int j=low; j<high; j++) {
        if(array[j].timeInTrip<=pivotValue) {
            swap(array[i], array[j]);
            i++;
        }
    }
    swap(array[i], array[high]);
    return i;
}

void quickSortRecursion(vector<Train> &array, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(array, low, high);
        quickSortRecursion(array, low, pivotIndex - 1);
        quickSortRecursion(array, pivotIndex + 1, high);
    }
}

void quickSort(vector<Train> &array) {
    quickSortRecursion(array, 0, array.size() - 1);
}

int main() {
    vector<Train> myTrain;
    Train train1(1, "Lviv", 92, 12, 12, 15, 16, 92);
    Train train2(2, "Chernivtsi", 120, 12,52, 16, 17, 122);
    Train train3(3, "Ivano-Frankivsk", 30, 9, 59, 11, 17, 100);
    myTrain.push_back(train1);
    myTrain.push_back(train2);
    myTrain.push_back(train3);
    quickSort(myTrain);
    cout<<"Train number: "<<myTrain[myTrain.size()-1].trainNumb<<endl;
    cout<<"Station: "<<myTrain[myTrain.size()-1].station<<endl;
    cout<<"Duration: "<<myTrain[myTrain.size()-1].timeInTrip<<" min"<<endl;
}
