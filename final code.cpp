#include <iostream>   // Input/output stream
#include <string>     // String handling
#include <vector>     // Dynamic array
#include <cstdlib>    // General utilities library
#include <ctime>      // C Time library for time-related functions
#include <algorithm>  // Algorithms that operate on ranges of elements
#include<cmath> // for base exponesnt
#include <windows.h>//for console password
using namespace std;

//
long long base=2;  

  long long exponent=8;  

   long long power=pow(base,exponent);  
const int MAX_IDS = power;

// Structure to represent data associated with an ID
struct UserData {
    string data;  // Data associated with a user
};

// Struct to store values of id and userData
struct MessageData {
    int id;           // Unique identifier for a message
    string userData;  // User data associated with a message
};

// Function to generate a random ID
int generateRandomID() {
    return rand() % MAX_IDS + 1;  // Generates a random ID within the range [1, MAX_IDS]
}

// Function to display information about a user
void displayUserInfo(const MessageData& message) {
    cout << "User Data: " << message.userData << endl;  // Display user data
    cout << "User ID: " << message.id << endl;           // Display user ID
}

// Function to send a message to the server
void SendMessageToServer(vector<MessageData>& messages) {
    srand(static_cast<unsigned int>(time(nullptr)));  // Seed the random number generator with current time

    // Let the user enter data into the string
    string userData;
    cout << "\nEnter data: ";
    cin.ignore();  // Ignore any previous newline character
    getline(cin, userData);

    // Assign a random ID to the string
    int id = generateRandomID();

    // Display the entered data and its assigned ID
    cout << "Entered data: " << userData << endl;
    cout << "Assigned ID: " << id << endl;

    // Create a struct to hold the data
    MessageData message;
    message.id = id;
    message.userData = userData;

    // Add the message to the vector
    messages.push_back(message);

    // Implement your logic to send the message to the server here
    cout << "Message sent to the server: " << userData << " with ID: " << id << endl;
}

// Function to retrieve a message from the vector based on ID
void RetrieveMessageById(const vector<MessageData>& messages, int id) {
    // Search for the message with the specified ID
    auto it = find_if(messages.begin(), messages.end(), [id](const MessageData& message) {
        return message.id == id;
    });

    // Check if the message was found
    if (it != messages.end()) {
        // Display the found message
        displayUserInfo(*it);
    } else {
        cout << "Message with ID " << id << " not found." << endl;
    }
}

// Function to display all stored messages
void DisplayAllMessages(const vector<MessageData>& messages) {
    cout << "\nAll stored messages:" << endl;
    for (const auto& message : messages) {
        displayUserInfo(message);
        cout << "--------------------------" << endl;
    }
}

// Function to perform user login
bool PerformLogin() {
    string userID, password;
    cout << "\nWelcome to the Admin panel \nSend your data to the server or retrieve from server" << endl;
    cout << "Please log in to continue.\n";
    cout << "Enter User ID: ";
    cin >> userID;
     HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    // Get the current console mode
    GetConsoleMode(hInput, &mode);
    // Disable echo in the console mode
    SetConsoleMode(hInput, mode & (~ENABLE_ECHO_INPUT));
    // Get the password from the user
    cout << "Enter password: ";
   
    cin >> password;
    // Enable echo back after getting the password
    SetConsoleMode(hInput, mode);

    //cout << "\nPassword entered: " << password << endl;
    //cout << "Enter Password: ";
    //cin >> password;

    // Check if the provided credentials are valid
    return (userID == "admin" && password == "236");
}

// Main function
int main() {
    	int choice;
    vector<MessageData> messages;  // Vector to store messages
    do {
        cout << "\nMenu:\n1. Send Message to Server\n2. Retrieve Message from Server\n";
        cout << "3. Display Message by ID\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                SendMessageToServer(messages);
                break;

            case 2:
                // Retrieve a message by ID
                int idToRetrieve;
                cout << "Enter ID to retrieve: ";
                cin >> idToRetrieve;
                RetrieveMessageById(messages, idToRetrieve);
                break;

            case 3:
            
    if (!PerformLogin()) {
        cout << "Login failed. Exiting the program." << endl;
        return 1;  // Exit with an error code
    }

                // Display all stored messages
                DisplayAllMessages(messages);
                break;

            case 4:
                cout << "Exiting the program. Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 4);

    return 0;
}
