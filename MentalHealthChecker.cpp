#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <limits>

using namespace std;

// -------- User Class --------
class User {
    string name;
    vector<string> moodHistory;

public:
    User(string username) {
        name = username;
    }

    string getName() {
        return name;
    }

    void addMood(string mood) {
        moodHistory.push_back(mood);
    }

    void showMoodHistory() {
        cout << "\n🧠 Mood History for " << name << ":\n";
        if (moodHistory.empty()) {
            cout << "No mood entries yet.\n";
        } else {
            for (size_t i = 0; i < moodHistory.size(); ++i) {
                cout << i + 1 << ". " << moodHistory[i] << "\n";
            }
        }
        cout << "-----------------------------\n";
    }
};

// -------- Quote Provider --------
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

// -------- Calm Activity --------
class CalmActivity {
public:
    void breathingExercise() {
        cout << "\n🧘 Breathing Exercise (3 rounds)...\n";
        for (int i = 0; i < 3; ++i) {
            cout << "Round " << i + 1 << ":\n";
            cout << "Breathe in... 🌬️\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            cout << "Hold... ✋\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            cout << "Breathe out... 😮‍💨\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
        cout << "✅ You're done. Hope you feel better!\n";
    }
};

// -------- Mood Tracker --------
class MoodTracker {
    vector<string> moods = {"Happy", "Sad", "Anxious", "Angry", "Tired", "Excited", "Okay"};

public:
    string askMood(const string& username) {
        cout << "\nHi " << username << ", how are you feeling today?\n";
        for (size_t i = 0; i < moods.size(); ++i) {
            cout << i + 1 << ". " << moods[i] << "\n";
        }

        int choice;
        while (true) {
            cout << "Enter the number corresponding to your mood: ";
            cin >> choice;
            if (cin.fail() || choice < 1 || choice > (int)moods.size()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "⚠️ Invalid input. Please choose a valid number.\n";
            } else {
                break;
            }
        }

        return moods[choice - 1];
    }
};

// -------- Assistant --------
class Assistant {
    User* userObj;
    MoodTracker moodTracker;
    QuoteProvider quoteProvider;
    CalmActivity calmActivity;

public:
    Assistant(string name) {
        userObj = new User(name);
    }

    void startSession() {
        string mood = moodTracker.askMood(userObj->getName());
        userObj->addMood(mood);
        cout << "\n📌 Mood Logged: " << mood << endl;

        cout << "\n💬 Motivational Quote:\n";
        cout << "👉 \"" << quoteProvider.getRandomQuote() << "\"\n";

        cout << "\nWould you like to try a short breathing exercise? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            calmActivity.breathingExercise();
        } else {
            cout << "😊 No problem! Take care.\n";
        }
    }

    void showMoodHistory() {
        userObj->showMoodHistory();
    }
};

// -------- Main Function --------
int main() {
    srand(time(0)); // Seed random number generator

    cout << "========================================\n";
    cout << "🧠 Welcome to Your Mental Health Tracker\n";
    cout << "========================================\n";

    cout << "Please enter your name: ";
    string name;
    cin >> name;

    Assistant assistant(name);

    while (true) {
        cout << "\n-------- MENU --------\n";
        cout << "1. Start a New Session\n";
        cout << "2. Show Mood History\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        int option;
        cin >> option;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "⚠️ Invalid input. Try again.\n";
            continue;
        }

        switch (option) {
            case 1:
                assistant.startSession();
                break;
            case 2:
                assistant.showMoodHistory();
                break;
            case 3:
                cout << "\n👋 Take care, and remember: You're not alone!\n";
                return 0;
            default:
                cout << "⚠️ Invalid option. Please try again.\n";
        }
    }

    return 0;
}
