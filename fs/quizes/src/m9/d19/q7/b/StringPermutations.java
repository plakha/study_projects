package m9.d19.q7.b;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class StringPermutations {
	List<String> permutations = new ArrayList<>();

	public StringPermutations(String input) {
		char[] inputArr = input.toCharArray();

		setPermutations(inputArr, 0);
	}

	private void setPermutations(char[] input, int n) {
		final int len = input.length;

		if (len == n) {			
			permutations.add(new String(input));
			return;
		}

		for (int i = n; len > i; ++i) {
			setPermutations(swapped(input, i, n), n + 1);
		}

	}

	private char[] swapped(char[] input, int index1, int index2) {
//		input[index1] = (char) ((int) input[index1] ^ (int) input[index2]);
//		input[index2] = (char) ((int) input[index1] ^ (int) input[index2]);
//		input[index1] = (char) ((int) input[index1] ^ (int) input[index2]);
//		
		char[] ret = Arrays.copyOf(input, input.length);
		char holder = input[index1];
		
		ret[index1] = ret[index2];
		ret[index2] = holder;
		
		return ret;

	}

	public List<String> getPermutations() {
		return permutations;
	}
}
