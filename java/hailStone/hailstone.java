
//public class hailstone
//when called performs the hailstone sequence
//printing the sequence in the terminal
public class hailstone
{
	public static void main(String[] args)
	{
		// gets item to perform the hailstone sequesnse on
		int start = Integer.parseInt(args[0]);

		// holds the current value
		int item = start;

		// looping variable
		// controls the loop
		boolean loop = true;


		// loop ends once the current item 
		// becomes 1
		while(loop)
		{
			//prints the current item
			System.out.println(""+item);

			// the case for ending the loop
			if(item==1)
			{
				loop = false;
			}
			else//case for continuing the loop
			{
				item = step(item);
			}
		}
	}

	//private static int step(int curr)
	//walks through one step of the 
	//hailstone sequence
	// int curr is the value for the number
	// at the begning for the step
	private static int step(int curr)
	{
		if(curr%2 == 0)//even
		{
			return even(curr);
		}
		else//odd
		{
			return odd(curr);
		}
	}

	// how to procide if the number is even
	private static int even(int num)
	{
		return num/2;
	}

	// how to procide if the number is odd
	private static int odd(int num)
	{
		return num*3+1;
	}
}