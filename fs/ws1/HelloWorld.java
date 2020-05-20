/** 
*22.8. ws1 ex1
*Hello Wotkd application
*Mind that the compiled class has the name of the "main" class in the text
*/

//import java.util.*;

class HelloWorld {
	public static void main(String[] args) {
		System.out.println("Hello World!"); // Display the string

		/* calling a static method from MySecondClass class */
		MySecondClass.foo1();

		MySecondClass objFoo2 = new MySecondClass();

		objFoo2.foo2();

	}
}
