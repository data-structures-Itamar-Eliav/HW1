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
        std::shared_ptr<Student> studentPtr =
                std::make_shared<Student>(studentId);
        this->studentSystem.insert(studentPtr);
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
        std::shared_ptr<Student> studentPtr =
                std::make_shared<Student>(studentId);

        if (this->studentSystem.find(studentPtr)->key->numOfCourses > 0) {
            return StatusType::FAILURE;
        }
        this->studentSystem.remove(studentPtr);
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
        std::shared_ptr<Course> coursePtr =
                std::make_shared<Course>(courseId, points);
        this->courseSystem.insert(coursePtr);
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
        std::shared_ptr<Course> coursePtr = std::make_shared<Course>(courseId);
        if (!this->courseSystem.find(coursePtr)->key->students.isEmpty()){
            return StatusType::FAILURE;
        }
        this->courseSystem.remove(coursePtr);
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