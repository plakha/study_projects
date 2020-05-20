package m9.d5.q3;

import org.junit.jupiter.api.Test;

class Q3Test {

	@Test
	void testIsPalindrome() {
		assert Q3.isPalindrome(151);
		assert !Q3.isPalindrome(54565);
		assert Q3.isPalindrome(-8);
	}

}
