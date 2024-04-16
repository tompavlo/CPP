#include <iostream>

using namespace std;

struct song {
    string typeOfMedium;
    string name;
    string artist;
    int duration;
    int amountOfReplays;
    int price;
    song *next;

} *first;

void addStack(string typeOfMedium,
              string name,
              string artist,
              int duration,
              int amountOfReplays,
              int price) {
    song *newSong = new song;
    newSong->typeOfMedium = typeOfMedium;
    newSong->name = name;
    newSong->artist = artist;
    newSong->duration = duration;
    newSong->amountOfReplays = amountOfReplays;
    newSong->price = price;
    if (first == nullptr) {
        first = newSong;
        newSong->next = nullptr;
    } else {
        newSong->next = first;
        first = newSong;
    }

}

int totalDurationOfArtistSongs(string targetArtist) {
    int totalDuration = 0;
    for (song *manip = first; manip != nullptr; manip = manip->next) {
        if (manip->artist == targetArtist)
            totalDuration += manip->duration;
    }
    return totalDuration;

}

double averagePrice() {
    double avg = 0;
    int counter = 0;
    for (song *manip = first; manip != nullptr; manip = manip->next) {
        avg += manip->price;
        counter++;
    }
    avg /= counter;
    return avg;
}

int main() {
    string typeOfMedium;
    string name;
    string artist;
    int duration;
    int amountOfReplays;
    int price;
    while (true) {
        cout << "Input type of medium for song(or done to stop input):";
        cin >> typeOfMedium;
        if (typeOfMedium == "done") break;
        cout << "Input song name:";
        cin.ignore();
        getline(cin, name);
        cout << "Input name of artist:";
        getline(cin, artist);
        cout << "Duration of the song in seconds:";
        cin >> duration;
        cout << "Amount of replays:";
        cin >> amountOfReplays;
        cout << "Price of the song:";
        cin >> price;
        addStack(typeOfMedium, name, artist, duration, amountOfReplays, price);
    }
    cout << "Input artist for whom you want count total songs duration:";
    string targetArtist;
    cin.ignore();
    getline(cin, targetArtist);
    cout << targetArtist << " total duration of their songs: " << totalDurationOfArtistSongs(targetArtist);
    cout << "\nAverage price of all songs:" << averagePrice();
}
