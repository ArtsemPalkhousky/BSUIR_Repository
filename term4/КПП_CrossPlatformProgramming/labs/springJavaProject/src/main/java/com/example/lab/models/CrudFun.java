package com.example.lab.models;

import java.util.ArrayList;
import java.util.List;

public class CrudFun<T> implements CRUD<T> {

    private final ArrayList<T> repository = new ArrayList<T>();

    public int size(){
        return repository.size();
    }

    @Override
    public String toString() {
        return repository.toString();
    }

    @Override
    public void create(T object) {
        repository.add(object);
    }

    @Override
    public T read(int index) {
        return repository.get(index);
    }

    @Override
    public List<T> readAll() {
        return repository;
    }

    @Override
    public void update(int index, T object) {

        repository.set(index,object);
    }

    @Override
    public void delete(T object) {

        repository.remove(object);
    }

    @Override
    public void deleteAll() {
        repository.clear();
    }

    @Override
    public ArrayList<T> showAll() {
        return this.repository;  }

    @Override
    public void deleteFirst () {
        if(repository.size() != 0)
        repository.remove(0);
    }

    @Override
    public void deleteLast () {
        if(repository.size() != 0)
        repository.remove(repository.size()-1);
    }
}
