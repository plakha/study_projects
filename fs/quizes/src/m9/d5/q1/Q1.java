package m9.d5.q1;

public class Q1 {

	public static void printReverseStr(String str) {
		final int LEN = str.length();
		char[] arrChars = new char[LEN];
		
		for (int i = 0; LEN > i; ++i) {
			arrChars[i] = str.charAt(i);
		}
		
		for (int i = LEN -1; 0 <= i; --i ) {
			System.out.print(arrChars[i]);
		}
	}
	
	public static void main(String[] args) {
		printReverseStr("abcd");
	}

}
