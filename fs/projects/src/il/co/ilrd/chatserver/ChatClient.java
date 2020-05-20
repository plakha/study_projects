package il.co.ilrd.chatserver;

import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.UnknownHostException;
import java.net.ProtocolException;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.util.Scanner;

/**
 * 
 * @author Andrei
 * @version 3/11/2019
 *
 */
public class ChatClient implements AutoCloseable {
	private SocketChannel socketChannel;
	private InetAddress serverAddr;
	private int port;
	private Scanner scanner;
	public static final String EXIT_STRING = "DISCONNECT";
	volatile private boolean shouldStop;

	public ChatClient(InetAddress serverAddr, int port) {
		this.serverAddr = serverAddr;
		this.port = port;
	}

	private Thread fromUser = new Thread(() -> {
		scanner = new Scanner(System.in);

		while (!shouldStop) {
			String userInput = scanner.nextLine().replace(System.lineSeparator(), "");
			if (userInput.equals(EXIT_STRING)) {
				shouldStop = true;

				break;
			}
			String userMessage = ChatProtocol.encode(userInput);

			try {
				socketChannel.write(ByteBuffer.wrap(userMessage.getBytes()));
			} catch (IOException e) {
				e.printStackTrace();
				System.err.println("Couldn't send message to server...");
			}

		}
	});

	private Thread fromServer = new Thread(() -> {
		ByteBuffer buf = ByteBuffer.allocate(TCPServer.DEFAULT_SIZE_OF_BUFFER);
		while (!shouldStop) {
			try {
				if (!socketChannel.isConnected()) {
					shouldStop = true;
					System.out.println("Server disconnect");
					break;
				}
				int nBytesRead = socketChannel.read(buf);// TODO SOCKET TIME OUT so it can die
				String message = ChatProtocol.decode(new String(buf.array(), 0, nBytesRead));
				System.out.println(message);
				buf.clear();
			} catch (ProtocolException e) {
				e.printStackTrace();
				System.err.println("Bad communication received, ChatProtocol error...");

			} catch (IOException e) {
				e.printStackTrace();
				System.err.println("Couldn't get message from server...");
			}
		}
	});

	public void start() {
		try {
			SocketChannel socketChannel = SocketChannel.open(new InetSocketAddress(serverAddr, port));
			socketChannel.configureBlocking(true);
			this.socketChannel = socketChannel;

			fromUser.start();
			fromServer.start();

			fromServer.join();
			fromUser.join();

		} catch (IOException e) {
			e.printStackTrace();
			System.err.println("Couldn't connect to server. Exiting...");
			System.exit(1);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		try (ChatClient chatClient = new ChatClient(InetAddress.getLocalHost(), TCPServer.DEFAULT_PORT);) {
			chatClient.start();
		} catch (UnknownHostException e) {
			e.printStackTrace();
			System.err.println("Couldn't find server address . Exiting...");
			System.exit(1);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			System.err.println("Couldn't close ...");
			System.err.println("Couldn't safely close client. Exiting...");

		}
	}

	@Override
	public void close() throws Exception {
		socketChannel.close();
		scanner.close();
	}
}
