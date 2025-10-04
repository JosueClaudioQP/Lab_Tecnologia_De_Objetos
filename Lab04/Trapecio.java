public class Trapecio{

    public interface Funcion{
        double eval(double x);
    }

    public static class FuncionEjemplo implements Funcion{
        @Override
        public double eval(double x){
            return 2.0*x*x+3.0*x+0.5;
        }
    }

    public static class Integrador{
        private final Funcion f;
        private final double a, b;
        private final long n;

        public Integrador(Funcion f, double a, double b, long n){
            this.f = f;
            this.a = a;
            this.b = b;
            this.n = n;
        }

        public double integrar() {
            double h = (b - a) / (double) n;
            double sum = 0.5 * (f.eval(a) + f.eval(b));
            for (long i = 1; i < n; i++) {
                double x = a + i * h;
                sum += f.eval(x);
            }
            return sum * h;
        }
    }

    public static void main(String[] args) {
        long n = 1000000;
        Funcion f = new FuncionEjemplo();
        double a = 2.0, b = 20.0;

        Integrador integrador = new Integrador(f, a, b, n);
        long t0 = System.currentTimeMillis();
        double result = integrador.integrar();
        long t1 = System.currentTimeMillis();

        System.out.printf("Integral aproximada (Trapecio) = %.10f%n", result);
        System.out.printf("Subintervalos = %d, Tiempo = %d ms%n", n, (t1 - t0));
    }
}