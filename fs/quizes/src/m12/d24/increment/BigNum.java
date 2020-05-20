package m12.d24.increment;

import java.util.LinkedList;

/**
 * Quiz
 * 
 * @author Andrei
 * @version 24/12/2019
 */
public class BigNum {
	public static void increment(LinkedList<Integer> num) {
		if (num.isEmpty()) {
			num.offerFirst(1);

			return;
		}

		int lsd = num.removeLast();
		assert 0 <= lsd;
		assert 9 >= lsd;

		if (9 == lsd) {
			increment(num);
			lsd = 0;
		} else {
			++lsd;
		}

		num.offerLast(lsd);
	}

	public static void main(String[] args) {
		LinkedList<Integer> num = new LinkedList<>();
		num.offerLast(9);
		num.offerLast(9);

		increment(num);

		for (Integer i : num) {
			System.out.print(i);
		}
	}
}
