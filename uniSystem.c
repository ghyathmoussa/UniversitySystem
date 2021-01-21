#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_LEN 100

typedef struct
{
    char id[10];
    char name[20];
    char surname[20];
    char pass[10];
    int credite;
    int current_credite;
} STUDENT;

typedef struct
{
    char id[10];
    char name[20];
    char surname[20];
    char title[10];
} TEACHER;

typedef struct
{
    char id[8];
    char name[20];
    char teacherId[10];
    int credite;
    int capacity;
} COURSE;

typedef struct
{
    char s_id[10];
    char c_id[10];
    char status[20];
    int day;
    int month;
    int year;
} ENROLLMENT;

void add_course();
void show_courses();
void delete_course();
void update_course();
void showCourseStudents();

void add_student();
void show_students();
void delete_student();

void add_teacher();
void show_teachers();
void delete_teacher();
void logIn();
// course operations

void course_operations(FILE *data)
{
    int stop = 1, choice;
    data = fopen("courses.txt", "r");
    if (!data)
    {
        printf("Please Add Course!");
    }
    while (stop)
    {
        printf("\t\t*Courses Operations*\n");
        printf("1-Add new Course\n2-Show Courses\n3-Deleting Course\n4-Update Course\n5-Main Menu\n");
        scanf(" %d", &choice);
        switch (choice)
        {
        case 1:
            add_course();
            break;
        case 2:
            show_courses();
            break;
        case 3:
            delete_course();
            break;
        case 4:
            update_course();
            break;
        case 5:
            stop = 0;
            break;
        }
    }
}

/* --- Adding new course---*/
void add_course()
{
    FILE *data;
    COURSE cr;
    int n, i, yon;
    char courseID[10];
    data = fopen("courses.txt", "r");
    if (!data)
    {
        printf("Document not found Do you want to create file (1-y/2-n): ");
        scanf(" %d", &yon);
        if (yon == 1)
        {
            fclose(data);
            data = fopen("courses.txt", "a+");
            printf("ID of course: ");
            scanf(" %s", cr.id);
            printf("Name of course: ");
            scanf(" %s", cr.name);
            printf("Teacher ID: ");
            scanf(" %s", cr.teacherId);
            printf("Credite of course: ");
            scanf(" %d", &cr.credite);
            printf("Capacity of course: ");
            scanf(" %d", &cr.capacity);
            fprintf(data, "%s %s %s %d %d\n", cr.id, cr.name, cr.teacherId,
                    cr.credite, cr.capacity);
            fclose(data);
        }
        else
            return;
    }
    else
    {
        fclose(data);
        printf("Course Id: ");
        scanf(" %s", courseID);
        data = fopen("courses.txt", "r");
        while (fscanf(data, "%s %s %s %d %d", cr.id, cr.name, cr.teacherId, &cr.credite, &cr.capacity) > 0)
        {
            if (strcmp(courseID, cr.id) == 0)
            {
                printf("The course ID %s is currently existing!\n", courseID);
                i = 0;
            }
        }
        fclose(data);
        if (i != 0)
        {
            data = fopen("courses.txt", "a+");
            printf("Name of course: ");
            scanf(" %s", cr.name);
            printf("Teacher ID : ");
            scanf(" %s", cr.teacherId);
            printf("Credite of course: ");
            scanf(" %d", &cr.credite);
            printf("Capacity of course: ");
            scanf(" %d", &cr.capacity);
            fprintf(data, "%s %s %s %d %d\n", courseID, cr.name, cr.teacherId,
                    cr.credite, cr.capacity);
        }
    }
    fclose(data);
}

/******* Show Current Courses ************/
void show_courses()
{
    char str[MAX_LEN];
    FILE *data = fopen("courses.txt", "r");
    if (!data)
    {
        printf("Document not found! please addcourses :)\n");
        return;
    }
    while (fgets(str, MAX_LEN, data) != NULL)
    {
        printf(" %s", str);
    }
    fclose(data);
}

void showCourseStudents()
{
    FILE *data;
    ENROLLMENT e;
    char studentId[10];
    // show_courses();
    printf("Enter the Student ID: ");
    scanf(" %s", studentId);
    data = fopen("studentCourse.txt", "r");
    while (fscanf(data, "%s %s %s %d %d %d\n", e.c_id, e.s_id, e.status, &e.day, &e.month, &e.year) > 0)
    {
        if (strcmp(studentId, e.s_id) == 0 && strcmp(e.status, "Enrolled") == 0)
        {
            printf("%s\n", e.c_id);
        }
    }
    fclose(data);
}

