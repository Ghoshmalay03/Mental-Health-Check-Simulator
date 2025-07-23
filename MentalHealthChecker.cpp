#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

class user {
    string name;
    vector<string> moodHistory;
public:
    user(string name) {
        this->name = name;
    }
    string getName() {
        return this->name;
    }
    void showMoodHistory() {
        for (int i = 0; i < moodHistory.size(); i++) {
            cout << moodHistory[i];
            if (i != moodHistory.size() - 1) cout << ", ";
        }
        cout << endl;
    }
    void addMoodHistory(string mood) {
        moodHistory.push_back(mood);
    }
};

class QuoteProvider {
    vector<string> quotes = {
        "You are stronger than you think.",
        "Take it one step at a time.",
        "This too shall pass.",
        "Breathe. You're doing okay.",
        "It's okay to ask for help.",
        "You matter. Your feelings are valid.",
        "Progress, not perfection."
    };
public:
    string getRandomQuote() {
        return quotes[rand() % quotes.size()];
    }
};

class CalmActivity {
public:
    void breathingExercise() {
        for (int i = 0; i < 3; i++) {
            cout << "Breathe in..." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
            cout << "Hold..." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            cout << "Breathe out..." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
};

class MoodTracker {
public:
    string askMood(user* user) {
        cout << "Hi " << user->getName() << ", how are you feeling today?" << endl;
        cout << "Options: Happy, Sad, Anxious, Angry, Tired, Excited, Okay" << endl;
        string ans;
        cin >> ans;
        return ans;
    }
};

class Assistant {
    user* obj = nullptr;
    MoodTracker mt;
    QuoteProvider qp;
    CalmActivity ca;
public:
    Assistant(string name) {
        obj = new user(name);
    }

    void startSession() {
        string mood = mt.askMood(obj);
        obj->addMoodHistory(mood);
        cout << "Here's a quote for you: " << qp.getRandomQuote() << endl;

        cout << "Would you like to do some breathing exercise? (y/n): ";
        char ch;
        cin >> ch;
        if (ch == 'y' || ch == 'Y') {
            ca.breathingExercise();
        } else {
            cout << "Thank you for starting the session..." << endl;
        }
    }

    void showMoodHistory() {
        obj->showMoodHistory();
    }
};

int main() {
    srand(time(0)); // Initialize random seed

    cout << "Hi, Welcome to the Mental Health Check-in." << endl;
    cout << "What is your name?" << endl;
    string name;
    cin >> name;

    Assistant as(name);

    while (1) {
        cout << "\n*** Mental Health Check-in Menu ***" << endl;
        cout << "1. Start Session" << endl;
        cout << "2. Show Mood History" << endl;
        cout << "3. Exit" << endl;

        int ch;
        cin >> ch;

        switch (ch) {
        case 1:
            as.startSession();
            break;

        case 2:
            as.showMoodHistory();
            break;

        case 3:
            cout << "Goodbye! Take care of yourself." << endl;
            return 0;

        default:
            cout << "Enter a valid choice..." << endl;
            break;
        }
    }

    return 0;
}
