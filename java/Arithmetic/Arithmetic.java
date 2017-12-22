// Author: Earl Blizzard
// Date:   9/6/2016
// Tabs:   1
public class Arithmetic 
{
//======================================================
	//inc(A) returns an array of bits representing A+1.
//======================================================
	public static byte[] inc(byte[] A)
	{
		byte[] B= new byte[1];
		B[1]=1;
		return sum(A,B);
	}
//=======================================================
	//sum(A,B) returns an array of bits representing A+B.
//=======================================================
	public static byte[] sum(byte[] A,byte[] B)
	{
		int length = 1+max(A.length,B.length);
		byte[] sum=new byte[length];
		byte[] newA= enlarged(A,length);
		byte[] newB= enlarged(B,length);
		boolean carry = false;
		for (int i=0;i<=length-1;i++)
		{
		
			if(carry==true)
			{
				if(newA[i]==1)
				{
					if(newB[i]==1)
					{
						sum[i]=1;
						carry=true;
					}
					else//newB[i]==0
					{
						sum[i]=0;
						carry=true;
					}
				}
				else//newA[i]==0
				{
					if(newB[i]==1)
					{
						sum[i]=0;
						carry=true;
					}
					else//newB[i]==0
					{
						sum[i]=1;
						carry=false;					
					}
				}
			}
			else//carry==false
			{
				if(newA[i]==1)
				{
					if(newB[i]==1)
					{
						sum[i]=0;
						carry=true;
					}
					else//newB[i]==0
					{
						sum[i]=1;
						carry=false;
					}
				}
				else//newA[i]==0
				{
					if(newB[i]==1)
					{
						sum[i]=1;
						carry=false;
					}
					else//newB[i]==0
					{
						sum[i]=0;
						carry=false;
					}
				}
			}
		}
		return optimized(sum);
	}


//===========================================================
	//product(A,B) returns an array of bits representing A*B.
//===========================================================
	public static byte[] product(byte[] A,byte[] B)
	{
		int length=A.length+B.length;
		byte[] product= new byte[length];
		int[] powerCounter= new int[length];
		zeroIntArray(powerCounter);
		for(int array1=0;array1<A.length;array1++)
		{
			if(A[array1]==1)
			{
				for(int array2=0;array2<B.length;array2++)
				{
					powerCounter[array1+array2]+=1;
				}
			}
		}
		for(int stepper=0;stepper<length;stepper++)
		{
			if(powerCounter[stepper]>1)
			{
				powerCounter[stepper+1]=powerCounter[stepper+1]+powerCounter[stepper]/2;
				powerCounter[stepper]=powerCounter[stepper]%2;
			}
		}
		for(int count=0;count<length;count++)
		{
			if(powerCounter[count]==0)
			{
				product[count]=0;
			}
			if(powerCounter[count]==1)
			{
				product[count]=1;
			}
		}
		return optimized(product);
	}
	
	private static void zeroIntArray(int[] A) 
	{
		for(int i=0;i<A.length;i++)
		{
			A[i]=0;
		}
	}
	private static void zeroByteArray(byte[] A)
	{
		for(int i=0;i<A.length;i++)
		{
			A[i]=0;
		}
	}
	
	private static byte[] optimized(byte[] array)
	{
		int length= array.length;
		
		for(int i=length-1;i>=0;i--)
		{
			if(array[i]==1)
			{
				return array;
			}
		array=sudoCopy(array);
		}
		return array;
	}
	
	private static byte[] sudoCopy(byte[] array)
	{
		int length=array.length-1;
		byte[] newArray= new byte[length];
		for(int i=0;i<length;i++)
		{
			newArray[i]=array[i];
		}
		return newArray;
	}
	private static byte[] enlarged(byte[] A, int length) 
	{
		byte[] newA= new byte[length];
		zeroByteArray(newA);
		for(int inc=0;inc<A.length;inc++)
		{
			newA[inc]=A[inc];
		}
		return newA;
	}
	private static int max(int first, int last)
	{
		if(first>last)
		{
			return first;
		}
		else
		{
			return last;
		}
	}
}