/********* Delete Course *************/
void delete_course()
{
    FILE *data = fopen("courses.txt", "r");
    COURSE cor;
    int count = 0, line = 0;
    FILE *fw = fopen("temp.txt", "w");
    char fileID[20], str[MAX_LEN];
    if (!data)
    {
        printf("You do not have any courses to delete!");
        return;
    }
    if (!fw)
    {
        printf("Temporary file not opened!");
    }
    printf("The ID of course you want to delete: ");
    scanf(" %s", fileID);

    while (fscanf(data, "%s %s %s %d %d", cor.id, cor.name, cor.teacherId, &cor.credite,
                  &cor.capacity) > 0)
    {
        line++;
        fprintf(fw, "%s %s %s %d %d\n", cor.id, cor.name, cor.teacherId, cor.credite,
                cor.capacity);
        // printf("%s %s %s %d %d\n", cor.id, cor.name, cor.teacherId, cor.credite,
        //        cor.capacity);
    }
    fclose(data);
    fclose(fw);
    data = fopen("courses.txt", "w");
    fw = fopen("temp.txt", "r");
    while (fscanf(fw, "%s %s %s %d %d", cor.id, cor.name, cor.teacherId, &cor.credite,
                  &cor.capacity) > 0)
    {
        // printf("%s %s %s %d %d\n", cor.id, cor.name, cor.teacherId, cor.credite,
        //        cor.capacity);
        if (data)
        {
            if (strcmp(cor.id, fileID) != 0)
            {
                count++;
                fprintf(data, "%s %s %s %d %d\n", cor.id, cor.name, cor.teacherId, cor.credite,
                        cor.capacity);
            }
        }
    }
    fclose(data);
    fclose(fw);
    remove("temp.txt");
    data = fopen("courses.txt", "r");
    if (line != count)
    {
        printf("Course removed successfully !");
    }
    else
    {
        printf("the ID: %s not found or not an ID of course!\n", fileID);
    }
    printf("the file after removing course: \n");
    while (fgets(str, MAX_LEN, data) != NULL)
    {
        printf(" %s", str);
    }
    fclose(data);
}

/**** Update Course****/
void update_course()
{
    COURSE cr;
    FILE *data, *fw;
    char courseID[15], str[MAX_LEN];
    int change = 0;
    data = fopen("courses.txt", "r");
    fw = fopen("temp.txt", "w");
    if (!data)
    {
        printf("Document not found please add courses! \n");
        return;
    }
    printf("Courses is: \n");
    while (fgets(str, MAX_LEN, data) != NULL)
    {
        printf(" %s", str);
        fputs(str, fw);
    }
    fclose(data);
    fclose(fw);
    printf("\nEnter the course ID to update: ");
    scanf(" %s", courseID);
    data = fopen("courses.txt", "w");
    fw = fopen("temp.txt", "r");
    while (fgets(str, MAX_LEN, fw) != NULL)
    {
        sscanf(str, "%s %s %s %d %d", cr.id, cr.name, cr.teacherId,
               &cr.credite, &cr.capacity);
        printf("Looking at: %s\n", cr.id);
        if (strcmp(cr.id, courseID) == 0)
        {
            printf("New Course's ID: ");
            scanf(" %s", cr.id);
            printf("New Course's Name: ");
            scanf(" %s", cr.name);
            printf("Course's Teacher ID: ");
            scanf(" %s", cr.teacherId);
            printf("New Course's Credite: ");
            scanf(" %d", &cr.credite);
            printf("New Course's Capacity: ");
            scanf(" %d", &cr.capacity);
            fprintf(data, "%s %s %s %d %d\n", cr.id, cr.name, cr.teacherId,
                    cr.credite, cr.capacity);
            change = 1;
        }
        else
        {
            fprintf(data, "%s %s %s %d %d\n", cr.id, cr.name, cr.teacherId,
                    cr.credite, cr.capacity);
        }
    }
    fclose(data);
    fclose(fw);
    remove("temp.txt");
    if (change == 1)
        printf("\nCourse has been updated successfully!\n");
    else
        printf("\nCourse not found!\n");
}

/***** Students Operations*/

