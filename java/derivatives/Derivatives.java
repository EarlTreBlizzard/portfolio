import java.io.*;

//==========================================================
//                     Class Expression
//==========================================================


abstract class Expression
{
  //-----------------------------------------------------
  // simplify() returns a possibly simplified version of
  // this expression.
  //-----------------------------------------------------

  public abstract Expression simplify();

  //-----------------------------------------------------
  // toString() returns a string that described this
  // expression.  It can be used for printing this
  // expression.
  //-----------------------------------------------------

  public abstract String toString();

  //-----------------------------------------------------
  // rawderiv() returns the derivative of this expression,
  // without simplification.
  //-----------------------------------------------------

  public abstract Expression rawderiv();

  //-----------------------------------------------------
  // deriv() returns the derivative of this expression,
  // with simplification.
  //-----------------------------------------------------

  public Expression deriv()
  {
      return rawderiv().simplify();
  }
}

//==========================================================
//                     Class ConstantExpression
//==========================================================
// A constant expression is the expression equivalent of a
// real number.
//==========================================================

class ConstantExpression extends Expression
{
  private double value;

  public ConstantExpression(double v)
  {
    value = v;
  }

  public Expression rawderiv()
  {
    return new ConstantExpression(0.0);
  }

  public Expression simplify()
  {
    return this;
  }

  public String toString()
  {
    return "" + value;
  }

  public double getvalue()
  {
    return value;
  }
}

//==========================================================
//                     Class VarExpression
//==========================================================
// A VarExpression is the independent variable x.
//==========================================================

class VarExpression extends Expression
{
  public VarExpression()
  {
  }

  public Expression rawderiv()
  {
    return new ConstantExpression(1.0);
  }

  public Expression simplify()
  {
    return this;
  }

  public String toString()
  {
    return "x";
  }

}

//==========================================================
//                    Class SumExpression
//==========================================================
// A SumExpression is an expression that is the sum of two
// other expressions.
//==========================================================

class SumExpression extends Expression
{
  private Expression addend1, addend2;

  public SumExpression(Expression e1, Expression e2)
  {
    addend1 = e1;
    addend2 = e2;
  }

  public Expression rawderiv()
  {
    return new SumExpression(addend1.rawderiv(), addend2.rawderiv());
  }

  public Expression simplify()
  {
    return simplifySum(addend1.simplify(), addend2.simplify());
  }

  public String toString()
  {
    return "(" + addend1.toString() + "+" + addend2.toString() + ")";
  }

  private static Expression simplifySum(Expression e1, Expression e2)
  {
    // 0 + x = x and constant arithmetic

    if(e1 instanceof ConstantExpression) {
      ConstantExpression ce = (ConstantExpression) e1;

      // 0 + x = x

      if(ce.getvalue() == 0.0) {
        return e2;
      }

      // Constant arithmetic 

     if(e2 instanceof ConstantExpression) {
      ConstantExpression ce2 = (ConstantExpression) e2;
      return new ConstantExpression(ce.getvalue() + ce2.getvalue());
      }
    }

    // x + 0 = x

    if(e2 instanceof ConstantExpression) {
      ConstantExpression ce = (ConstantExpression) e2;
      if(ce.getvalue() == 0.0) {
          return e1;
      }
    }

    // Default: do not simplify.

    return new SumExpression(e1, e2);

  }
}
//==========================================================
//                    Class MinExpression
//==========================================================
// A MinExpression is an expression that is the differnce of two
// other expressions.
//==========================================================
class MinExpression extends Expression
{
  private Expression minend1, minend2;

  public MinExpression(Expression e1, Expression e2)
  {
    minend1 = e1;
    minend2 = e2;
  }

  public Expression rawderiv()
  {
    return new MinExpression(minend1.rawderiv(), minend2.rawderiv());
  }

  public Expression simplify()
  {
    return simplifyMin(minend1.simplify(), minend2.simplify());
  }

  public String toString()
  {
    return "(" + minend1.toString() + "-" + minend2.toString() + ")";
  }

  private static Expression simplifyMin(Expression e1, Expression e2)
  {
     
    // x - 0 = x

    if(e2 instanceof ConstantExpression) 
    {
      ConstantExpression ce = (ConstantExpression) e2;
      if(ce.getvalue() == 0.0) 
      {
          return e1;
      }
    }
    // Constant arithmetic 
    if(e2 instanceof ConstantExpression && e1 instanceof ConstantExpression) 
    {
      ConstantExpression ce2 = (ConstantExpression) e2;
      ConstantExpression ce1 = (ConstantExpression) e1;
      return new ConstantExpression(ce1.getvalue() - ce2.getvalue());
    }
    
    // Default: do not simplify.

    return new SumExpression(e1, e2);

  }
}

