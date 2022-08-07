package com.example.lab.models;

public class Triangle {
    private double firstSide;
    private double secondSide;
    private double thirdSide;
    private double resultPerimeter;
    private double resultSquare;


    public double getFirstSide() {
        return firstSide;
    }

    public void setFirstSide(double side){
        this.firstSide = side;
    }

    public double getSecondSide() {
        return secondSide;
    }

    public void setSecondSide(double side) {
        this.secondSide = side;
    }

    public double getThirdSide() {
        return thirdSide;
    }

    public void setThirdSide(double side) {
        this.thirdSide = side;
    }

    public double getResultPerimeter() {
        return resultPerimeter;
    }

    public double getResultSquare() {
        return resultSquare;
    }

    public void setResultPerimeter(double result) {
        this.resultPerimeter = result;
    }

    public void countPerimeter() {
        this.resultPerimeter =  this.firstSide + this.secondSide + this.thirdSide;
    }

    public void countSquare(){
        if ((this.firstSide <= 0) || (this.secondSide <= 0) || (this.thirdSide <= 0)) {
            this.resultSquare = 0;
        }
        else {
            double p = (this.firstSide + this.secondSide + this.thirdSide) / 2;
            this.resultSquare = Math.sqrt(p * (p - this.firstSide) * (p - this.secondSide) * (p - this.thirdSide));
        }
    }
}
