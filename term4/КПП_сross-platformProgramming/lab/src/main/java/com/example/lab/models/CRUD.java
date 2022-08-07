package com.example.lab.models;


import java.util.ArrayList;
import java.util.List;

public interface CRUD<T> {
    public void create(T object);
    public T read(int index);
    public List<T> readAll();
    public void update(int index, T object);
    public void delete(T object);
    public void deleteAll();
    public ArrayList<T> showAll() ;
}
