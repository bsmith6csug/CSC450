public class Threads {
    private static int counter = 0;
    private static final Object lock = new Object();
    private static boolean firstThreadFinished = false;

    public static void countUp() {
        System.out.println("--- Counting Up ---");
        for (int i = 1; i <= 20; i++) {
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                System.err.println("CountUp thread interrupted: " + e.getMessage());
                return;
            }

            synchronized (lock) {
                counter = i;
                System.out.println("Up Thread: " + counter);
            }
        }

        synchronized (lock) {
            firstThreadFinished = true;
            System.out.println("--- Finished Counting Up ---");
            lock.notifyAll();
        }
    }

    public static void countDown() {
        synchronized (lock) {
            while (!firstThreadFinished) {
                try {
                    lock.wait();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    System.err.println("CountDown thread interrupted while waiting: " + e.getMessage());
                    return;
                }
            }
        }

        System.out.println("--- Counting Down ---");
        synchronized (lock) {
            while (counter >= 0) {
                System.out.println("Down Thread: " + counter);
                counter--;
                
                if (counter >= 0) {
                    try {
                        Thread.sleep(150);
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                        System.err.println("CountDown thread interrupted during countdown: " + e.getMessage());
                        return;
                    }
                }
            }
        }
        System.out.println("--- Up Thread and Down Thread Have Finished! ---");
    }

    public static void main(String[] args) {
        Thread upThread = new Thread(new Runnable() {
            @Override
            public void run() {
                countUp();
            }
        });
        
        Thread downThread = new Thread(new Runnable() {
            @Override
            public void run() {
                countDown();
            }
        });

        upThread.start();
        downThread.start();

        try {
            upThread.join();
            downThread.join();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            System.err.println("Main thread interrupted: " + e.getMessage());
        }
    }
}
