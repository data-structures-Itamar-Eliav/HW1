// You can edit anything you want in this file.
// However you need to implement all public StudentCourseManager function, as provided below as a template

#include "TechSystem26a1.h"

int TechSystem::Student::bonusPoints = 0;

TechSystem::TechSystem() = default;

TechSystem::~TechSystem() = default;

StatusType TechSystem::addStudent(const int studentId)
{
    if (studentId <= 0) {return StatusType::INVALID_INPUT;}
    try {
        this->studentSystem.insert(std::make_shared<Student>(studentId));
        return StatusType::SUCCESS;
    } catch (std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    } catch (...) {
        return StatusType::FAILURE;
    }
}

StatusType TechSystem::removeStudent(const int studentId)
{
    if (studentId <= 0) {return StatusType::INVALID_INPUT;}
    try {
        if (this->studentSystem.find(studentId)->numOfCourses > 0) {
            return StatusType::FAILURE;
        }
        this->studentSystem.remove(studentId);
        return StatusType::SUCCESS;
    } catch (std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    } catch (...) {
        return StatusType::FAILURE;
    }
}

StatusType TechSystem::addCourse(const int courseId, const int points)
{
    if (courseId <= 0 || points <= 0) {return StatusType::INVALID_INPUT;}
    try {
        this->courseSystem.insert(std::make_shared<Course>(courseId, points));
        return StatusType::SUCCESS;
    } catch (std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    } catch (...) {
        return StatusType::FAILURE;
    }
}

StatusType TechSystem::removeCourse(const int courseId)
{
    if (courseId <= 0) {return StatusType::INVALID_INPUT;}
    try {
        if (!this->courseSystem.find(courseId)->students.isEmpty()){
            return StatusType::FAILURE;
        }
        this->courseSystem.remove(courseId);
        return StatusType::SUCCESS;
    } catch (std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    } catch (...) {
        return StatusType::FAILURE;
    }
}

StatusType TechSystem::enrollStudent(const int studentId, const int courseId)
{
    if(studentId <= 0 || courseId <= 0){return StatusType::INVALID_INPUT;}
    try {
        courseSystem.find(courseId)->addStudent(studentSystem.find(studentId));
        return StatusType::SUCCESS;
    } catch (std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    } catch (...) {
        return StatusType::FAILURE;
    }
}

StatusType TechSystem::completeCourse(const int studentId, const int courseId)
{
    if (studentId <= 0 || courseId <= 0){return StatusType::INVALID_INPUT;}
    try {
        const std::shared_ptr<Course>& coursePtr =
            courseSystem.find(courseId);
        const std::shared_ptr<Student>& studentPtr =
            coursePtr->students.find(studentId);

        studentPtr->addPoints(coursePtr->points);
        studentPtr->numOfCourses--;
        coursePtr->removeStudent(studentPtr);

        return StatusType::SUCCESS;

    } catch (std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    } catch (...) {
        return StatusType::FAILURE;
    }
}

StatusType TechSystem::awardAcademicPoints(const int points)
{
    if (points <= 0) {return StatusType::INVALID_INPUT;}
    try {
        Student::bonusPoints += points;
        return StatusType::SUCCESS;
    } catch (std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::FAILURE;
}

output_t<int> TechSystem::getStudentPoints(const int studentId)
{
    if (studentId <= 0){return StatusType::INVALID_INPUT;}
    try {
        return studentSystem.find(studentId)->points +
            Student::bonusPoints;
    } catch(std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    } catch (...) {
        return StatusType::FAILURE;
    }
}