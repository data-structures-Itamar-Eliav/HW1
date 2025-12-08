// You can edit anything you want in this file.
// However you need to implement all public StudentCourseManager function, as provided below as a template

#include "TechSystem26a1.h"


TechSystem::TechSystem() {

}

TechSystem::~TechSystem()
{
    
}

StatusType TechSystem::addStudent(int studentId)
{
    if (studentId <= 0) {return StatusType::INVALID_INPUT;}
    try {
        Student student = new Student(studentId);
        this->studentSystem.insert(student);
        return StatusType::SUCCESS;
    } catch (std::bad_alloc) {
        return StatusType::ALLOCATION_ERROR;
    } catch (...) {
        return StatusType::FAILURE;
    }
    return StatusType::FAILURE;
}

StatusType TechSystem::removeStudent(int studentId)
{
    if (studentId <= 0) {return StatusType::INVALID_INPUT;}
    try {
        Student student = Student(studentId);
        if (this->studentSystem.find(student)->key.numOfCourses > 0) {
            return StatusType::FAILURE;
        }
        this->studentSystem.remove(student);
    } catch (std::bad_alloc) {
        return StatusType::ALLOCATION_ERROR;
    } catch (...) {
        return StatusType::FAILURE;
    }
    return StatusType::FAILURE;
}

StatusType TechSystem::addCourse(int courseId, int points)
{
    if (courseId <= 0 || points <= 0) {return StatusType::INVALID_INPUT;}
    try {
        Course course = new Course
    }
    return StatusType::FAILURE;
}

StatusType TechSystem::removeCourse(int courseId)
{
    return StatusType::FAILURE;
}

StatusType TechSystem::enrollStudent(int studentId, int courseId)
{
    return StatusType::FAILURE;
}

StatusType TechSystem::completeCourse(int studentId, int courseId)
{
    return StatusType::FAILURE;
}

StatusType TechSystem::awardAcademicPoints(int points)
{
    return StatusType::FAILURE;
}

output_t<int> TechSystem::getStudentPoints(int studentId)
{
    return 0;
}