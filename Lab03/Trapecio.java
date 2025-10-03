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
}