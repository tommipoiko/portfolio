// import here

public class Attainment {
    
    // Private
    private final String courseCode;
    private final String studentNumber;
    private final int grade;
    
    // Public
    public Attainment(String courseCode, String studentNumber, int grade) {
        
        //
        
        this.courseCode = courseCode;
        this.studentNumber = studentNumber;
        this.grade = grade;
    }
    
    public String getCourseCode() {
        
        //
        
        return this.courseCode;
    }
    
    public String getStudentNumber() {
        
        //
        
        return this.studentNumber;
    }
    
    public int getGrade() {
        
        //
        
        return this.grade;
    }
}