void add_student()
{
    FILE *data;
    STUDENT std;
    int n, i, yon;
    char studentID[10];
    data = fopen("students.txt", "r");
    if (!data)
    {
        printf("Document not found Do you want to create file (1-y/2-n): ");
        scanf(" %d", &yon);
        if (yon == 1)
        {
            fclose(data);
            data = fopen("students.txt", "w");
            printf("ID of Student: ");
            scanf(" %s", std.id);
            printf("Password of student (should be the ID for recommend)");
            scanf(" %s", std.pass);
            printf("Name of Student: ");
            scanf(" %s", std.name);
            printf("Surname of Student ID : ");
            scanf(" %s", std.surname);
            printf("Total Credite of Student: ");
            scanf(" %d", &std.credite);
            printf("Current Credite Student: ");
            scanf(" %d", &std.current_credite);
            fprintf(data, "%s %s %s %d %d %s\n", std.id, std.name, std.surname,
                    std.credite, std.current_credite, std.pass);
            fclose(data);
        }
        else
            return;
    }
    else
    {
        fclose(data);
        printf(" ID: ");
        scanf(" %s", studentID);
        data = fopen("students.txt", "r");
        while (fscanf(data, "%s %s %s %d %d %s", std.id, std.name, std.surname,
                      &std.credite, &std.current_credite, std.pass) > 0)
        {
            if (strcmp(studentID, std.id) == 0)
            {
                printf("The Student ID %s is currently existing\n", studentID);
                i = 0;
            }
        }
        fclose(data);
        if (i != 0)
        {
            data = fopen("students.txt", "a+");
            printf("Password of student (should be the ID for recommend)");
            scanf(" %s", std.pass);
            printf("Name of Student: ");
            scanf(" %s", std.name);
            printf("Surname of Student ID : ");
            scanf(" %s", std.surname);
            printf("Total Credite of Student: ");
            scanf(" %d", &std.credite);
            printf("Current Credite Student: ");
            scanf(" %d", &std.current_credite);
            fprintf(data, "%s %s %s %d %d %s\n", studentID, std.name, std.surname,
                    std.credite, std.current_credite, std.pass);
            fclose(data);
        }
    }
}

/****** Show Students *********/
void show_students()
{
    char str[MAX_LEN];
    FILE *data = fopen("students.txt", "r");
    if (!data)
    {
        printf("Document not found! please addcourses :)\n");
        return;
    }
    while (fgets(str, MAX_LEN, data) != NULL)
    {
        printf(" %s", str);
    }
    fclose(data);
}

void showStudentTakenCourses()
{
    FILE *data;
    ENROLLMENT e;
    int i;
    char studentId[20];
    printf("The Student ID: ");
    scanf(" %s", studentId);
    data = fopen("studentCourse.txt", "r");
    if (!data)
    {
        printf("The file is not existing now Do you want to create it ? (1-y/2-n): ");
        scanf(" %d", &i);
        if (i == 1)
        {
            logIn();
        }
    }
    while (fscanf(data, "%s %s %s %02d %02d %d\n", e.c_id, e.s_id, e.status, &e.day, &e.month, &e.year) > 0)
    {
        if (strcmp(studentId, e.s_id) == 0 && strcmp(e.status, "Enrolled") == 0)
            printf(" %s", e.c_id);
    }
    fclose(data);
}

/********* Delete Student *************/
void delete_student()
{
    FILE *data = fopen("students.txt", "r");
    STUDENT std;
    int count = 0, line = 0;
    FILE *fw = fopen("temp.txt", "w");
    char studentID[20], str[MAX_LEN];
    if (!data)
    {
        printf("You do not have any courses to delete!");
        return;
    }
    if (!fw)
    {
        printf("Temporary file not opened!");
    }
    printf("The ID of Student you want to delete: ");
    scanf(" %s", studentID);

    while (fscanf(data, "%s %s %s %d %d %s", std.id, std.name, std.surname, &std.credite,
                  &std.current_credite, std.pass) > 0)
    {
        line++;
        fprintf(fw, "%s %s %s %d %d %s\n", std.id, std.name, std.surname, std.credite,
                std.current_credite, std.pass);
        // printf("%s %s %s %d %d\n", cor.id, cor.name, cor.teacherId, cor.credite,
        //        cor.capacity);
    }
    fclose(data);
    fclose(fw);
    data = fopen("students.txt", "w");
    fw = fopen("temp.txt", "r");
    while (fscanf(fw, "%s %s %s %d %d %s", std.id, std.name, std.surname, &std.credite,
                  &std.current_credite, std.pass) > 0)
    {
        // printf("%s %s %s %d %d\n", cor.id, cor.name, cor.teacherId, cor.credite,
        //        cor.capacity);
        if (data)
        {
            if (strcmp(std.id, studentID) != 0)
            {
                count++;
                fprintf(data, "%s %s %s %d %d %s\n", std.id, std.name, std.surname, std.credite,
                        std.current_credite, std.pass);
            }
        }
    }
    fclose(data);
    fclose(fw);
    remove("temp.txt");
    data = fopen("students.txt", "r");
    if (line != count)
    {
        printf("Student removed successfully !");
    }
    else
    {
        printf("the ID: %s not found or not an ID ofstudent!\n", studentID);
    }
    printf("the file after removing student: \n");
    while (fgets(str, MAX_LEN, data) != NULL)
    {
        printf(" %s", str);
    }
    fclose(data);
}

