package m9.d19.q2;

public class ListTest {
    public static void main(String[] args) {
    	testOpenLoop();
    }
    
    private static void testOpenLoop() {
    	Node<Integer> tail = new Node<Integer>(1, null);
        Node<Integer> third = new Node<Integer>(2, tail);
        Node<Integer> second = new Node<Integer>(3, third);
        Node<Integer> first = new Node<Integer>(1, second);
        Node<Integer> head = new Node<Integer>(0, first);    
        
        System.out.println("false ? " + List.hasLoop(head));
        
        tail.setNext(first);
        
        System.out.println("true ? " + List.hasLoop(head));
        
        List.openLoop(head);
        
        System.out.println("false ? " + List.hasLoop(head));
    }
}
