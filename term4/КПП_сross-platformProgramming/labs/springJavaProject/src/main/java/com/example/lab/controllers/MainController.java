package com.example.lab.controllers;


import com.example.lab.models.CrudFun;

import com.example.lab.models.Triangle;
import com.example.lab.services.*;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;


    @Controller
    public  class MainController {

        private final CrudFun<Triangle> objects = new CrudFun<>();

        private Thread thread = ThreadLib.createThread();

        @GetMapping
        public String greeting(org.springframework.ui.Model model) {
            model.addAttribute("object", new Triangle());
            return "main";
        }

        @PostMapping
        public String changeSubmit(Triangle obj, org.springframework.ui.Model model, @RequestParam String action){

            if(action.equals("submit")) {
                Service.calculate(obj);
                objects.create(obj);
            }

            if(action.equals("reset")){
                objects.deleteAll();
                thread.interrupt();
                thread = ThreadLib.createThread();
            }

            model.addAttribute("object", obj);
            model.addAttribute("objects", objects.showAll());
            System.out.println("Площадь треугольника:  " + obj.getResultSquare());
            System.out.println("Периметр треугольника:  " + obj.getResultPerimeter() + "\n");
            return "main";
        }

    }

