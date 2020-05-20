package il.co.ilrd.chatserver;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

/**
 * 
 * @author Andrei
 * @version 3/11/2019
 *
 */
public class ChatRoom {
	private Server server;
	private Map<Communicator, ClientProfile> users = new HashMap<>();

	public ChatRoom(Server server) {
		this.server = server;
	}

	public void stop() throws Exception {
		server.close();
	}

	public void start() {
		server.registerClientDisconnect((Communicator deserter) -> {
			try {
				onClientDisconnect(deserter);
			} catch (IOException e) {
				e.printStackTrace();
			}
		});
		server.registerNewClient((Communicator newClient) -> {
			try {
				onNewClient(newClient);
			} catch (IOException e) {
				e.printStackTrace();
			}
		});
		server.registerNewMessage((Communicator sender, String message) -> {
			try {
				onNewMessage(sender, message);
			} catch (IOException e) {
				e.printStackTrace();
			}
		});
		try {
			server.start();
		} catch (IOException e) {
			System.err.println("Couldn't start the server");
			e.printStackTrace();
		}
	}

	private void onNewClient(Communicator newClient) throws IOException {
		assert !users.containsKey(newClient);

		users.put(newClient, null);
		newClient.handleMessage("Welcome! What is your name?");
	}

	private void onNewMessage(Communicator sender, String message) throws IOException {

		if (null == users.get(sender)) {
			users.put(sender, new ClientProfile(message));// the first message is the user's name
			message = " has joined";
		}

		for (Communicator receiver : users.keySet()) {

			if (!receiver.equals(sender)) {
				receiver.handleMessage(users.get(sender).getName() + ": " + message);
			} else {
				receiver.handleMessage("You: " + message);
			}
		}
	}

	private void onClientDisconnect(Communicator deserter) throws IOException {
		ClientProfile deserterProfile = users.remove(deserter);
		if (null != deserterProfile) {
			for (Communicator receiver : users.keySet()) {
				receiver.handleMessage(deserterProfile.getName() + " has left");
			}
		}
	}

	private static class ClientProfile {
		private String name;

		public ClientProfile(String name) {
			this.name = name;
		}

		public String getName() {
			return name;
		}
	}// class ClientProfile

	public static void main(String[] args) {
		try {
			new ChatRoom(new TCPServer()).start();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}// class ChatRoom
