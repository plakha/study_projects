package m9.d19.q1.b;

public class ArrayZerosToEnd {
	public static void zeroesToEnd(int[] arr) {
		final int len = arr.length;

		for (int i = 0; len > i; ++i) {
			if (0 == arr[i]) {
				for (int j = i + 1; len > j; ++j) {
					if (0 != arr[j]) {
						swap(arr, i, j);
						break;
					}
				}
			}
		}
	}

	private static void swap(int[] arr, int i, int j) {
		int holder = arr[i];

		arr[i] = arr[j];
		arr[j] = holder;
	}

	public static void main(String[] args) {
		int[] arr = { 0, 1, 0, 98, 0, 5};

		zeroesToEnd(arr);
		for (int i = 0; arr.length > i; ++i) {
			System.out.print(arr[i] + ",");
		}
		
	}
}