/**** Update Student****/
void update_student()
{
    STUDENT std;
    FILE *data, *fw;
    char studentID[15], str[MAX_LEN];
    int change = 0;
    data = fopen("students.txt", "r");
    fw = fopen("temp.txt", "w");
    if (!data)
    {
        printf("Document not found please add Student! \n");
        return;
    }
    printf("Current Students: \n");
    while (fgets(str, MAX_LEN, data) != NULL)
    {
        printf(" %s", str);
        fputs(str, fw);
    }
    fclose(data);
    fclose(fw);
    printf("\nEnter the Student ID to update: ");
    scanf(" %s", studentID);
    data = fopen("students.txt", "w");
    fw = fopen("temp.txt", "r");
    while (fgets(str, MAX_LEN, fw) != NULL)
    {
        sscanf(str, "%s %s %s %d %d %s", std.id, std.name, std.surname,
               &std.credite, &std.current_credite, std.pass);
        printf("Looking at: %s\n", std.id);
        if (strcmp(std.id, studentID) == 0)
        {
            printf("New Student's ID: ");
            scanf(" %s", std.id);
            printf("New Student's Name: ");
            scanf(" %s", std.name);
            printf("Student's Surname: ");
            scanf(" %s", std.surname);
            printf("New Student's Credite: ");
            scanf(" %d", &std.credite);
            printf("New Student's Current Credit: ");
            scanf(" %d", &std.current_credite);
            printf("Student's password: ");
            scanf(" %s", std.pass);
            fprintf(data, "%s %s %s %d %d %s\n", std.id, std.name, std.surname,
                    std.credite, std.current_credite, std.pass);
            change = 1;
        }
        else
        {
            fprintf(data, "%s %s %s %d %d %s\n", std.id, std.name, std.surname,
                    std.credite, std.current_credite, std.pass);
        }
    }
    fclose(data);
    fclose(fw);
    remove("temp.txt");
    if (change == 1)
        printf("\nStudent file has been updated successfully!\n");
    else
        printf("\nStudent not found!\n");
}

void students_operations(FILE *data)
{
    int stop = 1, choice;
    data = fopen("students.txt", "r");
    if (!data)
    {
        printf("Please Add Course!");
    }
    while (stop)
    {
        printf("\t\t*Students Operations*\n");
        printf("1-Add new Students\n2-Show Students\n3-Deleting Students\n4-Update Student\n5-Show student's courses\n6-Main Menu\n");
        scanf(" %d", &choice);
        switch (choice)
        {
        case 1:
            add_student();
            break;
        case 2:
            show_students();
            break;
        case 3:
            delete_student();
            break;
        case 4:
            update_student();
            break;
        case 5:
            showStudentTakenCourses();
            break;
        case 6:
            stop = 0;
            break;
        }
    }
}

/******* Add Teacher ***********/
void add_teachers()
{
    FILE *data;
    TEACHER tec;
    int i, yon;
    char teacherID[10];
    data = fopen("teachers.txt", "r");
    if (!data)
    {
        printf("Document not found Do you want to create file (1-y/2-n): ");
        scanf(" %d", &yon);
        if (yon == 1)
        {
            fclose(data);
            data = fopen("teachers.txt", "a+");
            printf("ID of Teacher: ");
            scanf(" %s", tec.id);
            printf("Name of Teacher: ");
            scanf(" %s", tec.name);
            printf("Surname of Teacher ID : ");
            scanf(" %s", tec.surname);
            printf("Teacher Title: ");
            scanf(" %s", tec.title);
            fprintf(data, "%s %s %s %s\n", tec.id,
                    tec.name, tec.surname,
                    tec.title);
            fclose(data);
        }
        else
            return;
    }
    else
    {
        printf("Teacher ID: ");
        scanf(" %s", teacherID);
        fclose(data);
        data = fopen("teachers.txt", "r");
        while (fscanf(data, "%s %s %s %s", tec.id, tec.name, tec.surname,
                      tec.title) > 0)
        {
            if (strcmp(teacherID, tec.id) == 0)
            {
                printf("Teh Teacher ID %s is currently existing!\n", teacherID);
                i = 0;
            }
        }
        fclose(data);
        if (i != 0)
        {
            data = fopen("teachers.txt", "a+");
            printf("Name of Teacher: ");
            scanf(" %s", tec.name);
            printf("Surname of Teacher ID : ");
            scanf(" %s", tec.surname);
            printf("Teacher Title: ");
            scanf(" %s", tec.title);
            fprintf(data, "%s %s %s %s\n", teacherID,
                    tec.name, tec.surname,
                    tec.title);
            fclose(data);
        }
    }
}

