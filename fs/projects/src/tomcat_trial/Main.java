package tomcat_trial;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class Main extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
	//	super.doGet(req, resp);
		
		PrintWriter out = resp.getWriter();
		  out.println("<HTML>");
		  out.println("<HEAD>");
		  out.println("<TITLE>Servlet Testing</TITLE>");
		  out.println("</HEAD>");
		  out.println("<BODY>");
		  out.println("Hello world");
		  out.println("</BODY>");
		  out.println("</HTML>");
	}
}
