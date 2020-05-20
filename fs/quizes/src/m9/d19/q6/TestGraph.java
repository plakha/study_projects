package m9.d19.q6;

public class TestGraph {
	@SuppressWarnings("unused")
	public static void main(String[] args) {
		Graph graph = new Graph();

		Graph.Node a1 = graph.insert('A', (Graph.Node[]) null);
		Graph.Node b2 = graph.insert('B', a1);
		Graph.Node d3 = graph.insert('D', b2);
		Graph.Node a4 = graph.insert('A', (Graph.Node[]) null);
		Graph.Node c5 = graph.insert('C', b2, a4);
		Graph.Node b6 = graph.insert('b', a4, c5);
		Graph.Node e7 = graph.insert('E', a4);
		Graph.Node c8 = graph.insert('C', b6);

	}
}
