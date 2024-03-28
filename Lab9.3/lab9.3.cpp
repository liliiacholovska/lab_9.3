#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

struct Note {
    string firstName;
    string lastName;
    string phoneNumber;
    int birthDate[3];
};

void Create(Note* notes, int N);
void Sort(Note* notes, int N);
void Search(Note* notes, int N, const string& lastName);
void SaveToFile(Note* notes, int N, const string& filename);
void LoadFromFile(Note*& notes, int& N, const string& filename);
void Print(Note* notes, int N);

int main() {
    int N;
    cout << "Enter the number of notes: ";
    cin >> N;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    Note* notes = new Note[N];

    string lastName;
    string filename;

    int menuItem;

    do {
        cout << "Choose an action:" << endl;
        cout << "[1] - Enter note information" << endl;
        cout << "[2] - Display note information" << endl;
        cout << "[3] - Sort by phone numbers" << endl;
        cout << "[4] - Search for a person by last name" << endl;
        cout << "[5] - Save data to file" << endl;
        cout << "[6] - Load data from file" << endl;
        cout << "[0] - Exit the program" << endl;
        cout << "Enter: ";
        cin >> menuItem;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        switch (menuItem) {
        case 1:
            Create(notes, N);
            break;
        case 2:
            Print(notes, N);
            break;
        case 3:
            Sort(notes, N);
            break;
        case 4:
            cout << "Enter search criteria: Last Name: ";
            getline(cin, lastName);
            Search(notes, N, lastName);
            break;
        case 5:
            cout << "Enter the filename to save data: ";
            getline(cin, filename);
            SaveToFile(notes, N, filename);
            break;
        case 6:
            cout << "Enter the filename to load data: ";
            getline(cin, filename);
            LoadFromFile(notes, N, filename);
            break;
        }
    } while (menuItem != 0);

    delete[] notes;

    return 0;
}


void Create(Note* notes, int N) {
    for (int i = 0; i < N; i++) {
        cout << "Enter data for person #" << i + 1 << ":" << endl;
        cout << "First name: ";
        getline(cin, notes[i].firstName);
        cout << "Last name: ";
        getline(cin, notes[i].lastName);
        cout << "Phone number: ";
        getline(cin, notes[i].phoneNumber);
        cout << "Birth date (day month year): ";
        cin >> notes[i].birthDate[0] >> notes[i].birthDate[1] >> notes[i].birthDate[2];
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void Sort(Note* notes, int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (notes[j].phoneNumber > notes[j + 1].phoneNumber) {
                Note temp = notes[j];
                notes[j] = notes[j + 1];
                notes[j + 1] = temp;
            }
        }
    }
}

void Search(Note* notes, int N, const string& lastName) {
    int flag = 0;
    for (int i = 0; i < N; i++) {
        if (notes[i].lastName == lastName) {
            flag = 1;
            cout << "============================================================================" << endl;
            cout << "|  ¹  |   Surname    |  Name  | Phone |  Day   |  Month  |   Year   |" << endl;
            cout << "----------------------------------------------------------------------------" << endl;
            cout << "|" << setw(4) << right << i + 1 << " ";
            cout << "|" << setw(14) << left << notes[i].lastName;
            cout << "|" << setw(8) << left << notes[i].firstName;
            cout << "|" << setw(14) << left << notes[i].phoneNumber;

            for (int j = 0; j < 3; j++) {
                cout << "|" << setw(8) << left << notes[i].birthDate[j];
            }

            cout << setw(6) << "|" << endl;
            cout << "============================================================================" << endl << endl;
            break; 
        }
    }
    if (!flag)
        cout << "Person with last name \"" << lastName << "\" not found." << endl;
}

void SaveToFile(Note* notes, int N, const string& filename) {
    ofstream fileOut(filename, ios::out | ios::binary);
    if (!fileOut) {
        cout << "Cannot open file " << filename << " for writing." << endl;
        return;
    }
    for (int i = 0; i < N; ++i) {
        fileOut.write((char*)&notes[i], sizeof(Note));
    }
    fileOut.close();
}

void LoadFromFile(Note*& notes, int& N, const string& filename) {
    ifstream fileIn(filename, ios::in | ios::binary);
    if (!fileIn) {
        cout << "Cannot open file " << filename << " for reading." << endl;
        return;
    }

    fileIn.seekg(0, ios::end);
    size_t fileSize = fileIn.tellg();
    fileIn.seekg(0, ios::beg);

    N = fileSize / sizeof(Note);

    delete[] notes;
    notes = new Note[N];

    for (int i = 0; i < N; ++i) {
        fileIn.read((char*)&notes[i], sizeof(Note));
    }

    fileIn.close();
}

void Print(Note* notes, int N) {
    cout << "=========================================================================" << endl;
    cout << "|  ¹  |   Surname    |  Name  |  Phone  |  Day   | Month  |  Year  |" << endl;
    cout << "-------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "|" << setw(4) << right << i + 1 << " ";
        cout << "|" << setw(14) << left << notes[i].lastName;
        cout << "|" << setw(8) << left << notes[i].firstName;
        cout << "|" << setw(14) << left << notes[i].phoneNumber;

        for (int j = 0; j < 3; j++) {
            cout << "|" << setw(8) << left << notes[i].birthDate[j];
        }

        cout << setw(6) << "|" << endl;
    }
    cout << "=========================================================================" << endl << endl;
}