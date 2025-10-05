import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class TrapecioPool {

    public static double f(double x) {
        return 2.0 * x * x + 3.0 * x + 0.5;
    }

    public static class IntegrarParcial implements Callable<Double> { 
        private final double a, h; 
        private final long inicio, fin; 
        public IntegrarParcial(double a, double h, long inicio, long fin) { 
            this.a = a; this.h = h; this.inicio = inicio; this.fin = fin; 
        } 
        
        @Override 
        public Double call() { 
            double suma = 0.0; 
            for (long i = inicio; i <= fin; i++){ 
                double x = a + i * h; 
                suma += f(x); 
            } 
            return suma; 
        }
    }

    public static double integrarPorTrapecioParalelo(double a, double b, long n, int numHilos) 
        throws InterruptedException, ExecutionException { 
        double h = (b - a) / n; 
        double sumaTotal = 0.5 * (f(a) + f(b)); 
        ExecutorService pool = Executors.newFixedThreadPool(numHilos); 
        List<Future<Double>> resultados = new ArrayList<>(); 
        long pasosPorHilo = n / numHilos; 

        for (int i = 0; i < numHilos; i++) { 
            long inicio = i * pasosPorHilo + 1; 
            long fin = (i == numHilos - 1) ? (n - 1) : ((i + 1) * pasosPorHilo); 
            resultados.add(pool.submit(new IntegrarParcial(a, h, inicio, fin))); 
        } 

        for (Future<Double> futuro : resultados) { 
            sumaTotal += futuro.get(); 
        }
        
        pool.shutdown(); 
        return sumaTotal * h; 
    }

    public static void main(String[] args) {
        
    }
}
