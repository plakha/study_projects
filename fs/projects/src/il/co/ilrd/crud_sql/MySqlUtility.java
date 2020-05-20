package il.co.ilrd.crud_sql;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;

public class MySqlUtility implements AutoCloseable {
	private final Connection connection;

	public MySqlUtility(String url, String username, String password) throws SQLException {
		DriverManager.registerDriver(new com.mysql.jdbc.Driver());
		connection = DriverManager.getConnection(url, username, password);// works because there's only one SQL driver
																			// in the shared library
	}

	public ResultSet executeQuery(String query) throws SQLException {

		return connection.createStatement().executeQuery(query);
	}

	public boolean execute(String sql) throws SQLException {
		return connection.createStatement().execute(sql);
	}

	public int executeUpdate(String sql) throws SQLException {
		return connection.createStatement().executeUpdate(sql);
	}

	@Override
	public void close() throws Exception {
		connection.close();
	}
}