//==========================================================
//                    Class ProExpression
//==========================================================
// A ProExpression is an expression that is the product of two
// other expressions.
//==========================================================
class ProExpression extends Expression
{
  private Expression proend1, proend2;

  public ProExpression(Expression e1, Expression e2)
  {
    proend1 = e1;
    proend2 = e2;
  }

  public Expression rawderiv()
  {
    return new SumExpression(new ProExpression(proend1.rawderiv(),proend2), new ProExpression(proend2.rawderiv(),proend1));
  }

  public Expression simplify()
  {
    return simplifyPro(proend1.simplify(), proend2.simplify());
  }

  public String toString()
  {
    return "(" + proend1.toString() + "*" + proend2.toString() + ")";
  }

  private static Expression simplifyPro(Expression e1, Expression e2)
  {
     
    
    // 0 * x = 0

    if(e1 instanceof ConstantExpression) 
    {
      ConstantExpression ce1 = (ConstantExpression) e1;
      if(ce1.getvalue() == 0.0) 
      {
        return new ConstantExpression(0.0);
      }

    }

    // x * 0 = 0

    if(e2 instanceof ConstantExpression) 
    {
      ConstantExpression ce2 = (ConstantExpression) e2;
      if(ce2.getvalue() == 0.0) 
      {
        return new ConstantExpression(0.0);
      }

    }

    // 1 * x = x

    if(e1 instanceof ConstantExpression)
    {
      ConstantExpression ce1 = (ConstantExpression) e1;
      if(ce1.getvalue() == 1.0) 
      {
        return e2;
      }
      
    }

    // x * 1 = x

    if(e2 instanceof ConstantExpression)
    {
      ConstantExpression ce2 = (ConstantExpression) e2;
      if(ce2.getvalue() == 1.0) 
      {
        return e1;
      }
      
    }
    
    // Constant arithmetic 

    if(e2 instanceof ConstantExpression && e1 instanceof ConstantExpression) 
    {
      ConstantExpression ce2 = (ConstantExpression) e2;
      ConstantExpression ce1 = (ConstantExpression) e1;
      return new ConstantExpression(ce1.getvalue() * ce2.getvalue());
    }

    // Variable arithmetic

    if(e2 instanceof VarExpression && e1 instanceof VarExpression)
    {
      if(e2 == e1)
      {
         return new PowExpression(e1,new ConstantExpression(2.0));
      }
    }
    
    // Default: do not simplify.

    return new ProExpression(e1, e2);

  }
}

//==========================================================
//                    Class PowExpression
//==========================================================
// A ProExpression is an expression that is the product of two
// other expressions.
//==========================================================
class PowExpression extends Expression
{
  private Expression powend1, powend2;

  public PowExpression(Expression e1, Expression e2)
  {
    powend1 = e1;
    powend2 = e2;
  }

  public Expression rawderiv()
  {
    return new ProExpression(new ProExpression(powend2, new PowExpression(powend1, new MinExpression(powend2, new ConstantExpression(1.0)))),powend1.rawderiv());
  }

  public Expression simplify()
  {
    return simplifyPow(powend1.simplify(), powend2.simplify());
  }

  public String toString()
  {
    return "(" + powend1.toString() + "^" + powend2.toString() + ")";
  }

  private static Expression simplifyPow(Expression e1, Expression e2)
  {
    
    
    // 0 ^ x = 0

  /*  if(e1 instanceof ConstantExpression) 
    {
      ConstantExpression ce1 = (ConstantExpression) e1;
      if(ce1.getvalue() == 0.0) 
      {
        return new ConstantExpression(0.0);
      }

    }
*/
    // x ^ 0 = 0

    if(e2 instanceof ConstantExpression) 
    {
      ConstantExpression ce2 = (ConstantExpression) e2;
      if(ce2.getvalue() == 0.0) 
      {
        return new ConstantExpression(1.0);
      }

    }

    //  x ^ 1 = x
    if(e2 instanceof ConstantExpression)
    {
      ConstantExpression ce2 = (ConstantExpression) e2;
      if(ce2.getvalue() == 1.0) 
      {
        return e1;
      }
    }

    // Constant arithmetic 

    if(e2 instanceof ConstantExpression && e1 instanceof ConstantExpression) 
    {
      ConstantExpression ce1 = (ConstantExpression) e1;
      ConstantExpression ce2 = (ConstantExpression) e2;
      MinExpression min1 = new MinExpression(e2, new ConstantExpression(1.0));
      PowExpression pow1 = new PowExpression(e1, min1.simplify());
      ProExpression prod1 = new ProExpression(ce1 , pow1.simplify());
      return prod1.simplify();
    }

    // Default: do not simplify.

    return new PowExpression(e1, e2);

  }
}