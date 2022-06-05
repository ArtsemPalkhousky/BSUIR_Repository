package com.example.lab.services;

import org.apache.log4j.Level;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;

public class ThreadLib {

    static Logger logger = LogManager.getLogger(ThreadLib.class);

    public static Thread createThread() {
        Runnable task = () -> {
            try {
                while (!Thread.currentThread().isInterrupted()) {
                    logger.log(Level.INFO, Thread.currentThread().getName());
                    Thread.currentThread().sleep(2000 * 1);
                }
            } catch (InterruptedException e) {
                logger.log(Level.ERROR, "Interrupted exception acquired");
                e.printStackTrace();
            }
        };
        Thread thread = new Thread(task);
        thread.start();
        return thread;
    }
}

