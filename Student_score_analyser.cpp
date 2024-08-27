#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <vector>
#include <iomanip>

// Ensuring that the program can handle a maximum of 100 students and 10 exams per student which will be validated in main program

const int MAX_STUDENTS = 100; 
const int MAX_EXAMS = 10; 
const int MAX_SCORE = 100; // Maximum possible score

// 1 - Taking Input of Student Details and Sort Exam Scores using Bubble Sort

void inputStudentDetailsAndSort(std::string names[], int scores[][MAX_EXAMS], int numStudents, int numExams) {
    for (int i = 0; i < numStudents; ++i) {
        std::cout << "Enter name for student " << i + 1 << ": ";
        std::cin >> names[i];
        std::cout << "Enter exam scores for student " << i + 1 << ": ";
        std::string scoreLine;
        std::getline(std::cin >> std::ws, scoreLine); 
        
        std::istringstream iss(scoreLine);
        int score;
        int j = 0;
        while (iss >> score && j < numExams) {
            scores[i][j++] = score;
        }
        
        
        //Bubble sort for exam scores
        
        for (int a = 0; a < numExams - 1; ++a) {
            for (int b = 0; b < numExams - a - 1; ++b) {
                if (scores[i][b] > scores[i][b + 1]) {
                    //Swap 
                    int temp = scores[i][b];
                    scores[i][b] = scores[i][b + 1];
                    scores[i][b + 1] = temp;
                }
            }
        }
    }
}

// 2 - Calculate Average Scores

void calculateAverageScores(int scores[][MAX_EXAMS], double averages[], int numStudents, int numExams) {
    
    // looping for every student and calculating sum and average
    
    for (int i = 0; i < numStudents; ++i) {
        double sum =0;
        for (int j =0; j < numExams; ++j) {
            sum += scores[i][j];
        }
        averages[i] = sum/numExams;  // average formula
    }
}

// 3 - Calculating Variance

double calculateVariance(int scores[][MAX_EXAMS], double averages[], int numStudents, int numExams) {
    double variance = 0.0;
    double sumSqDiff = 0.0;
    double sumSqDiffTotal = 0.0;

    // Calculate sum of squared differences looping under different students and different exams
    
    for (int i = 0; i < numStudents; ++i) {
        
        for (int j = 0; j < numExams; ++j) {
            
            sumSqDiff += pow(scores[i][j] - averages[i], 2); //squared difference sum formula
            
        }
        sumSqDiffTotal += sumSqDiff;
        sumSqDiff = 0.0;
    }
    
    variance = sumSqDiffTotal/(numStudents * numExams); //variance formula
    return variance;
}

// 4 - Calculating Standard Deviation

double calculateStandardDeviation(double variance) {
    double SD = sqrt(variance); // standard deviation formula
    return SD;
}

// 5 - Displaying Student Statistics with - name, avg score and standard deviation

void displayStudentStatistics(std::string names[], double averages[], double standardDeviation, int numStudents) {
    std::cout << "\nStudent Statistics:\n";
    std::cout << "------------------------------------------\n";
    std::cout << std::setw(15) << std::left << "Student Name" << std::setw(15) << std::right << "Average Score" << std::endl;
    std::cout << "------------------------------------------\n";
    for (int i = 0; i < numStudents; ++i) {
        std::cout << std::setw(15) << std::left << names[i] << std::setw(15) << std::right << averages[i] << std::endl;
    }
    std::cout << "------------------------------------------\n";
    std::cout << "Standard Deviation: " << standardDeviation << std::endl;
}

// 6 - Highest Score

int findHighestScore(int scores[][MAX_EXAMS], int numStudents, int numExams) {
    int highestScore = scores[0][0]; 

    // Iterating through all scores to find the highest one
    
    for (int i = 0; i < numStudents; ++i) {
        for (int j = 0; j < numExams; ++j) {
            if (scores[i][j] > highestScore) {
                highestScore = scores[i][j];
            }
        }
    }

    return highestScore;
}

// 7 - Find Lowest Score

int findLowestScore(int scores[][MAX_EXAMS], int numStudents, int numExams) {
    int lowestScore = scores[0][0]; 
    
    // Iterating through all scores to find the lowest one
    
    for (int i = 0; i < numStudents; ++i) {
        for (int j = 0; j < numExams; ++j) {
            if (scores[i][j] < lowestScore) {
                lowestScore = scores[i][j];
            }
        }
    }

    return lowestScore;
    
}

