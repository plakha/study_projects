package m9.d19.q7.b;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class StrPerm {
	
	public static void main(String[] args) {
		System.out.println(strPerm("abc"));
	}
	
	public static List<String> strPerm(String input) {

		class Permutations {
			List<String> permutations = new ArrayList<>();

			public Permutations(String input) {
				char[] inputArr = input.toCharArray();

				setPermutations(inputArr, 0);
			}

			private char[] swapped(char[] input, int i, int j) {
				char[] ret = Arrays.copyOf(input, input.length);
				char holder = input[i];
				
				ret[i] = ret[j];
				ret[j] = holder;
				
				return ret;

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

			public List<String> getPermutations() {
				return permutations;
			}

		}

		Permutations perm = new Permutations(input);

		return perm.getPermutations();
	}
}
