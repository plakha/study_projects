package m9.d19.q7.a;

public class ReverseString {

	public static void main(String[] args) {
		System.out.println(reverse("abcde"));
	}

	public static String reverse(String str) {
		char[] chArr = str.toCharArray();

		reverse(chArr, 0, chArr.length - 1);

		return new String(chArr);
	}

	private static void reverse(char[] arr, int i, int j) {
		if (i >= j) {
			return;
		}

		swap(arr, i, j);
		reverse(arr, i + 1, j - 1);
	}

	private static void swap(char[] arr, int i, int j) {
		arr[i] = (char) ((int) arr[i] ^ arr[j]);
		arr[j] = (char) ((int) arr[i] ^ arr[j]);
		arr[i] = (char) ((int) arr[i] ^ arr[j]);
	}
}