/***** Show Teachers ******/
void show_teachers()
{
    char str[MAX_LEN];
    FILE *data = fopen("teachers.txt", "r");
    if (!data)
    {
        printf("Document not found! please add teachers :)\n");
        return;
    }
    while (fgets(str, MAX_LEN, data) != NULL)
    {
        printf(" %s", str);
    }
    fclose(data);
}

void showTeacherCourses()
{
    FILE *data;
    COURSE cr;
    char teacherId[10];
    show_teachers();
    printf("Enter the Teacher ID: ");
    scanf(" %s", teacherId);
    data = fopen("courses.txt", "r");
    while (fscanf(data, "%s %s %s %d %d\n", cr.id, cr.name, cr.teacherId, &cr.credite, &cr.capacity) > 0)
    {
        if (strcmp(teacherId, cr.teacherId) == 0)
        {
            printf(" %s %s\n", cr.id, cr.name);
        }
    }
    fclose(data);
}

/****** Delete Teacher ******/
void delete_teacher()
{
    FILE *data = fopen("teachers.txt", "r");
    TEACHER tec;
    COURSE cr;
    int count = 0, line = 0;
    FILE *fw = fopen("temp.txt", "w");
    FILE *course, *fw1;
    char teacherID[20], str[MAX_LEN];
    //write in temporary teacher file
    if (!data)
    {
        printf("You do not have any courses to delete!");
        return;
    }
    if (!fw)
    {
        printf("Temporary file not opened!");
    }
    printf("The ID of Student you want to delete: ");
    scanf(" %s", teacherID);
    course = fopen("courses.txt", "r");
    fw1 = fopen("temp1.txt", "w");
    while (fscanf(data, "%s %s %s %s", tec.id, tec.name,
                  tec.surname, tec.title) > 0)
    {
        line++;
        fprintf(fw, "%s %s %s %s\n", tec.id, tec.name,
                tec.surname, tec.title);
    }
    fclose(data);
    fclose(fw);
    //write in temporary course file
    while (fscanf(course, "%s %s %s %d %d", cr.id, cr.name, cr.teacherId,
                  &cr.credite, &cr.capacity) > 0)
    {
        fprintf(fw1, "%s %s %s %d %d\n", cr.id, cr.name,
                cr.teacherId, cr.credite, cr.capacity);
    }
    fclose(course);
    fclose(fw1);
    data = fopen("teachers.txt", "w");
    fw = fopen("temp.txt", "r");
    course = fopen("courses.txt", "w");
    fw1 = fopen("temp1.txt", "r");
    //delete teacher from teachers file
    while (fscanf(fw, "%s %s %s %s", tec.id, tec.name,
                  tec.surname, tec.title) > 0)
    {
        if (data)
        {
            if (strcmp(tec.id, teacherID) != 0)
            {
                count++;
                fprintf(data, "%s %s %s %s\n", tec.id, tec.name,
                        tec.surname, tec.title);
            }
        }
    }
    fclose(data);
    fclose(fw);
    //delete course of teacher
    while (fscanf(fw1, "%s %s %s %d %d", cr.id, cr.name, cr.teacherId,
                  &cr.credite, &cr.capacity) > 0)
    {
        if (course)
        {
            if (strcmp(cr.teacherId, teacherID) != 0)
            {
                fprintf(course, "%s %s %s %d %d\n", cr.id, cr.name,
                        cr.teacherId, cr.credite, cr.capacity);
            }
        }
    }
    fclose(course);
    fclose(fw1);
    remove("temp.txt");
    remove("temp1.txt");
    data = fopen("teachers.txt", "r");
    if (line != count)
    {
        printf("Teacher removed successfully !");
    }
    else
    {
        printf("the ID: %s not found or not an ID ofstudent!\n", teacherID);
    }
    printf("the file after removing student: \n");
    while (fgets(str, MAX_LEN, data) != NULL)
    {
        printf(" %s", str);
    }
    fclose(data);
}

