package m9.d5.q3;

public class Q3 {

	public static boolean isPalindrome(int n) {
		if (reverseNum(n) == n) {
			return true;
		} else {
			return false;
		}
	}

	private static int reverseNum(int n) {
		int retval = 0;

		while (0 != n) {
			retval *= 10;
			retval += n % 10;
			n /= 10;
		}

		return retval;
	}
}
