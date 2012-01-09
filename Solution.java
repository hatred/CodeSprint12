import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.math.BigDecimal;

public class Solution
{
	public static void main(String args[])
	{
		int t;
		String line = null;
		try 
		{
			BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
			line = is.readLine();
			t = Integer.parseInt(line);
			while(t-- > 0)
			{
				line = is.readLine();
				int n=0,m=0;
				String temp[] = line.split(" ");
				n = Integer.parseInt(temp[0]);
				m = Integer.parseInt(temp[1]);
				if(m>=n)
				{
					System.out.println("0.00");
					continue;
				}
		/*		if(m==0)
			//	{
				//	BigDecimal num = new BigDecimal("2.00");
					//BigDecimal one = new BigDecimal("1.00");
					//num = num.pow(n);
					
				//	num = num.subtract(one);
					
					//num = num.multiply(new BigDecimal("2.00"));
					
					num = num.setScale(2, BigDecimal.ROUND_HALF_UP);
					System.out.println(num.toString());
					
					continue;
				}*/
				int moreHeads = n - m;
				int k = moreHeads;
				//double k = moreHeads % 2 ==0 ? moreHeads/2 : moreHeads/2 + 1;
				BigDecimal twoPower = new BigDecimal("0.50");
				twoPower = twoPower.pow((int)(k));
				BigDecimal one = new BigDecimal("1.00");
				
				twoPower = one.subtract(twoPower);
				
				BigDecimal twoPowerTemp = new BigDecimal("0.00");
				
				twoPowerTemp = twoPowerTemp.add(twoPower);
				
				twoPower = twoPower.multiply( new BigDecimal("2.00"));
				
				BigDecimal num = new BigDecimal("2.00");
				
				num = num.pow(n);
				
				num = num.subtract(one);
				
				num = num.multiply(new BigDecimal("2.00"));
				
				num = num.multiply(twoPowerTemp);
				num = num.add(twoPower);
				num = num.setScale(2, BigDecimal.ROUND_HALF_UP);
				System.out.println(num.toString());
				
			}
		
		}catch(Exception e)
		{
			System.out.println(e.toString());
		}
	}
}