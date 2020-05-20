package ws3.ex3;

public abstract class Shape {
	private String color;
	private boolean filled;
	static final protected String DEFAULT_COLOR = "green";
	
	protected Shape() {
		this(DEFAULT_COLOR, true);
	}
	
	protected Shape(String color, boolean filled) {
		this.color = color;
		this.filled = filled;
	}

	protected String getColor() {
		return color;
	}
	
	protected void setColor(String color) {
		this.color = color;
	}
	
	protected boolean isFilled() {
		return filled;
	}
	
	protected void setFilled() {
		
	}
	
}
