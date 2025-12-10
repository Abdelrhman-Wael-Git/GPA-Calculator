#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <iomanip>
using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

class AB {
public:
	int numofSubjects = 0;
	int numofSemster = 0;

	struct Subjects {
		string nameofSubjects;
		int credits = 0;
		double Score = 0;
	};
	struct Semster {
		double CGPA = 0;
	};

	vector<Subjects> subjects;
	vector<Semster> semster;

	void showTemporaryMessage(string msg, int delayMilliseconds) {
		SetConsoleTextAttribute(hConsole, 12);
		cout << msg << flush;
		Sleep(delayMilliseconds);
		cout << "\r" << string(msg.length(), ' ') << "\r" << flush;
		system("cls");
	}
	void welecometext(){
		SetConsoleTextAttribute(hConsole, 10);
		cout << "+-------------------------------------------+ " << endl;
		cout << "|       Welcome to the GPA Calculator!      |" << endl;
		cout << "+-------------------------------------------+ " << endl;
	}
};

class GPACALC : public AB {
public:
	void askNumofSubjects() {
		welecometext();

		SetConsoleTextAttribute(hConsole, 11);
		cout << "Calculate your GPA!" << endl;

		SetConsoleTextAttribute(hConsole, 13);
		cout << "======================" << endl;

		SetConsoleTextAttribute(hConsole, 15);
		cout << "\nEnter the number of subjects: ";
		cin >> this->numofSubjects;

		if (cin.fail() || this->numofSubjects <= 0 || this ->numofSubjects >= 50 ) {
			cin.clear();
			cin.ignore(1000, '\n');
			showTemporaryMessage("Please enter a valid number of Subjects.", 2000);
			askNumofSubjects();
		}
		else {
			SetConsoleTextAttribute(hConsole, 14);
			cout << "You have entered " << this->numofSubjects << " Subjects." << endl;
			SetConsoleTextAttribute(hConsole, 7);
		}
	}

	void askSubjectName() {
		subjects.resize(numofSubjects);
		cin.ignore();
		for (int i = 0; i < numofSubjects; ++i) {
			SetConsoleTextAttribute(hConsole, 15);
			cout << "\nEnter the name of subject " << (i + 1) << ": ";
			cin >> subjects[i].nameofSubjects;

			while (true) {
				cout << "Enter the credit hours for subject " << (i + 1) << ": ";
				cin >> subjects[i].credits;

				if (cin.fail() || subjects[i].credits <= 0 || subjects[i].credits >= 6) {
					cin.clear();
					cin.ignore(1000, '\n');
					SetConsoleTextAttribute(hConsole, 12);
					cout << "Invalid input. Please enter a number between 1 and 5.\n";
					SetConsoleTextAttribute(hConsole, 15);
				}
				else break;
			}

			while (true) {
				cout << "Enter your Score for each subject: ";
				cin >> subjects[i].Score;
				cout << "+--------------------------------------+" << endl;

				if (cin.fail() || subjects[i].Score > 100 || subjects[i].Score < 0) {
					cin.clear();
					cin.ignore(1000, '\n');
					SetConsoleTextAttribute(hConsole, 12);
					cout << "Please enter a Score between 0 to 100." << endl;
					SetConsoleTextAttribute(hConsole, 15);
				}
				else break;
			}
		}
		displayData();
	}
	string getLetterGrade(double score) {
		if (score >= 90) return "A";
		else if (score >= 85) return "B+";
		else if (score >= 80) return "B";
		else if (score >= 75) return "C+";
		else if (score >= 70) return "C";
		else if (score >= 65) return "D+";
		else if (score >= 60) return "D";
		else return "F";
	}

	double getGradePoint(double score) {
		if (score >= 90) return 4.0;
		else if (score >= 85) return 3.7;
		else if (score >= 80) return 3.3;
		else if (score >= 75) return 3.0;
		else if (score >= 70) return 2.7;
		else if (score >= 65) return 2.3;
		else if (score >= 60) return 2.0;
		else return 0.0;
	}

