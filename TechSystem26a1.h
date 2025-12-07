// 
// 234218 Data Structures 1.
// Semester: 2026A (Winter).
// Wet Exercise #1.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef TechSystem26WINTER_WET1_H_
#define TechSystem26WINTER_WET1_H_

#include "wet1util.h"
#include <memory>

class TechSystem {
private:
    class Student {
    private:
        int id;
        int points;
        int bonusPoints;
        int amountOfRegisterdCourses;
    public:
        Student () {
            this->id = 0;
            this->points = 0;
            this->bonusPoints = 0;
            this->amountOfRegisterdCourses = 0;
        }
        Student(int id) {
            this->id = id;
            this->points = 0;
            this->bonusPoints = 0;
            this->amountOfRegisterdCourses = 0;
        }

        int getId () {return this->id;}
        int getPoints () {return this->points;}
        void setPoints (int pts) {this->points = pts;}
        void addPoints (int pts) {this->points += pts;}
    };
    class Course {
    private:
        int id;
        int points;
        Tree<std::shared_ptr<Student>> studentTree;

    public:
        Course () {
            this->id = 0;
            this->points = 0;
            this->studentTree = Tree<std::shared_ptr<Student>>();
        }
        Course (int id, int points) {
            this->id = id;
            this->points = points;
            this->studentTree = Tree<std::shared_ptr<Student>>();
        }

        int getPoints () {
            return this->points;
        }

        void AddStudent (int studentId){
            this->studentTree.Insert(studentId);
        }
        void RemoveStudent (int studentId) {
            this->studentTree.Delete(studentId);
        }


    };
    Tree<Course> systemCourses;
    Tree<Student> systemStudents;
    
public:
    // <DO-NOT-MODIFY> {
    TechSystem();

    ~TechSystem();

    StatusType addStudent(int studentId);

    StatusType removeStudent(int studentId);

    StatusType addCourse(int courseId, int points);

    StatusType removeCourse(int courseId);

    StatusType enrollStudent(int studentId, int courseId);

    StatusType completeCourse(int studentId, int courseId);

    StatusType awardAcademicPoints(int points);
                    
    output_t<int> getStudentPoints(int studentId);

    // } </DO-NOT-MODIFY>
};

#endif // TechSystem26WINTER_WET1_H_
