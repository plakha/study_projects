package il.co.ilrd.complexnumber;
import static java.lang.System.out;

public final class TestComplexNumber {

	public static void main(String[] args) {
		out.println("Testing..." + "\n");
		
		//equals
		ComplexNumber comp1 = new ComplexNumber(2.0, 7.0);
		ComplexNumber comp2 = new ComplexNumber(2.0, 7.3);
		if (!comp1.equals(comp1)
		 || !comp2.equals(comp2)
		 ||  comp1.equals(comp2)
	 	 ||  comp2.equals(comp1)) {
			out.println("equals() FAIL");			
		}	
		
		//compareTo
		if (0 == comp1.compareTo(comp2) 
		 || 0 == comp2.compareTo(comp1)
		 || 0 != comp1.compareTo(comp1)
		 || 0 != comp2.compareTo(comp2)) {
			out.println("compareTo() FAIL");			
		}
		
		ComplexNumber sum = new ComplexNumber(4.0, 14.3);
		if (!sum.equals(comp1.add(comp2))) {
			out.println("add() FAIL");			
		}
			
	}

}
