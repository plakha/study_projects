package il.co.ilrd.networking;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketAddress;
import java.net.SocketException;
import java.util.Arrays;

public class UDPServerAdapter implements ServerNetworkAdapter, AutoCloseable {
	private final int port;
	private final DatagramSocket serverSocket;
	// private static final int BUF_SIZE = 1000;

	public UDPServerAdapter(int port) throws SocketException {
		this.port = port;
		serverSocket = new DatagramSocket(this.port);
	}

	@Override
	public Message receive(int maxBufSize) throws IOException {
		DatagramPacket received = new DatagramPacket(new byte[maxBufSize], maxBufSize);
		serverSocket.receive(received);

		return new UDPMessageImpl(received);
	}

	@Override
	public void close() throws Exception {
		serverSocket.close();
	}

	private class UDPMessageImpl implements Message {
		private final byte[] data;
		private final SocketAddress sender;

		public UDPMessageImpl(DatagramPacket received) {
			assert null != received;

			data = Arrays.copyOf(received.getData(), received.getLength());
			sender = received.getSocketAddress();

		}

		@Override
		public byte[] getData() {
			return Arrays.copyOf(data, data.length);
		}

		@Override
		public void reply(byte[] data) throws IOException {
			if (null == data) {
				throw new IllegalArgumentException("Passed null data to Message.reply()");
				// data = new byte[0];//TODO
			}

			serverSocket.send(new DatagramPacket(data, data.length, sender));
		}
	}// class UDPMessageImpl
}// class UDPServerAdapter