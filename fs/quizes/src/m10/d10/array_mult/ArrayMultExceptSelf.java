package m10.d10.array_mult;

/**
 * Get an array of integers and return an array arr in which every element
 * arr[i] is the multiplication of all elements in the original array except
 * arr[i]. Complexity O(n), no division.
 * 
 * @version 10/11/2019
 * @author student
 *
 */
public class ArrayMultExceptSelf {

	public static int[] multExceptSelf(int[] arr) {
		int leftWaveMult = 1;
		int[] leftWaveMultArr = new int[arr.length];

		for (int i = 0; arr.length > i; ++i) {
			leftWaveMultArr[i] = leftWaveMult;
			leftWaveMult *= arr[i];
		}

		int rightWaveMult = 1;
		int[] rightWaveMultArr = new int[arr.length];
		for (int i = arr.length - 1; 0 <= i; --i) {
			rightWaveMultArr[i] = rightWaveMult;
			rightWaveMult *= arr[i];
		}

		for (int i = 0; arr.length > i; ++i) {
			leftWaveMultArr[i] *= rightWaveMultArr[i];
		}

		return leftWaveMultArr;
	}

	public static void main(String[] args) {
		int[] res = multExceptSelf(new int[] { 1, 2, 3 });

		for (int i = 0; res.length > i; ++i) {
			System.out.println(res[i]);
		}
	}
}