	void displayData() {
		SetConsoleTextAttribute(hConsole, 11);
		cout << "\n+------------------+--------+--------+--------+\n";
		cout << "| Subject Name     | Score  | Credit | Grade  |\n";
		cout << "+------------------+--------+--------+--------+\n";

		for (const auto& s : subjects) {
			cout << "| " << setw(16) << left << s.nameofSubjects
				<< "| " << setw(7) << s.Score
				<< "| " << setw(7) << s.credits
				<< "| " << setw(7) << getLetterGrade(s.Score) << "|\n";
		}

		cout << "+------------------+--------+--------+--------+\n";
		SetConsoleTextAttribute(hConsole, 7);
		calculateGPA();
	}

	void calculateGPA() {
		double totalPoints = 0;
		int totalCredits = 0;

		for (const auto& s : subjects) {
			double gp = getGradePoint(s.Score);
			totalPoints += gp * s.credits;
			totalCredits += s.credits;
		}

		double GPA = totalCredits > 0 ? totalPoints / totalCredits : 0;

		SetConsoleTextAttribute(hConsole, 10);
		cout << fixed << setprecision(2);
		cout << "\nYour GPA is: " << GPA << "\n";
		SetConsoleTextAttribute(hConsole, 7);
	}
};

class CGPACalc : public GPACALC {
public:
	void asknumofSemster() {
		system("cls");
		welecometext(); 
		cout << endl;
		SetConsoleTextAttribute(hConsole, 11);
		cout << "Calculate your CGPA!" << endl;

		SetConsoleTextAttribute(hConsole, 13);
		cout << "======================" << endl;

		SetConsoleTextAttribute(hConsole, 15);
		cout << "\nEnter the number of Semesters: ";
		cin >> this->numofSemster;

		if (cin.fail() || this->numofSemster <= 0 || this->numofSemster >= 16) {
			cin.clear();
			cin.ignore(1000, '\n');
			showTemporaryMessage("Please enter a valid number of Semesters between 1 and 15.\n", 2000);
			asknumofSemster();
		}
		else {
			SetConsoleTextAttribute(hConsole, 14);
			cout << "You have entered " << this->numofSemster << " Semesters.\n";
			SetConsoleTextAttribute(hConsole, 9);
			cout << "===========================================\n";
			askSemsterGpa();
		}
	}

	void askSemsterGpa() {
		semster.resize(numofSemster);
		for (int y = 0; y < numofSemster; ++y) {
			while (true) {
				SetConsoleTextAttribute(hConsole, 15);
				cout << "Enter GPA for Semester " << (y + 1) << ": ";
				cin >> semster[y].CGPA;
				cout << "===========================================\n";

				if (cin.fail() || semster[y].CGPA < 0 || semster[y].CGPA > 4) {
					cin.clear();
					cin.ignore(1000, '\n');
					SetConsoleTextAttribute(hConsole, 12);
					showTemporaryMessage("Please enter a valid GPA between 0 and 4.\n", 2000);
					SetConsoleTextAttribute(hConsole, 10);

					welecometext();
					cout << endl;

					SetConsoleTextAttribute(hConsole, 11);
					cout << "Calculate your CGPA!" << endl;

					SetConsoleTextAttribute(hConsole, 13);
					cout << "======================" << endl;	
					SetConsoleTextAttribute(hConsole, 15);
				}
				else break;
			}
		}
		showResult();
	}

	void showResult() {
		double totalGPA = 0;
		for (int p = 0; p < numofSemster; ++p) {
			totalGPA += semster[p].CGPA;
		}
		double CGPA = totalGPA / numofSemster;
		SetConsoleTextAttribute(hConsole, 10);
		cout << fixed << setprecision(2) << "Your CGPA is: " << CGPA << endl;
		SetConsoleTextAttribute(hConsole, 7);
	}
};

