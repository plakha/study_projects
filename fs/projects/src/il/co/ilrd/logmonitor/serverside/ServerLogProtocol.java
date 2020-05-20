package il.co.ilrd.logmonitor.serverside;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

import il.co.ilrd.networking.ServerNetworkAdapter;
import il.co.ilrd.networking.ServerNetworkAdapter.Message;
import il.co.ilrd.networking.UDPServerAdapter;

/**
 * 
 * @author Andrei
 *
 */
public class ServerLogProtocol implements ServerProtocol {
	private static final String BOOKEND = "$@";
	private static final int BOOKEND_BYTE_ARR_LEN = BOOKEND.getBytes().length;
	private static final int MAX_LOG_ENTRY_SIZE = 1024;

	
	private final ServerNetworkAdapter adapter;
	private final Set<Long> receivedIDs = new HashSet<>();

	public ServerLogProtocol(String arg1, int arg2, ServerTransmissionProtocol protocol) throws Exception {
		adapter = protocol.newServerNetworkAdapter(arg1, arg2);
	}

	@Override
	public byte[] receiveNextMessage() throws IOException {
		byte[] nextMessage = null;

		while (null == nextMessage) {
			Message rawMessage = adapter.receive(MAX_LOG_ENTRY_SIZE);
			long id = -1;
			if (isValid(rawMessage.getData())) {
				id = getMessageID(rawMessage.getData());
				rawMessage.reply(acknowledgement(id));

				assert 0 <= id;
				if (receivedIDs.add(id)) {
					nextMessage = getMessage(rawMessage.getData());
				}
			}
		}

		return nextMessage;
	}

	@Override
	public void close() throws Exception {
		adapter.close();
	}

	public enum ServerTransmissionProtocol implements ServerNetworkAdapterFactory {
		UDP {
			/**
			 * Only portNumber is relevant for server construction
			 */
			@Override
			public ServerNetworkAdapter newServerNetworkAdapter(String unused, int portNumber) throws IOException {
				return new UDPServerAdapter(portNumber);
			}
		};
	}// enum ClientTransmissionProtocol

	private boolean isValid(byte[] rawMessage) {
		if (rawMessage.length <= 2 * BOOKEND.getBytes().length + Long.BYTES // too short
				// no bookend in the start
				|| !Arrays.equals(BOOKEND.getBytes(), Arrays.copyOfRange(rawMessage, 0, BOOKEND_BYTE_ARR_LEN))
				// no bookend in the end
				|| !Arrays.equals(BOOKEND.getBytes(),
						Arrays.copyOfRange(rawMessage, rawMessage.length - BOOKEND_BYTE_ARR_LEN, rawMessage.length))) {
			return false;
		}

		return true;
	}

	private long getMessageID(byte[] rawMessage) {
		assert isValid(rawMessage);

		return ByteBuffer.wrap(Arrays.copyOfRange(rawMessage, BOOKEND_BYTE_ARR_LEN, BOOKEND_BYTE_ARR_LEN + Long.BYTES))
				.getLong();
	}

	private byte[] getMessage(byte[] rawMessage) {
		assert isValid(rawMessage);

		return Arrays.copyOfRange(rawMessage, BOOKEND_BYTE_ARR_LEN + Long.BYTES,
				rawMessage.length - BOOKEND_BYTE_ARR_LEN);
	}

	private byte[] acknowledgement(long id) {
		ByteBuffer acknowledgementBuf = ByteBuffer.allocate(2 * BOOKEND_BYTE_ARR_LEN + Long.BYTES);
		
		return acknowledgementBuf.put(BOOKEND.getBytes()).putLong(id).put(BOOKEND.getBytes()).array();
	}

	private interface ServerNetworkAdapterFactory {
		public ServerNetworkAdapter newServerNetworkAdapter(String arg1, int arg2) throws Exception;
	}// interface ServerNetworkAdapterFactory
}// class ServerLogProtocol
