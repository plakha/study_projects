package il.co.ilrd.linkedlist;

import static java.lang.System.out;

/**
 * 
 * @author student
 *
 */
enum Status {
	SUCCESS, FAIL
}

public class TesterLinkedList {
	public static void main(String[] args) {
		
		SinglyLinkedList list1 = new SinglyLinkedList();
		String[] input = {"I", "me", "you", "we"};
		int expectedSize = 0;
		
		if (!list1.isEmpty()) {
			out.println( Status.FAIL);
			
			return ;
		}
		
		if (expectedSize != list1.size()){
			out.println(Status.FAIL);
			
			return ;
		}
		
		for (String element: input) {
			list1.pushFront(element);
			++expectedSize;
		}
		
		if (expectedSize != list1.size()){
			out.println(Status.FAIL);
			
			return ;
		}

		Iterator runner = list1.begin();

		while (runner.hasNext())
		{
			out.println(runner.next());
		};
		
		
		/*for (String element: input) {
			runner = list1.begin();
			
			if (!element.equals(runner.next())) {
				out.println(Status.FAIL);
				}
				return ;
			}
			
		out.println(runner.next());
			list1.popFront();
			--expectedSize;
		}*/

	if(expectedSize!=list1.size())

	{
		out.println(Status.FAIL);

		return;
	}

	out.println(Status.SUCCESS);

}// main()
}// class TesterLinkedList