package m9.d19.q2;

public class Node<T> {
    private Node<T> next;
    private T data;
    
    public Node(T data, Node<T> next){
	this.data = data;
	this.next = next;
    }
    
    public T getData() {
	return data;
    }
    
    public Node<T> next() {
	return next;
    }
    
    public boolean hasNext() {
	return null != next;
    }
    
    public void setNext(Node<T> next) {
	this.next = next;
    }
}
