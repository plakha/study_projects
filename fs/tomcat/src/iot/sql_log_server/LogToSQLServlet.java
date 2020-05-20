package iot.sql_log_server;

import java.io.IOException;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import il.co.ilrd.crud.CRUD;
import il.co.ilrd.crud_sql.CRUDSQL;


/**
 * Servlet implementation class LogToSQLServlet
 */
@WebServlet(description = "Log string entries to crud sql", urlPatterns = { "/LogToSQLServlet" })
public class LogToSQLServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private CRUD<String, Integer> outputCRUD;
       
    /**
     * @throws SQLException 
     * @see HttpServlet#HttpServlet()
     */
    public LogToSQLServlet() throws SQLException {
        super();
        outputCRUD = new CRUDSQL("localhost", 3306, "log", "andrei", "password", "logTable");
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		response.getWriter().append("Served at: ").append(request.getContextPath());
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
	//	doGet(request, response);
		
		byte[] buffer = new byte[Integer.parseInt(request.getHeader("Content-Length"))];
		int readBytes = request.getInputStream().read(buffer);
		
		assert buffer.length >= readBytes;
		
		int keyCRUD = outputCRUD.create(new String(buffer));
		int status = (keyCRUD >= 0) ? 200 : 500;
		response.setStatus(status);
		response.getWriter().write(keyCRUD);
	}

}
