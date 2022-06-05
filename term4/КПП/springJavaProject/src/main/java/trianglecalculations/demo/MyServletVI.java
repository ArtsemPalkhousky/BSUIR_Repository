package trianglecalculations.demo;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class MyServletVI extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws IOException {
        if (request.getRequestURI().equals("/")){
            response.setContentType("text/html");
            response.getWriter().print("<html><head></head><body>" +
                    "<h1>Welcome!</h1><p>This is a very cool page!</p>" +
                    "</body></html>");
        } else if (request.getRequestURI().startsWith("/api/users/")) {
            int prettyFragileUserId = request.getRequestURI().lastIndexOf("/") + 1;

            response.setContentType("application/json");

            response.getWriter().print("{\n" +
                    "  \"id\":" + prettyFragileUserId + ",\n" +
                    "  \"age\": 55,\n" +
                    "  \"name\" : \"John Doe\"\n" +
                    "}");
        } else{
            throw new IllegalStateException("Help, I don't know what to do with this url");
        }
    }
}
