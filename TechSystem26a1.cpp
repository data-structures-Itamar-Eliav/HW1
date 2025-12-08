// You can edit anything you want in this file.
// However you need to implement all public StudentCourseManager function, as provided below as a template

#include "TechSystem26a1.h"


TechSystem::TechSystem() {
    this->studentSystem = new Tree<Student>();
    this->courseSystem = new Tree<Course>();
}

TechSystem::~TechSystem()
{
    
}

StatusType TechSystem::addStudent(int studentId)
{
    if (studentId <= 0) {return StatusType::INVALID_INPUT}
    try {
        Student student = Student(studentId);
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
    return StatusType::FAILURE;
}

StatusType TechSystem::addCourse(int courseId, int points)
{
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