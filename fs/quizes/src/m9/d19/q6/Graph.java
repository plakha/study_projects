package m9.d19.q6;

import java.util.ArrayList;
import java.util.List;

public class Graph {
	private final List<Node> nodes = new ArrayList<>();

	public Node insert(char type, Node... connected) {
		Node newNode = new Node(type, connected);

		nodes.add(newNode);

		return newNode;
	}

	public List<Node> getAllNodes() {
		List<Node> copy = new ArrayList<>();

		for (Node node : nodes) {
			copy.add(node);
		}

		return copy;
	}

	public static class Node {
		private final char type;
		private final List<Node> connected = new ArrayList<>();
		private final int UID;
		private static int counter;

		{
			++counter;
			UID = counter;
		}

		private Node(char type, Node... connected) {
			this.type = type;

			if (null != connected) {

				for (int i = 0; connected.length > i; ++i) {
					this.connected.add(connected[i]);
					connected[i].connected.add(this);
				}
			}

			System.out.println("Created NOde of type " + this.type + " with UID " + this.UID);
		}

		public List<Node> getConnected() {
			List<Node> copy = new ArrayList<>();

			for (Node node : connected) {
				copy.add(node);
			}

			return copy;
		}

		public int getUID() {
			return UID;
		}

		public char getType() {
			return type;
		}
	}// class Node
}// class Graph
