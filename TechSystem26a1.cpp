// You can edit anything you want in this file.
// However you need to implement all public StudentCourseManager function, as provided below as a template

#include "TechSystem26a1.h"


TechSystem::TechSystem()
{
    this->systemCourses = Tree<Course>;
    this->systemStudents = Tree<Student>;
}

TechSystem::~TechSystem()
{
    
}

StatusType TechSystem::addStudent(int studentId)
{
    if (studentId <= 0) {return StatusType::INVALID_INPUT;}
    try {
        Student student(studentId);
        this->systemStudents.Insert(student);
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
        this->systemStudents.Delete(studentId);
        return StatusType::SUCCESS;
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
        this->systemCourses.Insert(Course(courseId, points));
        return StatusType::SUCCESS;
    } catch (std::bad_alloc) {
        return StatusType::ALLOCATION_ERROR;
    } catch (...) {
        return StatusType::FAILURE;
    }
    return StatusType::FAILURE;
}

StatusType TechSystem::removeCourse(int courseId)
{
    if (courseId <= 0) {return StatusType::INVALID_INPUT;}
    try {
        if (systemCourses.Find(courseId)->studentTree.getSize() == 0)
            return StatusType::FAILURE;
        this->systemCourses.Delete (courseId);
        return StatusType::SUCCESS;
    } catch (std::bad_alloc) {
        return StatusType::ALLOCATION_ERROR;
    } catch (...) {
        return StatusType::FAILURE;
    }
    return StatusType::FAILURE;
}

StatusType TechSystem::enrollStudent(int studentId, int courseId)
{
    if (studentId <= 0 || courseId <= 0) {return StatusType::INVALID_INPUT;}
    try {
        systemCourses.Find(courseId).AddStudent(studentId);
        return StatusType::SUCCESS;
    } catch (std::bad_alloc) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::FAILURE;
}

StatusType TechSystem::completeCourse(int studentId, int courseId)
{
    if (studentId <= 0 || courseId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        systemStudents.Find(studentId).addPoints(systemCourses.Find(courseId).getPoints());
        systemCourses.Find(courseId).removeStudent(studentId);
        return StatusType::SUCCESS;
    } catch (std::bad_alloc) {
        return StatusType::ALLOCATION_ERROR;
    } catch (...) {
        return StatusType::FAILURE;
    }
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