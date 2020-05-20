package il.co.ilrd.complexnumber;
import static java.lang.Math.pow;
import static java.lang.Math.abs;
import static java.lang.Math.round;
import java.util.regex.*;

/**
 * @version 1/9/2019      
 * @author Andrei
 */

public class ComplexNumber implements Comparable<ComplexNumber> {
	private double real;
	private double imaginary;
	private static final double SQUARE = 2.0;
	private static final double APPROACHES_ZERO = 0.000000000000001;
	//private static final int MAX_HASH_CODE = 
	
	public ComplexNumber() {
		this (0.0, 0.0);
	}
	
	public ComplexNumber(double real, double imaginary) {
		this.real = real;
		this.imaginary = imaginary;
	}
	
	public double getReal() {
		return real;
	}

	public double getImaginary() {
		return imaginary;
	}
	
	public void setReal(double real) {
		this.real = real;
	}
	
	public void setImaginary(double imaginary) {
		this.imaginary = imaginary;	
	}
	
	public void setValue(double real, double imaginary) {
		setReal(real);
		setImaginary(imaginary);
	}
	
	@Override
	public String toString() {
		double roundedReal = APPROACHES_ZERO * round(real / APPROACHES_ZERO);
		double roundedImaginary = APPROACHES_ZERO 
								* round(imaginary / APPROACHES_ZERO);
		
		return roundedReal + "+" + roundedImaginary + "i";
	}
	
	private static boolean approachesZero(double num) {
		return APPROACHES_ZERO > abs(num);
	}
	
	/**
	 * @params other -  an object of class ComplexNumber. 
	 * 		   Passing another type may result in an error.
	 * @return true if equal, false if not equal
	 */
	@Override
	public boolean equals(Object other) {
		
		//assert other instanceof ComplexNumber;//it is developers responsibility to check for types
		
		if (!(other instanceof ComplexNumber)) {
			return false;
		}
		
		return  approachesZero(real - ((ComplexNumber)other).real)
			&& approachesZero(imaginary - ((ComplexNumber)other).imaginary);	
	}
	
	@Override
	public int hashCode() {
		return (((Long)round(real)).hashCode() 
			 + ((Long)round(imaginary)).hashCode()) / 2;		
	}
	
	/**
	 * Can be used as a type-safe alternative to equals().
	 * Other uses may yield undefined results.
	 * 
	 * @param other - an object of class ComplexNumber
	 * @return 0 if equals, 1 otherwise
	 * 
	 */
	@Override
	public int compareTo(ComplexNumber other) {
		return equals(other) ? 0 : 1;
	}
	
	/**
	 * Effective Java p31:
	 *  To protect nonfinal classes from finalizer attacks,
	 * write a final finalize method that does nothing
	 */
	@Override
	public final void finalize() {
		throw new AssertionError();
	}
	
	public ComplexNumber add(ComplexNumber other) {
		real += other.real;
		imaginary += other.imaginary;
		
		return this;
	}
	
	public ComplexNumber subtract(ComplexNumber other) {
		real -= other.real;
		imaginary -= other.imaginary;
		
		return this;
	}
	
	public ComplexNumber multiply(ComplexNumber other) {
		final double thisReal = real;
		final double thisImaginary = imaginary;
		
		real = thisReal * other.real - thisImaginary * other.imaginary;
		imaginary = thisImaginary * other.real + thisReal * other.imaginary;
		
		return this;
	}
	
	public ComplexNumber divide(ComplexNumber other) {
		final double thisReal = real;
		final double thisImaginary = imaginary;

		real = (thisReal * other.real + thisImaginary * other.imaginary) 
			 / (pow(other.real, SQUARE) + pow(other.imaginary, SQUARE));
		imaginary = (thisImaginary * other.real - thisReal * other.imaginary) 
				  / (pow(other.real, SQUARE) + pow(other.imaginary, SQUARE));
		
		return this;
	}
	
	/**
	 * Factory method to produce new ComplexNumber object from String.
	 * It doesn't work right now :(
	 * 
	 * @param complexNumber - String representation of ComplexNumber
	 * @return new ComplexNumber instance
	 */
	public static ComplexNumber parseString(String complexNumberStr) {
		double real = 0.0, imaginary = 0.0;
		final String pattern = "\\d"; //"\\d+\\.\\d+";
		Matcher matcher = Pattern.compile(pattern).matcher(complexNumberStr);
		
		if (matcher.find()) 
			real = Double.parseDouble(matcher.group());
		if (matcher.find())
			imaginary = Double.parseDouble(matcher.group());
		
		return new ComplexNumber(real, imaginary);
	}
}//class ComplexNumber

class Test {

}