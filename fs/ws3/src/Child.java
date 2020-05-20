import static java.lang.System.*;

public class Child extends Human{

	/*
	 * public void walk() {
	 * 
	 * out.println("Child walks"); }
	 */
	
	public Child(int a) {
		
		super(0);
		out.println("Child constructor");
	}
	
	public static void whoAm() {
		out.println("I am child");
	}
}