// 8 - Display Histogram

void displayHistogram(int scores[][MAX_EXAMS], int numStudents, int numExams) {
    int scoreCounts[MAX_EXAMS][MAX_SCORE / 20 + 1] = {0}; 
    
    for (int i = 0; i < numStudents; ++i) {
        for (int j = 0; j < numExams; ++j) {
            int score = scores[i][j];
            scoreCounts[i][score / 20]++;
        }
    }

    std::cout << "\nHistogram of Exam Scores for Each Student:\n";
    std::cout << "------------------------------------------\n";
    for (int i = 0; i < numStudents; ++i) {
        std::cout << "Student " << (i + 1) << ": ";
        for (int j = 0; j < (MAX_SCORE - 1) / 20 + 1; ++j) {
            int lowerBound = j * 20;
            int upperBound = (j + 1) * 20 - 1;
            std::cout << "[" << lowerBound << "-" << upperBound << "]: " << scoreCounts[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// 9 - Grade scale calculater

char calculateGrade(double average) {
    if (average >= 90) {
        return 'A';
    } else if (average >= 80) {
        return 'B';
    } else if (average >= 70) {
        return 'C';
    } else if (average >= 60) {
        return 'D';
    } else {
        return 'F';
    }
}

// 10 - Display Grades

void displayGrades(std::string names[], double averages[], int numStudents) {
    std::cout << "\nGrades:\n";
    std::cout << "------------------------------------------\n";
    std::cout << std::setw(15) << std::left << "Student Name" << std::setw(15) << std::right << "Grades" << std::endl;
    std::cout << "------------------------------------------\n";
    for (int i = 0; i < numStudents; ++i) {
        char grade = calculateGrade(averages[i]);
        std::cout << std::setw(15) << std::left << names[i] << std::setw(15) << std::right << grade << std::endl;
    }
    std::cout << "------------------------------------------\n";
}

// 11 - Binary Search

bool binarySearch(int sortedScores[], int numExams, int target) {
    int left = 0;
    int right = numExams - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (sortedScores[mid] == target) {
            return true;
        }

        if (sortedScores[mid] < target) {
            left = mid + 1;
        }
        
        else {
            right = mid - 1;
        }
    }

    return false;
}


int main() {
    int numStudents;
    std::cout << "Enter the number of students: ";
    std::cin >> numStudents;

    // Validate the number of students
    if (numStudents <= 0 || numStudents > MAX_STUDENTS) {
        std::cout << "Invalid number of students. Please enter a number between 1 and " << MAX_STUDENTS << ".\n";
        return 1;
    }

    int numExams;
    std::cout << "Enter the number of exams per student: ";
    std::cin >> numExams;

    // Validate the number of exams
    if (numExams <= 0 || numExams > MAX_EXAMS) {
        std::cout << "Invalid number of exams. Please enter a number between 1 and " << MAX_EXAMS << ".\n";
        return 1;
    }

    std::string names[numStudents];
    int scores[numStudents][MAX_EXAMS];
    double averages[numStudents];

    inputStudentDetailsAndSort(names, scores, numStudents, numExams);
    calculateAverageScores(scores, averages, numStudents, numExams);

    //Calculate variance
    double variance = calculateVariance(scores, averages, numStudents, numExams);

    //Calculate standard deviation
    double standardDeviation = calculateStandardDeviation(variance);
    
    displayStudentStatistics(names, averages, standardDeviation, numStudents);
    
    //Find highest score
    int highestScore = findHighestScore(scores, numStudents, numExams);
    std::cout << "Highest Exam Score: " << highestScore << std::endl;
    
    //Find lowest score
    int lowestScore = findLowestScore(scores, numStudents, numExams);
    std::cout << "Lowest Exam Score: " << lowestScore << std::endl;

    //Display histogram
    displayHistogram(scores, numStudents, numExams);
    
    //Display Grades
    displayGrades(names,averages,numStudents);
    
    //Binary Search - User will enter the score to search
    std::cout << "Enter a score to search for: ";
    int targetScore;
    std::cin >> targetScore;

    //Perform binary search for the target score in sorted scores
    for (int i = 0; i < numStudents; ++i) {
        if (binarySearch(scores[i], numExams, targetScore)) {
            std::cout << "Score " << targetScore << " found for Student " << i + 1 << std::endl;
            break;
        }
    }

    return 0;
}
