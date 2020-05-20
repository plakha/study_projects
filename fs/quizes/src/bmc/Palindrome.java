package bmc;

public class Palindrome {
	
	/**
	 * 
	 * @param str - the string
	 * @param fromIndex - substring read from
	 * @param toIndex - substring read to, exclusively
	 * @return whether the substring is a palyndrome
	 */
	public static boolean isSubstrPalindrome(String str, int fromIndex, int toIndex) {
		if (0 > fromIndex || 0 > toIndex || null == str || toIndex > str.length()) {
			throw new IllegalArgumentException();
		}
		
		--toIndex;
		while (fromIndex < toIndex) {
			if (!Character.isLetter(str.charAt(fromIndex))) {
				++fromIndex;
				
				continue;
			}
			if (!Character.isLetter(str.charAt(toIndex))) {
				--toIndex;
				
				continue;
			}
			if (Character.toLowerCase(str.charAt(fromIndex)) != Character.toLowerCase(str.charAt(toIndex))) {
				return false;
			}
			
			++fromIndex;
			--toIndex;			
		}
		
		return true;
	}// isSubstrPalindrome()
	
	public static String palindromeFrom(String str) {
		for (int length = str.length(); 0 < length; --length) {
			String palindrome = nSizePalindromeFrom(str, length);
			if (null != palindrome) {
				return palindrome;
			}
		}
		
		return "";
	}
	
	private static String nSizePalindromeFrom(String str, int n) {
		
		for (int i = 0; str.length() > i + n; ++i) {
			if (isSubstrPalindrome(str, i, i + n)) {
				return str.substring(i, i + n); 
			}
		}
		
		return null;
	}
	
	public static void main(String[] args) {
		String str = "I am Dad, Mai!";
		System.out.println(isSubstrPalindrome(str, 4, 10));
		System.out.println(nSizePalindromeFrom(str, 4));
		System.out.println(palindromeFrom(str));
	}
	
	
	
	
	
	
	
	
	
	
}