/**** Update Teacher****/
void update_teacher()
{
    TEACHER tec;
    FILE *data, *fw;
    char teacherID[15], str[MAX_LEN];
    int change = 0;
    data = fopen("teachers.txt", "r");
    fw = fopen("temp.txt", "w");
    if (!data)
    {
        printf("Document not found please add Student! \n");
        return;
    }
    printf("Current Teachers: \n");
    while (fgets(str, MAX_LEN, data) != NULL)
    {
        printf(" %s", str);
        fputs(str, fw);
    }
    fclose(data);
    fclose(fw);
    printf("\nEnter the Teacher ID to update: ");
    scanf(" %s", teacherID);
    data = fopen("teachers.txt", "w");
    fw = fopen("temp.txt", "r");
    while (fgets(str, MAX_LEN, fw) != NULL)
    {
        sscanf(str, "%s %s %s %s", tec.id, tec.name, tec.surname,
               tec.title);
        if (strcmp(tec.id, teacherID) == 0)
        {
            printf("New Teacher's ID: ");
            scanf(" %s", tec.id);
            printf("New Teacher's Name: ");
            scanf(" %s", tec.name);
            printf("New Teacher's Surname: ");
            scanf(" %s", tec.surname);
            printf("Teacher's Title: ");
            scanf(" %s", tec.title);
            fprintf(data, "%s %s %s %s\n", tec.id, tec.name, tec.surname,
                    tec.title);
            change = 1;
        }
        else
        {
            fprintf(data, "%s %s %s %s\n", tec.id, tec.name, tec.surname,
                    tec.title);
        }
    }
    fclose(data);
    fclose(fw);
    remove("temp.txt");
    if (change == 1)
        printf("\nTeacher file has been updated successfully!\n");
    else
        printf("\nTeacher not found!\n");
}

void teacher_operations(FILE *data)
{
    int stop = 1, choice;
    data = fopen("teachers.txt", "r");
    if (!data)
    {
        printf("Please Add Teacher!");
    }
    while (stop)
    {
        printf("\t\t*Teachers Operations*\n");
        printf("1-Add new Teacher\n2-Show Teachers\n3-Deleting Teacher\n4-Update Teacher\n5-Show teacher Courses\n6-Main Menu\n");
        scanf(" %d", &choice);
        switch (choice)
        {
        case 1:
            add_teachers();
            break;
        case 2:
            show_teachers();
            break;
        case 3:
            delete_teacher();
            break;
        case 4:
            update_teacher();
            break;
        case 5:
            showTeacherCourses();
            break;
        case 6:
            stop = 0;
            break;
        }
    }
}

/***** Add course for student functions ******/

void addCourseToStudent(char *stdId, char *crID)
{
    FILE *enrollment;
    char enroll[] = "Enrolled";
    int day, month, year;
    time_t t = time(NULL);
    struct tm *ptm = localtime(&t);
    day = ptm->tm_mday;         // get day of month (1 to 31)
    month = ptm->tm_mon + 1;    // get month of year (0 to 11)
    year = ptm->tm_year + 1900; // get year since 1900
    enrollment = fopen("studentCourse.txt", "a+");
    if (enrollment)
    {
        printf(" %s", ctime(&t));
        fprintf(enrollment, "%s %s %s %02d %02d %d\n", crID, stdId, enroll, day, month, year);
    }
    fclose(enrollment);
}

void cheackCourseStudent(char *stdId, char *crID, int cred)
{
    FILE *data, *student, *fw;
    ENROLLMENT e;
    STUDENT std;
    int done = 0, cheack1 = 0;
    char cheack[20];
    data = fopen("studentCourse.txt", "r");
    if (!data)
    {
        addCourseToStudent(stdId, crID);
    }
    else
    {
        while (fscanf(data, "%s %s %s %02d %02d %d\n", e.c_id, e.s_id, e.status,
                      &e.day, &e.month, &e.year) > 0)
        {
            if (strcmp(e.c_id, crID) == 0 && (strcmp(e.s_id, stdId) == 0 && strcmp(e.status, "Enrolled") == 0))
            {
                strcpy(cheack, e.status);
                done++;
            }
        }
        fclose(data);
        if (done == 0)
        {
            student = fopen("students.txt", "r");
            fw = fopen("temp.txt", "w");
            while (fscanf(data, "%s %s %s %d %d %s\n", std.id, std.name, std.surname,
                          &std.credite, &std.current_credite, std.pass) > 0)
            {
                fprintf(fw, "%s %s %s %d %d %s\n", std.id, std.name, std.surname,
                        std.credite, std.current_credite, std.pass);
                if (strcmp(stdId, std.id) == 0)
                {
                    if (std.credite > std.current_credite && strcmp(cheack, "Enrolled") != 0)
                        addCourseToStudent(stdId, crID);
                    else
                        printf("You Don not have enough credite :) \n");
                }
            }
            fclose(data);
            fclose(fw);
            // if (cheack1 == 1)

            data = fopen("students.txt", "w");
            fw = fopen("temp.txt", "r");
            while (fscanf(fw, "%s %s %s %d %d %s\n", std.id, std.name, std.surname,
                          &std.credite, &std.current_credite, std.pass) > 0)
            {
                if (strcmp(stdId, std.id) == 0)
                {
                    std.current_credite = std.current_credite + cred;
                    fprintf(data, "%s %s %s %d %d %s\n", std.id, std.name, std.surname,
                            std.credite, std.current_credite, std.pass);
                }
                else
                {
                    fprintf(data, "%s %s %s %d %d %s\n", std.id, std.name, std.surname,
                            std.credite, std.current_credite, std.pass);
                }
            }
            fclose(data);
            fclose(fw);
            remove("temp.txt");
        }
        else
        {
            printf("The %s has taken this course %s befor\n ", stdId, crID);
        }
    }
}