class Aboutus : public CGPACalc {
public:
	void ABOUTUS() {
		system("cls");
		welecometext();
	
		SetConsoleTextAttribute(hConsole, 9);
		cout << "This GPA Calculator is developed by ";
		SetConsoleTextAttribute(hConsole, 10);
		cout << "[ABDELRAHMAN WAEL].\n";

		SetConsoleTextAttribute(hConsole, 9);
		cout << "This is a calculator that calculates GPA and CGPA.\n";
		cout << "This project represents the first c++ program that ";
		SetConsoleTextAttribute(hConsole, 13);
		cout << "@Abdelrahman Wael";
		SetConsoleTextAttribute(hConsole, 9);
		cout << " made.\n";
	}
};

class Exit0 : public Aboutus {
public:
	void Exit() {
		system("cls");
		SetConsoleTextAttribute(hConsole, 10);
		cout << "<===================== Welcome to the GPA Calculator! =====================>\n\n";
		cout << "Thank you for using GPA Calculator. Goodbye!\n";
		SetConsoleTextAttribute(hConsole, 0);
		exit(250);
	}
};

class interfaces : public Exit0 {
public:
	int choice = 0;
	int currentpage = 0;
	void askReturnOrExit() {
		int back;
		SetConsoleTextAttribute(hConsole, 7);
		cout << "+-------------------------------------------+\n";
		cout << "[1] Return to main menu.\n";
		cout << "[2] Exit the application.\n";
		cout << "+-------------------------------------------+\n";
		cout << "Enter your choice: ";
		cin >> back;

		if (cin.fail() || (back != 1 && back != 2)) {
			cin.clear();
			cin.ignore(1000, '\n');
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Invalid input. Try again.\n";
			Sleep(1500);
			if (currentpage == 1) {
				system("cls");
			    welecometext();
				displayData(); 
				askReturnOrExit();
			}
		else if (currentpage == 2) {
				system("cls");
				welecometext();
				cout << endl;
				showResult();
				askReturnOrExit();
	       }
			else if (currentpage == 3) {
					system("cls");
					ABOUTUS();
					askReturnOrExit();
				}else { askReturnOrExit(); }	
		}
		else if (back == 1) {
			system("cls");
			Welcome();
		}
		else {
			SetConsoleTextAttribute(hConsole, 10);
			cout << "Thank you for using GPA Calculator. Goodbye!\n";
			SetConsoleTextAttribute(hConsole, 0);
			exit(0);
		}
	}

	void Welcome() {
		int choice = 0;

		welecometext();

		SetConsoleTextAttribute(hConsole, 13);
		cout << "\nMENU:\n";
		cout << "1. Calculate your GPA.\n";
		cout << "2. Calculate your CGPA.\n";
		cout << "3. About us.\n";
		cout << "4. Exit.\n";
		cout << "+-------------------------------------------+\n";
		SetConsoleTextAttribute(hConsole, 15);
		cout << "Enter a number between 1 to 4 = ";
		cin >> choice;

		if (cin.fail() || (choice < 1 || choice > 4)) {
			cin.clear();
			cin.ignore(1000, '\n');
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Invalid input. Please enter a number from 1 to 4.\n";
			Sleep(1800);
			system("cls");
			Welcome();
			return;
		}

		switch (choice) {
		case 1:
			currentpage = 1;
			system("cls");
			askNumofSubjects();
			askSubjectName();
			askReturnOrExit();
			break;
		case 2:
			currentpage = 2;
			asknumofSemster();
			askReturnOrExit();
			break;
		case 3:
			currentpage = 3;
			ABOUTUS();
			askReturnOrExit();

			break;
		case 4:
			Exit();
			break;
		}
	}
};

class GPACalc : public interfaces {
public:
};

int main() {
	GPACalc app;
	app.Welcome();
	SetConsoleTextAttribute(hConsole, 0);
	return 0;
}
