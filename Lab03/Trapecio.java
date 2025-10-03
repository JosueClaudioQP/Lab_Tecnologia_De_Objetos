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
}