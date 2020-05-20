package m9.d19.q3.b;

import java.util.Stack;

public class StackSortAscending {

	public static void main(String[] args) {
		Stack<Integer> stack = new Stack<>();
		
		stack.push(12);
		stack.push(2);
		stack.push(1);
		stack.push(8);
		stack.push(32);
		stack.push(4);
		stack.push(3);
		stack.push(11);

		sort(stack);
		
		while (!stack.isEmpty()) {
			System.out.println(stack.peek());
			stack.pop();
		}
		
	}
	
	public static void sort(Stack<Integer> stack) {
		Stack<Integer> temp = new Stack<>();
		boolean isAscending = false;

		while (!isAscending) {
			isAscending = false;

			while (!stack.isEmpty()) {
				int holder = stack.peek();
				stack.pop();

				if (stack.isEmpty()) {
					temp.push((Integer) holder);
					break;
				}

				if (holder < stack.peek()) {
					temp.push((Integer) holder);
				} else {
					temp.push(stack.peek());
					stack.pop();
					stack.push(holder);
				}
			}
			
			isAscending = true;
			while (!temp.isEmpty()) {
				Integer holder = temp.peek();
				stack.push(holder);
				temp.pop();
				
				if (!temp.isEmpty()) {
					if (holder < temp.peek() ) {
						isAscending = false;
					}
				}
			}
		}

	}
}
