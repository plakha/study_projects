package ws3_ex4;
import static java.lang.System.out;
import il.co.ilrd.linkedlist;

public class DumpClassInfo {

	private static void printArr(Object[] arr) {
		
		for (Object element: arr) {
			out.println(element);
		}
	}
	private static void dumpClassInfo(Class className) {
		
		
		  out.println("\n" + "Class info"); 
		  printArr(className.getClasses());
		 
		
		  out.println("\n" + "Methods info"); 
		  printArr(className.getDeclaredMethods());
		  
		  out.println("\n" + "Fields info"); 
		  printArr(className.getDeclaredFields());
		 
	}

	public static void main(String[] args) {
		
		try {			
			Class className = Class.forName("il.co.ilrd.linkedlist.SinglyLinkedList");

			dumpClassInfo(className);
		}
		catch (ClassNotFoundException e) {
			out.println(e);
		}
		
		
	}

}
