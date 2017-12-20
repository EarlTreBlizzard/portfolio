// Earl (Tre) Blizzard


public class ArrayManip
{
	static final int MAX = 100;
	int[MAX] array;
	
	public ArrayManip(int[] array)
	{
		if (array.length>MAX)
		{
			for(int i = 0;i<MAX;i++)
			{
				this.array[i]=array[i];
			}
		}
		else
		{
			this.array = array;
		}
	}

	public void sort()
	{
		int size = array.length;
		

		for(int curr = 0; curr<size;curr++)
		{
			int smallest = curr;
			for(int small = 0; small<size;small++)
			{
				if(array[smallest]>array[small])
				{
					smallest = small;
				}
			}
			int selected = array[curr];
			array[curr] = array[smallest];
			array[smallest] = selected;
		}
	}

	public int[] getArray()
	{
		return array;
	}

	public void setArray(int[] array)
	{
		if (array.length>MAX)
		{
			for(int i = 0;i<MAX;i++)
			{
				this.array[i]=array[i];
			}
		}
		else
		{
			this.array = array;
		}
	}
}