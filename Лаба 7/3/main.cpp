#include <iostream>
#include <cmath>
using namespace std;
struct queue{
    int data{};
    queue* next;
}*first{}, *last{};

void addQueue(){
    queue* newQueue = new queue;
    newQueue->data=rand()%100;
    if(last== nullptr){
        last=newQueue;
        newQueue->next= nullptr;
        first=newQueue;
    }
    else{
        last->next=newQueue;
        newQueue->next= nullptr;
        last=newQueue;
    }

}
void put100(){
    for(queue* manip=first; manip!= nullptr; manip=manip->next ){
        if(manip->data%2==0){
            queue* newQueue = new queue;
            newQueue->data=100;
            newQueue->next=manip->next;
            manip->next=newQueue;
            manip=manip->next;
        }
    }
}
void print(){
    for(queue* manip=first; manip!= nullptr; manip=manip->next ){
        cout<<manip->data<<' ';
    }
}

double avgGeometrical(){
    double avg=1;
    int counter=0;
    for (queue* manip=first;  manip!= nullptr ; manip=manip->next) {
        avg*=manip->data;
        counter++;
    }
    avg=pow(avg, 1.0/counter);
    return avg;
}

int main() {
    srand(time(nullptr));
    cout<<"Input amount of queue:";
    int amount;
    cin>>amount;
    for (int i = 0; i < amount; ++i) {
        addQueue();
    }
    print();
    put100();
    cout<<"\n=============\n";
    print();
    cout<<"\nAverage of geometrical: "<<avgGeometrical();
    queue* manip=first;
    while (manip!= nullptr){
        queue* next=manip->next;
        delete manip;
        manip=next;
    }


}
