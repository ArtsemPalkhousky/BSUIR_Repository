package com.example.lab.controllers;

import org.apache.log4j.Level;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;
import org.springframework.boot.web.servlet.error.ErrorController;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;

import javax.servlet.RequestDispatcher;
import javax.servlet.http.HttpServletRequest;

@Controller
public class MyErrorController implements ErrorController {
    static Logger logger = LogManager.getLogger(MyErrorController.class);
    public MyErrorController(){}

    @GetMapping(value = "/error")
    public String handleError(HttpServletRequest request) {

        Object status = request.getAttribute(RequestDispatcher.ERROR_STATUS_CODE);

        if (status != null) {
            int statusCode = Integer.parseInt(status.toString());

            if(statusCode == HttpStatus.NOT_FOUND.value()) {
                logger.log(Level.ERROR,"404 Error occurred");
                return "error-404";
            }
        }
        return "error";
    }

    @Override
    public String getErrorPath(){
        return  null;
    }
}

