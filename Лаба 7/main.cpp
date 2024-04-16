#include <iostream>
using namespace std;

struct stack{
    double data = (rand()%171-60)/10.0;
    stack* next;
}*first{};

void addStack(){
    stack* newStack = new stack;
    if(first== nullptr){
        first=newStack;
        newStack->next= nullptr;
    }
    else {
        newStack->next = first;
        first=newStack;
    }
}
void print(){
    for(stack *manip=first; manip!= nullptr; manip=manip->next ){
        cout<<manip->data;
        cout<<endl;
    }
}
void deleteLowerTarget(int target){
    stack* manip=first;
    while(manip!= nullptr && manip->next!= nullptr) {
        if(manip->next->data<target){
            stack* toDelete=new stack;
            toDelete=manip->next;
            manip->next=toDelete->next;
            delete toDelete;
        }
        else if(manip==first && manip->data<target){
            first=manip->next;
            delete manip;
            manip=first;
        }
        else manip=manip->next;

    }

}
double findAvgOfStack(){
    int counter=0;
    double avg=0;
    for (stack* manip = first;  manip!= nullptr ; manip=manip->next) {
        counter++;
        avg+=manip->data;
    }
    avg/=counter;
    return avg;
}
int main() {
    cout<<"Total amount of stacks:";
    int counter;
    cin>>counter;
    srand(time(nullptr));
    for (int i = 0 ; i <counter ; i++) {
        addStack();
    }
    print();
    cout<<"Input number which all stacks must be equal or higher than it:";
    int target;
    cin>>target;
    deleteLowerTarget(target);
    cout<<"============"<<endl;
    print();
    cout<<"Average of left numbers is "<<findAvgOfStack();



}
