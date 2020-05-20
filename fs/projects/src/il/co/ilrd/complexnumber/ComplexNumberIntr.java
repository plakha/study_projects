package il.co.ilrd.complexnumber;

public interface ComplexNumberIntr {
	public double getReal();
	public double getImaginary();
	public void setReal(double real);
	public void setImaginary(double imaginary);
	public void setValue(double real, double imaginary);
	public ComplexNumber add(ComplexNumber other);
	public ComplexNumber subtract(ComplexNumber other);
	public ComplexNumber multiply(ComplexNumber other);
	public ComplexNumber divide(ComplexNumber other);
	public static ComplexNumber parseString(String complexNumber) {
		return null;
	}
}