void add_course_student(char *s_id)
{
    FILE *data, *course;
    COURSE cr;
    STUDENT std;
    int courseF = 0, cr_credit, cr_capacity, cheack = 0;
    char courseID[20], studentID[15];
    show_courses();
    printf("Enter the course ID: ");
    scanf(" %s", courseID);
    course = fopen("courses.txt", "r");
    while (fscanf(course, "%s %s %s %d %d\n", cr.id, cr.name, cr.teacherId,
                  &cr.credite, &cr.capacity) > 0)
    {
        if (strcmp(courseID, cr.id) == 0)
        {
            printf("Course %s Found \n", courseID);
            cr_credit = cr.credite;
            cr_capacity = cr.capacity;
            courseF = 1;
        }
    }
    fclose(course);
    if (courseF == 0)
        printf("Course %s not found", courseID);
    if (courseF == 1)
    {
        data = fopen("students.txt", "r");
        while (fscanf(data, "%s %s %s %d %d %s", std.id, std.name, std.surname,
                      &std.credite, &std.current_credite, std.pass) > 0)
        {
            if (strcmp(s_id, std.id) == 0)
            {
                if (std.credite > std.current_credite)
                {
                    cheackCourseStudent(std.id, courseID, cr_credit);
                    // strcpy(studentID, std.id);
                }
                else
                    printf("You Don not have enough credite :) \n");
            }
        }
        fclose(data);
    }
    // if (cheack == 1)
}

/**** Delete Course From Student *****/

void deleteCourseStudent(char *stdID)
{
    FILE *data, *student, *fw, *course;
    ENROLLMENT e;
    COURSE cr;
    STUDENT std;
    char courseID[10];
    int count = 0, std_cr;
    int day, month, year;
    time_t t = time(NULL);
    struct tm *ptm = localtime(&t);
    day = ptm->tm_mday;         // get day of month (1 to 31)
    month = ptm->tm_mon + 1;    // get month of year (0 to 11)
    year = ptm->tm_year + 1900; // get year since 1900
    data = fopen("studentCourse.txt", "r");
    if (!data)
    {
        printf("Please add course !\n");
        add_course_student(stdID);
    }
    printf("Enter Course ID: ");
    scanf(" %s", courseID);
    fw = fopen("temp.txt", "w");
    while (fscanf(data, "%s %s %s %02d %02d %d\n", e.c_id, e.s_id, e.status, &e.day, &e.month, &e.year) > 0)
    {
        fprintf(fw, "%s %s %s %02d %02d %d\n", e.c_id, e.s_id, e.status, e.day, e.month, e.year);
    }
    fclose(data);
    fclose(fw);
    data = fopen("studentCourse.txt", "w");
    fw = fopen("temp.txt", "r");
    while (fscanf(fw, "%s %s %s %02d %02d %d\n", e.c_id, e.s_id, e.status, &e.day, &e.month, &e.year) > 0)
    {
        if ((strcmp(courseID, e.c_id) == 0 && strcmp(e.status, "Not_Enrolled") != 0) && strcmp(stdID, e.s_id) == 0)
        {
            count++;
            strcpy(e.status, "Not_Enrolled");
            fprintf(data, "%s %s %s %d %d %d\n", e.c_id, e.s_id, e.status, e.day, e.month, e.year);
        }
        else
        {
            fprintf(data, "%s %s %s %02d %02d %d\n", e.c_id, e.s_id, e.status, e.day, e.month, e.year);
        }
    }
    fclose(data);
    fclose(fw);
    remove("temp.txt");
    course = fopen("courses.txt", "r");
    while (fscanf(course, "%s %s %s %d %d\n", cr.id, cr.name, cr.teacherId, &cr.credite, &cr.capacity) > 0)
    {
        if (strcmp(courseID, cr.id) == 0)
            std_cr = cr.credite;
    }
    fclose(course);
    student = fopen("students.txt", "r");
    fw = fopen("temp1.txt", "w");
    while (fscanf(student, "%s %s %s %d %d %s\n", std.id, std.name, std.surname,
                  &std.credite, &std.current_credite, std.pass) > 0)
    {
        fprintf(fw, "%s %s %s %d %d %s\n", std.id, std.name, std.surname,
                std.credite, std.current_credite, std.pass);
    }
    fclose(student);
    fclose(fw);
    fw = fopen("temp1.txt", "r");
    student = fopen("students.txt", "w");
    while (fscanf(fw, "%s %s %s %d %d %s\n", std.id, std.name, std.surname,
                  &std.credite, &std.current_credite, std.pass) > 0)
    {
        if (strcmp(stdID, std.id) == 0)
        {
            std.current_credite = std.current_credite - std_cr;
            fprintf(student, "%s %s %s %d %d %s\n", std.id, std.name, std.surname,
                    std.credite, std.current_credite, std.pass);
        }
        else
        {
            fprintf(student, "%s %s %s %d %d %s\n", std.id, std.name, std.surname,
                    std.credite, std.current_credite, std.pass);
        }
    }
    fclose(fw);
    fclose(student);
    remove("temp1.txt");
    if (count == 0)
        printf("The course ID not found");
    else
        printf("The course has been deleted Successfully!\n");
}

