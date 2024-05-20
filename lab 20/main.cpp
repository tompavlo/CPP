#include <iostream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <Windows.h>

using namespace std;

float computeCalories(float meat, float flour, float milk, float sugar)
{
    return 1500 * meat + 5000 * flour + 5000 * milk + 4000 * sugar;
}

struct TimeStruct
{
    int hours;
    int minutes;
};
struct Course
{
    string title;
    TimeStruct startTime;
    TimeStruct endTime;
    void inputData()
    {
        cout << "Enter course title, start time, end time: ";
        cin >> title >> startTime.hours >> startTime.minutes >> endTime.hours >> endTime.minutes;
    }
    void displayData()
    {
        cout <<"\nTitle: " << title << "\nStart: " << startTime.hours << ":" << endTime.minutes << "\nEnd: " <<endTime.hours << ":" << endTime.minutes << endl;
    }
};

bool compareEndTime(const Course& a, const Course& b)
{
    if (a.endTime.hours != b.endTime.hours)
        return a.endTime.hours < b.endTime.hours;
    return a.endTime.minutes < b.endTime.minutes;
}

void selectCourses(vector<Course>& courses)
{
    sort(courses.begin(), courses.end(), compareEndTime);
    vector<Course> selectedCourses;
    selectedCourses.push_back(courses[0]);
    int lastEndTimeHour = courses[0].endTime.hours;
    int lastEndTimeMinute = courses[0].endTime.minutes;
    for (int i = 1; i < courses.size(); i++)
    {
        if (courses[i].startTime.hours > lastEndTimeHour || (courses[i].startTime.hours == lastEndTimeHour && courses[i].startTime.minutes >= lastEndTimeMinute))
        {
            selectedCourses.push_back(courses[i]);
            lastEndTimeHour = courses[i].endTime.hours;
            lastEndTimeMinute = courses[i].endTime.minutes;
        }
    }
    cout << "Max number of courses: " << selectedCourses.size() << endl;
    cout << "Selected courses:" << endl;
    for (int i=0;i< selectedCourses.size(); i++)
        selectedCourses[i].displayData();
}

int main()
{
    int option;
    cout << "Choose an option:\n1) Calorie count\n2) Lesson time ";
    cin >> option;

    switch (option)
    {
    case 1:
    {
        float maxCalories=0;
        float bestMeat, bestFlour, bestMilk, bestSugar;
        for (float meat = 0; meat <= 35; meat += 0.1)
        {
            for (float flour = 0; flour <= (35 - meat); flour += 0.1)
            {
                for (float milk = 0; milk <= (35 - meat - flour); milk += 0.1)
                {
                    float sugar = 35 - meat - flour - milk;
                    if (meat + 1.5 * flour + 2 * milk + sugar <= 45 && meat >= 2 * flour && flour >= milk && milk >= 8 * sugar)
                    {
                        float calories = computeCalories(meat, flour, milk, sugar);
                        if (calories > maxCalories)
                        {
                            maxCalories = calories;
                            bestMeat = meat;
                            bestFlour = flour;
                            bestMilk = milk;
                            bestSugar = sugar;
                        }
                    }
                }
            }
        }
        cout << "Meat: " << bestMeat << "\nFlour: " << bestFlour << "\nMilk: " << bestMilk << "\nSugar: "  << bestSugar;
        cout << "\nMax calories: " << maxCalories;
        break;
    }
    case 2:
    {
        int num;
        cout << "Enter the number of courses: ";
        cin >> num;
        vector<Course> courses(num);
        for (int i = 0; i < num; ++i)
        {
            courses[i].inputData();
            while (courses[i].startTime.hours > 23 && courses[i].startTime.hours < 0 && courses[i].endTime.hours > 23 && courses[i].endTime.hours < 0 && courses[i].startTime.minutes > 59 || courses[i].startTime.minutes < 0 || courses[i].endTime.minutes > 59 || courses[i].endTime.minutes < 0)
            {
                cerr << "Incorrect input time." << endl;
                courses[i].inputData();
            }
        }
        selectCourses(courses);
        break;
    }
    default:
    {
        cerr << "Error. Choose 1 or 2";
        break;
    }
    }
    return 0;
}
