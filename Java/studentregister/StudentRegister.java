import java.util.ArrayList;

public class StudentRegister {
    
    // Private
    private final ArrayList<Student> studentsList;
    private final ArrayList<Course> coursesList;
    private final ArrayList<Attainment> attainmentsList;
    
    // Public
    public StudentRegister() {
        
        //
        
        this.studentsList = new ArrayList();
        this.coursesList = new ArrayList();
        this.attainmentsList = new ArrayList();
    }
    
    public ArrayList<Student> getStudents() {
        
        //
        
        ArrayList<Student> sortedList = new ArrayList();
        ArrayList<Student> tempList = new ArrayList();
        tempList.addAll(this.studentsList);
        
        while (!tempList.isEmpty()) {
            Student firstStudent = tempList.get(0);
            
            for (var student : tempList) {
                if (firstStudent.getName().compareTo(student.getName()) > 0) {
                    firstStudent = student;
                }
            }
            
            sortedList.add(firstStudent);
            tempList.remove(firstStudent);
        }
        
        return sortedList;
    }
    
    public ArrayList<Course> getCourses() {
        
        //
        
        ArrayList<Course> sortedList = new ArrayList();
        ArrayList<Course> tempList = new ArrayList();
        tempList.addAll(this.coursesList);
        
        while (!tempList.isEmpty()) {
            Course firstCourse = tempList.get(0);
            
            for (var course : tempList) {
                if (firstCourse.getName().compareTo(course.getName()) > 0) {
                    firstCourse = course;
                }
            }
            
            sortedList.add(firstCourse);
            tempList.remove(firstCourse);
        }
        
        return sortedList;
    }
    
    public ArrayList<Course> getCoursesCode() {
        
        //
        
        ArrayList<Course> sortedList = new ArrayList();
        ArrayList<Course> tempList = new ArrayList();
        tempList.addAll(this.coursesList);
        
        while (!tempList.isEmpty()) {
            Course firstCourse = tempList.get(0);
            
            for (var course : tempList) {
                if (firstCourse.getCode().compareTo(course.getCode()) > 0) {
                    firstCourse = course;
                }
            }
            
            sortedList.add(firstCourse);
            tempList.remove(firstCourse);
        }
        
        return sortedList;
    }
    
    public ArrayList<Attainment> getAttainments(String studentNum) {
        
        //
        
        ArrayList<Course> sortedCourseList = getCourses();
        ArrayList<Attainment> sortedList = new ArrayList();
        
        for (Course course : sortedCourseList) {
            for (var att : this.attainmentsList) {
                if (att.getStudentNumber().equals(studentNum)) {
                    if (att.getCourseCode().equals(course.getCode())) {
                        sortedList.add(att);
                    }
                }
            }
        }
        
        return sortedList;
    }
    
    public ArrayList<Attainment> getAttainmentsCode(String studentNum) {
        
        //
        
        ArrayList<Course> sortedCourseList = getCoursesCode();
        ArrayList<Attainment> sortedList = new ArrayList();
        
        for (Course course : sortedCourseList) {
            for (var att : this.attainmentsList) {
                if (att.getStudentNumber().equals(studentNum)) {
                    if (att.getCourseCode().equals(course.getCode())) {
                        sortedList.add(att);
                    }
                }
            }
        }
        
        return sortedList;
    }
    
    public void addStudent(Student student) {
        
        //
        
        this.studentsList.add(student);
    }
    
    public void addCourse(Course course) {
        
        //
        
        this.coursesList.add(course);
    }
    
    public void addAttainment(Attainment att) {
        
        //
        
        this.attainmentsList.add(att);
    }
    
    public void printStudentAttainments(String studentNumber, String order) {
        
        //
        
        String studentName = "";
        boolean studentFound = false;
        
        for (var student : this.studentsList) {
            if (studentNumber.equals(student.getStudentNumber())) {
                studentName = student.getName();
                studentFound = true;
            }
        }
        
        if (studentFound == false) {
            System.out.format("Unknown student number: %s\n", studentNumber);
            return;
        }
        
        System.out.format("%s (%s):\n", studentName, studentNumber);

        if (order.equals("by name")) {
            
            // Ordered by the name of the course
            
            for (var att : this.getAttainments(studentNumber)) {
                if (studentNumber.equals(att.getStudentNumber())) {
                    String courseNum = att.getCourseCode();
                    String courseName = "";
                    for (var course : this.coursesList) {
                        if (courseNum.equals(course.getCode())) {
                            courseName = course.getName();
                        }
                    }
                    int courseGrade = att.getGrade();

                    System.out.format("  %s %s: ", courseNum, courseName);
                    System.out.format("%d\n", courseGrade);
                }
            }
        } else if (order.equals("by code")) {
        
            // Ordered by the course code
            
            for (var att : this.getAttainmentsCode(studentNumber)) {
                if (studentNumber.equals(att.getStudentNumber())) {
                    String courseNum = att.getCourseCode();
                    String courseName = "";
                    for (var course : this.coursesList) {
                        if (courseNum.equals(course.getCode())) {
                            courseName = course.getName();
                        }
                    }
                    int courseGrade = att.getGrade();

                    System.out.format("  %s %s: ", courseNum, courseName);
                    System.out.format("%d\n", courseGrade);
                }
            }
            
        } else {
            
            // Original order
            
            for (var att : this.attainmentsList) {
                if (studentNumber.equals(att.getStudentNumber())) {
                    String courseNum = att.getCourseCode();
                    String courseName = "";
                    for (var course : this.coursesList) {
                        if (courseNum.equals(course.getCode())) {
                            courseName = course.getName();
                        }
                    }
                    int courseGrade = att.getGrade();

                    System.out.format("  %s %s: ", courseNum, courseName);
                    System.out.format("%d\n", courseGrade);
                }
            }
        }
    }
    
    public void printStudentAttainments(String studentNumber) {
        
        //
        
        String studentName = "";
        boolean studentFound = false;
        
        for (var student : this.studentsList) {
            if (studentNumber.equals(student.getStudentNumber())) {
                studentName = student.getName();
                studentFound = true;
            }
        }
        
        if (studentFound == false) {
            System.out.format("Unknown student number: %s\n", studentNumber);
            return;
        }
        
        System.out.format("%s (%s):\n", studentName, studentNumber);

        for (var att : this.attainmentsList) {
            if (studentNumber.equals(att.getStudentNumber())) {
                String courseNum = att.getCourseCode();
                String courseName = "";
                for (var course : this.coursesList) {
                    if (courseNum.equals(course.getCode())) {
                        courseName = course.getName();
                    }
                }
                int courseGrade = att.getGrade();
                
                System.out.format("  %s %s: ", courseNum, courseName);
                System.out.format("%d\n", courseGrade);
            }
        }
    }
}