/***** Log In Operations ******/

void logIn()
{
    FILE *data = fopen("students.txt", "r");
    STUDENT std;
    char id[15], pass[15];
    int done = 0, choice, stop = 1;
    if (!data)
    {
        printf("Please Add Students !");
        students_operations(data);
    }
    printf("Student ID: ");
    scanf(" %s", id);
    printf("PassWord: ");
    scanf(" %s", pass);
    while (fscanf(data, "%s %s %s %d %d %s", std.id, std.name, std.surname,
                  &std.credite, &std.current_credite, std.pass) > 0)
    {
        if (strcmp(std.id, id) == 0 && strcmp(std.pass, pass) == 0)
            done = 1;
    }
    fclose(data);
    while (stop && done == 1)
    {
        printf("\t\t*Student's Page*\n");
        printf("1-Add Course\n2-Delete Course\n3-Log out\n");
        scanf(" %d", &choice);
        switch (choice)
        {
        case 1:
            add_course_student(id);
            break;
        case 2:
            deleteCourseStudent(id);
            break;
        case 3:
            stop = 0;
            break;
        }
    }
    if (done == 0)
        printf("Student ID or Password Wrong!\n");
}

/***** Class Students with Teacher ******/
void classStudents()
{
    FILE *data, *class;
    COURSE cr;
    ENROLLMENT e;
    char teacherId[10], courseId[10];
    char strCr[10], strTId[10], stdID[10];
    int done = 0, count = 0;
    printf("Teacher ID: ");
    scanf(" %s", teacherId);
    printf("Course ID: ");
    scanf(" %s", courseId);
    data = fopen("courses.txt", "r");
    while (fscanf(data, "%s %s %s %d %d", cr.id, cr.name, cr.teacherId, &cr.credite, &cr.capacity) > 0)
    {
        if (strcmp(cr.id, courseId) == 0 && strcmp(teacherId, cr.teacherId) == 0)
        {
            strcpy(strCr, cr.id);
            strcpy(strTId, cr.teacherId);
            done = 1;
        }
    }
    fclose(data);
    if (done == 1)
    {
        data = fopen("studentCourse.txt", "r");
        class = fopen("courseIdStudents.txt", "a+");
        while (fscanf(data, "%s %s %s %02d %02d %d", e.c_id, e.s_id, e.status,
                      &e.day, &e.month, &e.year) > 0)
        {
            if (strcmp(courseId, e.c_id) == 0)
            {
                count++;
                fprintf(class, "%s %s\n", e.c_id, e.s_id);
                printf("%s %s\n", e.c_id, e.s_id);
            }
        }
        printf("The class has %d students\n", count);
        fclose(data);
        fclose(class);
    }
    else
        printf("Course ID : %s or Teacher : %s not found\n", courseId, teacherId);
}

int main()
{
    int i, j, stop = 1, choice;
    FILE *data;
    while (stop)
    {
        printf("\t\t*University System*\n");
        printf("Select your operation:\n");
        printf("1-Course Operations\n");
        printf("2-Student Operations\n");
        printf("3-Teacher Operations\n");
        printf("4-Log In (to add course for students!)\n5-Show Class Students\n6-Show Student's of Course\n");
        printf("7-Exit\n");
        scanf(" %d", &choice);
        switch (choice)
        {
        case 1:
            course_operations(data);
            break;
        case 2:
            students_operations(data);
            break;
        case 3:
            teacher_operations(data);
            break;
        case 4:
            logIn();
            break;
        case 5:
            classStudents();
            break;
        case 6:
            showCourseStudents();
        case 7:
            stop = 0;
            break;
        }
    }
    return 0;
}