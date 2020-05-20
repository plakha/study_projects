package m9.d19.q1.a;

public class ArrayNShift {

	public static void main(String[] args) {
		char[] arr = "abcde".toCharArray();

		// reverse(arr, 0, arr.length);
		shift(arr, 2);

//		for (int i = 0; arr.length > i; ++i) {
//			System.out.print(arr[i]);
//		}
	}

	private static void swap(char[] arr, int i, int j) {
		char holder = arr[i];

		arr[i] = arr[j];
		arr[j] = holder;
	}

	private static void reverse(char[] arr, int from, int to) { // exclusive to
		for (int i = from, j = to - 1; i < j; ++i, --j) {
			swap(arr, i, j);
		}
	}

	public static void shift(char[] arr, int shiftBy) {
		reverse(arr, 0, arr.length);
		reverse(arr, 0, shiftBy);		
		reverse(arr, shiftBy, arr.length);
	}
}
