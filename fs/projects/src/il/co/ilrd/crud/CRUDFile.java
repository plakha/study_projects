package il.co.ilrd.crud;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

/**
 * 
 * @author Andrei
 *
 */
public class CRUDFile implements CRUD<String, Integer> {
	private final BufferedWriter writer;

	/**
	 * @param dest - denotes valid file directory
	 * @throws IOException
	 */
	public CRUDFile(String dest) throws IOException {
		File newFile = new File(dest);
		if (!newFile.exists()) {
			newFile.createNewFile();
		}

		writer = new BufferedWriter(new FileWriter(newFile, true));
	}

	@Override
	public void close() throws Exception {
		writer.close();
	}

	@Override
	public Integer create(String entry) {
		try {
			writer.append(entry);
			writer.newLine();
			writer.flush();
		} catch (IOException e) {
		}
		return null;
	}

	@Override
	public String read(Integer key) {
		throw new UnsupportedOperationException();
	}

	@Override
	public void update(Integer key, String data) {
		throw new UnsupportedOperationException();

	}

	@Override
	public void delete(Integer key) {
		throw new UnsupportedOperationException();
	}
}