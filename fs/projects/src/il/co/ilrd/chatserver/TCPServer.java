package il.co.ilrd.chatserver;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.ProtocolException;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.function.BiConsumer;
import java.util.function.Consumer;

/**
 * 
 * @author Andrei
 * @version 3/11/2019
 *
 */
public class TCPServer implements Server {
	public static final int DEFAULT_PORT = 4444;
	public static final int DEFAULT_SIZE_OF_BUFFER = 256;

	private final int port;
	private final int sizeBuf;

	private Selector selector;
	private ServerSocketChannel serverSocket;
	private Consumer<Communicator> onNewClient;
	private BiConsumer<Communicator, String> onNewMessage;
	private Consumer<Communicator> onClientDisconnect;

	public TCPServer() {
		this(DEFAULT_PORT, DEFAULT_SIZE_OF_BUFFER);
	}

	public TCPServer(int port, int sizeBuf) {
		this.port = port;
		this.sizeBuf = sizeBuf;

	}

	@Override
	public void start() throws IOException {
		selector = Selector.open();
		serverSocket = ServerSocketChannel.open();
		System.out.println("selector open");
		serverSocket.configureBlocking(false);
		serverSocket.bind(new InetSocketAddress(port));
		serverSocket.register(selector, SelectionKey.OP_ACCEPT);
		ByteBuffer buf = ByteBuffer.allocate(sizeBuf);

		while (true) {
			selector.select();
			// It is preferable to use while(iter.hasNext()), so the r3emove is in O(1)
			for (SelectionKey key : selector.selectedKeys()) {
				if (key.isAcceptable()) {
					acceptKey(key);
				} else if (key.isReadable()) {
					read(key, buf);
				} else if (!key.isValid()) {
					System.out.println("is invalid");
					onClientDisconnect.accept((Communicator) key.attachment());
				}
				selector.selectedKeys().remove(key);
			}
		}
	}

	private void read(SelectionKey key, ByteBuffer buf) throws IOException {
		SocketChannel clientChannel = (SocketChannel) key.channel();
		int read = clientChannel.read(buf);

		assert key.attachment() instanceof Communicator;
		if (/* 0 == read || */ -1 == read) {
			// onClientDisconnect.accept((Communicator) key.attachment());
			key.cancel();
		} else {
			try {
				onNewMessage.accept((Communicator) key.attachment(),
						ChatProtocol.decode(new String(buf.array(), 0, read)));
			} catch (ProtocolException e) {
				System.err.println("Bad communication received, ChatProtocol error...");
			}
		}
		buf.clear();
	}

	private void acceptKey(SelectionKey key) throws IOException {
		ServerSocketChannel keysServerChannel = (ServerSocketChannel) key.channel();
		SocketChannel clientSocket = keysServerChannel.accept();
		clientSocket.configureBlocking(false);
		Communicator newClient = null;
		clientSocket.register(selector, SelectionKey.OP_READ).attach(newClient = new CommunicatorTCPImpl(clientSocket));
		onNewClient.accept(newClient);
	}

	@Override
	public void close() throws IOException {
		serverSocket.close();
		selector.close();
	}

	@Override
	public void registerNewClient(Consumer<Communicator> onNewClient) {
		this.onNewClient = onNewClient;
	}

	@Override
	public void registerNewMessage(BiConsumer<Communicator, String> onNewMessage) {
		this.onNewMessage = onNewMessage;
	}

	@Override
	public void registerClientDisconnect(Consumer<Communicator> onClientDisconnect) {
		this.onClientDisconnect = onClientDisconnect;
	}

	private static class CommunicatorTCPImpl implements Communicator {
		SocketChannel clientSocket;

		public CommunicatorTCPImpl(SocketChannel clientSocket) {
			this.clientSocket = clientSocket;
		}

		@Override
		public void handleMessage(String message) throws IOException {
			clientSocket.write(ByteBuffer.wrap(ChatProtocol.encode(message).getBytes()));
		}

		@Override
		public boolean equals(Object other) {
			if (!(other instanceof CommunicatorTCPImpl)) {
				return false;
			}

			return this == other;
		}
	}// class CommunicationObjectImpl
}// class TCPServer