// Author: Earl Blizzard
// Date:   9/6/2016
// Tabs:   1
public class ArithmeticTest 
{

	public static void main(String[] args)
	{
		byte[] array1= new byte[]{};
		byte[] array2= new byte[]{1,1,1};
		for(int i=0;i<array1.length;i++)
		{
			System.out.print(array1[i]+" ");
		}
		System.out.println("");
		for(int i=0;i<array2.length;i++)
		{
			System.out.print(array2[i]+" ");
		}
		System.out.println("");
		byte[] multiple=product(array1,array2);
		for(int i=0;i<multiple.length;i++)
		{
			System.out.print(multiple[i]+" ");
		}
		System.out.println("");
		byte[] total=sum(array1,array2);
		for(int i=0;i<total.length;i++)
		{
			System.out.print(total[i]+" ");
		}
	}

}
