public class TestDeriv
{
    public static void main(String args[])
    {
	Expression a = new ConstantExpression(4.0);
	Expression x = new VarExpression();
	Expression s = new MinExpression(x, x);
        Expression t = new PowExpression(a, a);
        Expression d1 = s.deriv();
        Expression d2 = t.deriv();
	System.out.println("deriv(" + s + ") = " + d1);
        System.out.println("deriv(" + t + ") = " + d2);

    }
}