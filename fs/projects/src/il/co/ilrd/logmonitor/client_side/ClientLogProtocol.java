package il.co.ilrd.logmonitor.client_side;

import java.io.IOException;
import java.net.ProtocolException;
import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

import il.co.ilrd.networking.ClientNetworkAdapter;
import il.co.ilrd.networking.UDPClientAdapter;

/**
 * 
 * @author Andrei
 *
 */
public class ClientLogProtocol implements ClientProtocol {
	private static final String BOOKEND = "$@";//TODO byte[] 
	private static final int N_RETRIES = 3;
	private static final int BUF_SIZE = 2 * BOOKEND.getBytes().length + Long.BYTES;
	private static final int maxTimeoutMillis = 100;
	private final ClientNetworkAdapter adapter;
	private long cnt;

	public ClientLogProtocol(String arg1, int arg2, ClientTransmissionProtocol protocol) throws Exception {
		adapter = protocol.newClientNetworkAdapter(arg1, arg2);
	}

	@Override
	public void sendData(byte[] data) throws IOException, ProtocolException {
		byte[] ack = null;
		byte[] expectedAck = ByteBuffer.allocate(2 * BOOKEND.getBytes().length + Long.BYTES).put(BOOKEND.getBytes())
				.putLong(cnt).put(BOOKEND.getBytes()).array();

		for (int i = 0; N_RETRIES > i; ++i) {
			adapter.send(wrap(data));
			try {
				ack = adapter.receive(BUF_SIZE, adapter.testTimeout(maxTimeoutMillis), TimeUnit.MILLISECONDS);
				if (Arrays.equals(ack, expectedAck)) {
					break;
				}
			} catch (TimeoutException e) {
				continue;
			}
		}

		++cnt;

		if (!Arrays.equals(ack, expectedAck)) {
			throw new ProtocolException("ClientLogProtocol.sendData() didn't get acknowledgement from the server");
		}
	}

	@Override
	public void close() throws Exception {
		adapter.close();
	}

	public enum ClientTransmissionProtocol implements ClientNetworkAdapterFactory {
		UDP {
			@Override
			public ClientNetworkAdapter newClientNetworkAdapter(String address, int portNumber) throws IOException {
				return new UDPClientAdapter(address, portNumber);
			}
		};
	}// enum ClientTransmissionProtocol

	private byte[] wrap(byte[] data) {
		ByteBuffer concatinator = ByteBuffer.allocate(2 * BOOKEND.getBytes().length + Long.BYTES + data.length);

		return concatinator.put(BOOKEND.getBytes()).putLong(cnt).put(data).put(BOOKEND.getBytes()).array();
	}

	private interface ClientNetworkAdapterFactory {
		public ClientNetworkAdapter newClientNetworkAdapter(String arg1, int arg2) throws Exception;
	}// interface ClientNetworkAdapterFactory
}
