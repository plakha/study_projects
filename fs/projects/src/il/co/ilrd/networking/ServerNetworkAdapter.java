package il.co.ilrd.networking;

import java.io.IOException;

public interface ServerNetworkAdapter extends AutoCloseable {
	public Message receive(int maxBufSize) throws IOException;

	public interface Message {
		public byte[] getData();

		public void reply(byte[] data) throws IOException;
	}
}
