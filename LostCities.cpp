#include <iostream>

void Set_Up_List() {

	int x, y;
	
	for (x = 0; x < 5; x++) {
	
		for (y = 0; y < 12; y++) {
			
			All_Possible[12 * x + y].color = x;
					
			if(y > 8) {
						
				All_Possible[12 * x + y].value = 1;
			}

			else {
			
				All_Possible[12 * x + y].value = y + 2;
			}
		}
	}
}

int main() {
  Set_Up_List();
  return 0;

}
