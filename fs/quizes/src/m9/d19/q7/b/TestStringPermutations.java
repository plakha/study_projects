package m9.d19.q7.b;

import java.util.List;

public class TestStringPermutations {

	public static void main(String[] args) {
		StringPermutations strPerm = new StringPermutations("abc");
		List<String> output = strPerm.getPermutations();
		
		System.out.println(output);
	}

}
