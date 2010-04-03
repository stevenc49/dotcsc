import java.io.IOException;

import javax.servlet.*;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class SampleServlet extends HttpServlet
{
	public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException{
		
		response.getWriter().write("this is an example");
		
	}
	
	public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException{
		
		response.getWriter().write("doPost invoked");
		
	}
}
