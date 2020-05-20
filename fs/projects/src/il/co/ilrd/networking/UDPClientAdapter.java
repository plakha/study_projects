package il.co.ilrd.networking;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketTimeoutException;
import java.util.Arrays;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

public class UDPClientAdapter implements ClientNetworkAdapter {
	private final InetAddress serverIPAddr;
	private final int serverPort;
	private final DatagramSocket serverSocket;

	public UDPClientAdapter(String serverIPAddr, int serverPort) throws IOException {
		this.serverPort = serverPort;
		this.serverIPAddr = InetAddress.getByName(serverIPAddr);
		serverSocket = new DatagramSocket();
	}

	@Override
	public void send(byte[] data) throws IOException {
		serverSocket.send(new DatagramPacket(data, data.length, serverIPAddr, serverPort));
	}

	@Override
	public byte[] receive(int maxBytes, long timeout, TimeUnit timeUnit) throws IOException, TimeoutException {
		if (0 > timeout) {
			timeout = 0;
		}
		serverSocket.setSoTimeout((int) timeUnit.toMillis(timeout));

		DatagramPacket receivePacket = new DatagramPacket(new byte[maxBytes], maxBytes);
		try {
			serverSocket.receive(receivePacket);
			return Arrays.copyOf(receivePacket.getData(), receivePacket.getLength());
		} catch (SocketTimeoutException e) {
			throw new TimeoutException("UDPClientAdapter.receive() timed out");
		}
	}

//	@Override
//	public byte[] receive() throws IOException, TimeoutException {
//		return receive(testTimeout(serverIPAddr, DEFAULT_TIMEOUT), TimeUnit.MILLISECONDS);
//	}

	@Override
	public void close() throws Exception {
		serverSocket.close();
	}

	/**
	 * @return a recommended timeout for the receive method in milliseconds
	 * @throw UnknownHostException - Illegal destination
	 */
	@Override
	public long testTimeout(int maxTimeoutMillis) {
		long startTime = System.nanoTime();
		try {
			serverIPAddr.isReachable(maxTimeoutMillis);
		} catch (IOException e) {
			return maxTimeoutMillis;
		}

		return (int) TimeUnit.NANOSECONDS.toMillis(System.nanoTime() - startTime);
	}
}