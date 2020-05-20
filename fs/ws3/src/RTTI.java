
	//: c12:Shapes.java
	import java.util.*;

class Shape {
  void draw() {
   
		System.out.println(this + (new Shape()).toString() + ".draw()");
  }
  
  public String toString() {
	  
	  return "Shape";
  }
}

class Circle extends Shape {
 
	public String toString() { 
		return "Circle"; 
		}
}

class Square extends Shape {
  public String toString() { 
	 return "Square"; 
	  }
}

class Triangle extends Shape {
	public String toString() { 
		return "Triangle"; 
		}
}

class Shapes {
  public static void main(String[] args) {
    ArrayList s = new ArrayList();
    
    s.add(new Circle());
    s.add(new Square());
    s.add(new Triangle());
    
    Iterator e = s.iterator();
    
    while(e.hasNext())
      ((Shape)e.next()).draw();
  }
}
