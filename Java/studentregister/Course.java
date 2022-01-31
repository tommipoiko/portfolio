// import here

public class Course {
    
    // Private
    private final String code;
    private final String name;
    private final int credits;
    
    // Public
    public Course(String code, String name, int credits) {
        
        //
        
        this.code = code;
        this.name = name;
        this.credits = credits;
    }
    
    public String getCode() {
        
        //
        
        return this.code;
    }
    
    public String getName() {
        
        //
        
        return this.name;
    }
    
    public int getCredits() {
        
        //
        
        return this.credits;
    }
}
