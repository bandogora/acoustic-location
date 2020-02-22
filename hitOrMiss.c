
boolean[][] targetLibrary;

void addTarget(int x, int y, boolean[][] targetLibrary){
	//mark the given position as true in the given library
	targetLibrary[x][y] = true;
}


boolean hitOrMiss(int x, int y, boolean[][] targetLibrary, boolean[][] hasBeenHit){
	// x, y is the coordinates of the position being hit
	// it return true if the position is a target and has not been hit before
	return targetLibrary[x][y] && hasBeenHit[x][y];
}