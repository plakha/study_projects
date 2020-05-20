package m9.d19.q3.a;

import java.util.Stack;

public class ReverseWords {

	private ReverseWords() {
	}

	public static void main(String[] args) {
		printReverseWords("Hello I love you");
	}

	private static void print(Stack<Character> stack) {
		while (!stack.isEmpty()) {
			System.out.print(stack.peek());
			stack.pop();
		}
	}

	public static void printReverseWords(String str) {
		final int strlen = str.length();
		Stack<Character> stack = new Stack<>();

		for (int i = 0; strlen > i; ++i) {
			final char ch = str.charAt(i);

			if (' ' != ch) {
				stack.push((Character) ch);
			} else {
				print(stack);
				System.out.print(" ");
			}
		}

		print(stack);
	}// printReverseWords()
}
