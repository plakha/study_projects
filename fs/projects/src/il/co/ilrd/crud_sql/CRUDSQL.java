package il.co.ilrd.crud_sql;

import java.lang.reflect.UndeclaredThrowableException;
import java.sql.ResultSet;
import java.sql.SQLException;

import il.co.ilrd.crud.CRUD;

/**
 * 
 * @author Andrei
 * @version 19/11/2019
 *
 */
public class CRUDSQL implements CRUD<String, Integer> {
	private final MySqlUtility dbSQLUtility;
	private final String table;
	private int key_cnt;// the highest key already occupied

	public static final int DEFAULT_MYSQL_PORT = 3306;
	public static final String LOCAL_ADDR = "localhost";

	public CRUDSQL(String host, int port, String db, String user, String password, String table) throws SQLException {
		this.table = table;
		dbSQLUtility = new MySqlUtility("jdbc:mysql://" + host + ":" + port + "/" + db, user, password);
		if (!createTableIfNone()) {
			key_cnt = maxKey();
		}
	}

	@Override
	public Integer create(String entry) {
		entry = entry.replaceAll("'", "''");// query Sanitization
		try {
			dbSQLUtility.execute("INSERT INTO " + table + " VALUES (" + ++key_cnt + ", '" + entry + "');");
		} catch (SQLException e) {
			throw new UndeclaredThrowableException(e.fillInStackTrace());
		}

		return key_cnt;
	}

	@Override
	public String read(Integer key) {
		try {
			String entry = null;
			ResultSet resultSet = dbSQLUtility.executeQuery("SELECT entry from " + table + " WHERE id=" + key + ";");
			if (!resultSet.next()) {
				entry = null;
			} else {
				entry = resultSet.getString(1);
			}
			assert !resultSet.next();

			return entry;
		} catch (SQLException e) {
			throw new UndeclaredThrowableException(e.fillInStackTrace());
		}
	}

	@Override
	public void update(Integer key, String data) {
		try {
			dbSQLUtility.execute("UPDATE " + table + " SET entry=" + data + " WHERE id=" + key + ";");
		} catch (SQLException e) {
			throw new UndeclaredThrowableException(e.fillInStackTrace());
		}
	}

	@Override
	public void delete(Integer key) {
		try {
			dbSQLUtility.execute("DELETE FROM " + table + "WHERE id=" + key + ";");
		} catch (SQLException e) {
			throw new UndeclaredThrowableException(e.fillInStackTrace());
		}
	}

	@Override
	public void close() throws Exception {
		dbSQLUtility.close();
	}

	/**
	 * 
	 * @return true if a new table was created
	 * @throws SQLException
	 */
	private boolean createTableIfNone() throws SQLException {
		assert null != table;

		String query = "show tables like" + "'" + table + "'";
		ResultSet resultSet = dbSQLUtility.executeQuery(query);
		final int size = size(resultSet);
		if (0 == size) {
			dbSQLUtility.execute("CREATE TABLE " + table + "(id INT PRIMARY KEY , entry TEXT);");
			return true;
		} else if (1 == size) {
			return false;
		} else {
			assert false;
			throw new SQLException("More than 1 table exists by name ");
		}
	}

	private static int size(ResultSet resultSet) throws SQLException {
		int cnt = 0;
		while (resultSet.next()) {
			++cnt;
		}

		return cnt;
	}

	private int maxKey() throws SQLException {
		ResultSet resultSet = dbSQLUtility.executeQuery("SELECT MAX(id) FROM " + table);
		int ret = 0;

		if (resultSet.next()) {
			ret = resultSet.getInt(1);
		} else {
			assert false;
		}
		assert !resultSet.next();

		return ret;
	}
}
